// 7_18_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include "BST.h"
#include <algorithm>
#include <iostream>
using namespace std;


int main()
{
	BST<int> tree;
	tree.insert(5);
	tree.insert(2);
	tree.insert(3);
	tree.insert(7);
	tree.insert(6);
	tree.insert(10);
	tree.print();
	cout << "Count = " << tree.count() << endl;
	cout << "Height = " << tree.height() << endl;

	int temp;
	tree.select(5, temp);
	cout << temp << endl;
	return 0;
}



