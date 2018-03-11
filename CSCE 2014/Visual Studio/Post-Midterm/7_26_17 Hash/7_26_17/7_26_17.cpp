// 7_26_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

bool search(const int* array, const int size, const int value)
{
	int index = value % size;
	for (int i = 0; i < size; ++i)
	{
		if (array[index] == value)
			return true;
		else if (array[index] == -1)
			return false;

		index = (index + 1) % size;
	}
	return false;
}

bool insert(int* array, const int size, const int value)
{
	if (search(array, size, value)) return true;

	int index = value % size;
	for (int i = 0; i < size; ++i)
	{
		if (array[index] == -1)
		{
			array[index] = value;
			return true;
		}

		index = (index + 1) % size;
	}
	return false;
}

void print(const int* array, const int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

int main()
{
	const int SIZE = 10;
	int array[SIZE];
	for (int i = 0; i < SIZE; ++i)
		array[i] = -1;

	insert(array, SIZE, 5);
	insert(array, SIZE, 15);
	insert(array, SIZE, 7);
	insert(array, SIZE, 0);
	print(array, SIZE);
	if (insert(array, SIZE, 10))
		print(array, SIZE);
	else cout << "FAIL" << endl;

	/*if (insert(array, SIZE, 10))
		print(array, SIZE);
	else cout << "FAIL" << endl;*/

	if (search(array, SIZE, 10))
		cout << "FOUND THE VALUE" << endl;
	else cout << "FAIL" << endl;
    return 0;
}

