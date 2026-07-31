#include <cstdlib>
#include <iostream>

#include <raylib/raylib.h>

int main(int argC, char* argV[])
{
	InitWindow(800, 600, "Path");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawCircle(400, 300, 25.f, RED);

		EndDrawing();
	}

	return EXIT_SUCCESS;
}