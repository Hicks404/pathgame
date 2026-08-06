#include "Application.h"

#include <ctime>
#include <iostream>
#include <raylib/raylib.h>

Application::Application(int x_size, int y_size, const char* _title)
	: xSize{ x_size }, ySize{ y_size }, title{ _title }, startMos{40,40}, endMos{40,40}
{
	
}

Application::~Application() = default;

int Application::Run(float runTime, const function<void()>& testStart, const function<void()>& testCompleted)
{
	srand(static_cast<uint32_t>(time(nullptr)));

	InitWindow(xSize, ySize, title);

	BeginPlay();

	while (!WindowShouldClose())
	{
		Tick(GetFrameTime());

		BeginDrawing();
		ClearBackground(RAYWHITE);

		Render();

		EndDrawing();
	}

	EndPlay();

	CloseWindow();

	return EXIT_SUCCESS;
}

void Application::BeginPlay()
{
	// Create node map
	mapGen.CreateMap();
	nodeMap.Initialise(mapGen.GetMap(), cellSize);
}

void Application::Tick(float dt)
{
	if (IsMouseButtonPressed(0))
	{
		startMos = GetMousePosition();
		nodePath = nodeMap.PathSearch(nodeMap.GetClosestNode(startMos), nodeMap.GetClosestNode(endMos));
	}
	
	if (IsMouseButtonPressed(1))
	{
		endMos = GetMousePosition();
		nodePath = nodeMap.PathSearch(nodeMap.GetClosestNode(startMos), nodeMap.GetClosestNode(endMos));
	}
}

void Application::Render()
{
	nodeMap.Draw();
	nodeMap.DrawPath(nodePath);
}

void Application::EndPlay()
{
	nodeMap.End();
}