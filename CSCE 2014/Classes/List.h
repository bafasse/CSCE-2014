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
	//Linked Lists are not good for large amounts of data
	T data;
	Node<T>* next;
	Node<T>* prev;
};

// Defines the interface for our List class. Because the
// nodes are templated, the List class must be too.
template <class T>
class List
{
public:

	// Constructors / Destructors
	List();
	List(const List<T>& orig);
	~List();

	// Modification
	void insertHead(const T& value);
	void insertTail(const T& value);

	// Try to remove the head/tail. If we can, its data will be saved
	// in 'value' and true is returned. If we can't (because there
	// is no head/tail), we return false.
	bool removeHead(T& value);
	bool removeTail(T& value);
	bool remove(const T& value);

	Node<T>* search(const T& value) const;

	// Status
	void print()        const;
	void printReverse() const;
	int count()         const;
	bool isEmpty()      const;

private:
	Node<T>* mHead;
	Node<T>* mTail;
};

//----------------------------------------------------------------//

template <class T>
List<T>::List()
{
	mHead = NULL;
	mTail = NULL;
}

template <class T>
List<T>::List(const List<T>& orig)
{
	// We have the same code as from List2.h, but now that we've
	// made insertTail() an O(1) operation instead of an O(N)
	// operation, the runtime for creating a copy drops from O(N^2)
	// to O(N). Cool!
	mHead = NULL;
	mTail = NULL;
	Node<T>* cur = orig.mHead;
	while (cur != NULL)
	{
		insertTail(cur->data);
		cur = cur->next;
	}
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

// NOTICE THE MIRRORED BEHAVIOR FOR insertHead()/insertTail().

template <class T>
void List<T>::insertHead(const T& value)
{
	// Create new node
	Node<T>* node = new Node<T>();
	node->data = value;
	node->next = mHead;
	node->prev = NULL;

	// List is empty - Update tail
	if (mHead == NULL)
		mTail = node;

	// List is not empty - Update head->prev
	else mHead->prev = node;

	mHead = node;
}

template <class T>
void List<T>::insertTail(const T& value)
{
	// Create new node
	Node<T>* node = new Node<T>();
	node->data = value;
	node->prev = mTail;
	node->next = NULL;

	// List is empty - Update head
	if (mTail == NULL)
		mHead = node;

	// List is not empty - Update tail->next
	else mTail->next = node;

	mTail = node;
}

// NOTICE THE MIRRORED BEHAVIOR FOR removeHead()/removeTail().

template <class T>
bool List<T>::removeHead(T& value)
{
	// No head - nothing we can do
	if (mHead == NULL)
		return false;

	// Only one node - Update both head and tail
	else if (mHead->next == NULL)
	{
		value = mHead->data;
		delete mHead;
		mHead = NULL;
		mTail = NULL;
		return true;
	}

	// There's at least two nodes left
	else
	{
		Node<T>* cur = mHead;
		value = cur->data;
		mHead = mHead->next;
		mHead->prev = NULL;

		delete cur;
		return true;
	}
}

template <class T>
bool List<T>::removeTail(T& value)
{
	// No tail - nothing we can do
	if (mTail == NULL)
		return false;

	// Only one node - Update both head and tail
	else if (mTail->prev == NULL)
	{
		value = mTail->data;
		delete mTail;
		mHead = NULL;
		mTail = NULL;
		return true;
	}

	// There's at least two nodes left
	else
	{
		Node<T>* cur = mTail;
		value = cur->data;
		mTail = mTail->prev;
		mTail->next = NULL;

		delete cur;
		return true;
	}
}

template <class T>
bool List<T>::remove(const T& value)
{
	Node<T>* cur = search(value);
	T data;

	if (cur == NULL)
		return false;

	else if (cur == mHead)
	{
		removeHead(data);
		return true;
	}
	else if (cur == mTail)
	{
		removeTail(data);
		return true;
	}
	else
	{	
		Node<T>* left  = cur->prev;
		Node<T>* right = cur->next;

		left->next = right;
		right->prev = left;

		delete cur;
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

// NOTICE THE MIRRORED BEHAVIOR FOR print()/printReverse().

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
void List<T>::printReverse() const
{
	Node<T>* cur = mTail;
	while (cur != NULL)
	{
		cout << cur->data << " ";
		cur = cur->prev;
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
