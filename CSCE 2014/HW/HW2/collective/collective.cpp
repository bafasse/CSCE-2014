// collective.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

const int HYBRID_THRESHOLD = 500;

template <class T>
bool load(const string& filename, T array[], int size, int& numElements)
{
	ifstream din;
	din.open(filename.c_str());
	if (!din)
		return false;

	for (numElements = 0; numElements < size && !din.eof(); ++numElements)
		din >> array[numElements];

	din.close();
	return true;
}
//-----------------------------------------------------
//*****************************************************
//(1) Baseline
template <class T>
void partition(T data[], int low, int high, int &mid)
{
	T pivot = data[high];
	int left = low;
	int right = high;

	while (left < right)
	{

		while ((left < right) && (data[left] < pivot))
			left++;

		while ((left < right) && (data[right] >= pivot))
			right--;

		swap(data[left], data[right]);
	}

	mid = left;
	data[high] = data[mid];
	data[mid] = pivot;
}

template <class T>
void baselineQuickSort(T data[], int low, int high)
{
	if (low < high)
	{

		int mid = 0;
		int right;
		int left;
		partition(data, low, high, mid);

		baselineQuickSort(data, low, mid - 1);
		baselineQuickSort(data, mid + 1, high);
	}
}

//----------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//(2) 3 Way
template <class T>
void partition3Way(T data[], int low, int high, int& left, int& right)
{
	T pivot = data[high];

	left = low;
	right = high;

	for (int i = low; i <= right;)
	{
		if (data[i] > pivot)
		{
			swap(data[i], data[right]);
			--right;
		}
		else if (data[i] < pivot)
		{
			swap(data[left], data[i]);
			++left;
			++i;
		}
		else
			++i;
	}
}

template <class T>
void quickSort3Way(T data[], int low, int high)
{
	if (low < high)
	{
		int right;
		int left;
		partition3Way(data, low, high, left, right);

		quickSort3Way(data, low, left - 1);
		quickSort3Way(data, right + 1, high);
	}
}

//----------------------------------------------------------
//==========================================================
//(3) Median
template <class T>
string median(T low, T center, T high)
{
	T median[] = { low, center, high };

	insertionSort(median, 0, 2);

	return median[1];
}

template <class T>
void partitionMedian(T data[], int low, int high, int &mid)
{
	int center = (low + high) / 2;
	T pivot = median(data[low], data[center], data[high]);
	if (pivot == data[low])
		swap(data[low], data[high]);
	else if (pivot == data[center])
		swap(data[center], data[high]);

	int left = low;
	int right = high;

	while (left < right)
	{

		while ((left < right) && (data[left] < pivot))
			left++;

		while ((left < right) && (data[right] >= pivot))
			right--;

		swap(data[left], data[right]);
	}

	mid = left;
	data[high] = data[mid];
	data[mid] = pivot;
}

template <class T>
void quickSortMedian(T data[], int low, int high)
{
	if (low < high)
	{

		int mid = 0;
		partitionMedian(data, low, high, mid);

		quickSortMedian(data, low, mid - 1);
		quickSortMedian(data, mid + 1, high);
	}
}

//---------------------------------------------------------
//#########################################################
//(4) Hybrid
template <class T>
void quickSortHybrid(T data[], int low, int high)
{
	if ((high - low) + 1 < HYBRID_THRESHOLD)
	{
		insertionSort(data, low, high);
		//cout << "insertionSort()" << endl;
	}

	if (low < high)
	{

		int mid = 0;
		int right;
		int left;
		//partitionHybrid() is not needed
		partition(data, low, high, mid);

		quickSortHybrid(data, low, mid - 1);
		quickSortHybrid(data, mid + 1, high);
	}
}
//---------------------------------------------------------
//#########################################################
//(5) 3Way + Median
template <class T>
void partition3WayMedian(T data[], int low, int high, int& left, int& right)
{
	int center = (low + high) / 2;
	T pivot = median(data[low], data[center], data[high]);
	if (pivot == data[low])
		swap(data[low], data[high]);
	else if (pivot == data[center])
		swap(data[center], data[high]);

	left = low;
	right = high;

	for (int i = low; i <= right;)
	{
		if (data[i] > pivot)
		{
			swap(data[i], data[right]);
			--right;
		}
		else if (data[i] < pivot)
		{
			swap(data[left], data[i]);
			++left;
			++i;
		}
		else
			++i;
	}
}

template <class T>
void quickSort3WayMedian(T data[], int low, int high)
{
	if (low < high)
	{
		int right;
		int left;
		partition3WayMedian(data, low, high, left, right);

		quickSort3WayMedian(data, low, left - 1);
		quickSort3WayMedian(data, right + 1, high);
	}
}

//---------------------------------------------------------
//#########################################################
//(6) 3Way + Hybrid
template <class T>
void partition3WayHybrid(T data[], int low, int high, int& left, int& right)
{
	T pivot = data[high];

	left = low;
	right = high;

	for (int i = low; i <= right;)
	{
		if (data[i] > pivot)
		{
			swap(data[i], data[right]);
			--right;
		}
		else if (data[i] < pivot)
		{
			swap(data[left], data[i]);
			++left;
			++i;
		}
		else
			++i;
	}
}
template <class T>
void quickSort3WayHybrid(T data[], int low, int high)
{
	if ((high - low) + 1 < HYBRID_THRESHOLD)
	{
		insertionSort(data, low, high);
		//cout << "insertionSort()" << endl;
	}

	if (low < high)
	{
		int right;
		int left;
		partition3WayHybrid(data, low, high, left, right);

		quickSort3WayHybrid(data, low, left - 1);
		quickSort3WayHybrid(data, right + 1, high);
	}
}

