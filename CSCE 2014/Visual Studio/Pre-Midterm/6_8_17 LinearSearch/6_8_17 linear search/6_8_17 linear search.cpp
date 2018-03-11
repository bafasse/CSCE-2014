// 6_8_17 linear search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int linearSearch(int array[], int start, int end, int value)
{
	for (int i = start; i <= end; ++i)
	{
		//we found it 
		if (array[i] == value)
			return i;
	}
	return -1;
}

int binarySearch(int array[], int start, int end, int value)
{
	//binary search has to be sorted in order to work
	while (start <= end)
	{
		//calcuate midpoint
		int mid = (start + end) / 2;

		if (array[mid] == value)
			return mid;

		//Search left side
		else if (value < array[mid])
			end = mid - 1;

		//Search right side
		else
			start = mid + 1;
	}
	//Value could not be found
	return -1;
}

int main()
{
	int array[] = { 1,5,7,13,14,17,21,25 };
	cout << linearSearch(array, 0, 7, 1) << endl;
	cout << binarySearch(array, 0, 7, 1) << endl;

    return 0;
}

