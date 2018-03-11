// basline.cpp : Defines the entry point for the console application.
//
//3 Way - Median

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

template <class T>
bool load(const string& filename, T array[], int size, int& numElements)
{
	ifstream din;
	din.open(filename.c_str());
	if (!din)
		return false;

	for (numElements = 0; numElements < size && !din.eof(); ++numElements)
		din >> array[numElements];

	din.close();
	return true;
}

template <class T>
string median(T low, T center, T high)
{
	T median[] = { low, center, high };

	insertionSort(median, 0, 2);

	return median[1];
}

template <class T>
void partition3Way(T data[], int low, int high, int& left, int& right)
{
	int center = (low + high) / 2;
	T pivot = median(data[low], data[center], data[high]);
	if (pivot == data[low])
		swap(data[low], data[high]);
	else if (pivot == data[center])
		swap(data[center], data[high]);

	left = low;
	right = high;

	for (int i = low; i <= right;)
	{
		if (data[i] > pivot)
		{
			swap(data[i], data[right]);
			--right;
		}
		else if (data[i] < pivot)
		{
			swap(data[left], data[i]);
			++left;
			++i;
		}
		else
			++i;
	}
}
template <class T>
void quickSort(T data[], int low, int high)
{
	if (low < high)
	{
		int right;
		int left;
		partition3Way(data, low, high, left, right);

		quickSort(data, low, left - 1);
		quickSort(data, right + 1, high);
	}
}

template <class T>
void insertionSort(T data[], int low, int high)
{
	for (int unsorted = low + 1; unsorted <= high; unsorted++)
	{
		T value = data[unsorted];
		int posn = unsorted;

		while ((posn > 0) && (data[posn - 1] > value))
		{
			data[posn] = data[posn - 1];
			posn--;
		}

		data[posn] = value;
	}
}

template <class T>
bool isSorted(T data[], int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		if (data[i] > data[i + 1])
			return false;
	}
	return true;
}


int main()
{
	const int SIZE = 1000;
	string array[SIZE];
	int numElements = 0;

	cout << "Please enter the name of the maze file: ";
	string filename;
	getline(cin, filename);

	if (!load(filename, array, SIZE, numElements))
	{
		cout << "Unable to read file. Please try again." << endl;
		return 1;
	}

	cout << numElements << endl;

	clock_t start = clock();

	// Code to be timed here 
	quickSort(array, 0, numElements - 1);
	// ...

	clock_t end = clock();

	double runTime = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Baseline Run time: (s)" << runTime << endl;

	if (isSorted(array, numElements))
		cout << "Sorted" << endl;
	else
		cout << "Not sorted" << endl;

	return 0;
}

