#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <string>
#include "Vector.h"
using namespace std;

class String
{
public:
	// Constructors
	String();
	String(const String& orig);

	// Character modification
	char getChar(const int index) const;
	void setChar(const int index, const char c);
	void append(const char c);

	// String status
	int getLength() const;
	void print() const;

	// Other useful functions
	int find(const char c) const;

private:
	Vector<char> mChars;
};

// [Your function implementations go here...]
String::String()
{
}

String::String(const String& orig)
{
	mChars.resize(orig.getLength());
	for (int i = 0; i < mChars.getSize(); ++i)
		mChars[i] = orig.mChars[i];
}

char String::getChar(const int index) const
{
	return mChars.get(index);
}

void String::setChar(const int index, const char c)
{
	mChars.set(index, c);
}

void String::append(const char c)
{
	mChars.pushBack(c);
}

int String::getLength() const
{
	return mChars.getSize();
}

void String::print() const
{
	mChars.print();
}

int String::find(const char c) const
{
	for (int i = 0; i < mChars.getSize(); ++i)
	{
		if (mChars[i] == c)
			return i;
	}
	return -1;
}
#endif