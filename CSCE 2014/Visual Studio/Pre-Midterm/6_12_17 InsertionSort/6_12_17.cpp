// 6_12_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
using namespace std;

//Good
void bubbleSort(int data[], int low, int high)
{
	int pass = 1;
	int exchange = 1;
	int count = high - low + 1;

	// Bubble largest value to the right N times
	while ((pass < count) && (exchange > 0))
	{
		// Scan unsorted part of data array
		exchange = 0;
		for (int index = low; index <= high - pass; index++)
		{
			// Swap two data values if out of order
			if (data[index] > data[index + 1])
			{
				swap(data[index], data[index + 1]);
				exchange++;
			}
		}
		pass++;
	}
}

//Better
void selectionSort(int data[], int low, int high)
{
	// Put largest unsorted value at end of sorted list
	for (int last = high; last > low; last--)
	{
		// Find index of largest value in unsorted array
		int largest = low;
		for (int index = low + 1; index <= last; index++)
			if (data[index] > data[largest])
				largest = index;

		// Swap with last element in unsorted array
		swap(data[last], data[largest]);
	}
}

//Best
void insertionSort(int data[], int low, int high)
{
	// Insert each element of unsorted list into sorted list
	for (int unsorted = low + 1; unsorted <= high; unsorted++)
	{
		// Select unsorted value to be inserted
		int value = data[unsorted];
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

void highLowSort(int data[], int low, int high)
{
	for (int last = high; last > low; last--)
	{
		
		int largest = low;
		int smallest = low;
		for (int index = low + 1; index <= last; index++)
		{
			if (data[index] > data[largest])
				largest = index;
			if (data[index] < data[smallest])
				smallest = index;
		}

		swap(data[last], data[largest]);

		if (smallest == last)
			smallest = largest;
		//for (int i = low + 1; i <= last; ++i)
			//if (data[i] < data[smallest])
				//smallest = i;


		// Swap with last element in unsorted array
		
		swap(data[smallest], data[low]);
		//swap(data[last], data[smallest]);
		++low;
	}
}

void print(int array[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

int main()
{
	int array[] = { 5,3,8,17,6,1,2,20 };
	int small[] = { 5,3,8,17,6,2,20,1 };
	cout << "array = ";
	print(array, 8);

	selectionSort(array, 0, 7);
	cout << "selectionSort = ";
	print(array, 8);

	highLowSort(array, 0, 7);
	cout << "highLowSort = ";
	print(array, 8);

	highLowSort(small, 0, 7);
	cout << "highLowSort = ";
	print(small, 8);

    return 0;
}

