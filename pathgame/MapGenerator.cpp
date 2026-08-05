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
			string fullTemp;
			stringstream ss(line);

			// adds each letter into temp per loop
			while (ss >> temp)
			{
				fullTemp.append(temp);
			}
			map.emplace_back(fullTemp);
			continue;
		}
	}
}

vector<string> MapGenerator::GetMap()
{
	return map;
}

vector<string> MapGenerator::GetNodeMap()
{
	vector<string> NodeMap;

	for (string str : map)
	{
		string fullTemp;

		for (string c : map)
		{
			if (str == "j" || str == "m" || str == "n")
			{
				fullTemp.append("1");
			}
			else
			{
				fullTemp.append("0");
			}
		}

		NodeMap.emplace_back(fullTemp);
	}

	return NodeMap;
}
