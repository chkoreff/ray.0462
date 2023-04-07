// raylib [core] example - 3d camera first person
// Copyright (c) 2015-2022 Ramon Santamaria (@raysan5)
//
// References:
// https://www.raylib.com/cheatsheet/cheatsheet.html
// https://www.raylib.com/cheatsheet/raymath_cheatsheet.html

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <pthread.h>

#define MAX_COLUMNS 40
#define COL_INTERVAL 20

static const int screenWidth = 800;
static const int screenHeight = 450;
static Camera camera = { 0 };
static const Vector3 startPosition = (Vector3){ 0.0, 4.0, 0.0 };

static float heights[MAX_COLUMNS] = { 0 };
static Vector3 positions[MAX_COLUMNS] = { 0 };
static Color colors[MAX_COLUMNS] = { 0 };
static int colsOffset = 0;
static const float renderInterval = 16.0;
static float renderBound = renderInterval;
static float manuY = 0.0;
static float manuZ = 0.0;
static Vector3 manuBoundFactor = (Vector3){ 0.0f, 0.0f, 0.0f };

/*
LATER Generate these colors from the color transformation functions:

  cconvLabToRgb

  cconvXyzToRgb
  cconvLabToXyz

Also define this, not used yet:
  cconvRgbToXyz

LATER:  A Fexl scripting interface could look something like this:

	\color=(create_random_color)
	put_color color

The C code would call that 40 times, incrementing the position and poking the
color values into the colors array.  It's not necessary to do that in Fexl, but
it might be a good example of embedding a tiny scripting language into the C
code.
*/

static void init_colors(void)
	{
	colors[0] = (Color){27,35,22,255};
	colors[1] = (Color){19,11,6,255};
	colors[2] = (Color){30,43,44,255};
	colors[3] = (Color){30,28,39,255};
	colors[4] = (Color){31,30,26,255};
	colors[5] = (Color){37,41,34,255};
	colors[6] = (Color){46,47,42,255};
	colors[7] = (Color){34,20,21,255};
	colors[8] = (Color){44,31,24,255};
	colors[9] = (Color){43,45,35,255};
	colors[10] = (Color){45,30,28,255};
	colors[11] = (Color){52,59,49,255};
	colors[12] = (Color){43,36,41,255};
	colors[13] = (Color){68,60,62,255};
	colors[14] = (Color){70,59,62,255};
	colors[15] = (Color){62,64,62,255};
	colors[16] = (Color){52,40,36,255};
	colors[17] = (Color){59,65,71,255};
	colors[18] = (Color){76,72,59,255};
	colors[19] = (Color){54,63,69,255};
	colors[20] = (Color){67,79,85,255};
	colors[21] = (Color){79,66,57,255};
	colors[22] = (Color){69,81,65,255};
	colors[23] = (Color){67,70,62,255};
	colors[24] = (Color){96,87,82,255};
	colors[25] = (Color){61,80,81,255};
	colors[26] = (Color){95,105,109,255};
	colors[27] = (Color){54,59,68,255};
	colors[28] = (Color){95,93,102,255};
	colors[29] = (Color){92,77,72,255};
	colors[30] = (Color){88,79,89,255};
	colors[31] = (Color){65,69,80,255};
	colors[32] = (Color){80,70,70,255};
	colors[33] = (Color){64,81,78,255};
	colors[34] = (Color){122,111,124,255};
	colors[35] = (Color){118,126,109,255};
	colors[36] = (Color){83,82,96,255};
	colors[37] = (Color){102,108,109,255};
	colors[38] = (Color){92,95,95,255};
	colors[39] = (Color){118,115,130,255};
	}

// Define the camera to look into our 3d world (position, target, up vector)
static void init_camera(void)
	{
	camera.position = startPosition;
	camera.target = (Vector3){ 4.0, 4.0, 0.0 };
	camera.up = (Vector3){ 0.0, 1.0, 0.0 };
	camera.fovy = 60.0;
	camera.projection = CAMERA_PERSPECTIVE;
	}

