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
private:
	std::vector<Node> generatedPath;

public:
	BFS() {};
	~BFS() {};
	void GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition);
	std::vector<Node> GetGeneratedPath();
};