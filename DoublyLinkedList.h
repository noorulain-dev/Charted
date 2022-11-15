#pragma once
#include <iostream>
#include "Itr.h"
#include "DoublyLinkedNode.h"

using namespace std;

//template class
template<class Info>

//child class inheriting from parent template class
class DoublyLinkedList : public Iterator<Info> 
{
private:

	//attributes
	DoublyLinkedNode<Info> fDoubly_node;
	DoublyLinkedNode<Info>* fDoubly_ptr;

public:
	//Constructor
	DoublyLinkedList() {

	}

	//Destructor
	virtual ~DoublyLinkedList() {

	}

	// Overloaded constructor
	DoublyLinkedList(DoublyLinkedNode<Info>& aObject) 
	{
		fDoubly_node = aObject;
		fDoubly_node.setPrevious(nullptr);
		fDoubly_ptr = &fDoubly_node;
		DoublyLinkedNode<Info>* indexPtr = &(aObject);
		if (indexPtr->getNext() != nullptr) 
		{
			DoublyLinkedNode<Info> previousNode = fDoubly_node;
			while (indexPtr->getNext() != &previousNode.NIL) 
			{
				fDoubly_ptr->setNext(indexPtr->getNext());
				indexPtr = indexPtr->getNext();
				fDoubly_ptr = fDoubly_ptr->getNext();
				*fDoubly_ptr->getPrevious() = previousNode;
				previousNode = *fDoubly_ptr;
			}
			fDoubly_ptr = &fDoubly_node;
		}
		else 
		{
			fDoubly_node.setNext(nullptr);
		}
	}

	//  * operator overload
	Info operator*() override 
	{
		return fDoubly_ptr->getValue();
	}

	// Accessor
	// Setter
	void setDoublyPtr(DoublyLinkedNode<Info>& aNode) 
	{
		fDoubly_ptr = &aNode;
	}

	/// ++ operator overload
	Iterator<Info>& operator++() override 
	{
		fDoubly_ptr = fDoubly_ptr->getNext();
		return *this;
	}

	// ++(int operator overload)
	Iterator<Info>& operator++(int) override 
	{
		DoublyLinkedList* temp = new DoublyLinkedList(*this);
		++(*this);
		return *temp;
	}

	// -- operator overload
	Iterator<Info>& operator--() override 
	{
		fDoubly_ptr = fDoubly_ptr->getPrevious();
		return *this;
	}

	// --(int) operator overload
	Iterator<Info>& operator--(int) override 
	{
		DoublyLinkedList* temp = new DoublyLinkedList(*this);
		--(*this);
		return *temp;
	}

	// == operator overload
	bool operator== (Iterator<Info>& aOther) override 
	{
		DoublyLinkedList* castedIterator = dynamic_cast<DoublyLinkedList*>(&aOther);
		return (fDoubly_ptr == castedIterator->fDoubly_ptr);
	}

	// points to the beginning of the array
	Iterator<Info>& begin() override 
	{
		DoublyLinkedList* temp = new DoublyLinkedList(*this);
		while (temp->fDoubly_ptr->getPrevious() != &(temp->fDoubly_node.NIL)) 
		{
			temp->fDoubly_ptr = temp->fDoubly_ptr->getPrevious();
		}
		return *temp;
	}

	// points to the end of the array
	Iterator<Info>& end() const override 
	{
		DoublyLinkedList* temp = new DoublyLinkedList(*this);
		while (temp->fDoubly_ptr->getNext() != &(temp->fDoubly_node.NIL)) 
		{
			temp->fDoubly_ptr = temp->fDoubly_ptr->getNext();
		}
		return *temp;
	}
};