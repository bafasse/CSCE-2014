// 7_19_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include "BST.h"


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
	int temp1;
	int temp2;
	int temp3;
	int temp4;
	int temp5;

	tree.select(0, temp);
	tree.select(1, temp1);
	tree.select(2, temp2);
	tree.select(3, temp3);
	tree.select(4, temp4);
	tree.select(5, temp5);
	cout << "Select: " << temp << " " << temp1 << " " << temp2 << " " << temp3 << " " << temp4 << " " << temp5 << endl;
    return 0;
}

