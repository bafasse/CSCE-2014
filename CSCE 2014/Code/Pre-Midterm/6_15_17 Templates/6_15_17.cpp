// 6_15_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

// Swaps two values of arbitrary types. Requires the
// = operator to be defined.
template <class T>
void swap2(T& left, T& right)
{
	T temp = left;
	left = right;
	right = temp;
}

// Returns the index of the largest element in array between
// 'low' and 'high'. Requires the > operator to be defined.
template <class T>
int maxElement(T array[], int low, int high)
{
	int minIndex = low;
	for (int i = low + 1; i <= high; ++i)
	{
		if (array[i] > array[minIndex])
			minIndex = i;
	}
	return minIndex;
}

// Sorts the given segment of the 'data' array using
// the selection sort algorithm. Requires the maxElement()
// and swap() functions to have compatible overloads for
// type T.
template <class T>
void selectionSort(T data[], int low, int high)
{
	// Put largest unsorted value at end of sorted list
	for (int last = high; last > low; last--)
	{
		// Find index of largest value in unsorted array
		int largest = maxElement(data, low, last);

		// Swap with last element in unsorted array
		swap(data[last], data[largest]);
	}
}

template <class T>
void mergeSort(T data[], int low, int high)
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
		T *copy = new T [range];

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

//class can also be called typename
template <typename T>
void print(T data[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << data[i] << " ";
	}

	cout << endl;
}


int main()
{
	// Try swapping with integers
	int x = 5;
	int y = 7;
	swap2(x, y); // x == 7, y == 5
	cout << x << ", " << y << endl;

				// Try swapping with strings
	string a = "Aardvark";
	string b = "ZZ Top";
	swap2(a, b); // a == "ZZ Top", b == "Aardvark"
	cout << a << ", " << b << endl;

				// Try swapping with doubles. Explicitly tell
				// the compiler which version of the template to use
	double m = 5.6;
	double n = 7.8;
	swap2<double>(m, n); // m == 7.8, n == 5.6
	cout << m << ", " << n << endl;

	const int SIZE = 6;
	const int SMALL = 5;
	int data[] = { 5, 4, 7, 200, 4, 1 };
	char array[] = { 'z', 'Z', 'A', 'B', 'C', 'D' };
	string words[] = { "Tool", "Meshuggah", "Gojira", "Decapitated", "AliceInChains", "AmonAmarth" };
	//<...> is not necessary but is helpful
	mergeSort<int>(data, 0, SMALL);
	mergeSort<char>(array, 0, SMALL);
	mergeSort<string>(words, 0, SMALL);
	print<int>(data, SIZE);
	print<char>(array, SIZE);
	print<string>(words, SIZE);
	return 0;
}

