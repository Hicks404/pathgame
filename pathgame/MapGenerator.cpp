#include "MapGenerator.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using std::fstream;
using std::ifstream;
using std::getline;
using std::stringstream;

MapGenerator::MapGenerator()
{
	terrain.SetData();

	terrain.PrintTD("plains");
}

void MapGenerator::CreateMap()
{
	ifstream file("WorldMap.txt");
	if (!file.is_open())
	{
		std::cerr << "Error: File couldn't open Terrain Stats \n";
		return;
	}

	map.clear();

	string line;
	bool start = false;

	while (getline(file, line))
	{
		if (line.empty() || line.front() == '#')
		{
			// skip rest of loop
			continue;
		}

		// find map start
		if (line.front() == '[' && line.back() == ']')
		{
			start = true;
			continue;
		}

		if (start)
		{
			string temp;
			stringstream ss(line);

			// adds each letter into temp per loop
			while (ss >> temp)
			{
				map.emplace_back(terrain.GetTD(terrainSymbol[temp]));
			}

			terrainData nextLineIndicator;
			nextLineIndicator.name = "next";
			map.emplace_back(nextLineIndicator);

			continue;
		}
	}
}

vector<terrainData> MapGenerator::GetMap()
{
	return map;
}