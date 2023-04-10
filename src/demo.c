// raylib [core] example - 3d camera first person
// Adapted from: Copyright (c) 2015-2022 Ramon Santamaria (@raysan5)
//
// References:
// https://www.raylib.com/cheatsheet/cheatsheet.html
// https://www.raylib.com/cheatsheet/raymath_cheatsheet.html

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

typedef struct triple
	{
	double x;
	double y;
	double z;
	} triple;

// LATER 20230409 Create test suites for color conversions.

static double scale_4117(double v)
	{
	v /= 255.0;
	if (v > 0.04045)
		v = pow((v+0.055)/1.055, 2.4);
	else
		v /= 12.92;

	return 100 * v;
	}

triple color_rgb_xyz(triple color)
	{
	double rx = color.x;
	double gx = color.y;
	double bx = color.z;

	double vr = scale_4117(rx);
	double vg = scale_4117(gx);
	double vb = scale_4117(bx);

	return (triple){ vr, vg, vb };
	}

static double scale_7761(double v)
	{
	double v3 = pow(v,3);
	if (v3 > 0.00856)
		return v3;
	else
		// LATER check this case, we never hit it.
		return (v - 16.0/116.0) / 7.787;
	}

triple color_lab_xyz(triple color)
	{
	double lx = color.x;
	double ax = color.y;
	double bx = color.z;

	double vy = (lx+16) / 116;
	double vx = vy + ax/500;
	double vz = vy - bx/200;

	vx = 94.811 * scale_7761(vx);
	vy = 100 * scale_7761(vy);
	vz = 107.304 * scale_7761(vz);

	return (triple){vx,vy,vz};
	}

static double scale_0813(double v)
	{
	if (v > 0.0031308)
		v = 1.055 * (pow(v,(1.0/2.4)) - 0.055);
	else
		v *= 12.92;

	return 255 * v;
	}

triple color_xyz_rgb(triple color)
	{
	double xx = color.x;
	double yx = color.y;
	double zx = color.z;

	double vx = xx / 100;
	double vy = yx / 100;
	double vz = zx / 100;

	double vr = ceil(scale_0813(
		(vx  * 3.2406) + (vy * -1.5372) + (vz * -0.4986)
		));

	double vg = ceil(scale_0813(
		(vx * -0.9689) + (vy * 1.8758) + (vz * 0.0415)
		));

	double vb= ceil(scale_0813(
		(vx * 0.0557) + (vy * -0.2040) + (vz * 1.0570)
		));

	return (triple){ vr, vg, vb };
	}

triple color_lab_rgb(triple color)
	{
	return color_xyz_rgb(color_lab_xyz(color));
	}

static void init_colors(void)
	{
	int color_dir1 = (random_bit() ? -1 : 1);
	int color_dir2 = (random_bit() ? -1 : 1);

	double a = 15 * get_rand();
	double ad = 2 * get_rand();

	double b = color_dir1 * 8 * get_rand();
	double bd = color_dir1 * 0.1 * get_rand();

	double c = color_dir2 * 8 * get_rand();
	double cd = color_dir2 * 0.1 * get_rand();

	for (int i = 0; i < MAX_COLUMNS; i++)
		{
		triple color = color_lab_rgb((triple){a, b, c});
		colors[i] = (Color){ color.x, color.y, color.z, 255 };

		a += ad;
		b += bd;
		c += cd;
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
