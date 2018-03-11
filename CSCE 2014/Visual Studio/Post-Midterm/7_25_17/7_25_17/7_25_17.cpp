// 7_25_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Heap.h"

int main()
{
	Heap<int> n; //larger Heap
	n.insert(5);
	n.insert(2);
	n.insert(3);
	n.insert(11);
	n.insert(6);
	n.insert(10);
	n.insert(1);
	//heapSort(n, 7);
	cout << "n: ";
	n.print();
	
	Heap<int> m; //Smaller Heap
	m.insert(4);
	m.insert(7);
	m.insert(12);
	cout << "m: ";
	m.print();

	cout << "m + n: ";
	Heap<int> p = merge(n, m);
	p.print();

	//n.print();
	return 0;
}
