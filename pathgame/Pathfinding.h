#pragma once

#include <vector>
#include <string>
#include <raylib/raylib.h>

#include "TerrainTypes.h"

using std::vector;
using std::string;

struct Node;

struct Edge
{
	Node* target;
	float cost;

public:
	Edge(Node* _target, float _cost);
};

struct Node
{
	Vector2 position;
	vector<Edge> connections;
	Color color;

	float gScore;

public:
	Node(Vector2 pos, float cost);

	void SetColor(Color _color);
	
	void ConnectTo(Node* other, float cost);
};

class NodeMap
{
public:
	float m_cellSize;

	vector<Node*> m_nodes;

public:
	Node* GetNode(Vector2 pos);

public:
	void Initialise(vector<terrainData> map, float cellSize);

	void Draw();
};