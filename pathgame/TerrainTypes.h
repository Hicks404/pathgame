#pragma once

#include <unordered_map>
#include <string>
#include <raylib/raylib.h>

using std::string;
using std::unordered_map;

struct terrainData
{
public:
	// front details
	string name;
	Color color;

public:
	// modifiers
	float moveSpeed;
	float temperature;
	float fertility;

public:
	// sets
	bool moveable;
	bool trees;
};

class Terrain
{
public:
	Terrain();

public:
	/** Setup data dictionary */
	void SetData();

	terrainData GetTD(string name);

	/** Prints data of terrain given as string */
	void PrintTD(string name);

private:
	/** Removes front and end spaces from string */
	string trim(const string& str);

	unordered_map<string, terrainData> TerrainDataMap;
};