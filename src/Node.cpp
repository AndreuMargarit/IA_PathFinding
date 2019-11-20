#include "Node.h"



Node::Node()
{
}

Node::Node(Vector2D _position) : position(_position){
	
};

Node::~Node()
{
}

Vector2D Node::GetPosition()
{
	return position;
}

void Node::AddConnexion(Connexion conn)
{
	connexions.push_back(conn);
}
