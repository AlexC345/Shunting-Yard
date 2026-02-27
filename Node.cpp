#include <iostream>
#include <cstring>
#include "Node.h"
using namespace std;

Node::Node(int inputValue){
	value = inputValue;
	right = NULL;
	left = NULL;
}

Node::~Node(){}

Node* Node::getRight(){//gets right node
	return right;
}

Node* Node::getLeft(){//gets left node
	return left;
}

void Node::setRight(Node* input){//sets right value
	right = input;
}

void Node::setLeft(Node* input){//sets left value
	left = input;
}

int Node::getValue(){//gets current value
	return value;
}

void Node::setValue(int input){//sets current value
	value = input;
}
