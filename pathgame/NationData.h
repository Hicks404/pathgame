#pragma once

#include <raylib/raylib.h>

#include <string>
#include <vector>
#include "unordered_map"

using std::string;
using std::vector;
using std::unordered_map;

namespace PathGame
{
	struct NationData
	{
		string id;
		string name;
		string description;
		Color color;
		vector<Vector2>landVec;
	};

	// map
	static unordered_map<string, NationData> nationDataMap;

	class NationDataClass
	{
	public:
		NationDataClass();

		void SetupData();

	private:
		string trim(const string& str);

	public:
		/** Get Unordered Map of NationData */
		unordered_map<string, NationData> GetNationMap();

		Color getColor(string id);

		NationData nationOfId(string id);
	};
}