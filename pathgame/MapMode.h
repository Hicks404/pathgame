#pragma once

#include "raylib/raylib.h"

enum MapModeEnum
{
	Political,
	Terrain,
	Tempeture
};

class MapMode
{
private:
	MapModeEnum mode;

public:
	MapMode();
	MapMode(MapModeEnum _mode);

public:
	/** Get Map Mode */
	MapModeEnum GetMapMode();

	/** Changes the Map Mode */
	void ChangeMapMode(MapModeEnum newMode);

private:
	void BeginPlay();

	void Tick(float dt);
	void Render();

	void EndPlay();
};