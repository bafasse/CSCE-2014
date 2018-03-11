// hw2.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class T>
bool load(const string& filename, T array[], int size)
{
	ifstream din;
	din.open(filename.c_str());
	if (!din)
		return false;
	for (int i = 0; i < size; ++i)
		din >> array[i];
	din.close();
	return true;
}

template <class T>
void print(T array[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << array[i] << " ";
	}

	cout << endl;
}

template <class T>
void partition(T data[], int low, int high, int &mid)
{
	// Select pivot value
	T pivot = data[high];
	int left = low;
	int right = high;

	// Partition array into two parts
	while (left < right)
	{
		// Scan left to right
		while ((left < right) && (data[left] < pivot))
			left++;

		// Scan right to left
		while ((left < right) && (data[right] >= pivot))
			right--;

		// Swap data values
		swap(data[left], data[right]);
	}

	// Swap pivot to mid
	mid = left;
	data[high] = data[mid];
	data[mid] = pivot;
}

template <class T>
//doesnt work well with sorted 
int quickSort(T data[], int low, int high)
{
	if (low > high)
	{
		return 1;
		insertionSort(data, low, high);
	}
	else if (low < high)
	{
		// Partition data into two parts
		int mid = 0;
		partition(data, low, high, mid);

		// Recursive calls to sort array
		quickSort(data, low, mid - 1);
		quickSort(data, mid + 1, high);
	}
}

template <class T>
void insertionSort(T data[], int low, int high)
{
	// Insert each element of unsorted list into sorted list
	for (int unsorted = low + 1; unsorted <= high; unsorted++)
	{
		// Select unsorted value to be inserted
		T value = data[unsorted];
		int posn = unsorted;

		// Make room for new data value
		while ((posn > 0) && (data[posn - 1] > value))
		{
			data[posn] = data[posn - 1];
			posn--;
		}

		// Put new value into array
		data[posn] = value;
	}
}

template <class T>
void shuffle(T array[], int count, int swaps)
{
	for (int i = 0; i < swaps; ++i)
	{
		int index1 = rand() % count;
		int index2 = rand() % count;
		swap(array[index1], array[index2]);
	}
}


int main()
{ 
	const int SIZE = 1000;
	string small[SIZE];
	cout << "Please enter the name of the maze file: ";
	string filename;
	getline(cin, filename);

	if (!load(filename, small, SIZE))
	{
		cout << "Unable to read file. Please try again." << endl;
		return 1;
	}
	
	//sorted.txt
	if (quickSort(small, 0, SIZE - 1) == 1)
	{
		shuffle(small, SIZE, SIZE / 4);
		cout << endl << "quickSort(): Failed" << endl << "Calling insertionSort()" << endl;
		insertionSort(small, 0, SIZE - 1);
	}
	//unsorted.txt
	else
	{
		cout << endl << "quickSort(): Success! " << endl;
	}
	//print(small, SIZE);

	//insertionSort(small, 0, SIZE - 1);
	//cout << endl << "insertionSort(): " << endl;
	//print(small, SIZE);
    return 0;
}

