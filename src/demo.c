// raylib [core] example - 3d camera first person
// Adapted from: Copyright (c) 2015-2022 Ramon Santamaria (@raysan5)
//
// References:
// https://www.raylib.com/cheatsheet/cheatsheet.html
// https://www.raylib.com/cheatsheet/raymath_cheatsheet.html

#include <color.h>
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <pthread.h>
#include <time.h>

#define MAX_COLUMNS 40
#define COL_INTERVAL 20

static const int screenWidth = 800;
static const int screenHeight = 450;
static Camera camera = { 0 };
static const Vector3 startPosition = { 0.0, 4.0, 0.0 };

static float heights[MAX_COLUMNS] = { 0 };
static Vector3 positions[MAX_COLUMNS] = { 0 };
static Color colors[MAX_COLUMNS] = { 0 };
static int colsOffset = 0;
static const float renderInterval = 16.0;
static float renderBound = renderInterval;
static float manuY = 0.0;
static float manuZ = 0.0;
static Vector3 manuBoundFactor = { 0.0f, 0.0f, 0.0f };

// Return a weak random double in range (0 <= r <= 1).
double get_rand(void)
	{
	return (double)rand() / (double)RAND_MAX;
	}

// Return a weak random bit.
static int random_bit(void)
	{
	return rand() % 2;
	}

static void init_colors(void)
	{
	int color_dir1, color_dir2;
	double a=0, ad=0, b=0, bd=0, c=0, cd=0;

	for (int i = 0; i < MAX_COLUMNS; i++)
		{
		if (0 == i % 10)
			{
			color_dir1 = (random_bit() ? -1 : 1);
			color_dir2 = (random_bit() ? -1 : 1);

			a = 50 * get_rand();
			ad = 5 * get_rand();

			b = color_dir1 * 40 * get_rand();
			bd = color_dir1 * 8 * get_rand();

			c = color_dir2 * 40 * get_rand();
			cd = color_dir2 * 8 * get_rand();
			}
		else
			{
			a += ad;
			b += bd;
			c += cd;
			}

		{
		triple color = color_lab_rgb((triple){a, b, c});
		colors[i] = (Color){ color.x, color.y, color.z, 255 };
		}
		}
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
	{
	time_t t = time(0);
	srand(t);
	}

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
