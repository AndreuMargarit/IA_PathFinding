#pragma once
#include <vector>
#include "Connexion.h"
#include "Vector2D.h"

class Connexion;

class Node
{
private:
	std::vector<Connexion> connexions;
	Vector2D position;
public:
	Node();
	Node(Vector2D position);
	~Node();

	Vector2D GetPosition();
	void AddConnexion(Connexion conn);
};

