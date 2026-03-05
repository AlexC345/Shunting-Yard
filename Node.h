#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
using namespace std;
//header guard and includes
class Node{
	public://public constructor, destructor, and functions
		Node(char);
		~Node();
		Node* getRight();
		void setRight(Node*);
		Node* getLeft();
		void setLeft(Node*);
		char getValue();
		void setValue(char);
		Node* getNext();
		void setNext(Node*);
	private://private variables
		char value;
		Node* right;
		Node* left;
		Node* next;
};
#endif
//header guard end
