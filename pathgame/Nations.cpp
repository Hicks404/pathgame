#include "Nations.h"

namespace PathGame
{
	Nation::Nation(string _id, string _name, vector<Node*> _land, Color _color)
		: reserve{ 0.f }, income{ 0.f }, manpower{ 0 }, id{ _id }, name{ _name }, land{ _land }, color{ _color }
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

	void Nation::DrawName()
	{
		// find angle between
		float dx = namePoint2.x - namePoint1.x;
		float dy = namePoint2.y - namePoint1.y;

		// convert to radians
		float angle = atan2f(dy, dx) * (180.f / PI); 

		Font font = GetFontDefault();
		float fontSize = 20.f;
		float spacing = 1.f;

		// measure text
		Vector2 textSize = MeasureTextEx(font, name.c_str(), fontSize, spacing);

		// Find center between points
		Vector2 midPoint = { namePoint1.x + dx / 2.f, namePoint1.y + dy / 2.f };

		// Get origin
		Vector2 origin = { textSize.x / 2.0f, textSize.y / 2.0f };

		DrawTextPro(font, name.c_str(), midPoint, origin, angle, fontSize, spacing, WHITE);
	}

	void Nation::SetNamePoints()
	{
		// get point positions
		for (Node* node : land)
		{
			namePoint1.x = std::min(node->position.x, namePoint1.x);
			namePoint2.x = std::max(node->position.x, namePoint2.x);

			namePoint1.y = std::min(node->position.y, namePoint1.y);
			namePoint2.y = std::max(node->position.y, namePoint2.y);
		}
	}

	void Nation::Update()
	{

	}
}