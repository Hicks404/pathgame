#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class MapGenerator
{
public:
	MapGenerator();

private:
	vector<string> map;

public:
	void CreateMap();
	vector<string> GetMap();
	vector<string> GetNodeMap();
};
