#pragma once

#include <vector>
#include <string>
#include <math.h>
#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <algorithm>
#include <iostream>

#include "Pathfinding.h"

using std::vector;
using std::string;

namespace PathGame
{
	class Nation;

	struct Diplomacy
	{
		Nation* nation;
		int relation;
		vector<string> modifiers;
	};

	class Nation
	{
	public:
		Nation(string _id, string _name, vector<Node*>_land, Color _color);

	private:
		vector<Node*>land;

		string id;
		string name;

		Color color;

		float reserve;
		float income;

		int manpower;

	private:
		Vector2 namePoint1 = { 0,0 };
		Vector2 namePoint2 = { 0,0 };

	public:
		void landTag();

		void DrawName();
		void SetNamePoints();

		void Update();
	};
}