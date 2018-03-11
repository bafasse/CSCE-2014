#pragma once
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

	// Constructors / Destructors
	List();
	~List();

	// Modification
	void insertHead(const T& value);

	// Try to remove the head. If we can, its data will be saved
	// in 'value' and true is returned. If we can't (because there
	// is no head), we return false.
	bool removeHead(T& value);

	// Status
	void print()   const;
	int count()    const;
	bool isEmpty() const;
	void move(List<T>& src, List<T>& dest);

private:
	Node<T>* mHead;
};

//----------------------------------------------------------------//

template <class T>
List<T>::List()
{
	mHead = NULL;
}

template <class T>
List<T>::~List()
{
	T value;
	while (!isEmpty())
	{
		removeHead(value);
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
