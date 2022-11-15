#pragma once
#include <iostream>
#include "SinglyLinkedNode.h"
#include "Itr.h"

using namespace std;
//template class
template<class Info>

//child class inheriting from parent template class
class SinglyLinkedList : public Iterator<Info> 
{
private:
	SinglyLinkedNode<Info> fSingly_node;
	SinglyLinkedNode<Info>* fPtr_;

public:
	// Constructor
	SinglyLinkedList() {

	}

	//Destructor
	virtual ~SinglyLinkedList() {

	}

	/// Overloaded constructor
	SinglyLinkedList(SinglyLinkedNode<Info>& aObject) 
	{
		fSingly_node = aObject;
		fPtr_ = &fSingly_node;
		SinglyLinkedNode<Info>* lDefaulPointerOfObject = &aObject;

		SinglyLinkedNode<Info>* lMovingPointer = &aObject;
		if (lMovingPointer->next != nullptr) 
		{
			while (lMovingPointer->next != nullptr) 
			{
				fPtr_->next = lMovingPointer->next;
				lMovingPointer = lMovingPointer->next;
				fPtr_ = fPtr_->next;
			}
			fPtr_ = &fSingly_node;
			lMovingPointer = lDefaulPointerOfObject;
		}
		else 
		{
			fSingly_node.next = nullptr;
		}
	}

	// Accessor
	SinglyLinkedNode<Info>& getIterPointer() 
	{
		return *fPtr_;
	}

	// Accessor
	void setIterPointer(SinglyLinkedNode<Info>& aNode) 
	{
		fPtr_ = &aNode;
	}

	// * operator overload
	Info operator*() override 
	{
		return fPtr_->object;
	}

	// ++ operator overload
	Iterator<Info>& operator++() override 
	{
		fPtr_ = fPtr_->next;
		return *this;
	}

	// ++(int) operator overload
	Iterator<Info>& operator++(int) override 
	{
		SinglyLinkedList* temp = new SinglyLinkedList(*this);
		++(*this);
		return *temp;
	}

	// -- operator overload
	Iterator<Info>& operator--() override 
	{ 
		return *this; 
	}

	// --(int) operator overload
	Iterator<Info>& operator--(int) override 
	{ 
		return *this; 
	}

	// == operator overload
	bool operator== (Iterator<Info>& aOther) override 
	{
		SinglyLinkedList* castedIterator = dynamic_cast<SinglyLinkedList*>(&aOther);
		return (fPtr_ == castedIterator->fPtr_);
	}

	// points to beginning of the array
	Iterator<Info>& begin() override { 
		return *this; 
	}

	// points to end of the array
	Iterator<Info>& end() const override 
	{
		SinglyLinkedList* temp = new SinglyLinkedList(*this);
		while (temp->fPtr_->next != nullptr) 
		{
			temp->fPtr_ = temp->fPtr_->next;
		}
		return *temp;
	}

};