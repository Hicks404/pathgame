#pragma once

#include <vector>
#include <string>
#include <raylib/raylib.h>

using std::vector;
using std::string;

struct Node;

struct Edge
{
	Node* target;
	float cost;

public:
	Edge() { target = nullptr; cost = 0; }
	Edge(Node* _target, float _cost) : target{ _target }, cost(_cost) {}
};

struct Node
{
	Vector2 position;
	std::vector<Edge> connections;

	float gScore;
	Node* previous = nullptr;

public:
	Node() {}
	Node(float x, float y) { position = { x, y }; }

	void ConnectTo(Node* other, float cost);
};

class NodeMap
{
public:
	int m_width, m_height;
	float m_cellSize;

	Node** m_nodes;

public:
	Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }

	Node* GetClosestNode(Vector2 worldPos);

	Node* GetRandomNode();

	float GetCellSize();

	std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);

public:
	void Initialise(vector<string> asciiMap, int cellSize);

	void Draw();
	void DrawPath(vector<Node*> nodeMapPath, Color lineColor);
};