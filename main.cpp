#include <iostream>
#include <cstring>
#include <string>
#include "Node.h"
#include <cctype>
using namespace std;

struct Queue{
	Node* first = NULL;
	void Enqueue(Node* inputNode){//adds to back of queue
		if (first != NULL){
			Node* current = first;
			while (current->getNext() != NULL){
				current = current->getNext();
			}
			current->setNext(inputNode);
		}
		else{
			first = inputNode;
		}
	}
	Node* Dequeue(){//deletes front of queue
		if (first != NULL){
			Node* oldFirst = first;
			Node* newFirst = first->getNext();
			first->setNext(NULL);
			first = newFirst;
			return oldFirst;
		}
		else{
			return NULL;
		}
	}
	void Printqueue(){//prints out the queue
		Node* current = first;
		while (current != NULL){
			cout << current->getValue();
			current = current->getNext();
		}
		cout << endl;
	}
};

struct Stack{
	Node* first = NULL;
	void Push(Node* inputNode){ //adds to back (top)
		if (first != NULL){
			Node* current = first;
			while (current->getNext() != NULL){
				current = current->getNext();
			}
			current->setNext(inputNode);
		}
		else{
			first = inputNode;
		}
	}
	Node* Pop(){ //removes back (top)
		if (first != NULL){
			Node* prev = first;
			if (first->getNext() != NULL){
				Node* current = first->getNext();
				while (current->getNext() != NULL){
					prev = current;
					current = current->getNext();
				}
				prev->setNext(NULL);
				return current;
			}
			else{
				Node* tempFirst = first;
				first = NULL;
				return tempFirst;
			}
		}
		else{
			first = NULL;
			return first;
		}
	}
	Node* Peek(){ //returns back (top)
		if (first != NULL){
			Node* current = first;
			while (current->getNext() != NULL){
				current = current->getNext();
			}
			return current;
		}
		else{
			return NULL;
		}
	}
	void Printstack(){ //prints out the stack
		Node* current = first;
		while (current != NULL){
			cout << current->getValue();
			current = current->getNext();
		}
		cout << endl;
	}
};

void infixMe(Node* current){//recursive infix function
	Node* left = current->getLeft();
	Node* right = current->getRight();
	cout << "(";//print out parenthesis before and after
	if (!isdigit(left->getValue())){//if left child is an operator
		infixMe(left);//recursion on left
	}
	else{//if left child is number
		cout << left->getValue();//print it out
	}
	cout << current->getValue();//print out current operator
	if (!isdigit(right->getValue())){//if right child is an operator
		infixMe(right);//recursion on right
	}
	else{//if right child is number
		cout << right->getValue();//print it out
	}
	cout << ")";//print out parenthesis before and after
}

void prefixMe(Node* current){//recursive prefix function
	Node* left = current->getLeft();
	Node* right = current->getRight();
	cout << current->getValue();//print current value first (number or operator)
	if (!isdigit(left->getValue())){//if left child is operator
		prefixMe(left);//recursion on left
	}
	else{//if left child is number
		cout << left->getValue();//print it out
	}
	if (!isdigit(right->getValue())){//if right child is operator
		prefixMe(right);//recursion on right
	}
	else{//if right hcild is number
		cout << right->getValue();//print it out
	}
}

void postfixMe(Node* current){//recursive postfix function
	Node* left = current->getLeft();
	Node* right = current->getRight();
	if (!isdigit(left->getValue())){//if left child is operator
		postfixMe(left);//recursion on left
	}
	else{//if left child is number
		cout << left->getValue();//print it out
	}
	if (!isdigit(right->getValue())){//if right child is operator
		postfixMe(right);//recursion on right
	}
	else{//if right child is number
		cout << right->getValue();//print it out
	}
	cout << current->getValue();//print current value last (number or operator)
}

int main(){
	string expression;
	cout << "Enter expression: ";
	cin >> expression;
	Queue inputExpression;
	Stack operators;
	Queue finalExpression;
	for (int i = 0; i < expression.length(); i++){//adds expression to inputExpression
		inputExpression.Enqueue(new Node(expression[i]));
	}
	//inputExpression.Printqueue();
	//shunting yard algorithm
	for (int i = 0; i < expression.length(); i++){
		Node* current = inputExpression.Dequeue();//deletes and remembers what was deleted
		if (isdigit(current->getValue())){//if current is a number:
			finalExpression.Enqueue(current);
		}
		else{//if current is not a number:
			if (current->getValue() != ')'){
				operators.Push(current);
			}
			else{
				while (operators.Peek()->getValue() != '(' or current == NULL){
					Node* currentOp = operators.Pop();
					finalExpression.Enqueue(currentOp);
				}
				operators.Pop();
			}
		}
	}
	//cout << "fault here? " << endl;
	while (operators.Peek() != NULL){ //pushes remaining operators into final expression
		Node* currentOp = operators.Pop();
		finalExpression.Enqueue(currentOp);
	}

	finalExpression.Printqueue();
	//expression tree algorithm
	Stack treeNodes;
	bool atEnd = false;
	while (!atEnd){//loop through final expression
		Node* current = finalExpression.Dequeue();
		if (current != NULL){
			if (isdigit(current->getValue())){//if current is an operand:
				treeNodes.Push(current);
			}
			else{//if current is an operator:
				current->setRight(treeNodes.Pop());
				current->setLeft(treeNodes.Pop());
				treeNodes.Push(current);
			}
		}
		else{
			atEnd = true;
		}
	}
	//cout << treeNodes.Peek()->getValue() << endl;
	Node* root = treeNodes.Pop();//root will be the final operator
	
	string expressionType;
	bool whileBreak = false;
	while (!whileBreak){
		cout << "Print expression in: (prefix, infix, postfix, quit) " << endl;
		cin >> expressionType; //take in user input for expression type
		if (expressionType == "prefix"){//prefix
			prefixMe(root);
		}
		else if (expressionType == "infix"){//infix
			infixMe(root);
		}
		else if (expressionType == "postfix"){//postfix
			postfixMe(root);
		}
		else if (expressionType == "quit"){
			whileBreak = true;
		}
		cout << endl;
	}

	return 0;
}
