// 7_3_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
#include "List1.h"
using namespace std;

template <class T>
void move(List<T>& src, List<T>& dest)
{
	List<T> temp;
	T data;
	while (src.removeHead(data))
	{
		temp.insertHead(data);
	}
	while (temp.removeHead(data))
	{
		dest.insertHead(data);
	}
}

int main()
{
	List<int> list;
	List<int> list2;
	list.insertHead(10);
	list.insertHead(9);
	list.insertHead(8);
	list.insertHead(7);
	list.print();
	list2.print();
	cout << "Count = " << list.count() << endl << endl;

	move(list, list2);

	list.print();
	list2.print();
    return 0;
}

