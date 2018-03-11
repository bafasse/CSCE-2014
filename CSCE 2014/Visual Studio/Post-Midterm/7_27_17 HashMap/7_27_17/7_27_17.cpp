// 7_27_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "HashTable.h"
#include "HashMap.h"


int main()
{
	/*HashTable<int> h;
	h.insert(5);
	h.insert(6);
	h.insert(4);
	h.insert(12);
	h.insert(22);
	h.insert(1);
	h.insert(7);
	h.print();
	if (h.search(12))
		cout << "FOUND" << endl;
	else cout << "FAIL" << endl;*/

	HashMap<int, string> m;
	m.insert(5, "x");
	m.insert(6, "y");
	m.insert(4, "a");
	m.insert(12, "b");
	m.insert(22, "c");
	m.insert(1, "d");
	m.insert(7, "e");
	m.print();

	string search;
	if (m.search(12, search))
		cout << "FOUND " << search << endl;
	else cout << "FAIL" << endl;

	string value;
	if (m.remove(12, value))
		cout << "Removed " << value << endl;
	else cout << "FAIL" << endl;
    return 0;
}

