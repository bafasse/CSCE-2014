// 6_13_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
using namespace std;

//----------------------------------------------------------------
// Partition function used by Quicksort.
//----------------------------------------------------------------
void partition(int data[], int low, int high, int &mid)
{
	// Select pivot value
	int pivot = data[high];
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

//----------------------------------------------------------------
// Recursive Quicksort algorithm using basic partition function.
//----------------------------------------------------------------
void quickSort(int data[], int low, int high)
{
	// Check terminating condition
	if (low < high)
	{
		// Partition data into two parts
		int mid = 0;
		partition(data, low, high, mid);

		// Recursive calls to sort array
		quickSort(data, low, mid - 1);
		quickSort(data, mid + 1, high);
	}
}

//----------------------------------------------------------------
// Mergesort using secondary storage for data merging.
//----------------------------------------------------------------
void mergeSort(int data[], int low, int high)
{
	// Check terminating condition
	int range = high - low + 1;
	if (range > 1)
	{
		// Divide the array and sort both halves
		int mid = (low + high) / 2;
		mergeSort(data, low, mid);
		mergeSort(data, mid + 1, high);

		// Create temporary array for merged data
		int *copy = new int[range];

		// Initialize array indices
		int index1 = low;
		int index2 = mid + 1;
		int index = 0;

		// Merge smallest data elements into copy array
		while (index1 <= mid && index2 <= high)
		{
			if (data[index1] < data[index2])
				copy[index++] = data[index1++];
			else
				copy[index++] = data[index2++];
		}

		// Copy any remaining entries from the first half
		while (index1 <= mid)
			copy[index++] = data[index1++];

		// Copy any remaining entries from the second half
		while (index2 <= high)
			copy[index++] = data[index2++];

		// Copy data back from the temporary array
		for (index = 0; index < range; index++)
			data[low + index] = copy[index];
		delete[]copy;
	}
}

void print(int data[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

void shuffle(int array[], int count, int swaps)
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
	const int SIZE = 43252;
	//43252 is highest number that can be used on Surface
	int array[SIZE];
	for (int i = 0; i < SIZE - 1; ++i)
	{
		array[i] = rand();
	}
	
	cout << "Size of Array: " << SIZE << endl;
	cout << "Random Array: " << endl;
	//print(array, SIZE);

	clock_t start = clock();

	// Code to be timed here 
	quickSort(array, 0, SIZE - 1);
	// ...

	clock_t end = clock();

	double runTime = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "quickSort() Run time: (s)" << runTime << endl;
	//----------------------------------------------------
	clock_t start2 = clock();
	for (int i = 0; i < SIZE - 1; ++i)
	{
		array[i] = rand();
	}
	// Code to be timed here 
	mergeSort(array, 0, SIZE - 1);
	// ...

	clock_t end2 = clock();

	double runTime2 = (end2 - start2) / (double)CLOCKS_PER_SEC;
	cout << "mergeSort() Run time: (s)" << runTime2 << endl;
	//--------------------------------------------------------------
	//==============================================================
	
	
	cout << endl << "Sorted Array: " << endl;
	//print(array, SIZE);

	clock_t start3 = clock();

	// Code to be timed here 
	quickSort(array, 0, SIZE - 1);
	// ...

	clock_t end3 = clock();

	double runTime3 = (end3 - start3) / (double)CLOCKS_PER_SEC;
	cout << "quickSort() Run time: (s)" << runTime3 << endl;
	//---------------------------------------------------------
	clock_t start4 = clock();

	// Code to be timed here 
	mergeSort(array, 0, SIZE - 1);
	// ...

	clock_t end4 = clock();

	double runTime4 = (end4 - start4) / (double)CLOCKS_PER_SEC;
	cout << "mergeSort() Run time: (s)" << runTime4 << endl;
	//--------------------------------------------------------------
	//==============================================================
	
	
	cout << endl << "Semi-Sorted Array: " << endl;
	shuffle(array, SIZE, SIZE/4);
	//print(array, SIZE);

	clock_t start5 = clock();

	// Code to be timed here 
	quickSort(array, 0, SIZE - 1);
	// ...

	clock_t end5 = clock();

	double runTime5 = (end5 - start5) / (double)CLOCKS_PER_SEC;
	cout << "quickSort() Run time: (s)" << runTime5 << endl;
	//---------------------------------------------------------
	clock_t start6 = clock();
	shuffle(array, SIZE, SIZE / 4);
	// Code to be timed here 
	mergeSort(array, 0, SIZE - 1);
	// ...

	clock_t end6 = clock();

	double runTime6 = (end6 - start6) / (double)CLOCKS_PER_SEC;
	cout << "mergeSort() Run time: (s)" << runTime6 << endl;
    return 0;
}

