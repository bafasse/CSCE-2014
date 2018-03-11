// 6_26_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include <iostream>
using namespace std;


int main()
{
	String string;
	string.append('a');
	string.append('b');
	string.append('c');
	string.print();

	cout << string.find('b') << endl;

	String string2(string);
	string2.print();

    return 0;
}

