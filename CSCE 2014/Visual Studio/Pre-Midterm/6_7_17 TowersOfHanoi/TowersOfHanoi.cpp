// TowersOfHanoi.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
#include <ctime>
using namespace std;

void tower(int count, char src, char dest, char extra)
{
	
	if(count != 1)
	{
		tower(count - 1, src  , extra, dest);
		tower(1        , src  , dest , extra);
		tower(count - 1, extra, dest , src);
	}
}

int main()
{
	clock_t start = clock();

	// Code to be timed here
	tower(25, 'A', 'C', 'B');
	// ...

	clock_t end = clock();

	double runTime = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Run time: (s)" << runTime << endl;
    return 0;
}

