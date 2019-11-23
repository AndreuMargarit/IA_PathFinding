#pragma once
#include "Node.h"

class Node;

class Connexion
{
private:
	Node* nodes[2];
	int weight;
public:
	Connexion();
	Connexion(Node* n1, Node* n2, int w = 1);
	~Connexion();
	Node GetNodeConexion(Node actualNode);
	Node GetNodesConnected(int j);
	int GetWeight();
};

