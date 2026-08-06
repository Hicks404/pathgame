#include "Pathfinding.h"

#include <iostream>
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

Node::Node(Vector2 pos, float cost, Color _color)
{
	position = pos;
	gScore = cost;
	color = _color;
}

void Node::SetColor(Color _color)
{
	color = _color;
}

void Node::ConnectTo(Node* other, float cost)
{
	connections.emplace_back(other, cost);
}

Node* NodeMap::GetNode(Vector2 pos)
{
	for (Node* node : m_nodes)
	{
		if (node->position.x == pos.x && node->position.y == pos.y)
		{
			return node;
		}
	}

	std::cout << "Couldn't find node at " << pos.x << "," << pos.y << "\n";
	return nullptr;
}

void NodeMap::Initialise(vector<terrainData> map, float cellSize)
{
	m_cellSize = cellSize;

	float x = 0.f;
	float y = 0.f;

	// setup nodes
	for (terrainData td : map)
	{
		if (td.name == "next")
		{
			y += 1;
			x = 0;
			continue;
		}

		m_nodes.emplace_back(new Node({ x * cellSize, y * cellSize }, 0.f, td.color));

		x += 1;
	}

	// create edges
	for (Node* node : m_nodes)
	{
		if (node)
		{
			// check if node west
			Node* nodeWest = GetNode({node->position.x - 1 * m_cellSize, node->position.y});

			if (nodeWest)
			{
				node->ConnectTo(nodeWest, 1);
				nodeWest->ConnectTo(node, 1);
			}

			// check if node south
			Node* nodeSouth = GetNode({ node->position.x, node->position.y - 1 * m_cellSize });

			if (nodeSouth)
			{
				node->ConnectTo(nodeSouth, 1);
				nodeSouth->ConnectTo(node, 1);
			}
		}
	}
}

void NodeMap::Draw()
{
	for (Node* node : m_nodes)
	{
		// Draw tile
		DrawRectangle(node->position.x - m_cellSize/2, node->position.y - m_cellSize / 2, m_cellSize, m_cellSize, node->color);

		// Draw line
		for (Edge edge : node->connections)
		{
			DrawLine(node->position.x, node->position.y, edge.target->position.x, edge.target->position.y, WHITE);
		}
	}
}
