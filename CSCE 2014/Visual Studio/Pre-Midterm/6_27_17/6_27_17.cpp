// 6_27_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
using namespace std;
//Look up base cases

int main()
{

	//Factorial
	//n * factorial(n-1)
	//0! = 1
	//1! = 1
	//2! = 2
	//3! = 6

	//swap(array[0], array[last])
	//reverse(array, 1, last - 1)

	//Fibonacci
	//1 1 2 3 5 8 13 21 
	//fibonacci(i) = fibonacci(i - 1) + fibonacci(i - 2)
	//fib(1) = 1
	//fib(2) = 1
	//runtime = 0(fib(N))

	//Power(x , p) x^p
	//x * powrr(x, p-1)  0(N)
	//power(x, p/2) * power(x, p/2)
	//5^5 = 5^2 * 5^2 * 5
	//0(log(N))

	//Max Element
	//max(array) = max(array[0], max(array[1:]))
	//O (N)

	//Towers of Hanoi
	//0 (2^N)

	//Flood Fill (MS Paint)
	//O(N)


    return 0;
}

