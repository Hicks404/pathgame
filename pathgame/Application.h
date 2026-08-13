#pragma once
#include <functional>

#include "MapGenerator.h"
#include "Pathfinding.h"
#include "MapMode.h"
#include "Agent.h"
#include "Nations.h"

using std::function;

namespace PathGame
{
	class Application
	{
	public:
		explicit Application(int x_size, int y_size, const char* _title);
		~Application();

	public:
		int Run(float runTime = 0.f, const function<void()>& testStart = nullptr, const function<void()>& testCompleted = nullptr);

	private:
		int xSize;
		int ySize;
		const char* title;

		float cellSize = 36;

		float m_time = 0.f;
		int m_secondago = 1;

	private:
		NodeMap nodeMap;
		MapGenerator mapGen;
		MapMode mapMode;

		/** Nations */
		vector<Nation*> m_nations;

		/** Map Tiles */
		vector<terrainData> map;

		/** NodePath */
		vector<Node*> nodePath;

		vector<Agent*> m_agents;
		Agent* selectedAgent;

	private:
		void BeginPlay();

		void Secondly();
		void Tick(float dt);
		void Render();

		void EndPlay();
	};
};
