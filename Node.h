#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
using namespace std;
//header guard and includes
class Node{
	public://public constructor, destructor, and functions
		Node(int);
		~Node();
		Node* getRight();
		Node* getLeft();
		int getValue();
		void setValue(int);
	private://private variables
		int value;
		Node* right;
		Node* left;
};
#endif
//header guard end
