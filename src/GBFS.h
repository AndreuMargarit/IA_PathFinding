#pragma once
#include <map>
#include <vector>
#include <queue>
#include "Agent.h"
#include "Node.h"

class GBFS :
	public Agent::PathfindingAlgorithm
{
private:
	std::vector<Node> generatedPath;

public:
	GBFS() {};
	~GBFS() {};
	void GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition);
	std::vector<Node> GetGeneratedPath();
	int CalculateHeuristic(Vector2D position, Vector2D targetPosition);
};

