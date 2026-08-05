#include "Pathfinding.h"

#include <raylib/raylib.h>

Edge::Edge(Node* _target, float _cost)
{
	target = _target;
	cost = _cost;
}

Node::Node(Vector2 pos, float cost)
{
	position = pos;
	gScore = cost;
}

void Node::SetColor(Color _color)
{
	color = _color;
}

void Node::ConnectTo(Node* other, float cost)
{
	connections.emplace_back(other, cost);
}

void NodeMap::Initialise(vector<terrainData> map, float cellSize)
{
	m_cellSize = cellSize;

	float x = 0.f;
	float y = 0.f;

	for (terrainData td : map)
	{
		if (td.name == "next")
		{
			y += 1;
			x = 0;
			continue;
		}

		m_nodes.emplace_back(new Node({ x * cellSize, y * cellSize }, 0.f));

		x += 1;
	}
}

void NodeMap::Draw()
{
	for (Node* node : m_nodes)
	{
		DrawRectangle(node->position.x, node->position.y, m_cellSize, m_cellSize, node->color);
	}
}
