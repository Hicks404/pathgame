#include "Pathfinding.h"

#include <algorithm>
#include <iostream>
#include <raylib/raylib.h>

void Node::ConnectTo(Node* other, float cost)
{
	connections.push_back(Edge(other, cost));
}

Node* NodeMap::GetClosestNode(Vector2 worldPos)
{
	int i = (worldPos.x / m_cellSize);
	if (i < 0 || i >= m_width) { return nullptr; };

	int j = (worldPos.y / m_cellSize);
	if (j < 0 || j >= m_height) { return nullptr; };

	return GetNode(i, j);
}

Node* NodeMap::GetRandomNode()
{
	Node* node = nullptr;
	while (node == nullptr)
	{
		int x = rand() % m_width;
		int y = rand() % m_height;
		node = GetNode(x, y);
	}
	return node;
}

float NodeMap::GetCellSize()
{
	return m_cellSize;
}

std::vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode)
{
	// Validate input
	if (startNode == nullptr || endNode == nullptr)
	{
		return {};
	}

	if (startNode == endNode)
	{
		return {};
	}

	// Initialise starting node
	startNode->gScore = 0;
	startNode->previous = nullptr;

	// Create temporary lists for storing nodes we're visiting
	vector<Node*> openList;
	vector<Node*> closedList;

	openList.emplace_back(startNode);

	while (openList.empty() == false)
	{
		std::sort(openList.begin(), openList.end(), [](const Node* a, const Node* b)
			{
				return a->gScore < b->gScore;
			});

		Node* currentNode = openList.front();

		// Ends when get to endNode.
		// Sorting openList ensures shortest path

		if (currentNode == endNode)
		{
			break;
		}

		// Remove currentNode and put it in closed list
		std::erase_if(openList, [currentNode](Node* node)
			{
				return node == currentNode;
			});

		closedList.emplace_back(currentNode);

		for (Edge c : currentNode->connections)
		{
			if (std::ranges::find(closedList, c.target) == closedList.end())
			{
				float gScore = currentNode->gScore + c.cost;

				// Calculate score and update parent.
				// Also add to openList for processing
				if (std::ranges::find(openList, c.target) == openList.end())
				{
					c.target->gScore = gScore;
					c.target->previous = currentNode;
					openList.emplace_back(c.target);
				}

				// Node in openList with valid score.
				// Compare calculated score with existing for shorter path.
				else if (gScore < c.target->gScore)
				{
					c.target->gScore = gScore;
					c.target->previous = currentNode;
				}
			}
		}
	}

	// Create path in reverse from endNode to startNode
	vector<Node*> Path;
	Node* currentNode = endNode;

	while (currentNode != nullptr)
	{
		Path.emplace_back(currentNode);

		currentNode = currentNode->previous;
	}

	return Path;
}

void NodeMap::Initialise(vector<string> asciiMap, int cellSize)
{
	m_cellSize = cellSize;
	const char emptySquare = '0';

	// assuming all strings same length
	// sizing map according to string amount and length of first
	m_height = asciiMap.size();
	m_width = asciiMap[0].size();

	m_nodes = new Node * [m_width * m_height];

	// loop over strings, creating node entries
	for (int y = 0; y < m_height; y++)
	{
		string& line = asciiMap[y];

		// report user with mis matched str length
		if (line.size() != m_width)
		{
			std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << std::endl;
		}

		for (int x = 0; x < m_width; x++)
		{
			// get x-th character, or return empty node if string not long enough
			char title = x < line.size() ? line[x] : emptySquare;

			// create node for anything but '.' character
			m_nodes[x + m_width * y] = title == emptySquare ? nullptr
				: new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
		}
	}

	// loop over nodes, creating connections between them and neighbours west and south of grid
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node)
			{
				// sees if there is node west or array overruns if west-most edge
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);

				if (nodeWest)
				{
					node->ConnectTo(nodeWest, 1); // TODO weights
					nodeWest->ConnectTo(node, 1);
				}

				// see if node south or overrun
				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);

				if (nodeSouth)
				{
					node->ConnectTo(nodeSouth, 1);
					nodeSouth->ConnectTo(node, 1);
				}
			}
		}
	}
}

void NodeMap::Draw()
{
	// red blocks
	Color cellColor;
	cellColor.a = 255;
	cellColor.r = 255;
	cellColor.g = 0;
	cellColor.b = 0;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node == nullptr)
			{
				// draw solid block in empty squares without nav node
				DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
					(int)m_cellSize - 1, (int)m_cellSize - 1, cellColor);
			}
			else
			{
				// draw the connections between the node and its neighbours
				for (int i = 0; i < node->connections.size(); i++)
				{
					Node* other = node->connections[i].target;
					DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize,
						(int)other->position.x, (int)other->position.y,
						GRAY);
				}
			}
		}
	}
}

void NodeMap::DrawPath(vector<Node*> nodeMapPath, Color lineColor)
{
	for (Node* nm : nodeMapPath)
	{
		if (nm->previous)
		{
			Node* other = nm->previous;

			int xPos = other->position.x;
			int yPos = other->position.y;

			DrawLine((nm->position.x + 0.5f), (nm->position.y + 0.5f),
				xPos, yPos,
				lineColor);
		}
	}
}