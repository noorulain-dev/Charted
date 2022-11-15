#pragma once
#include <iostream>

using namespace std;
//template class
template <class T>
class SinglyLinkedNode 
{
public:
	T object;
	SinglyLinkedNode* next;

	// Constructor
	SinglyLinkedNode() {

	}

	//Destructor
	~SinglyLinkedNode() {

	};

	// Overloaded constructor for the first node
	SinglyLinkedNode(T x) 
	{
		object = x;
		next = nullptr;
	}

	/// Overloaded constructor for rest of the nodes
	SinglyLinkedNode(T x, SinglyLinkedNode* ptr) 
	{
		object = x;
		next = ptr;
	}

	// adds node
	void addNode(T value, SinglyLinkedNode<T>* before) 
	{
		SinglyLinkedNode<T>* newNode = new SinglyLinkedNode<T>(value);
		newNode->next = before->next;
		before->next = newNode;
	}

	// add a node in first position
	void addNodeAtEnd(T value, SinglyLinkedNode<T>*& firstNode) 
	{
		SinglyLinkedNode<T>* newNode = new SinglyLinkedNode<T>(value,
			firstNode);
		firstNode = newNode;
	}

	// add a node in last position
	void addNodeAtStart(T value, SinglyLinkedNode<T>* firstNode) 
	{
		SinglyLinkedNode<T>** newNodePtr = &firstNode;
		while (*newNodePtr != nullptr) {
			newNodePtr = &((*newNodePtr)->next);
		}
		*newNodePtr = new SinglyLinkedNode<T>(value);
	}
};