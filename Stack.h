#pragma once
#include <iostream>

using namespace std;

template<class Info>

class Stack 
{
private:
	//attributes
	Info* fStackArr;
	int fStackIndex;
	int fSize;

public:
	//constructor
	Stack() 
	{

	};

	// checks the size of stack
	Stack(int aSize) 
	{
		if (aSize <= 0) {
			throw invalid_argument("Invalid size");
		}
		else {
			fStackArr = new Info[aSize];
			fSize = aSize;
			fStackIndex = 0;
		}
	}

	//Destructor
	~Stack() 
	{
		delete[] fStackArr;
	}

	// if the stack is empty
	bool ifNull() const 
	{
		return fStackIndex == 0;
	}

	// the size of stack
	int countIndex() const 
	{
		return fStackIndex;
	}

	// if the stack is full else adds to the stack
	void add(const Info& aObj) 
	{
		if (fStackIndex <= fSize) {
			fStackArr[fStackIndex] = aObj;
			fStackIndex += 1;
		}
		else {
			throw overflow_error("Full");
		}
	}

	//checks the stack count
	void stackCount() 
	{
		if (ifNull()) 
		{
			throw underflow_error("Null");
		}
		else
		{
			fStackIndex -= 1;
		}
	}

	// gives the stack object
	Info& stackReturn() 
	{
		if (ifNull()) 
		{
			throw underflow_error("Null");
		}
		else 
		{
			return fStackArr[fStackIndex - 1];
		}
	}
};