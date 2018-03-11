// 6_5_17fibonacci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int fibonacci(int n)
{
	//1. Base Case(s)
	if (n <= 2) return 1;

	//2. Recursive Case(s)
	else
	{
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}

int main()
{
	int fib;
	cin >> fib;
	cout << fibonacci(fib) << endl;
    return 0;
}

