// 6_8_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int binarySearch(int array[], int first, int last, int value)
{
	while (first <= last)
	{
		// Calculate the midpoint
		int mid = (first + last) / 2;

		// Did we find what we were looking for?
		if (array[mid] == value)
			return mid;

		// Search either the left half of the array...
		else if (array[mid] > value)
			last = mid - 1;

		// ... or the right half of the array
		else first = mid + 1;
	}

	// No luck. 'value' was not in the array
	return -1;
}

int recursiveBinarySearch(int array[], int first, int last, int value)
{
	int mid = (first + last) / 2;
	//Base Case(s)
	if (first > last)
	{
		//value isnt in the array
		return -1;
	}
	else if (array[mid] == value)
	{
		//We have found the value 
		return mid;
	}
	//Recursive Case(s)
	else if (array[mid] > value)
	{
		//Searches left half
		return recursiveBinarySearch(array, first, mid - 1, value);
	}
	else
	{
		//Searchs right half
		return recursiveBinarySearch(array, mid + 1, last, value);
	}

}


int main()
{
	int array[] = { 1,5,7,13,14,17,21,25 };
	cout << binarySearch(array, 0, 7, 25) << endl;
	cout << recursiveBinarySearch(array, 0, 7, 25) << endl;

    return 0;
}

