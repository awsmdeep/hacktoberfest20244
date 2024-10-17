#include <iostream>
#include <vector>
using namespace std;

#define N 9

// Function to check if placing num in board[row][col] is valid
bool isSafe(vector<vector<int>>& board, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; x++)
        if (board[row][x] == num)
            return false;

    // Check the column
    for (int x = 0; x < N; x++)
        if (board[x][col] == num)
            return false;

    // Check the 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Backtracking function to solve Sudoku
bool solveSudoku(vector<vector<int>>& board) {
    int row = -1, col = -1;
    bool isEmpty = true;

    // Find an unassigned location
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty) break;
    }

    // No unassigned location left, return true
    if (isEmpty) return true;

    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            // Place num in the cell
            board[row][col] = num;

            // Recur to solve the next cells
            if (solveSudoku(board))
                return true;

            // If placing num leads to no solution, backtrack
            board[row][col] = 0;
        }
    }
    return false; // Trigger backtracking
}

// Function to print the Sudoku board
void printBoard(vector<vector<int>>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

int main() {
    // Example Sudoku puzzle (0 represents an empty cell)
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        cout << "Solved Sudoku board:" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
