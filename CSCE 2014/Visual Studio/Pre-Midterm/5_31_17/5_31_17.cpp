// 5_31_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool load(const string& filename, int arr[], const int arrSize, int& numElements)
{
	ifstream din;
	din.open(filename.c_str());
	if (!din)
	{
		cout << "ERROR!" << endl;
		return 0;
	}
	
	for (int i = 0; i < arrSize; ++i) 
	{
		din >> arr[i];
		++numElements;

		if (din.eof())
			break;
	}

	din.close();
	numElements--;
	return true;
}

int main()
{
	string filename;
	const int arrSize = 10;
	int numElements = 1;
	int arr[arrSize];
	cout << "What would you like the filename to be: ";
	cin >> filename;
	if (load(filename, arr, arrSize, numElements))
	{
		for (int i = 0; i < numElements; ++i)
		{
			cout << arr[i] << " " ;
		}
		cout << endl << numElements << endl;
	}

    return 0;
}

