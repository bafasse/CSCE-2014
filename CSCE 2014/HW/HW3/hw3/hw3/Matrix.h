// Purpose: PF2 - Matrix class
// Author:  [Your name here]
// Date:    [Enter date here]

// Header guards - Used to ensure this file doesn't get copied
// into the final executable multiple times. Generally, ALL
// header files should have guards around the content to guard
// against this possibility.
#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
using namespace std;

// This class represents a generic resizable 2D matrix. It supports
// element access and several statistics calculations.
template <class T>
class Matrix
{
public:

	// Constructors / Destructors
	Matrix();
	Matrix(const int rows, const int cols);
	Matrix(const Matrix<T>& orig);
	~Matrix();

	// Display
	void print() const;

	// Size modification
	void addRow();
	void addCol();
	void resize(const int rows, const int cols);

	// Element access
	T getCell(const int r, const int c) const;
	void setCell(const int r, const int c, const T& value);
	void fill(const T& value);

	// Operator Access
	T& operator()(const int r, const int c) { return mData[r * mCols + c]; }
	const T& operator()(const int r, const int c) const { return mData[r * mCols + c]; }

	// Statistics - Window [(r1, c1), (r2, c2)]
	T sum(const int r1, const int c1, const int r2, const int c2)       const;
	T product(const int r1, const int c1, const int r2, const int c2)   const;
	T max(const int r1, const int c1, const int r2, const int c2)       const;
	double mean(const int r1, const int c1, const int r2, const int c2) const;

	// Statistics - Complete Matrix
	T sum()       const; // Call other version of sum()
	T product()   const;
	T max()       const;
	double mean() const;

	// Getters / Setters
	int getRows() const; //return rows
	int getCols() const; // return cols

private:
	T* mData;
	int mRows, mCols;
};

// [Your implementations go here]

template <class T>
Matrix<T>::Matrix()
{
	mRows = 0;
	mCols = 0;
	mData = NULL;
}

template <class T>
Matrix<T>::Matrix(const int rows, const int cols)
{
	mRows = 0;
	mCols = 0;
	mData = NULL;
	resize(mRows, mCols);
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& orig)
{
	mRows = 0;
	mCols = 0;
	mData = NULL;
	resize(mRows, mCols);
}

template <class T>
Matrix<T>::~Matrix()
{
	mRows = 0;
	mCols = 0;
	mData = NULL;
	resize(mRows, mCols);
}
// -------------------------------------------------------------------
template <class T>
void Matrix<T>::print() const
{
	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mCols; ++c)
			cout << mData[r * mCols + c] << " ";
		cout << endl;
	}
}
// --------------------------------------------------------------------
template <class T>
void Matrix<T>::addRow()
{
	resize(mRows + 1, mCols);
}

template <class T>
void Matrix<T>::addCol()
{
	resize(mRows, mCols + 1);
}

template <class T>
void Matrix<T>::resize(const int rows, const int cols)
{
	if (rows != mRows && cols != mCols)
	{
		T* data = new T[rows * cols]();

		// 2. Copy everything from mData to data - 2 for loops
		for (int r = 0; r < fmin(rows, mRows); ++r)
		{
			for (int c = 0; c < fmin(cols, mCols); ++c)
			{
				mData[r * mCols + c] = data[r * mCols + c];
			}
		}

		delete[] mData;
		mData = data;
		mRows = rows;
		mCols = cols;
	}
}
//// -----------------------------------------------------------------------
template <class T>
T Matrix<T>::getCell(const int r, const int c) const
{
	if (r >= 0 && r < mRows && c >= 0 && c < mCols)
		return mData[r * mCols + c];
	else return T();
}

template <class T>
void Matrix<T>::setCell(const int r, const int c, const T& value)
{
	if (r!= 0 && r < mRows && c != 0 && c < mCols)
		mData[r * mCols + c] = value;
}

template <class T>
void Matrix<T>::fill(const T& value)
{
	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mCols; ++c)
		{
			mData[r * mCols + c] = value;
		}
	}
}

//// --------------------------------------------------------------------------
template <class T>
T Matrix<T>::sum(const int r1, const int c1, const int r2, const int c2) const
{
	T value = 0;
	for (int i = r1; i <= r2; ++i)
	{
		for (int j = c1; j <= c2; ++j)
		{
			value += mData[i * mCols + j];
		}
	}
	return value;
}

template <class T>
T Matrix<T>::product(const int r1, const int c1, const int r2, const int c2)   const
{
	T value = 1;
	for (int i = r1; i <= r2; ++i)
	{
		for (int j = c1; j <= c2; ++j)
		{
			value *= mData[i * mCols + j];
		}
	}
	return value;
}

template <class T>
T Matrix<T>::max(const int r1, const int c1, const int r2, const int c2)       const
{
	int max = r1;
	for (int i = r1; i < r2; ++i)
	{
		for (int j = c1; j < c2; ++j)
		{
			if (j > i)
				max = j;
		}
	}
	return max;
}

template <class T>
double Matrix<T>::mean(const int r1, const int c1, const int r2, const int c2) const
{
	T value = 0;
	int count = 0;
	for (int i = r1; i <= r2; ++i)
	{
		for (int j = c1; j <= c2; ++j)
		{
			value += mData[i * mCols + j];
			++count;
		}
	}
	return value / count;
}
// -----------------------------------------------------------------------
template <class T>
T Matrix<T>::sum() const
{
	return sum(mRows, mCols, mRows, mCols);
}

template <class T>
T Matrix<T>::product() const
{
	return product(mRows, mCols, mRows, mCols);
}

template <class T>
T Matrix<T>::max() const
{
	return max(mRows, mCols, mRows, mCols);
}

template <class T>
double Matrix<T>::mean() const
{
	return mean(mRows, mCols, mRows, mCols);
}
// -----------------------------------------------------------------------
template <class T>
int Matrix<T>::getRows() const
{
	return mRows;
}

template <class T>
int Matrix<T>::getCols() const
{
	return mCols;
}
#endif
