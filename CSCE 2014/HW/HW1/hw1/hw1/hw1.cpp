// hw1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// Purpose: PF2 - HW1: Recursive Maze Solver
// Author:  Blake Fasse
// UAID:    010702626

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Global Constants
const int MAX_ROWS = 10;
const int MAX_COLS = 10;

const char WALL = '*';
const char SPACE = '_';
const char PATH = '!';

// Reads the maze description from the given file into the given maze.
// Returns true if the operation succeeds and false if the file couldn't be opened.
bool loadMaze(const string& filename, char maze[MAX_ROWS][MAX_COLS])
{
	// TODO: Implement
	ifstream din;
	din.open(filename.c_str());
	if (!din)
		return false;
	for (int r = 0; r < MAX_ROWS; ++r)
	{
		for (int c = 0; c < MAX_COLS; ++c)
		{
			din >> maze[r][c];
		}
	}
	din.close();
	return true;
}

// Prints the given maze to the console.
void printMaze(const char maze[MAX_ROWS][MAX_COLS])
{
	// TODO: Implement
	for (int r = 0; r < MAX_ROWS; ++r)
	{
		for (int c = 0; c < MAX_COLS; ++c)
		{
			cout << maze[r][c] << " ";
		}
		cout << endl;
	}
}

// Returns true if the proposed move (r,c) is a valid one. Valid moves are within
// the range of the board, do not move into a wall, and do not move to a cell
// we have already seen.
bool validMove(const int r, const int c, const char maze[MAX_ROWS][MAX_COLS], const bool seen[MAX_ROWS][MAX_COLS])
{
	// TODO: Implement
	if (r < 0 || r >= MAX_ROWS || c < 0 || c >= MAX_COLS || maze[r][c] == WALL || seen[r][c])
		return false;

	return true;
}

// Returns true if the given cell is an entry point for the maze. Entry points
// must be on the outer edge and must not be walls.
bool entryPoint(const int r, const int c, const char maze[MAX_ROWS][MAX_COLS])
{
	// (r, c) is an entry IF
	// 1. (r, c) is on the outer edge of the maze
	// 2. maze[r][c] != WALL
	
	return ((r == 0 || r == MAX_ROWS - 1 || c == 0 || c == MAX_COLS - 1) &&
		maze[r][c] != WALL);
}

// Searches the maze for a valid entry point. If one is found, the 
// coordinates will be saved in 'startRow' and 'startCol'. If one is not found,
// the function will return false and 'startRow' and 'startCol' will be set
// to -1.
bool findEntryPoint(const char maze[MAX_ROWS][MAX_COLS], int& startRow, int& startCol)
{
	startRow = -1;
	startCol = -1;
	for (int r = 0; r < MAX_ROWS; ++r)
	{
		for (int c = 0; c < MAX_COLS; ++c) 
		{
			if (entryPoint(r, c, maze))
			{
				startRow = r;
				startCol = c;
				return true;
			}
			
		}
	}
	return false;
}

// Recursively finds a solution to the given maze.
//
// Inputs:
// 'maze' is the maze we're searching.
// 'startRow' and 'startCol' hold the entry point into the maze.
// 'r' and 'c' tell us which cell we're currently working on.
//
// Outputs:
// 'seen' tells us whether or not we've already been to a given cell.
// 'solution' will hold the final answer once we're done (if there is one).
//
// This function will return true when a solution is found and false if there
// is no such solution. 
bool solveHelper(const char maze[MAX_ROWS][MAX_COLS], const int startRow, const int startCol, const int r, const int c,
                 bool seen[MAX_ROWS][MAX_COLS], char solution[MAX_ROWS][MAX_COLS])
{
	// TODO: Implement
	if (entryPoint(r, c, maze) && (r != startRow || c != startCol))
	{
		solution[r][c];
		return true;
	}
	else
	{
		seen[r][c] = { true };

		if (solveHelper(maze, startRow, startCol, r - 1, c, seen, solution) && validMove(r - 1, c, maze, seen))
		{
			solution[r - 1][c] = PATH;
			return true;
		}
		else if (solveHelper(maze, startRow, startCol, r, c + 1, seen, solution) && validMove(r, c + 1, maze, seen))
		{
			solution[r][c + 1] = PATH;
			return true;
		}
		else if (solveHelper(maze, startRow, startCol, r + 1, c, seen, solution) && validMove(r + 1, c, maze, seen))
		{
			solution[r + 1][c] = PATH;
			return true;
		}
		else if (solveHelper(maze, startRow, startCol, r, c - 1, seen, solution) && validMove(r, c - 1, maze, seen))
		{
			solution[r][c - 1] = PATH;
			return true;
		}
		else
			return false;
	}
}

// Attempts to find a solution to the given maze. If one is found, it will be
// placed in 'solution' and true will be returned. Otherwise, false will be
// returned.
bool solve(const char maze[MAX_ROWS][MAX_COLS], char solution[MAX_ROWS][MAX_COLS])
{
	// TODO: Implement. 

	// 1. Create and initialize the 'seen' 2D array.
	bool seen[MAX_ROWS][MAX_COLS] = {false};
	// 2. Find an entry point using the findEntryPoint() function.
	int startRows;
	int startCols;
	if (!findEntryPoint(maze, startRows, startCols))
		return false;
	// 3. Initialize 'solution'.
	for (int r = 0; r < MAX_ROWS; ++r)
	{
		for (int c = 0; c < MAX_COLS; ++c)
		{
			solution[r][c] = maze[r][c];
		}
	}

	// 4. Call solveHelper() with the proper parameters to get the recursion started.
	return solveHelper(maze, startRows, startCols, startRows, startCols, seen, solution);
}

int main()
{
	// Variables
	char maze[MAX_ROWS][MAX_COLS];
	char solution[MAX_ROWS][MAX_COLS];

	// Get the maze filename from the user
	cout << "Please enter the name of the maze file: " << endl;
	string filename = "maze.txt";
	//getline(cin, filename);

	// Try to load the maze description from the file
	if (!loadMaze(filename, maze))
	{
		cout << "Unable to read file. Please try again." << endl;
		return 1;
	}

	// Print the original maze
	cout << "Maze: " << endl;
	printMaze(maze);
	cout << endl;

	// Find the solution or show that there is none.
	if (solve(maze, solution))
	{
		cout << "Solution: " << endl;
		printMaze(solution);
	}
	else
	{
		cout << "No solution." << endl;
	}
	
	return 0;
}