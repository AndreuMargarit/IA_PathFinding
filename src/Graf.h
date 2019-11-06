#pragma once
#include <vector>
#include "Node.h"
#include "Connexion.h"
#include "Vector2D.h"
class Graf
{
private:
	std::vector<Connexion> connexions;
	std::vector<Node> nodes;
public:
	Graf();
	~Graf();
	Node GetNode(Vector2D position);
};

