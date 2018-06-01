// 7_6_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include "List.h"


int main()
{
	List<int> list;
	list.insertHead(5);
	list.insertHead(4);
	list.insertHead(3);
	list.insertHead(2);
	list.insertHead(1);
	cout << "Count: " << list.count() << endl;
	list.print();
	if (list.remove(4))
		cout << "remove() has worked" << endl;
	else
		cout << "remove() did not work";
	list.print();
    return 0;
}

