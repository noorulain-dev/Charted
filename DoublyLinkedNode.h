#pragma once
#include <iostream>
using namespace std;

template<class Info>

class DoublyLinkedNode 
{
public:
	//creating a type definition to shorten the code for later use
	typedef DoublyLinkedNode<Info> Node;

private:
	//attributes
	Info fValue;
	Node* fNext;
	Node* fPrevious;

public:
	//creating a nil static node
	static Node NIL;

	// constructor
	DoublyLinkedNode() 
	{
		fValue = Info();
		fNext = &NIL;
		fPrevious = &NIL;
	}

	// constructor
	DoublyLinkedNode(const Info& aValue) 
	{
		fValue = aValue;
		fNext = &NIL;
		fPrevious = &NIL;
	}

	// add a node in the previous position of the called node
	void prepend(Node& aNode) 
	{
		aNode.fNext = this;
		if (fPrevious != &NIL) {
			aNode.fPrevious = fPrevious;
			fPrevious->fNext = &aNode;
		}
		fPrevious = &aNode;
	}

	// add a node in the next position of the called node
	void append(Node& aNode) 
	{
		aNode.fPrevious = this;
		if (fNext != &NIL) {
			aNode.fNext = fNext;
			fNext->fPrevious = &aNode;
		}
		fNext = &aNode;
	}

	// delete a node
	void remove() 
	{
		if (fNext == &NIL) {
			fPrevious->fNext = &NIL;
		}
		else if (fPrevious == &NIL) {
			fNext->fPrevious = &NIL;
		}
		else {
			fPrevious->fNext = fNext;
			fNext->fPrevious = fPrevious;
		}
	}

	//Accessors
	//getters and setters

	//returns value of node
	Info& getValue() 
	{
		return fValue;
	}

	//returns the next node
	Node* getNext() const 
	{
		return fNext;
	}

	//sets the next node
	void setNext(Node* aNode) 
	{
		fNext = aNode;
	}

	//returns the previous node
	Node* getPrevious() const 
	{
		return fPrevious;
	}

	//sets the previous node
	void setPrevious(Node* aNode) 
	{
		fPrevious = aNode;
	}

	//returns the first node
	Node& getFirstNode() 
	{
		Node* ptr = this;
		while (ptr->getPrevious() != &NIL) 
		{
			ptr = (*ptr).fPrevious;
		}
		return *ptr;
	}

	//sets the first node
	void setFirstNode(Node& aNode) 
	{
		Node* ptr = this;
		while (ptr->getPrevious() != &NIL) 
		{
			ptr = (*ptr).fPrevious;
		}
		*ptr = aNode;
	}

	//returns the end node
	Node& getEndNode() 
	{
		Node* ptr = this;
		while (ptr->getNext() != &NIL) 
		{
			ptr = (*ptr).fNext;
		}
		return *ptr;
	}

	bool operator== (Info& aOther) 
	{
		return (fValue == aOther);
	}
};
template<class Info>
DoublyLinkedNode<Info> DoublyLinkedNode<Info>::NIL;