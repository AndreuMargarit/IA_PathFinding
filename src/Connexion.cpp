#include "Connexion.h"

Connexion::Connexion()
{
	nodes[0] = new Node();
	nodes[1] = new Node();
	weight = 1;
}

Connexion::Connexion(Node* n1, Node* n2, int w)
{
	nodes[0] = new Node(*n1);
	nodes[1] = new Node(*n2);
	weight = w;
}

Connexion::~Connexion()
{
}
