#pragma once
#ifndef QUEUE_H
#define QUEUE_H

// Necessary for print()
#include <iostream>
using namespace std;

// This class implements a simple array-based queue.
// Note that this implementation uses an inefficient copy-based
// remove() operation. A circular array is used in Queue2.h.
// All types that support assignment (=) and optionally
// the stream insertion operator (<<) are supported.
template <class T>
class Queue
{
public:
	// Constructors / Destructors
	Queue();
	Queue(const int size);
	Queue(const Queue<T>& orig);
	~Queue();

	// Modification
	bool insert(const T& value);
	bool remove(T& value);

	// Status
	void print()         const;
	bool front(T& value) const;
	bool isFull()        const;
	bool isEmpty()       const;

private:
	static const int DEFAULT_SIZE = 32;

	T* mData;      // Array containing the actual data
	int mCapacity; // The size of the array
	int mEnd;      // The index of the end of the queue
	int mFront;
	int mCount;
};

template <class T>
Queue<T>::Queue()
{
	mData = new T[DEFAULT_SIZE];
	mCapacity = DEFAULT_SIZE;
	mEnd = -1;
	mFront = 0;
	mCount = 0;
}

template <class T>
Queue<T>::Queue(const int size)
{
	mData = new T[size];
	mCapacity = size;
	mEnd = -1;
	mFront = -1;
	mCount = -1;
}

template <class T>
Queue<T>::Queue(const Queue<T>& orig)
{
	// Create a new array big enough to hold everything in 'orig'
	mData = new T[orig.mCapacity];
	mCapacity = orig.mCapacity;
	mEnd = orig.mEnd;
	mFront = orig.mFront;
	mCount = orig.mCount;

	// Copy the data over
	for (int i = 0; i < mCapacity; ++i)
		mData[i] = orig.mData[i];
}

template <class T>
Queue<T>::~Queue()
{
	// Take care of deallocation of the dynamically allocated array
	delete[] mData;
	mData = NULL;
}

template <class T>
bool Queue<T>::insert(const T& value)
{
	// Ensure we're still in the array
	if (!isFull())
	{
		mEnd++;
		mData[mEnd] = value;
		return true;
	}

	// The queue must be full.
	else return false;
}

template <class T>
bool Queue<T>::remove(T& value)
{
	// Let front() do most of the work. If it returns false,
	// the queue was empty. If it returns true, we have
	// the front value stored already, so we just need to
	// copy the remaining elements down one cell and update
	// mEnd.
	if (front(value))
	{
		// Shift all the data down one index
		for (int i = 0; i < mEnd; ++i)
			mData[i] = mData[i + 1];

		// Move mFront forward one
		// Decrement Count

		mEnd--;
	}
	else return false;
}

template <class T>
void Queue<T>::print() const
{
	// Remember, the start of the queue will be somewhere
	// in the middle of the array (in general)
	int index = mFront;

	for (int i = 0; i < mCount; i++)
	{
		cout << mData[index] << " ";
		index = (index + 1) % mCapacity;
	}
	cout << endl;
}


template <class T>
bool Queue<T>::front(T& value) const
{
	// Make sure the queue has content first
	if (!isEmpty())
	{
		value = mData[mFront];
		return true;
	}

	// The queue was empty, so there is no front
	else return false;
}

template <class T>
bool Queue<T>::isFull() const
{
	return mCount >= mCapacity;
}

template <class T>
bool Queue<T>::isEmpty() const
{
	return mCount <= 0;
}

#endif