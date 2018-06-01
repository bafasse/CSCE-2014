// 6_1_17.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <ctime>
using namespace std;

int factorial(int n)
{
	if (n <= 1) 
		return 1;
	else        
		return n * factorial(n - 1);
}

int loopFactorial(int n)
{
	int count = 1;
	for (int i = 1; i <= n; ++i)
	{
		count *= i;
	}
	return count;
}

int main()
{
	int num;
	cout << "Please input a number: ";
	cin >> num;
	cout << factorial(num) << endl;
	cout << loopFactorial(num) << endl;
	clock_t start = clock();

	// Code to be timed here 
	for (int i = 0; i < 1000; ++i)
		factorial(num);
	// ...

	clock_t end = clock();

	double runTime = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Recursive Run time: (s)" << runTime << endl;

	clock_t star = clock();

	// Code to be timed here 
	for (int i = 0; i < 1000; ++i)
		loopFactorial(num);
	// ...

	clock_t en = clock();

	double runTim = (en - star) / (double)CLOCKS_PER_SEC;
	cout << "Iterative Run time: (s)" << runTim << endl;
    return 0;
}

