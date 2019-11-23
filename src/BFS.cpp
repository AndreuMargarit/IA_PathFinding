#include <iostream>
#include "BFS.h"

void BFS::GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition)
{
	generatedPath.clear();
	std::map<int, Node*> cameFrom;
	std::queue<Node*> queue;
	Node* currentNode = new Node();
	queue.push(graph.GetNode(startPosition));
	Node* nodesContainer;

	while (queue.size() > 0) {

		currentNode = queue.front();
		queue.pop();
		if (currentNode->GetPosition() == targetPosition)
			break;

		nodesContainer = currentNode->GetNeighbors();
		
		for (int i = 0; i < currentNode->SizeConnexions(); i++) {
			if (cameFrom.count(graph.GetIdNode(nodesContainer[i])) == 0) {
				queue.push(graph.GetNode(nodesContainer[i].GetPosition()));
				cameFrom[graph.GetIdNode(nodesContainer[i])] = currentNode;
			}
		}
	}
	std::cout << "Data BFS" << std::endl;
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

std::vector<Node> BFS::GetGeneratedPath()
{
	return generatedPath;
}
