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
	List(const List<T>& orig); // Copy Constructor is always going to be this way
	~List();

	// Modification
	void insertHead(const T& value);
	void insertTail(const T& value);
	void insertSorted(const T& value);

	// Try to remove the head/tail. If we can, its data will be saved
	// in 'value' and true is returned. If we can't (because there
	// is no head/tail), we return false.
	bool removeHead(T& value);
	bool removeTail(T& value);

	// Status
	void print()   const;
	int count()    const;
	bool isEmpty() const;

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
List<T>::List(const List<T>& orig)
{
	// NOTE: This is slow, O(N^2), because we have to
	// iterate over the entire list to insert at the tail.
	// We'll deal with this problem on Thursday.
	mHead = NULL;
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
	Node<T>* tail = mHead;
	while ((tail != NULL) && (tail->next != NULL)) // the order in while loop matters
		tail = tail->next;

	// Create new node
	Node<T>* node = new Node<T>();
	node->data = value;
	node->next = NULL;

	// We have an existing list. Add to the end.
	if (tail != NULL)
		tail->next = node;

	// The list was initially empty. We need to set mHead.
	else mHead = node;
}

template <class T>
void List<T>::insertSorted(const T& value)
{
	if (mHead == NULL || mHead->data >= value)
		insertHead(value);
	else
	{
		Node<T>* cur = mHead;
		Node<T>* prev = mHead;
		while ((cur != NULL) && (cur->data < value))
		{
			prev = cur;
			cur = cur->next;
		}
		Node<T>* node = new Node<T>();
		node->next = cur;
		prev->next = node;
		node->data = value;
	}
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