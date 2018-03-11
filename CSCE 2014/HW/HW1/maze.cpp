// Purpose: PF2 - HW1: Recursive Maze Solver
// Author:  [YOUR NAME HERE]
// UAID:    [YOUR UAID HERE]

#include <iostream>
#include <fstream>
using namespace std;

// Global Constants
const int MAX_ROWS = 10;
const int MAX_COLS = 10;

const char WALL    = '*';
const char SPACE   = '_';
const char PATH    = '!';

// Reads the maze description from the given file into the given maze.
// Returns true if the operation succeeds and false if the file couldn't be opened.
bool loadMaze(const string& filename, char maze[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
    return true;
}

// Prints the given maze to the console.
void printMaze(const char maze[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
}

// Returns true if the proposed move (r,c) is a valid one. Valid moves are within
// the range of the board, do not move into a wall, and do not move to a cell
// we have already seen.
bool validMove(const int r, const int c, 
    const char maze[MAX_ROWS][MAX_COLS], const bool seen[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
    return true;
}

// Returns true if the given cell is an entry point for the maze. Entry points
// must be on the outer edge and must not be walls.
bool entryPoint(const int r, const int c, const char maze[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
    return true;
}

// Searches the maze for a valid entry point. If one is found, the 
// coordinates will be saved in 'startRow' and 'startCol'. If one is not found,
// the function will return false and 'startRow' and 'startCol' will be set
// to -1.
bool findEntryPoint(const char maze[MAX_ROWS][MAX_COLS], int& startRow, int& startCol)
{
    startRow = -1;
    startCol = -1;
    return true;
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
bool solveHelper(
    const char maze[MAX_ROWS][MAX_COLS], 
    const int startRow, const int startCol, 
    const int r, const int c, 
    bool seen[MAX_ROWS][MAX_COLS], 
    char solution[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement
    return true;
}

// Attempts to find a solution to the given maze. If one is found, it will be
// placed in 'solution' and true will be returned. Otherwise, false will be
// returned.
bool solve(const char maze[MAX_ROWS][MAX_COLS], char solution[MAX_ROWS][MAX_COLS])
{
    // TODO: Implement. 
    
    // 1. Create and initialize the 'seen' 2D array.
    
    // 2. Find an entry point using the findEntryPoint() function.
    
    // 3. Initialize 'solution'.
    
    // 4. Call solveHelper() with the proper parameters to get the recursion started.
    
    return true;
}

int main()
{
    // Variables
    char maze[MAX_ROWS][MAX_COLS];
    char solution[MAX_ROWS][MAX_COLS];
    
    // Get the maze filename from the user
    cout << "Please enter the name of the maze file: " << endl;
    string filename;
    getline(cin, filename);
    
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