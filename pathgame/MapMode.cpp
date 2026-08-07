#include "MapMode.h"

MapMode::MapMode()
	: mode{ MapModeEnum::Political }
{}

MapMode::MapMode(MapModeEnum _mode)
	: mode{ _mode }
{}

MapModeEnum MapMode::GetMapMode()
{
	return mode;
}

void MapMode::ChangeMapMode(MapModeEnum newMode)
{
	mode = newMode;
}

void MapMode::BeginPlay()
{

}

void MapMode::Tick(float dt)
{

}

void MapMode::Render()
{

}

void MapMode::EndPlay()
{

}