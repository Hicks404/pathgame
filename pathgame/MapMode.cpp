#include "MapMode.h"

namespace PathGame
{
	MapMode::MapMode()
		: mode{ MapModeEnum::Political }
	{
	}

	MapMode::MapMode(MapModeEnum _mode)
		: mode{ _mode }
	{
	}

	MapMode::~MapMode()
	{
		for (IconData data : IconVec)
		{
			UnloadTexture(data.icon);
		}
	}

	MapModeEnum MapMode::GetMapMode()
	{
		return mode;
	}

	Texture2D MapMode::GetIcon(MapModeEnum _mode)
	{
		TraceLog(LOG_INFO, "Working directory: %s", GetWorkingDirectory());
		return LoadTexture((MapIcons[_mode] + ".png").c_str());
	}

	void MapMode::ChangeMapMode(MapModeEnum newMode)
	{
		mode = newMode;
	}

	bool MapMode::ButtonPress()
	{
		bool pressed = false;

		for (IconData data : IconVec)
		{
			Rectangle rect = { data.position.x, data.position.y, data.size.x, data.size.y };

			Vector2 mousePos = GetMousePosition();

			if (CheckCollisionPointRec(mousePos, rect))
			{
				mode = data.mode;
				pressed = true;
			}
		}

		return pressed;
	}

	void MapMode::Init(int _width, int _height, float _cellSize)
	{
		// save init stats
		width = _width;
		height = _height;
		cellSize = _cellSize;

		// add mode and icons to vector
		for (int i = 0; i < MapModeEnum::End; ++i)
		{
			IconData data;
			data.mode = static_cast<MapModeEnum>(i);
			data.icon = GetIcon(data.mode);
			data.position = { static_cast<float>(i * cellSize + i * cellSize / 4), static_cast<float>(height - cellSize * 1.2) };
			data.size = { static_cast<float>(cellSize * 1.1), static_cast<float>(cellSize * 1.1) };
			IconVec.emplace_back(data);
		}
	}

	void MapMode::Tick(float dt)
	{

	}

	void MapMode::Render()
	{
		// Create buttons display
		for (IconData data : IconVec)
		{
			// Color of buttons
			Color col = GRAY;

			if (data.mode == mode)
			{
				col = WHITE;
			}

			DrawRectangleV(data.position, data.size, col);
			DrawTextureEx(data.icon, data.position, 0.f, height / 5538.7, WHITE);
		}
	}
}