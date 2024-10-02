#include <iostream>
#define N 9
using namespace std;

// Initialize the Sudoku grid
int grid[N][N] = {
    {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
};

// Check if num is present in the given column
bool isPresentInCol(int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Check if num is present in the given row
bool isPresentInRow(int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Check if num is present in the 3x3 box
bool isPresentInBox(int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}

// Print the Sudoku grid
void sudokuGrid() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (col == 3 || col == 6)
                cout << " | ";
            cout << grid[row][col] << " ";
        }
        if (row == 2 || row == 5) {
            cout << endl;
            for (int i = 0; i < N; i++)
                cout << "---";
        }
        cout << endl;
    }
}

// Find an empty location in the grid
bool findEmptyPlace(int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0) // marked with 0 is empty
                return true;
    return false;
}

// Check if num can be placed in grid[row][col]
bool isValidPlace(int row, int col, int num) {
    // When num is not present in row, col and the 3x3 box
    return !isPresentInRow(row, num) && 
           !isPresentInCol(col, num) && 
           !isPresentInBox(row - row % 3, col - col % 3, num);
}

// Solve the Sudoku puzzle using backtracking
bool solveSudoku() {
    int row, col;
    if (!findEmptyPlace(row, col))
        return true; // No empty space left, puzzle solved

    for (int num = 1; num <= 9; num++) { // Valid numbers are 1 - 9
        if (isValidPlace(row, col, num)) { // Check if valid
            grid[row][col] = num; // Place num in the grid

            if (solveSudoku()) // Recursively solve the rest of the grid
                return true;

            grid[row][col] = 0; // Backtrack if solution is not found
        }
    }
    return false; // Trigger backtracking
}

int main() {
    if (solveSudoku())
        sudokuGrid();
    else
        cout << "No solution exists";
    return 0;
}
