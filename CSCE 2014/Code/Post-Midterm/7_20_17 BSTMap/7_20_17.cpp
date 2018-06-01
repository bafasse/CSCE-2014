// 7_20_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <string>
#include "Map.h"
//#include "BST.h"

int main()
{
	Map<string, int> map;
	map.insert("x", 5);
	map.insert("x", 2);
	
	map.insert("y", 7);
	map.insert("y", 10);
	map.insert("z", 12);
	map.print();
	cout << endl;

	int value;
	if (map.remove("y", value))
	{
		cout << "Value was : " << value << endl;
		cout << "Removed (y, " << value << ")" << endl;
		map.print();
	}
	else cout << "remove() failed" << endl;
	cout << endl;
	
	int search;
	if (map.search("x", search))
	{
		cout << "Search found : " << search << endl;
		cout << "Found (x, " << search << ")" << endl;
		map.print();
	}
	else cout << "search() failed" << endl;
    return 0;
}

