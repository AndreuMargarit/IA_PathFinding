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

int Node::SizeConnexions() 
{
	return connexions.size();
}

Node* Node::GetNeighbors() {

	Node* aux = new Node[connexions.size()];

	for (int i = 0; i < connexions.size(); i++) {
		aux[i] = connexions[i].GetNodeConexion(*this);
	}

	return aux;

}