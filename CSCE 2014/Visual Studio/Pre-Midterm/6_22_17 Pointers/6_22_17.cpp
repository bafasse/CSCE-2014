// 6_22_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
using namespace std;

double randRange(double min, double max)
{
	return ((double)rand() / (double)RAND_MAX) * (max - min) + min;
}

double* createRandomArray(const int size)
{
	double* x = new double[size];
	for (int i = 0; i < size; ++i)
	{
		x[i] = randRange(0.0, 1.0);
	}
	return x;
}

void print(double array[], const int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << array[i] << endl;
	}
}

template <class T>
T* resize(const T* orig, const int oldSize, const int newSize)
{
	T* array = new T[newSize];

	if (oldSize < newSize)
	{
		for (int i = 0; i < oldSize; ++i)
			array[i] = orig[i];

		for (int i = oldSize; i < newSize; ++i)
			array[i] = 0;
	}
	else
	{
		for (int i = 0; i < newSize; ++i)
			array[i] = orig[i];
	}

	delete[] orig;
	return array;
}

int main()
{
	int oldSize;
	const int newSize = 10;
	cout << "Enter array size: ";
	cin >> oldSize;
	double *array = createRandomArray(oldSize);
	print(array, oldSize);

	array = resize(array, oldSize, 10);
	cout << endl;
	print(array, newSize);

	delete[] array;

    return 0;
}

