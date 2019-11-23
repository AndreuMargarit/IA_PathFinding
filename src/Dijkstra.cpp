#include "Dijkstra.h"



Dijkstra::Dijkstra()
{
}


Dijkstra::~Dijkstra()
{
}

void Dijkstra::GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition)
{
	generatedPath.clear();
	std::map<int, Node*> cameFrom;
	std::map<int, int> costSoFar;
	std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, std::greater<std::pair<int, Node*>>> priority_queue;
	Node* currentNode = new Node();
	Node* nodesContainer;
	priority_queue.push({ 0, graph.GetNode(startPosition) });
	costSoFar[graph.GetIdNode(startPosition)] = 0;

	while (priority_queue.size() > 0)
	{
		currentNode = priority_queue.top().second;
		priority_queue.pop();

		if (currentNode->GetPosition() == targetPosition)
		{
			int x = 0;
			break;
		}
		 
		nodesContainer = currentNode->GetNeighbors();
		int newCost;
		for (int i = 0; i < currentNode->SizeConnexions(); i++)
		{
			newCost = costSoFar[graph.GetIdNode(*currentNode)] + graph.GetCost(*currentNode, nodesContainer[i]);
			if (costSoFar.count(graph.GetIdNode(nodesContainer[i])) == 0 || newCost < costSoFar[graph.GetIdNode(nodesContainer[i])]) {
				costSoFar[graph.GetIdNode(nodesContainer[i])] = newCost;
				priority_queue.push({ newCost, &nodesContainer[i] });
				cameFrom[graph.GetIdNode(nodesContainer[i])] = currentNode;
			}
		}
	}

	std::cout << "Data Dijkstra" << std::endl;
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

std::vector<Node> Dijkstra::GetGeneratedPath()
{
	return generatedPath;
}
