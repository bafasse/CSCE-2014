#pragma once
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// Necessary for print()
#include <cmath>
#include <iostream>
using namespace std;

//===================================================//
// Sample Hash Functions                             //
//===================================================//

int dash(int value)
{
	return value;
}

int hashFn(int value)
{
	return abs(value * 7);
}

//===================================================//
// The Hash Table Class Definition                   //
//===================================================//
template <class T>
class HashTable
{
public:
	// Constructors / Destructors
	HashTable();
	HashTable(const int capacity);
	HashTable(const HashTable<T>& orig);
	~HashTable();

	// Modification
	bool insert(const T& value); // value = key
	bool search(const T& value);
	bool remove(const T& value);

	// Status
	bool isFull() const;
	bool isEmpty() const;
	void print() const;
	int getSize() const;

private:
	static const int DEFAULT_SIZE = 32;
	static const char FULL = 'F';
	static const char EMPTY = 'E';
	static const char AVAILABLE = 'A';

	T* mData;
	char* mState;
	int mCapacity;
	int mSize;

	int indexOf(const T& value) const;
	int auxHash(const int dash) const;
};

//===================================================//
// Hash Table Class Implementations                  //
//===================================================//

template <class T>
HashTable<T>::HashTable()
{
	mData = new T[DEFAULT_SIZE];
	mState = new char[DEFAULT_SIZE];
	mCapacity = DEFAULT_SIZE;
	mSize = 0;

	for (int i = 0; i < mCapacity; ++i)
		mState[i] = EMPTY;
}

template <class T>
HashTable<T>::HashTable(const int capacity)
{
	mData = new T[capacity];
	mState = new char[capacity];
	mCapacity = capacity;
	mSize = 0;

	for (int i = 0; i < mCapacity; ++i)
		mState[i] = EMPTY;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& orig)
{
	mData = new T[orig.mCapacity];
	mState = new char[orig.mCapacity];
	mCapacity = orig.mCapacity;
	mSize = orig.mSize;

	for (int i = 0; i < mCapacity; ++i)
	{
		mData[i] = orig.mData[i];
		mState[i] = orig.mState[i];
	}
}

template <class T>
HashTable<T>::~HashTable()
{
	delete[] mData;
	delete[] mState;
	mData = NULL;
	mState = NULL;
}

//===================================================//

// Linear probing
template <class T>
int HashTable<T>::auxHash(const int dash) const
{
	return dash + 1;
}

// This is a helper function for the search() and remove() functions. 
// It will search the table for a cell with the given value and return
// the index at which that cell was found. If the given value is not
// present, -1 will be returned.
template <class T>
int HashTable<T>::indexOf(const T& value) const
{
	// Determine where to start looking
	int index = dash(value) % mCapacity;
	for (int i = 0; i < mCapacity; ++i)
	{
		// If we found what we were looking for, return the index
		if (mState[index] == FULL && mData[index] == value)
			return index;

		// If we find an empty cell, we can simply stop
		else if (mState[index] == EMPTY)
			return -1;

		// Apply collision resolution scheme
		else index = auxHash(index) % mCapacity;
	}

	// We wrapped back around to the original index, so we can stop.
	return -1;
}

//===================================================//

template <class T>
bool HashTable<T>::insert(const T& value)
{
	// We can't insert if the table is full
	if (isFull()) return false;

	// If 'value' is already in the table, we don't need
	// to do any more work.
	else if (search(value)) return true;

	// This value was not in the table already
	else
	{
		// Determine the first available cell
		int index = dash(value) % mCapacity;
		while (mState[index] == FULL)
			index = auxHash(index) % mCapacity;

		// Perform the insertion
		mState[index] = FULL;
		mData[index] = value;
		mSize++;

		return true;
	}
}

template <class T>
bool HashTable<T>::search(const T& value)
{
	return indexOf(value) != -1;
}

template <class T>
bool HashTable<T>::remove(const T& value)
{
	int index = indexOf(value);
	if (index != -1)
	{
		// Cells that have been removed are AVAILABLE. They can be reused
		// in another insertion, but they cannot be used as stopping
		// criteria for searches.
		mState[index] = AVAILABLE;
		mSize--;
		return true;
	}
	else return false;
}

//===================================================//

template <class T>
bool HashTable<T>::isFull() const
{
	return mSize >= mCapacity;
}

template <class T>
bool HashTable<T>::isEmpty() const
{
	return mSize <= 0;
}

template <class T>
void HashTable<T>::print() const
{
	for (int i = 0; i < mCapacity; ++i)
	{
		// We should only print the cells that are occupied
		if (mState[i] == FULL)
			cout << mData[i] << " ";
		else cout << "x ";
	}
	cout << endl;
}

template <class T>
int HashTable<T>::getSize() const
{
	return mSize;
}

#endif