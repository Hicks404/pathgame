#pragma once
#include <string>
#include <vector>
#include "unordered_map"

#include "TerrainTypes.h"

using std::string;
using std::vector;
using std::unordered_map;

namespace PathGame
{
	inline unordered_map<string, string> terrainSymbol
	{
		{"a", "plains"},
		{"b", "grasslands"},
		{"c", "savannah"},
		{"d", "steppe"},
		{"e", "desert"},
		{"f", "desertFlood"},
		{"g", "tundra"},
		{"h", "polar"},
		{"i", "seaIce"},
		{"j", "mountains"},
		{"k", "shore"},
		{"m", "ocean"},
		{"n", "deepOcean"},
		{"o", "forest"},
		{"p", "marsh"},
		{"q", "drylands"},
		{"r", "jungle"}
	};

	class MapGenerator
	{
	public:
		MapGenerator();

	private:
		vector<terrainData> map;
		Terrain terrain;

	public:
		void CreateMap();
		vector<terrainData> GetMap();
	};
};
