#pragma once
#include <iostream>
#include <string>
using namespace std;

//ADT
class Person
{
public:
	//These is called methods, not functions
	//Defualt Constructor
	Person();

	//Non-Default Constructor
	Person(string name, int age, double height);

	//Copy Constructor
	Person(const Person& orig);

	//Getters / Accessors
	int getAge();
	double getHeight();
	string getName();

	//Setter / Mutator
	void setAge(int age);
	void setHeight(double height);
	void setName(string name);

	void print();

private:
	int Age;
	double Height;
	string Name;
};

//Default Constructor
Person::Person()
{
	Name = " ";
	Age = -1;
	Height = 0.0;
}

//Non-Default Constructor
Person::Person(string name, int age, double height)
{
	Name = name;
	Age = age;
	Height = height;
}

//Copy Constructo
Person::Person(const Person& orig)
{
	Name = orig.Age;
	Age = orig.Age;
	Height = orig.Height;
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