#include "TerrainTypes.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using std::fstream;
using std::ifstream;
using std::getline;
using std::stof;

namespace PathGame
{
	Terrain::Terrain()
	{

	}

	void Terrain::SetData()
	{
		ifstream file("TerrainStats.txt");
		if (!file.is_open())
		{
			std::cerr << "Error: File couldn't open Terrain Stats \n";
			return;
		}

		string line;
		string currentTerrain = "";

		while (getline(file, line))
		{
			line = trim(line);

			if (line.empty() || line.front() == '#')
			{
				// skip rest of loop
				continue;
			}

			// find terrain name
			if (line.front() == '[' && line.back() == ']')
			{
				currentTerrain = line.substr(1, line.length() - 2);
				TerrainDataMap[currentTerrain].name = currentTerrain;
				continue;
			}

			size_t delimPos = line.find('=');

			// If '=' found then success
			if (delimPos != string::npos && !currentTerrain.empty())
			{
				string key = trim(line.substr(0, delimPos));
				string value = trim(line.substr(delimPos + 1));

				// Save data
				if (key == "moveSpeed")
				{
					TerrainDataMap[currentTerrain].moveSpeed = stof(value);
				}
				else if (key == "tempeture")
				{
					TerrainDataMap[currentTerrain].temperature = stof(value);
				}
				else if (key == "fertility")
				{
					TerrainDataMap[currentTerrain].fertility = stof(value);
				}
				else if (key == "terrainCost")
				{
					TerrainDataMap[currentTerrain].terrainCost = stof(value);
				}
				else if (key == "water")
				{
					TerrainDataMap[currentTerrain].water = (value == "true");
				}
				else if (key == "trees")
				{
					TerrainDataMap[currentTerrain].trees = (value == "true");
				}
				else if (key == "red")
				{
					TerrainDataMap[currentTerrain].color.r = stoi(value);
				}
				else if (key == "green")
				{
					TerrainDataMap[currentTerrain].color.g = stoi(value);
				}
				else if (key == "blue")
				{
					TerrainDataMap[currentTerrain].color.b = stoi(value);
				}
			}
		}

		file.close();
	}

	terrainData Terrain::GetTD(string name)
	{
		if (TerrainDataMap.find(name) != TerrainDataMap.end())
		{
			terrainData data = TerrainDataMap.find(name)->second;
			return data;
		}

		std::cout << "GetTD failed: " << name << "\n";
		return {};
	}

	void Terrain::PrintTD(string name)
	{
		if (TerrainDataMap.find(name) != TerrainDataMap.end())
		{
			terrainData data = TerrainDataMap.find(name)->second;

			std::cout << "Name: " << data.name << "\n";

			std::cout << "Color: " << data.color.r << " / " << data.color.g << " / " << data.color.b << "\n";

			std::cout << "moveSpeed: " << data.moveSpeed << "\n";
			std::cout << "temperature: " << data.temperature << "\n";
			std::cout << "fertility: " << data.fertility << "\n";

			std::cout << "water: " << data.water << "\n";
			std::cout << "trees: " << data.trees << "\n\n";
		}
	}

	string Terrain::trim(const string& str)
	{
		// remove front spaces
		size_t first = str.find_first_not_of(" \t\r\n");

		// return if string empty
		if (first == string::npos)
		{
			return "";
		}

		// remove end spaces
		size_t last = str.find_last_not_of(" \t\r\n");

		return str.substr(first, (last - first + 1));
	}
}