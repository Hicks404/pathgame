#pragma once

#include "raylib/raylib.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

using std::unordered_map;
using std::string;
using std::vector;

namespace PathGame
{
	enum MapModeEnum
	{
		Political,
		Terra,
		Temperature,
		End
	};

	inline unordered_map<MapModeEnum, string> MapIcons
	{
		{Political, "Political"},
		{Terra, "Terrain"},
		{Temperature, "Temperature" }
	};

	struct IconData
	{
		MapModeEnum mode;
		Texture2D icon;
		Vector2 position;
		Vector2 size;
	};

	class MapMode
	{
	private:
		MapModeEnum mode;

		int width;
		int height;
		int cellSize;

	public:
		vector<IconData> IconVec;

	public:
		MapMode();
		MapMode(MapModeEnum _mode);
		~MapMode();

	public:
		/** Get Map Mode */
		MapModeEnum GetMapMode();

		/** Get texture of Mode */
		Texture2D GetIcon(MapModeEnum _mode);

		/** Changes the Map Mode */
		void ChangeMapMode(MapModeEnum newMode);

	public:
		void Init(int _width, int _height, float _cellSize);

		void Tick(float dt);
		void Render();

		void EndPlay();
	};
}