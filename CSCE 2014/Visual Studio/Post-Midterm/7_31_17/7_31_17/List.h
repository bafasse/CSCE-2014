#pragma once
// Purpose: An implementation of a simple singly-linked list.
//          This version uses only a head pointer. 
// Author:  Jon C. Hammer
// Date:    6/28/17

#ifndef LIST_H
#define LIST_H

// Required for print()
#include <iostream>
using namespace std;

// Represents a single Node in the list. We use templates so
// our list will work with any type, as long as it supports
// assignment (=), test for equality (!=), and optionally, 
// the stream operator (<<).
template <class T>
struct Node
{
	T data;
	Node<T>* next;
};

// Defines the interface for our List class. Because the
// nodes are templated, the List class must be too.
template <class T>
class List
{
public:

	// Constructors
	List();
	List(const List<T>& orig);
	~List();

	// Modification
	void insertHead(const T& value);
	void insertTail(const T& value);
	bool remove(const T& value);
	bool removeHead(T& value);
	bool removeTail(T& value);

	// Status
	Node<T>* search(const T& value) const;
	void clone(List<T>& dest) const;
	void print()   const;
	int count()    const;
	bool isEmpty() const;

private:
	Node<T>* mHead;
};

template <class T>
List<T>::List()
{
	mHead = NULL;
}

template <class T>
List<T>::List(const List<T>& orig)
{
	// Easy implementation - O(N^2), though. The runtime
	// reduces to O(N) if we have a tail pointer, though.
	mHead = NULL;
	Node<T>* cur = orig.mHead;
	while (cur != NULL)
	{
		insertTail(cur->data);
		cur = cur->next;
	}

	// Advanced implementation - O(N), even without tail
	// pointer. We use a dummy head node to do the work,
	// then we delete the dummy node when we're done.
	/*Node<T>* copy = new Node<T>();
	mHead         = copy;
	Node<T>* cur  = orig.mHead;
	while (cur != NULL)
	{
	copy->next = new Node<T>();
	copy       = copy->next;
	copy->data = cur->data;
	copy->next = NULL;

	cur = cur->next;
	}

	copy  = mHead;
	mHead = copy->next;
	delete copy;*/
}

template <class T>
List<T>::~List()
{
	while (mHead != NULL)
	{
		Node<T>* ptr = mHead;
		mHead = mHead->next;
		delete ptr;
	}
}

template <class T>
void List<T>::insertHead(const T& value)
{
	// Create new node
	Node<T>* node = new Node<T>();
	node->data = value;
	node->next = mHead;

	// Insert into the list
	mHead = node;
}

template <class T>
void List<T>::insertTail(const T& value)
{
	// Find the tail node
	Node<T>* ptr = mHead;
	while ((ptr != NULL) && (ptr->next != NULL))
		ptr = ptr->next;

	// Create new node
	Node<T>* node = new Node<T>();
	node->data = value;
	node->next = NULL;

	// We have an existing list. Add to the end.
	if (ptr != NULL)
	{
		ptr->next = node;
	}

	// The list was initially empty. We need to set mHead.
	else
	{
		//node->next = mHead;
		mHead = node;
	}
}

template <class T>
bool List<T>::remove(const T& value)
{
	Node<T>* cur = mHead;
	Node<T>* prev = mHead;
	while ((cur != NULL) && (cur->data != value))
	{
		prev = cur;
		cur = cur->next;
	}

	// 'value' wasn't in the list.
	if (cur == NULL)
		return false;

	// Remove 'cur' from the list rerouting the pointers
	if (cur == mHead)
		mHead = cur->next;
	else prev->next = cur->next;

	// Deallocate the memory associated with 'cur'.
	delete cur;
	return true;
}

template <class T>
bool List<T>::removeHead(T& value)
{
	// No head - nothing we can do
	if (mHead == NULL)
		return false;

	// There's at least one node, so we can remove it.
	else
	{
		Node<T>* cur = mHead;
		value = cur->data;
		mHead = mHead->next;
		delete cur;
		return true;
	}
}

template <class T>
bool List<T>::removeTail(T& value)
{
	// No tail - nothing we can do
	if (mHead == NULL)
		return false;

	// There's at least one node, so we can remove it.
	else
	{
		// Find the tail node
		Node<T>* cur = mHead;
		Node<T>* prev = mHead;
		while ((cur != NULL) && (cur->next != NULL))
		{
			prev = cur;
			cur = cur->next;
		}
		value = cur->data;

		// There are at least 2 nodes
		if (cur != mHead)
		{
			prev->next = NULL;
			delete cur;
		}

		// There is only one node in the list
		else
		{
			delete mHead;
			mHead = NULL;
		}
		return true;
	}
}

template <class T>
Node<T>* List<T>::search(const T& value) const
{
	Node<T>* cur = mHead;
	while ((cur != NULL) && (cur->data != value))
		cur = cur->next;

	// If cur != NULL, we've found what we're looking for
	// and 'cur' tells us where to find it. If cur == NULL,
	// 'value' wasn't in the list.
	return cur;
}

template <class T>
void List<T>::clone(List<T>& dest) const
{
	Node<T>* cur = mHead;
	while (cur != NULL)
	{
		dest.insertTail(cur->data);
		cur = cur->next;
	}
}

template <class T>
void List<T>::print() const
{
	Node<T>* cur = mHead;
	while (cur != NULL)
	{
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}

template <class T>
int List<T>::count() const
{
	int counter = 0;
	Node<T>* cur = mHead;

	while (cur != NULL)
	{
		counter++;
		cur = cur->next;
	}
	return counter;
}

template <class T>
bool List<T>::isEmpty() const
{
	return (mHead == NULL);
}

#endif