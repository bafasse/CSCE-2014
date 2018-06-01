// 7_5_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include "List1.h"

int main()
{
	List<int> list;
	list.insertHead(5);
	list.insertHead(3);
	list.insertHead(2);
	list.insertHead(1);
	list.print();
	cout << "Count: " << list.count() << endl;
	cout << endl << "Insert: 4" << endl << endl;
	list.insertSorted(0);
	list.print();
	cout << "Count: " << list.count() << endl;
    return 0;
}

