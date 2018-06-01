#pragma once
#include "List.h"
#include <iostream>
using namespace std;

int dash(int value)
{
	return value;
}

int auxHash(const int hash)
{
	// all integers < p, where p  is prime are coprime to p
	return hash + 5;
}

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
	bool insert(const T& value);
	bool remove(const T& value);

	// Status
	bool search(const T& value) const;
	bool isFull()  const;
	bool isEmpty() const;
	void print()   const;
	int getSize()  const;

private:
	static const int DEFAULT_SIZE = 32;

	List<T>* mData;  // An array of lists
	int mCapacity;   // The size of the array
	int mSize;       // The number of elements total
};

// ==================================================
// --------------------------------------------------
// ==================================================

template <class T>
HashTable<T>::HashTable()
{
	mData = new List<T>[DEFAULT_SIZE];
	mCapacity = DEFAULT_SIZE;
	mSize = 0;
}

template <class T>
HashTable<T>::HashTable(const int capacity)
{
	mData = new List<T>[capacity];
	mCapacity = capacity;
	mSize = 0;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& orig)
{
	mData = new List<T>[orig.mCapacity];
	mCapacity = orig.mCapacity;
	mSize = orig.mSize;

	for (int i = 0; i < mCapacity; ++i)
		orig.mData[i].clone(mData[i]);
}

template <class T>
HashTable<T>::~HashTable()
{
	delete[] mData;
	mData = NULL;
}

// ==================================================
// --------------------------------------------------
// ==================================================

template <class T>
bool HashTable<T>::insert(const T& value)
{
	if (search(value)) return true;

	int temp = value % mCapacity;
	mData[temp].insertHead(value);
	mSize++;
	return true;
}

template <class T>
bool HashTable<T>::remove(const T& value)
{
	int temp = value % mCapacity;
	if (mData[temp].remove(value))
	{
		mSize--;
		return true;
	}
	else return false;
}

// ==================================================
// --------------------------------------------------
// ==================================================

template <class T>
bool HashTable<T>::search(const T& value) const
{
	int temp = value % mCapacity;
	return mData[temp].search(value) != NULL;
}

template <class T>
bool HashTable<T>::isFull()  const
{
	return false;
}

template <class T>
bool HashTable<T>::isEmpty() const
{
	return mSize <= 0;
}

template <class T>
void HashTable<T>::print()   const
{
	for (int i = 0; i < mCapacity; ++i)
	{
		cout << i << ": ";
		mData[i].print();
		
	}
	cout << endl;
}

template <class T>
int HashTable<T>::getSize()  const
{
	return mSize;
}