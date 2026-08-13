#pragma once

#include "Pathfinding.h"

namespace PathGame
{
	class Agent
	{
	private:
		Vector2 m_position;
		Vector2 m_smoother;

		NodeMap nodeMap;
		std::vector<Node*> m_path;
		Node* currentNode;

		float m_speed;
		float m_time;
		float m_age;

		bool moveBool;

		Color color = { 255, 255, 0, 255 };

	private:
		int m_currentIndex = 0;

	public:
		Vector2 GetPosition();

	public:
		void SetNode(Node* start);

		void SetSpeed(int speed);

		void SetNodeMap(NodeMap map);

		void SetColor(Color c);

		void ClearPath();

	public:
		void Update(float dt);

		/** Set node agent goes to */
		void GoToNode(Node* node);

		/** Draw Agent */
		void Draw();
	};
};