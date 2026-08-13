#include "Agent.h"

namespace PathGame
{
	Vector2 Agent::GetPosition()
	{
		return m_position;
	}

	void Agent::SetNode(Node* start)
	{
		currentNode = start;
	}

	void Agent::SetSpeed(int speed)
	{
		m_speed = speed;
	}

	void Agent::SetNodeMap(NodeMap map)
	{
		nodeMap = map;
	}

	void Agent::SetColor(Color c)
	{
		color = c;
	}

	void Agent::ClearPath()
	{
		m_path.clear();
	}

	void Agent::Update(float dt)
	{
		m_age += dt;

		if (m_path.empty())
		{
			moveBool = false;
			return;
		}

		m_position = m_path[m_currentIndex]->position;

		currentNode = nodeMap.GetClosestNode(m_position);

		if (0 < m_currentIndex)
		{
			m_time += dt;

			if (m_time > 10 / m_speed / m_path[m_currentIndex]->data.moveSpeed)
			{
				m_currentIndex -= 1;
				m_time = 0;
			}
		}
		else
		{
			moveBool = false;
		}
	}

	void Agent::GoToNode(Node* node)
	{
		m_path = nodeMap.PathSearch(currentNode, node);
		m_currentIndex = m_path.size() - 1;
		moveBool = true;
	}

	void Agent::Draw()
	{
		DrawCircle(static_cast<int>(m_position.x), static_cast<int>(m_position.y), 10, color);
	}
}