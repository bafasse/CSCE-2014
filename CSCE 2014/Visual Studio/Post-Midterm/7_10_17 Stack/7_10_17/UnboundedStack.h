#pragma once
#pragma once
#ifndef STACK_H
#define STACK_H

// Necessary for print()
#include <iostream>
#include "List.h"
//#include <list>
using namespace std;

// This class implements a simple array-based stack.
// All types that support assignment (=) and optionally
// the stream insertion operator (<<) are supported.
template <class T>
class Stack
{
public:
	// Constructors / Destructors
	

	// Modification
	bool push(const T& value); // add to top of stack
	bool pop(T& value);        // remove from top

							   // Status
	void print() const;
	bool top(T& value) const; // look at top but dont change it (read-only)
	bool isFull() const;
	bool isEmpty() const;

private:
	List<T> mData;
	//static const int DEFAULT_SIZE = 32;

	//T* mData;      // Array containing the actual data
	//int mCapacity; // The size of the array
	//int mTop;      // The index of the top of the stack
};



template <class T>
bool Stack<T>::push(const T& value)
{
	mData.insertHead(value);
	return true;
}

template <class T>
bool Stack<T>::pop(T& value)
{
	return mData.removeHead(value);
}

template <class T>
void Stack<T>::print() const
{
	// Remember, 'mTop' is the index of the top of the stack.
	mData.print();
}

template <class T>
bool Stack<T>::top(T& value) const
{
	return mData.front(value);
}

template <class T>
bool Stack<T>::isFull() const
{
	return false;
}

template <class T>
bool Stack<T>::isEmpty() const
{
	return mData.isEmpty();
}
#endif