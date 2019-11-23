#pragma once
#include <vector>
#include <queue>
#include <map>
#include "Vector2D.h"
#include "Node.h"
#include "Agent.h"
class Dijkstra
	:public Agent::PathfindingAlgorithm
{
private:
	std::vector<Node> generatedPath;
public:
	Dijkstra();
	~Dijkstra();
	void GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition);
	std::vector<Node> GetGeneratedPath();
};

