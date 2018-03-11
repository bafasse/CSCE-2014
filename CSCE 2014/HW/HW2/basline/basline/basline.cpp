// basline.cpp : Defines the entry point for the console application.
//
//Baseline

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
void partition(T data[], int low, int high, int &mid)
{
	T pivot = data[high];
	int left = low;
	int right = high;

	while (left < right)
	{

		while ((left < right) && (data[left] < pivot))
			left++;

		while ((left < right) && (data[right] >= pivot))
			right--;

		swap(data[left], data[right]);
	}

	mid = left;
	data[high] = data[mid];
	data[mid] = pivot;
}

template <class T>
void quickSort(T data[], int low, int high)
{
	if (low < high)
	{

		int mid = 0;
		int right;
		int left;
		partition(data, low, high, mid);

		quickSort(data, low, mid - 1);
		quickSort(data, mid + 1, high);
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

