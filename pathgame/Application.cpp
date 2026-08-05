#include "Application.h"

#include <ctime>
#include <raylib/raylib.h>

Application::Application(int x_size, int y_size, const char* _title)
	: xSize{ x_size }, ySize{ y_size }, title{ _title }
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
	// Get terrain data
	terrain.SetData();
	//terrain.PrintTD("plains");

	// Create node map
	mapGen.CreateMap();
	nodeMap.Initialise(mapGen.GetNodeMap(), 10);

	// Pathfinding
	Node* start = nodeMap.GetNode(1, 1);
	Node* end = nodeMap.GetNode(10, 2);
	std::vector<Node*> nodeMapPath = nodeMap.DijkstrasSearch(start, end);
}

void Application::Tick(float dt)
{
	
}

void Application::Render()
{
	nodeMap.Draw();
}

void Application::EndPlay()
{
	
}