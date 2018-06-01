// 6_7_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
using namespace std;

const int ROWS = 10;
const int COLS = 10;


void floodfill(int array[ROWS][COLS], int color, int x, int y)
{
	// Bounds checking
	if (x < 0 || x >= 10 || y < 0 || y >= 10) return;

	// Fundamental base case
	//y is rows, x is columns
	//array starts in top left corner 
	else if (array[y][x] == color) return;

	// Recursive cases
	else
	{
		array[y][x] = color;
		//goes up
		floodfill(array, color, x, y - 1);
		//goes right
		//floodfill(array, color, x + 1, y);
		for (int r = x + 1; r < COLS; ++r)
			if (array[y][r] == color) 
				break;
			else
				array[y][r] = color;
		//goes down
		floodfill(array, color, x, y + 1);
		//goes left
		//floodfill(array, color, x - 1, y);
		for (int c = x - 1; c >= 0; --c)
		{
			if (array[y][c] == color) 
				break;
			else
				array[y][c] = color;
		}
	}
}

int main()
{
	// Initialize the board to a cross
	int colors[ROWS][COLS] = { 0 };
	for (int c = 0; c < COLS; ++c)
	{
		colors[0][c] = 1;
		colors[ROWS - 1][c] = 1;
		colors[ROWS / 2][c] = 1;
	}
	for (int r = 0; r < ROWS; ++r)
	{
		colors[r][0] = 1;
		colors[r][COLS - 1] = 1;
		colors[r][COLS / 2] = 1;
	}

	// Print the board
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			cout << colors[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Fill the top-left quadrant
	floodfill(colors, 1, 2, 2);

	// Print the board again
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			cout << colors[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}

