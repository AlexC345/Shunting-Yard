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
			cout << current->getValue() << endl;
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
			if (first->getNext(0 != NULL){
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
			cout << current->getValue() << endl;
			current = current->getNext();
		}
		cout << endl;
	}
};

int main(){
	string expression;
	cout << "Enter expression: ";
	cin >> expression;
	Queue inputExpression;
	Stack operators;
	Stack finalExpression;
	for (int i = 0; i < expression.length(); i++){
		inputExpression.Enqueue(new Node(expression[i]));
	}
	inputExpression.Printqueue();
	for (int i = 0; i < expression.length(); i++){
		Node* current = inputExpression.Dequeue();//deletes and remembers what was deleted
		if (isdigit(current->getValue())){
			finalExpression.Push(current);
		}
		else{
			if (current->getValue() != ')'){
				operators.Push(current);
			}
			else{
				while (operators.Peek()->getValue() != '('){
					Node* currentOp = operators.Pop();
					finalExpression.Push(currentOp);
				}
				operators.Pop();
			}
		}
	}
	cout << "fault here? " << endl;
	while (operators.Peek() != NULL){
		Node* currentOp = operators.Pop();
		finalExpression.Push(currentOp);
	}


	operators.Printstack();
	finalExpression.Printstack();
	
	
	return 0;
}
