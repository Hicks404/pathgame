#include "NationData.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using std::fstream;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::stof;

namespace PathGame
{
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
				nationDataMap[currentNation].name = currentNation;
				continue;
			}

			size_t delimPos = line.find('=');

			// If '=' found then success
			if (delimPos != string::npos)
			{
				string key = trim(line.substr(0, delimPos));
				string value = trim(line.substr(delimPos + 1));

				// Save data
				if (key == "id")
				{
					nationDataMap[currentNation].id = stof(value);
				}
				else if (key == "name")
				{
					nationDataMap[currentNation].name = stof(value);
				}
				else if (key == "description")
				{
					nationDataMap[currentNation].description = stof(value);
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
}