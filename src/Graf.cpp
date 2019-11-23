#include "Graf.h"

Graf::Graf()
{
}

Graf::~Graf()
{
}

Node* Graf::GetNode(Vector2D position)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].GetPosition() == position)
		{
			return &nodes[i];
		}
	}
	return new Node();
}

bool Graf::CheckNode(Vector2D position)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].GetPosition() == position)
		{
			return true;
		}
	}
	return false;
}

void Graf::AddNode(Node node)
{
	nodes.push_back(node);
}

int Graf::GetGrafSize()
{
	return nodes.size();
}

int Graf::GetIdNode(Node node) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].GetPosition() == node.GetPosition()) {
			return i;
		}
	}
}

int Graf::GetCost(Node n1, Node n2)
{
	for (int i = 0; i < n1.SizeConnexions(); i++)
	{
		for (int j = 0; j < 2; j++) {
			Connexion* connexions = &n1.GetConnexions()[i];
			Node nodesConected = n1.GetConnexions()[i].GetNodesConnected(j);
			Vector2D pos = n1.GetConnexions()[i].GetNodesConnected(j).GetPosition();
			if (n2.GetPosition() == n1.GetConnexions()[i].GetNodesConnected(j).GetPosition()) {
				return n1.GetConnexions()[i].GetWeight();
			}
		}
	}
	return 0;
}
