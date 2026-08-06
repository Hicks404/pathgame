#pragma once
#include <functional>

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

	float cellSize = 36;

private:
	NodeMap nodeMap;
	MapGenerator mapGen;
	vector<terrainData> map;

	vector<Node*> nodePath;

private:
	Vector2 startMos;
	Vector2 endMos;

private:
	void BeginPlay();

	void Tick(float dt);
	void Render();

	void EndPlay();
};
