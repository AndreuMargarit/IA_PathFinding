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
