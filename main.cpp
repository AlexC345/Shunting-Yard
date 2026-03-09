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

void infixMe(Node* current){
	Node* left = current->getLeft();
	Node* right = current->getRight();
	cout << "(";
	if (!isdigit(left->getValue())){
		infixMe(left);
	}
	else{
		cout << left->getValue();
	}
	cout << current->getValue();
	if (!isdigit(right->getValue())){
		infixMe(right);
	}
	else{
		cout << right->getValue();
	}
	cout << ")";
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
	cout << treeNodes.Peek()->getValue() << endl;
	Node* root = treeNodes.Pop();//root will be the final operator
	
	string expressionType;
	cout << "Print expression in: (prefix, infix, postfix) " << endl;
	cin >> expressionType; //take in user input for expression type
	if (expressionType == "prefix"){
			
	}
	else if (expressionType == "infix"){
		infixMe(root);
	}
	else if (expressionType == "postfix"){

	}

	return 0;
}
