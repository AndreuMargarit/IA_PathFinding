#pragma once
#include <vector>
#include "Connexion.h"
#include "Node.h"
#include "Vector2D.h"


class Graf
{
private:
	//std::vector<Connexion> connexions;
	std::vector<Node> nodes;
public:
	Graf();
	~Graf();
	bool GetNode(Vector2D position, Node* node);
	void AddNode(Node node);
	int GetGrafSize();
};

