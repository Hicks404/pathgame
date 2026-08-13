#pragma once
#include <functional>
#include <algorithm>
#include <cmath>

#include "MapGenerator.h"
#include "Pathfinding.h"
#include "MapMode.h"
#include "Agent.h"
#include "Nations.h"
#include "NationData.h"

using std::function;
using std::to_string;
using std::round;

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
		NationDataClass nationData;

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
