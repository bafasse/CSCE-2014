#pragma once
#ifndef HEAP_H
#define HEAP_H

// Necessary for print()
#include <algorithm>
#include <iostream>
using namespace std;

//-------------------------------------------------------//
// Free functions                                        //
//-------------------------------------------------------//

// This function is given an array and a starting index.
// The array is interpreted as a possibly invalid binary
// max-heap. This function will repeatedly swap nodes with 
// their parents until the heap property has been restored,
// moving up the tree.
template <class T>
void shuffleUp(T* data, const int start)
{
	int child = start;
	int parent = (child - 1) / 2;
	while (child > 0 && data[child] > data[parent])
	{
		swap(data[child], data[parent]);
		child = parent;
		parent = (parent - 1) / 2;
	}
}

// This function is given an array and a starting index.
// The array is interpreted as a possibly invalid binary
// max-heap. This function will repeatedly swap parents with 
// the largest of their children until the heap property 
// has been restored, moving down the tree.
template <class T>
void shuffleDown(T* data, const int size, const int start)
{
	int parent = start;
	int largest = -1;
	while (parent != largest)
	{
		largest = parent;

		// Examine the left child
		int left = 2 * parent + 1;
		if (left < size && data[left] > data[largest])
			largest = left;

		// Examine the right child
		int right = 2 * parent + 2;
		if (right < size && data[right] > data[largest])
			largest = right;

		// Swap parent with largest child if necessary
		if (parent != largest)
		{
			swap(data[parent], data[largest]);
			parent = largest;
			largest = -1;
		}
	}
}

//-------------------------------------------------------//
// Heap Class                                            //
//-------------------------------------------------------//

// This class implements a fixed-size array-based Max-Heap. 
// Insertion and removal are guaranteed to be O(lg N). All
template <class T>
class Heap
{
public:
	// Constructors / Destructors
	Heap();
	Heap(const int capacity);
	Heap(const Heap<T>& orig);
	~Heap();

	// Heap modification
	bool insert(const T& value);
	bool remove(T& value);
	bool replace(const T& newValue, T& maxValue);

	// Heap status
	bool top(T& value) const;
	bool isFull()      const;
	bool isEmpty()     const;
	int getSize()      const;
	void print()       const;

private:
	static const int DEFAULT_SIZE = 32;

	T* mData;      // The array that stores the heap
	int mCapacity; // The size of the underlying array
	int mSize;     // The number of elements currently in the heap
};

//-------------------------------------------------------//

template <class T>
Heap<T>::Heap()
{
	mData = new T[DEFAULT_SIZE];
	mCapacity = DEFAULT_SIZE;
	mSize = 0;
}

template <class T>
Heap<T>::Heap(const int capacity)
{
	mData = new T[capacity];
	mCapacity = capacity;
	mSize = 0;
}

template <class T>
Heap<T>::Heap(const Heap<T>& orig)
{
	mData = new T[orig.mCapacity];
	mCapacity = orig.mCapacity;
	mSize = orig.mSize;

	for (int i = 0; i < mCapacity; ++i)
		mData[i] = orig.mData[i];
}

template <class T>
Heap<T>::~Heap()
{
	delete[] mData;
	mData = NULL;
}

//-------------------------------------------------------//

template <class T>
bool Heap<T>::insert(const T& value)
{
	// There is no more room in the heap
	if (isFull()) return false;

	// Insert the new data element in the first available cell
	mData[mSize] = value;
	++mSize;

	// Shuffle up until we've restored the heap property.
	shuffleUp(mData, mSize - 1);

	return true;
}

template <class T>
bool Heap<T>::remove(T& value)
{
	// Ensure there is a heap to remove from. If so, we save
	// top the topmost element.
	if (!top(value)) return false;

	// Swap the first and last elements, then
	// remove the last cell
	swap(mData[0], mData[mSize - 1]);
	mSize--;

	// Shuffle down until we've restored the heap property.
	shuffleDown(mData, mSize, 0);

	return true;
}

//-------------------------------------------------------//

template <class T>
bool Heap<T>::replace(const T& newValue, T& maxValue)
{
	if (!top(maxValue)) return false;
	
	else
	{
		mData[0] = newValue;
		shuffleDown(mData, mSize, 0);
		return true;
	}
}
//-------------------------------------------------------//

template <class T>
bool Heap<T>::top(T& value) const
{
	if (isEmpty()) return false;
	else
	{
		value = mData[0];
		return true;
	}
}

template <class T>
bool Heap<T>::isFull() const
{
	return mSize >= mCapacity;
}

template <class T>
bool Heap<T>::isEmpty() const
{
	return mSize == 0;
}

template <class T>
int Heap<T>::getSize() const
{
	return mSize;
}

template <class T>
void Heap<T>::print() const
{
	for (int i = 0; i < mSize; ++i)
		cout << mData[i] << " ";
	cout << endl;
}

#endif