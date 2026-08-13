#define _CRT_SECURE_NO_WARNINGS

#include "NationData.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>

using std::fstream;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::stof;

namespace PathGame
{
	NationDataClass::NationDataClass()
	{

	}

	void NationDataClass::SetupData()
	{
		ifstream file("Nations.txt");
		if (!file.is_open())
		{
			std::cerr << "Error: File couldn't open Terrain Stats \n";
			return;
		}

		string line;
		string currentNation = "";

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
				currentNation = line.substr(1, line.length() - 2);
				nationDataMap[currentNation].id = currentNation;
				continue;
			}

			size_t delimPos = line.find('=');

			// If '=' found then success
			if (delimPos != string::npos)
			{
				string key = trim(line.substr(0, delimPos));
				string value = trim(line.substr(delimPos + 1));

				// Save data
				if (key == "name")
				{
					nationDataMap[currentNation].name = value;
				}
				else if (key == "description")
				{
					nationDataMap[currentNation].description = value;
				}
				else if (key == "red")
				{
					nationDataMap[currentNation].color.r = stof(value);
				}
				else if (key == "green")
				{
					nationDataMap[currentNation].color.g = stof(value);
				}
				else if (key == "blue")
				{
					nationDataMap[currentNation].color.b = stof(value);
				}
				else if (key == "alpha")
				{
					nationDataMap[currentNation].color.a = stof(value);
				}
				else if (key == "land")
				{
					// Get each land vec
					string vecStr;
					bool collect = true;

					for (char c : value)
					{
						if (c == '{')
						{
							collect = true;
						}
						else if (c == '}')
						{
							collect = false;
						}
						else if (collect)
						{
							vecStr += c;
						}
						else if (c == '&' && !collect)
						{
							// add land vec as data
							Vector2 stor = { 0,0 };
							int parsed = std::sscanf(vecStr.c_str(), "%f,%f", &stor.x, &stor.y);

							nationDataMap[currentNation].landVec.emplace_back(stor);
							vecStr = "";
						}
					}
				}
			}

			continue;
		}

		file.close();
	}

	string NationDataClass::trim(const string& str)
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

	unordered_map<string, NationData> NationDataClass::GetNationMap()
	{
		return nationDataMap;
	}
	Color NationDataClass::getColor(string id)
	{
		return nationDataMap[id].color;
	}
	NationData NationDataClass::nationOfId(string id)
	{
		return nationDataMap[id];
	}
}