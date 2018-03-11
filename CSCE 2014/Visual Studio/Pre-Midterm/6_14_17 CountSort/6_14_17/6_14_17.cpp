// 6_14_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

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

void countSort(int data[], const int size)
{
	int counts[10] = { 0 };

	for (int i = 0; i < size; ++i)
	{
		counts[data[i]]++;
	}

	// Convert counts to a sorted array
	int index = 0;
	for (int j = 0; j < size; ++j)
	{
		for (int k = 0; k < counts[j]; ++k)
		{
			data[index] = j;
			++index;
		}
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

int main()
{
	const int SIZE = 10;
	//int array[] = { 5,3,8,17,2,1,2,7 };
	int PI[] = { 3,1,4,1,5,9,2,6,5,3 };

	cout << "Array: ";
	print(PI, SIZE);

	//mergeSort(PI, 0, SIZE - 1);
	countSort(PI, SIZE);

	cout << endl << "countSort(): ";
	print(PI, SIZE);
    return 0;
}

