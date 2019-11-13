#pragma once
#include "Node.h"

class Node;

class Connexion
{
private:
	Node* nodes[2];
	float weight;
public:
	Connexion();
	Connexion(Node* n1, Node* n2, int w = 1);
	~Connexion();
};

