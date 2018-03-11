// 6_5_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
using namespace std;

double recursivePower(double x, int p)
{
	if (p == 0)
		return 1;
	else if (p == 1)
		return x;

	else if (p % 2 == 0)
	{
		double temp = recursivePower(x, p / 2);
		return temp * temp;
	}
	else
	{
		double temp = recursivePower(x, p / 2);
		return x * temp * temp;
	}
}


double iterativePower(double x, int p)
{
	double power = 1;
	for (int i = 0; i < p; ++i)
	{
		power *= x;
	}
	return power;
}

int main()
{
	double base;
	int pow;
	cout << "Please enter the base number and the number you would like to have that number raised to: " << endl;
	cin >> base >> pow;

	clock_t start = clock();

	// Code to be timed here
	for (int i = 0; i < 1000; ++i)
		recursivePower(base, pow);
	// ...

	clock_t end = clock();

	double runTime = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Run time: (s)" << runTime << endl;
	//----------------------------------------------------------
	clock_t start2 = clock();

	// Code to be timed here
	for (int i = 0; i < 1000; ++i)
		iterativePower(base, pow);
	// ...

	clock_t end2 = clock();

	double runTime2 = (end2 - start2) / (double)CLOCKS_PER_SEC;
	cout << "Run time: (s)" << runTime2 << endl;
    return 0;
}

