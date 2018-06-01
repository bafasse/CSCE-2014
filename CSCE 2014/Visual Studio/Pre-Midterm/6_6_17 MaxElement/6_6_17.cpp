// 6_6_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

int recursiveMaxElement(int array[], int start, int end)
{
	if (start == end)
		return array[start];
	else
		return max ( array[start], recursiveMaxElement(array, start + 1, end));
}

int maxElement(int array[], int start, int end)
{
	int elem = array[start];
	for (int i = start; i <= end; ++i)
		elem = max(elem, array[i]);
	return elem;
}


int main()
{
	const int SIZE = 9;
	int array[SIZE] = { 0,1,2,3,4,5,6,1000,8};
	cout << "maxElement = " << maxElement(array, 0, SIZE - 1) << endl;
	cout << "recurisveMaxElement = " << recursiveMaxElement(array, 0, SIZE - 1) << endl;
    return 0;
}

