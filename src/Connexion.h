#pragma once
#include "Node.h"

class Connexion
{
private:
	Node nodes[2];
	float weight = 1;
public:
	Connexion();
	~Connexion();
};

