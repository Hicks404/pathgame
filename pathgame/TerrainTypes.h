#pragma once

#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;

struct terrainData
{
public:
	string name;

public:
	// modifiers
	float moveSpeed;
	float temperature;
	float fertility;

public:
	bool moveable;
	bool trees;
};

class Terrain
{
public:
	Terrain();

public:
	void SetData();
	void PrintTD(string name);

private:
	string trim(const string& str);

	unordered_map<string, terrainData> TerrainDataMap;
};