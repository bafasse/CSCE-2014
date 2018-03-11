#pragma once
#include <string>
#include <iostream>
using namespace std;


//===================================================//
// Sample Hash Functions                             //
//===================================================//

int dash(int value)
{
	return value;
}

template <class Key, class Value>
class HashMap
{
public:
	// Constructors / Destructors
	HashMap();
	HashMap(const int capacity);
	HashMap(const HashMap<Key, Value>& orig);
	~HashMap();

	// HashMap modification
	bool insert(const Key& key, const Value& value);
	bool remove(const Key& key, Value& value);

	// HashMap statistics
	bool search(const Key& key, Value& value) const;
	void print() const;
	int size() const;
	bool isFull() const;
	bool isEmpty() const;
	int getSize() const;

private:
	static const int DEFAULT_SIZE = 32;
	static const char FULL = 'F';
	static const char EMPTY = 'E';
	static const char AVAILABLE = 'A';

	Value* mValue;
	char* mState;
	Key* mKey;
	int mCapacity;
	int mSize;

	int indexOf(const Key& key) const;
	int auxHash(const int dash) const;
};

// ===========================================================================
// ---------------------------------------------------------------------------
// ===========================================================================

template <class Key, class Value>
HashMap<Key, Value>::HashMap()
{
	mValue = new Value[DEFAULT_SIZE];
	mState = new char[DEFAULT_SIZE];
	mKey = new Key[DEFAULT_SIZE];
	mCapacity = DEFAULT_SIZE;
	mSize = 0;

	for (int i = 0; i < mCapacity; ++i)
		mState[i] = EMPTY;
}

template <class Key, class Value>
HashMap<Key, Value>::HashMap(const int capacity)
{
	mValue = new Value[capacity];
	mState = new char[capacity];
	mKey = new Key[capacity];
	mCapacity = capacity;
	mSize = 0;

	for (int i = 0; i < mCapacity; ++i)
		mState[i] = EMPTY;
}

template <class Key, class Value>
HashMap<Key, Value>::HashMap(const HashMap<Key, Value>& orig)
{
	mValue = new Value[orig.mCapacity];
	mState = new char[orig.mCapacity];
	mKey = new Key[orig.mCapacity];
	mCapacity = orig.mCapacity;
	mSize = orig.mSize;

	for (int i = 0; i < mCapacity; ++i)
	{
		mValue[i] = orig.mValue[i];
		mKey[i] = orig.mKey[i];
		mState[i] = orig.mState[i];
	}
}

template <class Key, class Value>
HashMap<Key, Value>::~HashMap()
{
	delete[] mValue;
	delete[] mState;
	delete[] mKey;
	mValue = NULL;
	mState = NULL;
	mKey = NULL;
}

// ===========================================================================
// ---------------------------------------------------------------------------
// ===========================================================================

template <class Key, class Value>
int HashMap<Key, Value>::auxHash(const int dash) const
{
	return dash + 1;
}

template <class Key, class Value>
int HashMap<Key, Value>::indexOf(const Key& key) const
{
	// Determine where to start looking
	int index = dash(key) % mCapacity;
	for (int i = 0; i < mCapacity; ++i)
	{
		// If we found what we were looking for, return the index
		if (mState[index] == FULL && mKey[index] == key)
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

template <class Key, class Value>
bool HashMap<Key, Value>::insert(const Key& key, const Value& value)
{
	// We can't insert if the table is full
	if (isFull()) return false;

	// If 'key' is already in the table, we don't need
	// to do any more work
	int index = indexOf(key);
	if (index != -1)
	{
		mValue[index] = value;
		return true;
	}

	// This key was not in the table already
	else
	{
		// Determine the first available cell
		int index = dash(key) % mCapacity;
		while (mState[index] == FULL)
			index = auxHash(index) % mCapacity;

		// Perform the insertion
		mState[index] = FULL;
		mKey[index] = key;
		mValue[index] = value;
		mSize++;

		return true;
	}
}

template <class Key, class Value>
bool HashMap<Key, Value>::search(const Key& key, Value& value) const
{
	int index = indexOf(key);
	if (index != -1)
	{
		value = mValue[index];
		return true;
	}
	else return false;
	//return indexOf(key) != -1;
}

template <class Key, class Value>
bool HashMap<Key, Value>::remove(const Key& key, Value& value)
{
	int index = indexOf(key);
	if (index != -1)
	{
		// Cells that have been removed are AVAILABLE. They can be reused
		// in another insertion, but they cannot be used as stopping
		// criteria for searches.
		mState[index] = AVAILABLE;
		value = mValue[index];
		mSize--;
		return true;
	}
	else return false;
}

//===================================================//

template <class Key, class Value>
bool HashMap<Key, Value>::isFull() const
{
	return mSize >= mCapacity;
}

template <class Key, class Value>
bool HashMap<Key, Value>::isEmpty() const
{
	return mSize <= 0;
}

template <class Key, class Value>
void HashMap<Key, Value>::print() const
{
	for (int i = 0; i < mCapacity; ++i)
	{
		// We should only print the cells that are occupied
		if (mState[i] == FULL)
			cout << "[" << mKey[i] << ", " << mValue[i] << "] ";
		else cout << "x ";
	}
	cout << endl;
}

template <class Key, class Value>
int HashMap<Key, Value>::getSize() const
{
	return mSize;
}

template <class Key, class Value>
int HashMap<Key, Value>::size() const
{
	getSize();
}