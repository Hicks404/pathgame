#pragma once

#include <vector>
#include <string>
#include <raylib/raylib.h>

#include "TerrainTypes.h"
#include "MapMode.h"

using std::vector;
using std::string;
using std::pow;
using std::sqrt;

namespace PathGame
{
	struct Node;

	struct Edge
	{
		Node* target;
		float cost;
		bool water;

	public:
		Edge(Node* _target, float _cost);
		Edge(Node* _target, float _cost, bool _water);
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

		void ConnectTo(Node* other, float cost, bool water);
	};

	class NodeMap
	{
	public:
		float m_cellSize;

		vector<Node*> m_nodes;

		MapModeEnum mode = Political;

	private:
		bool waterMode;

	public:
		Node* GetNode(Vector2 pos);

		Node* GetClosestNode(Vector2 pos);

		int MakeDivisible(int num, int div);

		bool EqualVec(Vector2 vec1, Vector2 vec2);

		void SetMapMode(MapModeEnum set);

		vector<Node*> PathSearch(Node* start, Node* end);

	public:
		void Initialise(vector<terrainData> map, float cellSize);

		void Draw();

		void DrawPath(vector<Node*> nodeMapPath);

		void End();
	};
};