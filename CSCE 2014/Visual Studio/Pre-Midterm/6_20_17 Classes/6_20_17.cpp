// 6_20_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class Person
{
	public:
		//These is called a method
		Person();
		int getAge();
		double getHeight();
		string getName();

		void setAge(int age);
		void setHeight(double height);
		void setName(string name);

		void print();

	private:
		int Age;
		double Height;
		string Name;
};

Person::Person()
{
	Name = "Bob";
	Age = 1;
	Height = 1.0;
}

int Person::getAge()
{
	return Age;
}

double Person::getHeight()
{
	return Height;
}

string Person::getName()
{
	return Name;
}

void Person::setAge(int age)
{
	Age = age;
}

void Person::setHeight(double height)
{
	Height = height;
}

void Person::setName(string name)
{
	Name = name;
}

void Person::print()
{
	cout << Name << endl;
	cout << Age << endl;
	cout << Height << endl;
}

int main()
{
	Person person;
	person.setName("Larry Page");
	person.setAge(25);
	person.setHeight(1.80);
	cout << person.getAge() << endl;
	cout << person.getName() << endl;
	cout << person.getHeight() << endl;
	person.print();
    return 0;
}

