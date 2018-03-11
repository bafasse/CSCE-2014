// 7_31_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.h"


int main()
{
	int value;
	int val;
	HashTable<int> l(10);
	l.insert(5);
	l.insert(55);
	l.insert(75);
	l.insert(0);
	l.insert(10);
	l.insert(20);
	l.insert(30);
	l.insert(1);
	l.insert(11);
	l.print();
	cout << "Insert a value to remove: ";
	cin >> value;
	if (l.remove(value)) l.print();
	else cout << "FAIL" << endl;

	cout << "Insert a value to find: ";
	cin >> val;
	if (l.search(val)) l.print();
	else cout << "FAIL" << endl;
    return 0;
}

