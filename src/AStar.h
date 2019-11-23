#pragma once
#include <vector>
#include <queue>
#include <map>
#include "Vector2D.h"
#include "Node.h"
#include "Agent.h"

class AStar
	:public Agent::PathfindingAlgorithm
{
private:
	std::vector<Node> generatedPath;
public:
	AStar();
	~AStar();
	void GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition);
	std::vector<Node> GetGeneratedPath();
	int CalculateHeuristic(Vector2D position, Vector2D targetPosition);
};

