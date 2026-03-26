#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<char>>& board, int row, int col, char dig) {
    // Check horizontal
    for (int j = 0; j < 9; j++) {
        if (board[row][j] == dig) {
            return false;
        }
    }
    // Check vertical
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == dig) {
            return false;
        }
    }
    // Check 3x3 subgrid
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == dig) {
                return false;
            }
        }
    }
    return true;
}

bool helper(vector<vector<char>>& board, int row, int col) {
    if (row == 9) {
        return true;
    }
    int nextRow = row, nextCol = col + 1; //next is used to for the next recursive call of helper function
    if (nextCol == 9) {
        nextRow = row + 1;
        nextCol = 0;
    }
    if (board[row][col] != '.') {
        return helper(board, nextRow, nextCol);
    }
    for (char dig = '1'; dig <= '9'; dig++) {
        if (isSafe(board, row, col, dig)) {
            board[row][col] = dig;
            if (helper(board, nextRow, nextCol)) {
                return true;
            }
            board[row][col] = '.';
        }
    }
    return false;
}

void solveSudoku(vector<vector<char>>& board) {
    helper(board, 0, 0);
}


//this code is for the valid sudoku problem
//here we are only checking that the given sudoku is valid or not , we are not solving the sudoku
/*
ALGORITHM: Valid Sudoku Checker
================================
1. Create three 2D boolean arrays to track used numbers:
    - rows[9][9]: tracks which digits (0-8) are used in each row
    - cols[9][9]: tracks which digits (0-8) are used in each column
    - boxes[9][9]: tracks which digits (0-8) are used in each 3x3 box

2. Iterate through each cell (i, j) in the 9x9 board:
    a. If cell is not empty ('.')
    b. Convert character digit to index (0-8) by subtracting '1'
    c. Calculate which 3x3 box this cell belongs to using formula: (i/3)*3 + (j/3)
    d. Check if this digit already exists in:
        - Current row, current column, or current box
    e. If found duplicate, return false (invalid sudoku)
    f. Otherwise, mark this digit as used in row, column, and box
    
3. If all cells are validated without conflict, return true (valid sudoku)

TIME COMPLEXITY: O(1) - Fixed 81 cells to check
SPACE COMPLEXITY: O(1) - Fixed size arrays
*/

class Solution {
public:
     bool isValidSudoku(vector<vector<char>>& board) {
          // Arrays to track if a digit (0-8) is used in each row, column, and box
          bool rows[9][9] = {false};    // rows[i][digit] = true if digit used in row i
          bool cols[9][9] = {false};    // cols[j][digit] = true if digit used in column j
          bool boxes[9][9] = {false};   // boxes[boxId][digit] = true if digit used in box

          // Iterate through all 81 cells in the board
          for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                     // Skip empty cells
                     if (board[i][j] != '.') {
                          // Convert character '1'-'9' to index 0-8
                          int num = board[i][j] - '1';
                          
                          // Calculate which 3x3 box this cell belongs to (0-8)
                          // (i/3)*3 gives box row (0, 3, or 6)
                          // (j/3) gives box column (0, 1, or 2)
                          // Combined: results in box index 0-8
                          int boxIndex = (i / 3) * 3 + (j / 3);
                          
                          // If digit already exists in row, column, or box, sudoku is invalid
                          if (rows[i][num] || cols[j][num] || boxes[boxIndex][num]) {
                                return false;
                          }
                          
                          // Mark this digit as used in current row, column, and box
                          rows[i][num] = cols[j][num] = boxes[boxIndex][num] = true;
                     }
                }
          }
          // All cells validated successfully
          return true;
     }
};

int main() {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    solveSudoku(board);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}