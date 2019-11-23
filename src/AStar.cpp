#include "AStar.h"

AStar::AStar()
{
}

AStar::~AStar()
{
}

void AStar::GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition)
{
	generatedPath.clear();
	std::map<int, Node*> cameFrom;
	std::map<int, int> costSoFar;
	std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, std::greater<std::pair<int, Node*>>> priority_queue;
	Node* currentNode = new Node();
	Node* nodesContainer;
	int newCost;
	int i;
	priority_queue.push({ 0, graph.GetNode(startPosition) });
	costSoFar[graph.GetIdNode(startPosition)] = 0;

	while (priority_queue.size() > 0)
	{
		currentNode = priority_queue.top().second;
		priority_queue.pop();

		if (currentNode->GetPosition() == targetPosition)
			break;

		nodesContainer = currentNode->GetNeighbors();
		for (i = 0; i < currentNode->SizeConnexions(); i++)
		{
			newCost = costSoFar[graph.GetIdNode(*currentNode)] + graph.GetCost(*currentNode, nodesContainer[i]);
			if (costSoFar.count(graph.GetIdNode(nodesContainer[i])) == 0 || newCost < costSoFar[graph.GetIdNode(nodesContainer[i])]) {
				costSoFar[graph.GetIdNode(nodesContainer[i])] = newCost;
				priority_queue.push({ CalculateHeuristic(nodesContainer[i].GetPosition(), targetPosition) + newCost, graph.GetNode(nodesContainer[i].GetPosition()) });
				cameFrom[graph.GetIdNode(nodesContainer[i])] = currentNode;
			}
		}
	}

	std::cout << "Data A*" << std::endl;
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

std::vector<Node> AStar::GetGeneratedPath()
{
	return generatedPath;
}

int AStar::CalculateHeuristic(Vector2D position, Vector2D targetPosition)
{
	return abs(position.x - targetPosition.x) + abs(position.y - targetPosition.y);
}