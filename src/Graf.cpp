#include "Graf.h"

Graf::Graf()
{
}


Graf::~Graf()
{
}

bool Graf::GetNode(Vector2D position, Node* node)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].GetPosition() == position)
		{
			node = &nodes[i];
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
