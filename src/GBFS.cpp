#include <iostream>
#include "GBFS.h"

void GBFS::GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition)
{
	generatedPath.clear();
	std::map<int, Node*> cameFrom;
	std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, std::greater<std::pair<int, Node*>>> priority_queue;
	Node* currentNode = new Node();
	Node* nodesContainer;
	priority_queue.push({ CalculateHeuristic(startPosition, targetPosition), graph.GetNode(startPosition) });


	while (priority_queue.size() > 0) {
		currentNode = priority_queue.top().second;
		priority_queue.pop();

		if (currentNode->GetPosition() == targetPosition)
			break;

		nodesContainer = currentNode->GetNeighbors();

		for (int i = 0; i < currentNode->SizeConnexions(); i++) {
			if (cameFrom.count(graph.GetIdNode(nodesContainer[i])) == 0) {
				priority_queue.push({ CalculateHeuristic(nodesContainer[i].GetPosition(), targetPosition), graph.GetNode(nodesContainer[i].GetPosition()) });
				cameFrom[graph.GetIdNode(nodesContainer[i])] = currentNode;
			}
		}
	}

	std::cout << "Data GBFS" << std::endl;
	std::cout << "Total nodes explorats:" << cameFrom.size() << std::endl;
	currentNode = graph.GetNode(targetPosition);
	generatedPath.push_back(*currentNode);
	while (currentNode->GetPosition() != startPosition) {
		currentNode = cameFrom[graph.GetIdNode(*currentNode)];
		generatedPath.push_back(*currentNode);
	}

	std::cout << "Path real: " << generatedPath.size() << std::endl;
	std::reverse(generatedPath.begin(), generatedPath.end());
}

std::vector<Node> GBFS::GetGeneratedPath()
{
	return generatedPath;
}

int GBFS::CalculateHeuristic(Vector2D position, Vector2D targetPosition)
{
	return abs(position.x - targetPosition.x) + abs(position.y - targetPosition.y);
}
