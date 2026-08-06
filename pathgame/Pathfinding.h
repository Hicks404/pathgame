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
	terrainData data;

	float gScore;
	Node* previous;

public:
	Node(Vector2 pos, float cost);
	Node(Vector2 pos, float cost, terrainData _data);
	
	void ConnectTo(Node* other, float cost);
};

class NodeMap
{
public:
	float m_cellSize;

	vector<Node*> m_nodes;

public:
	Node* GetNode(Vector2 pos);

	Node* GetClosestNode(Vector2 pos);

	int MakeDivisible(int num, int div);

	vector<Node*> PathSearch(Node* start, Node* end);

public:
	void Initialise(vector<terrainData> map, float cellSize);

	void Draw();

	void DrawPath(vector<Node*> nodeMapPath);

	void End();
};