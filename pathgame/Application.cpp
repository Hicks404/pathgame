#include "Application.h"

#include <ctime>
#include <iostream>
#include <raylib/raylib.h>

namespace PathGame
{
	Application::Application(int x_size, int y_size, const char* _title)
		: xSize{ x_size }, ySize{ y_size }, title{ _title }, m_nations{}
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

		mapMode.Init(xSize, ySize, cellSize);

		selectedAgent = new Agent();
		m_agents.emplace_back(selectedAgent);
		selectedAgent->SetNodeMap(nodeMap);
		selectedAgent->SetNode(nodeMap.GetClosestNode({ 200,200 }));
		selectedAgent->SetSpeed(20);
		
		vector<Node*> land;
		land.emplace_back(nodeMap.GetNodeFG(9,3));
		land.emplace_back(nodeMap.GetNodeFG(9,2));
		m_nations.emplace_back(new Nation("REB", land, {200,200,200,255}));
	}

	void Application::Secondly()
	{
		for (Nation* nation : m_nations)
		{
			nation->Update();
		}
	}

	void Application::Tick(float dt)
	{
		m_time += dt;

		if (m_time > m_secondago)
		{
			m_secondago += 1;
			Secondly();
		}

		// Set map mode
		nodeMap.SetMapMode(mapMode.GetMapMode());

		if (IsMouseButtonPressed(0))
		{
			// Make path
			Vector2 mos = GetMousePosition();
			nodePath = nodeMap.PathSearch(nodeMap.GetClosestNode(selectedAgent->GetPosition()), nodeMap.GetClosestNode(mos));

			selectedAgent->GoToNode(nodeMap.GetClosestNode(mos));
		}

		mapMode.Tick(dt);

		for (Agent* agent : m_agents)
		{
			agent->Update(dt);
		}
	}

	void Application::Render()
	{
		nodeMap.Draw();
		nodeMap.DrawPath(nodePath);

		mapMode.Render();

		for (Agent* agent : m_agents)
		{
			agent->Draw();
		}
	}

	void Application::EndPlay()
	{
		nodeMap.End();

		for (Agent* agent : m_agents)
		{
			delete agent;
			agent = nullptr;
		}

		for (Nation* nation : m_nations)
		{
			delete nation;
			nation = nullptr;
		}
	}
}