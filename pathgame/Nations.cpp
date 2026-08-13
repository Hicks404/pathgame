#include "Nations.h"

namespace PathGame
{
	Nation::Nation(string _id, vector<Node*> _land, Color _color)
		: reserve{ 0.f }, income{ 0.f }, manpower{ 0 }, id{ _id }, land{ _land }, color{ _color }
	{
		landTag();
	}

	void Nation::landTag()
	{
		for (Node* node : land)
		{
			node->data.ownerID = id;
		}
	}

	void Nation::Update()
	{

	}
}