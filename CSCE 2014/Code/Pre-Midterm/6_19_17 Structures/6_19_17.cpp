// 6_19_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//POD- Plain Old Data
struct Address
{
	int houseNumber;
	string roadName;
	string city;
	string state;
	int zipCode;
};
//This is possible
struct AddressBook
{
	Address home;
	Address work;
	Address address[100];
	int numAddresses;
};

//Always pass by reference 
void print(const Address& addr)
{
	cout << addr.houseNumber << endl;
	cout << addr.roadName << endl;
	cout << addr.city << endl;
	cout << addr.state << endl;
	cout << addr.zipCode << endl << endl;
}
//------------------------------------------------

template <class T>
struct Point2D
{
	T x;
	T y;
};

double randRange(double min, double max)
{
	return ((double)rand() / (double)RAND_MAX) * (max - min) + min;
}

template <class T>
double maxDistance(Point2D<T> points[], int numPoints)
{
	double max = 0;
	double distance = 0;

	for (int r = 0; r < numPoints; ++r)
	{
		for (int c = 0; c < numPoints; ++c)
		{
			distance = sqrt( ( (points[r].x - points[c].x) * (points[r].x - points[c].x) ) + ((points[r].y - points[c].y) * (points[r].y - points[c].y)) );
			if (distance > max)
				max = distance;
		}
	}
	
	return max;
}

int main()
{
/*	//AddressBook book;
	//cout << sizeof(book) << endl;
	//book.numAddresses = 0;
	//book.address[0].zipCode = 72705;

	Address home;
	home.houseNumber = 123;
	home.roadName = "Poplar Ave.";
	home.city = "Fayetteville";
	home.state = "AR";
	home.zipCode = 72703;

	Address work;
	work.houseNumber = 8086;
	work.roadName = "Harmon Ave.";
	work.city = "Fayetteville";
	work.state = "AR";
	work.zipCode = 72704;

	cout << home.houseNumber << endl;
	cout << home.roadName << endl;
	cout << home.city << endl;
	cout << home.state << endl;
	cout << home.zipCode << endl << endl;

	print(home);
	print(work);
*/

	Point2D<double> array[100];
	for (int i = 0; i < 100; ++i)
	{
		array[i].x = randRange(-10, 10);
		array[i].y = randRange(-10, 10);
	}
	cout << maxDistance(array, 100) << endl;
    return 0;
}

