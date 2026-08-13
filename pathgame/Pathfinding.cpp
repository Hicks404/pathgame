#include "Pathfinding.h"

#include <algorithm>
#include <iostream>
#include <raylib/raylib.h>
#include <raylib/raymath.h>

namespace PathGame
{
	Edge::Edge(Node* _target, float _cost)
	{
		target = _target;
		cost = _cost;
		water = false;
	}

	Edge::Edge(Node* _target, float _cost, bool _water)
	{
		target = _target;
		cost = _cost;
		water = _water;
	}

	Node::Node(Vector2 pos, float cost)
	{
		position = pos;
		gScore = cost;
	}

	Node::Node(Vector2 pos, float cost, terrainData _data)
	{
		position = pos;
		gScore = cost;
		data = _data;
	}

	void Node::ConnectTo(Node* other, float cost, bool water)
	{
		connections.emplace_back(other, cost, water);
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

	Node* NodeMap::GetClosestNode(Vector2 pos)
	{
		float i = MakeDivisible(pos.x, m_cellSize);

		float j = MakeDivisible(pos.y, m_cellSize);

		return GetNode({ i, j });
	}

	int NodeMap::MakeDivisible(int num, int div)
	{
		return (num + div / 2) / div * div;
	}

	bool NodeMap::EqualVec(Vector2 vec1, Vector2 vec2)
	{
		return (vec1.x == vec2.x && vec1.y == vec2.y);
	}

	void NodeMap::SetMapMode(MapModeEnum set)
	{
		mode = set;
	}

	vector<Node*> NodeMap::PathSearch(Node* start, Node* end)
	{
		// Validate input
		if (start == nullptr || end == nullptr)
		{
			return {};
		}

		if (start == end)
		{
			return {};
		}

		// Create temporary lists
		vector<Node*> openList;
		vector<Node*> closedList;

		start->gScore = 0;
		start->previous = nullptr;

		openList.emplace_back(start);

		// loop until path is found
		while (!openList.empty())
		{
			// get gNode
			Node* firstG = openList.back();
			firstG->gScore = 0;

			// remove firstG from openList
			openList.pop_back();

			for (Node* node : openList)
			{
				node->gScore = 10000;
			}

			// add to closed list
			closedList.emplace_back(firstG);

			// find successor
			float best = 1000000.f;

			// true if found an edge
			bool foundWay = false;

			// begin path finding
			for (Edge edge : firstG->connections)
			{
				if (std::ranges::find(closedList, edge.target) == closedList.end())
				{
					// When reached destination
					if (EqualVec(edge.target->position, end->position) || best < 0)
					{
						firstG->gScore += best;
						edge.target->previous = firstG;
						openList.clear();
						foundWay = true;
					}
					else
					{
						// based on cost and distance from end
						// distance is hScore
						float distance = Vector2Distance(edge.target->position, end->position) / m_cellSize;

						// gscore using total score and terrain cost
						float gScore = firstG->gScore + edge.cost;

						//// continue water travel if already in water. Hesitant to begin water travel
						//if (edge.water && waterMode)
						//{
						//	gScore = 0;
						//}
						//else if (edge.water && !waterMode)
						//{
						//	gScore *= 2;
						//}

						// final cost
						float fScore = distance + gScore;

						// add best node to reach destination
						if (fScore < best)
						{
							best = fScore;
							edge.target->previous = firstG;
							openList.emplace_back(edge.target);
							foundWay = true;
							waterMode = edge.water;
						}
					}
				}
			}

			if (!foundWay)
			{
				return {};
			}
		}

		// create path vector in reverse
		vector<Node*> Path;
		Node* currentNode = end;

		while (currentNode != nullptr)
		{
			Path.emplace_back(currentNode);

			currentNode = currentNode->previous;
		}

		return Path;
	}

	void NodeMap::Initialise(vector<terrainData> map, float cellSize)
	{
		m_cellSize = cellSize;

		waterMode = false;

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


			m_nodes.emplace_back(new Node({ x * cellSize, y * cellSize }, 0.f, td));

			x += 1;
		}

		// create edges
		for (Node* node : m_nodes)
		{
			if (node)
			{
				if (node->position.x > 0 && node->position.y > 0)
				{
					// water bool
					bool water = node->data.water;

					// check if node west
					Node* nodeWest = GetNode({ node->position.x - 1 * m_cellSize, node->position.y });

					if (nodeWest)
					{
						// minimum score
						float score = std::max(node->data.terrainCost, nodeWest->data.terrainCost);

						node->ConnectTo(nodeWest, score, water);
						nodeWest->ConnectTo(node, score, water);
					}

					// check if node south
					Node* nodeSouth = GetNode({ node->position.x, node->position.y - 1 * m_cellSize });

					if (nodeSouth)
					{
						float score = std::max(node->data.terrainCost, nodeSouth->data.terrainCost);

						node->ConnectTo(nodeSouth, score, water);
						nodeSouth->ConnectTo(node, score, water);
					}
				}
			}
		}
	}

	void NodeMap::Draw()
	{
		for (Node* node : m_nodes)
		{
			// Decide tile color
			Color tileCol = node->data.color;

			if (mode == Temperature)
			{
				tileCol = {
					static_cast<unsigned char>(std::max(node->data.temperature * 5, 0.f)),
					30,
					static_cast<unsigned char>(std::max(155 - node->data.temperature * 5, 0.f)),
					255
				};
			}

			// Draw tile
			DrawRectangle(node->position.x - m_cellSize / 2, node->position.y - m_cellSize / 2, m_cellSize, m_cellSize, tileCol);

			// Draw line
			for (Edge edge : node->connections)
			{
				DrawLine(node->position.x, node->position.y, edge.target->position.x, edge.target->position.y, WHITE);
			}
		}
	}

	void NodeMap::DrawPath(vector<Node*> nodeMapPath)
	{
		for (Node* nm : nodeMapPath)
		{
			if (nm->previous)
			{
				Node* other = nm->previous;

				float xPos = other->position.x;
				float yPos = other->position.y;

				DrawLineEx({ nm->position.x + 0.5f, nm->position.y + 0.5f },
					{ xPos, yPos },
					8,
					BLACK);
			}
		}
	}

	void NodeMap::End()
	{
		for (Node* node : m_nodes)
		{
			delete node;
			node = nullptr;
		}
	}
}