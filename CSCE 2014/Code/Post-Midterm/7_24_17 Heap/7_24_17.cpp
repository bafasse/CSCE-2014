// 7_24_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include "Heap.h"

int main()
{
	Heap<int> heap;
	heap.insert(5);
	heap.insert(2);
	heap.insert(3);
	heap.insert(7);
	heap.insert(6);
	heap.insert(10);
	heap.insert(1);
	heap.print();
	int temp;
	if (heap.replace(4, temp))
	{
		cout << "replace(): ";
		heap.print();
	}
	else cout << "FAIL" << endl;
    return 0;
}