// Generates some random column attributes.
static void set_columns(void)
	{
	for (int i = colsOffset; i < (colsOffset + COL_INTERVAL); i++)
		{
		heights[i] = (float)GetRandomValue(1, 4);

		positions[i] =
			(Vector3)
			{
			((renderBound - renderInterval) + (float)GetRandomValue(0, 32)),
			heights[i]/2.0f,
			(float)GetRandomValue(-15, 15)
			};
		}
	}

static void draw_instructions(void)
	{
	DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5));
	DrawRectangleLines( 10, 10, 220, 70, BLUE);

	DrawText("First person camera default controls:", 20, 20, 10, BLACK);
	DrawText("- Move with keys: W, A, S, D", 40, 40, 10, DARKGRAY);
	DrawText("- Mouse move to look around", 40, 60, 10, DARKGRAY);
	}

// UpdateCamera(&camera); // LATER I guess we don't need this anywhere.

static float clip_delta(float delta, float offset)
	{
	return
		(delta > 0) ? (fmax(0.0, (1.0 - offset))) :
		(delta < 0) ? (fmax(0.0, (1.0 + offset))) :
			1.0;
	}

static void adjust_camera(void)
	{
	manuY =
		((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_KP_2)))
			? 1.0f :
		((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_KP_8)))
			? -1.0f :
			0.0f;

	manuZ =
		((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_KP_4)))
			? -1.0f :
		((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_KP_6)))
			? 1.0f :
			0.0f;

	{
	float offset = (0.4 * (camera.position.y - 4.0));
	manuBoundFactor.y = clip_delta(manuY, offset);
	}

	{
	float offset = (0.1 * camera.position.z);
	manuBoundFactor.z = clip_delta(manuZ, offset);
	}

	{
	Vector3 offset =
		Vector3Multiply(
			manuBoundFactor,
			Vector3Multiply(
				(Vector3){ 0.0, 0.1, 0.1 },
				(Vector3){ 0.0, manuY, manuZ }));

	camera.position = Vector3Add(camera.position, offset);
	camera.target = Vector3Add(camera.target, offset);
	}

	{
	Vector3 offset  = (Vector3){ 0.06, 0.0, 0.0 };

	camera.position = Vector3Add(camera.position, offset);
	camera.target = Vector3Add(camera.target, offset);
	}
	}

static void draw_floor(void)
	{
	const float bound = (renderBound - (0.4 * renderInterval));
	Vector2 size = (Vector2){ renderInterval, 2 * renderInterval };

	DrawPlane(
		(Vector3){ bound, 0.0, 0.0 },
		size,
		(colsOffset == 0) ? DARKGRAY : LIGHTGRAY
		);

	DrawPlane(
		(Vector3){ (renderInterval + bound), 0.0, 0.0 },
		size,
		(colsOffset == 0) ? LIGHTGRAY : DARKGRAY
		);
	}

static void draw_columns(void)
	{
	for (int i = 0; i < MAX_COLUMNS; i++)
		{
		DrawCube(positions[i], 2.0, heights[i], 2.0, colors[i]);
		DrawCubeWires(positions[i], 2.0, heights[i], 2.0, MAROON);
		}
	}

static void draw_scene(void)
	{
	BeginMode3D(camera);

	draw_floor();
	draw_columns();

	EndMode3D();
	}

static void draw_frame(void)
	{
	BeginDrawing();
	adjust_camera();

	ClearBackground(RAYWHITE);

	if (abs(camera.position.x) > renderBound)
		{
		renderBound += renderInterval;
		set_columns();

		colsOffset = (colsOffset + COL_INTERVAL) % MAX_COLUMNS;
		}

	draw_scene();
	draw_instructions();

	EndDrawing();
	}

static void ray_win_display(void)
	{
	init_colors();

	InitWindow(screenWidth, screenHeight,
	"raylib [core] example - 3d camera first person"
	);

	init_camera();
	set_columns();

	colsOffset = (colsOffset + COL_INTERVAL) % MAX_COLUMNS;
	SetCameraMode(camera, CAMERA_FIRST_PERSON);
	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
		draw_frame();

	CloseWindow(); // Close window and OpenGL context
	}

int main(void)
	{
	ray_win_display();
	return 0;
	}
