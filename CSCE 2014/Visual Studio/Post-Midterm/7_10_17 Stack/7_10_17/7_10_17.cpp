// 7_10_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UnboundedStack.h"
#include <iostream>
using namespace std;

int main()
{
	// LIFO - Last in, first out
	Stack<int> stack;
	for (int i = 0; i < 32; ++i)
		stack.push(i);
	stack.print();

	int value;
	while (!stack.isEmpty())
	{
		stack.pop(value);
		stack.print();
	}

    return 0;
}

