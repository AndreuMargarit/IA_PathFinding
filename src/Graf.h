#pragma once
#include <vector>
#include "Connexion.h"
#include "Node.h"
#include "Vector2D.h"


class Graf
{
	private:
		std::vector<Node> nodes;
	public:
		Graf();
		~Graf();
		Node* GetNode(Vector2D position);
		bool CheckNode(Vector2D position);
		void AddNode(Node node);
		int GetGrafSize();
};

