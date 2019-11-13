#include "Connexion.h"



Connexion::Connexion()
{
}

Connexion::Connexion(Node* n1, Node* n2, int w)
{
	nodes[0] = n1;
	nodes[1] = n2;
	weight = w;
}


Connexion::~Connexion()
{
}
