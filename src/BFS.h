#pragma once
#include <vector>
#include <map>
#include <queue>
#include "Vector2D.h"
#include "Node.h"
#include "Agent.h"

class BFS : 
	public Agent::PathfindingAlgorithm
{
public:
	std::vector<Node> generatedPath;
	BFS() {};
	~BFS() {};
	void GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition);
};