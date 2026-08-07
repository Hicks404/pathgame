#include "Pathfinding.h"

#include <algorithm>
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

Node::Node(Vector2 pos, float cost, terrainData _data)
{
	position = pos;
	gScore = cost;
	data = _data;
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

Node* NodeMap::GetClosestNode(Vector2 pos)
{
	float i = MakeDivisible(pos.x, m_cellSize);

	float j = MakeDivisible(pos.y, m_cellSize);

	return GetNode({i, j});
}

int NodeMap::MakeDivisible(int num, int div)
{
	return (num + div / 2) / div * div;
}

bool NodeMap::EqualVec(Vector2 vec1, Vector2 vec2)
{
	return (vec1.x == vec2.x && vec1.y == vec2.y);
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

	float savedDist = 10000;

	openList.emplace_back(start);

	while (!openList.empty())
	{
		// Get smallest node gScore
		std::sort(openList.begin(), openList.end(), [](const Node* a, const Node* b)
			{
				return a->gScore > b->gScore;
			});

		Node* smallest = openList.back();

		// remove smallest
		openList.pop_back();

		// add to closed list
		closedList.emplace_back(smallest);

		// find successor
		float best = 1000000.f;
		Node* successor = smallest;

		// begin path finding
		for (Edge edge : successor->connections)
		{
			if (std::ranges::find(closedList, edge.target) == closedList.end())
			{
				if (EqualVec(edge.target->position, end->position) || best < 0)
				{
					successor = edge.target;
					successor->previous = smallest;
					openList.clear();

					std::cout << best << "\n";
				}
				else
				{
					// based on cost and distance from end
					float distance = sqrt(pow(edge.target->position.x - end->position.x, 2) + pow(edge.target->position.y - end->position.y, 2)) / m_cellSize;
					float score = distance * edge.cost;

					if (score < best) // && distance <= savedDist )
					{
						best = score;
						savedDist = distance;
						successor = edge.target;
						successor->previous = smallest;
						openList.emplace_back(successor);
					}
				}
			}
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
				// check if node west
				Node* nodeWest = GetNode({ node->position.x - 1 * m_cellSize, node->position.y });

				if (nodeWest)
				{
					// make edge score
					float score = node->data.terrainCost;
					score = std::max(score, 0.f);

					node->ConnectTo(nodeWest, score);
					nodeWest->ConnectTo(node, score);
				}

				// check if node south
				Node* nodeSouth = GetNode({ node->position.x, node->position.y - 1 * m_cellSize });

				if (nodeSouth)
				{
					float score = node->data.terrainCost;
					score = std::max(score, 0.f);
					node->ConnectTo(nodeSouth, score);
					nodeSouth->ConnectTo(node, score);
				}
			}
		}
	}
}

void NodeMap::Draw()
{
	for (Node* node : m_nodes)
	{
		// Draw tile
		DrawRectangle(node->position.x - m_cellSize/2, node->position.y - m_cellSize / 2, m_cellSize, m_cellSize, node->data.color);

		// Draw line
		for (Edge edge : node->connections)
		{
			DrawLine(node->position.x, node->position.y, edge.target->position.x, edge.target->position.y, WHITE);

			//const char* text = std::to_string(node->gScore).c_str();
			//DrawText(text, edge.target->position.x - node->position.x, edge.target->position.y - node->position.y, 40, BLACK);
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
