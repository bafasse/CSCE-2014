// Purpose: PF2 - HW1: Recursive Maze Solver
// Author:  Jon C. Hammer
// Date:    5/19/2107

#include <iostream>
#include <fstream>
using namespace std;

// Constants
const int MAX_ROWS = 10;
const int MAX_COLS = 10;
const char WALL    = '*';
const char PATH    = '!';

// Reads the maze description from the given file into the given maze.
// Returns true if the operation succeeds and false if the file couldn't be opened.
bool loadMaze(const string& filename, char maze[MAX_ROWS][MAX_COLS])
{
    ifstream din(filename.c_str());
    if (!din) return false;
    
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            din >> maze[i][j];
        }
    }
    din.close();
    
    return true;
}

// Prints the given maze to the screen.
void printMaze(const char maze[MAX_ROWS][MAX_COLS])
{
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

// Returns true if the proposed move is a valid one. Valid moves are within
// the range of the board, do not move into a wall, and do not move to a cell
// we have already seen.
bool validMove(const int r, const int c, 
    const char maze[MAX_ROWS][MAX_COLS], const bool seen[MAX_ROWS][MAX_COLS])
{
    return r >= 0             && c >= 0       && 
           r < MAX_ROWS       && c < MAX_COLS && 
           maze[r][c] != WALL && !seen[r][c];
}

// Returns true if the given cell is an entry point for the maze. Entry points
// must be on the outer edge and must not be walls.
bool entryPoint(const int r, const int c, const char maze[MAX_ROWS][MAX_COLS])
{
    return (r == 0 || r == MAX_ROWS - 1 || c == 0 || c == MAX_COLS - 1) &&
            maze[r][c] != WALL;
}

// Searches the maze for a valid entry point. If one is found, the 
// coordinates will be saved in 'startRow' and 'startCol'. If one is not found,
// the function will return false.
bool findEntryPoint(const char maze[MAX_ROWS][MAX_COLS], int& startRow, int& startCol)
{
    startRow = -1;
    startCol = -1;
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            if (entryPoint(i, j, maze))
            {
                startRow = i;
                startCol = j;
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
bool solveHelper(
    const char maze[MAX_ROWS][MAX_COLS], 
    const int startRow, const int startCol, 
    const int r, const int c, 
    bool seen[MAX_ROWS][MAX_COLS], 
    char solution[MAX_ROWS][MAX_COLS])
{
    // Base condition - We've found the way out!
    if (entryPoint(r, c, maze) && (r != startRow || c != startCol))
    {
        solution[r][c] = PATH;
        return true;
    }
    
    // Mark this cell since we've been here
    seen[r][c] = true;
    
    // Try going up
    if (validMove(r-1, c, maze, seen) && 
        solveHelper(maze, startRow, startCol, r - 1, c, seen, solution))
    {
        solution[r][c] = PATH;
        return true;
    }
    
    // Try going right
    else if (validMove(r, c + 1, maze, seen) && 
        solveHelper(maze, startRow, startCol, r, c + 1, seen, solution))
    {
        solution[r][c] = PATH;
        return true;
    }
    
    // Try going down
    else if (validMove(r + 1, c, maze, seen) && 
        solveHelper(maze, startRow, startCol, r + 1, c, seen, solution))
    {
        solution[r][c] = PATH;
        return true;
    }
    
    // Try going left
    else if (validMove(r, c - 1, maze, seen) && 
        solveHelper(maze, startRow, startCol, r, c - 1, seen, solution))
    {
        solution[r][c] = PATH;
        return true;
    }
    
    // We've run into a dead end. We'll need to backtrack to find our way out.
    else return false;
}

// Attempts to find a solution to the given maze. If one is found, it will be
// placed in 'solution' and true will be returned. Otherwise, false will be
// returned.
bool solve(const char maze[MAX_ROWS][MAX_COLS], char solution[MAX_ROWS][MAX_COLS])
{
    bool seen[MAX_ROWS][MAX_COLS] = {false};

    // Figure out where to start
    int startRow, startCol;
    if (!findEntryPoint(maze, startRow, startCol)) 
        return false;
    
    // Initialize 'solution' to contain the maze
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            solution[i][j] = maze[i][j];
        }
    }

    // Use DFS to solve the maze
    return solveHelper(maze, startRow, startCol, startRow, startCol, seen, solution);
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