//---------------------------------------------------------
//#########################################################
//(7) Median + Hybrid

template <class T>
void partitionMedianHybrid(T data[], int low, int high, int &mid)
{
	int center = (low + high) / 2;
	T pivot = median(data[low], data[center], data[high]);
	if (pivot == data[low])
		swap(data[low], data[high]);
	else if (pivot == data[center])
		swap(data[center], data[high]);

	int left = low;
	int right = high;

	while (left < right)
	{

		while ((left < right) && (data[left] < pivot))
			left++;

		while ((left < right) && (data[right] >= pivot))
			right--;

		swap(data[left], data[right]);
	}

	mid = left;
	data[high] = data[mid];
	data[mid] = pivot;
}

template <class T>
void quickSortMedianHybrid(T data[], int low, int high)
{
	if ((high - low) + 1 < HYBRID_THRESHOLD)
	{
		insertionSort(data, low, high);
		//cout << "insertionSort()" << endl;
	}

	if (low < high)
	{

		int mid = 0;
		partitionMedianHybrid(data, low, high, mid);

		quickSortMedianHybrid(data, low, mid - 1);
		quickSortMedianHybrid(data, mid + 1, high);
	}
}

//---------------------------------------------------------
//#########################################################
//(8) 3 Way + Hybrid + Median

template <class T>
void partition3WayHybridMedian(T data[], int low, int high, int& left, int& right)
{
	int center = (low + high) / 2;
	T pivot = median(data[low], data[center], data[high]);
	if (pivot == data[low])
		swap(data[low], data[high]);
	else if (pivot == data[center])
		swap(data[center], data[high]);

	left = low;
	right = high;

	for (int i = low; i <= right;)
	{
		if (data[i] > pivot)
		{
			swap(data[i], data[right]);
			--right;
		}
		else if (data[i] < pivot)
		{
			swap(data[left], data[i]);
			++left;
			++i;
		}
		else
			++i;
	}
}

template <class T>
//doesnt work well with sorted 
void quickSort3WayHybridMedian(T data[], int low, int high)
{
	if ((high - low) + 1 < HYBRID_THRESHOLD)
	{
		insertionSort(data, low, high);
		//cout << "insertionSort()" << endl;
	}

	else if (low < high)
	{
		//cout << "partition3Way()" << endl;
		int left;
		int right;
		partition3WayHybridMedian(data, low, high, left, right);

		quickSort3WayHybridMedian(data, low, left - 1);
		quickSort3WayHybridMedian(data, right + 1, high);
	}
}

template <class T>
void insertionSort(T data[], int low, int high)
{
	for (int unsorted = low + 1; unsorted <= high; unsorted++)
	{
		T value = data[unsorted];
		int posn = unsorted;

		while ((posn > 0) && (data[posn - 1] > value))
		{
			data[posn] = data[posn - 1];
			posn--;
		}

		data[posn] = value;
	}
}

template <class T>
bool isSorted(T data[], int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		if (data[i] > data[i + 1])
			return false;
	}
	return true;
}


int main()
{
	const int SIZE = 1000;
	string array[SIZE];
	int numElements = 0;

	cout << "Please enter the name of the maze file: ";
	string filename;
	getline(cin, filename);

	if (!load(filename, array, SIZE, numElements))
	{
		cout << "Unable to read file. Please try again." << endl;
		return 1;
	}

	cout << numElements << endl;

	int choice;
	cout << "------------------------------------" << endl;
	cout << "(1) Baseline" << endl;
	cout << "(2) 3 Way" << endl;
	cout << "(3) Median" << endl;
	cout << "(4) Hybrid" << endl;
	cout << "(5) 3 Way + Median" << endl;
	cout << "(6) 3 Way + Hybrid" << endl;
	cout << "(7) Median + Hybrid" << endl;
	cout << "(8) 3 Way + Median + Hybrid" << endl;
	cout << "(0) End Program" << endl;
	cout << endl << "Enter the number of the sorting algorithm you would like to use: ";
	cin >> choice;

	while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 0)
	{
		cout << "That is not a valid input. Try Again!" << endl;
		cin >> choice;
	}

	clock_t start = clock();

	// Code to be timed here 
	if (choice == 1)
		baselineQuickSort(array, 0, numElements - 1);
	else if (choice == 2)
	{
		quickSort3Way(array, 0, numElements - 1);
	}
	else if (choice == 3)
	{
		quickSortMedian(array, 0, numElements - 1);
	}
	else if (choice == 4)
	{
		quickSortHybrid(array, 0, numElements - 1);
	}
	else if (choice == 5)
	{
		quickSort3WayMedian(array, 0, numElements - 1);
	}
	else if (choice == 6)
	{
		quickSort3WayHybrid(array, 0, numElements - 1);
	}
	else if (choice == 7)
	{
		quickSortMedianHybrid(array, 0, numElements - 1);
	}
	else if (choice == 8)
	{
		quickSort3WayHybridMedian(array, 0, numElements - 1);
	}
	else
	{
		cout << "--------------Terminating Program--------------" << endl;
		return 0;
	}
	// ...

	clock_t end = clock();

	double runTime = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Baseline Run time: (s)" << runTime << endl;

	if (isSorted(array, numElements))
		cout << "The array is sorted" << endl;
	else
		cout << "The array is not sorted" << endl;

	return 0;
}



