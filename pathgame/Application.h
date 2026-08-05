#pragma once
#include <functional>

#include "TerrainTypes.h"
#include "MapGenerator.h"
#include "Pathfinding.h"

using std::function;

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

private:
	NodeMap nodeMap;
	Terrain terrain;
	MapGenerator mapGen;
	vector<string> map;

private:
	void BeginPlay();

	void Tick(float dt);
	void Render();

	void EndPlay();
};
