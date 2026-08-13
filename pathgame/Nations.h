#pragma once

#include <vector>
#include <string>

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
		Nation(string _id, vector<Node*>_land, Color _color);

	private:
		vector<Node*>land;

		string id;

		Color color;

		float reserve;
		float income;

		int manpower;
	};
}