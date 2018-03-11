// 6_21_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	/*Person person;
	person.setName("Larry Page");
	person.setAge(25);
	person.setHeight(1.80);
	cout << person.getAge() << endl;
	cout << person.getName() << endl;
	cout << person.getHeight() << endl;
	person.print();*/

	Person chad("Chad", 31, 182.2);
	Person copy(chad);
	chad.print();

	return 0;
}



