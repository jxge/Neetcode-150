#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool rows[9][9] = {false};
        bool cols[9][9] = {false};
        bool boxes[9][9] = {false};
        
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] == '.') continue;
                
                int digit = board[r][c] - '1';
                int boxIdx = (r / 3) * 3 + (c / 3);
                
                if (rows[r][digit] || cols[c][digit] || boxes[boxIdx][digit]) {
                    return false;
                }
                
                rows[r][digit] = true;
                cols[c][digit] = true;
                boxes[boxIdx][digit] = true;
            }
        }
        return true;
    }
};

int main() {
    Solution solver;

    // Test Case 1: Valid Sudoku board from your example
    vector<vector<char>> validBoard = {
        {'1','2','.','.','3','.','.','.','.'},
        {'4','.','.','5','.','.','.','.','.'},
        {'.','9','8','.','.','.','.','.','3'},
        {'5','.','.','.','6','.','.','.','4'},
        {'.','.','.','8','.','3','.','.','5'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','.','.','.','.','.','2','.','.'},
        {'.','.','.','4','1','9','.','.','8'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    // Test Case 2: Invalid Sudoku board (Row 0 has duplicate '1's)
    vector<vector<char>> invalidBoard = {
        {'1','2','.','.','3','.','.','.','1'}, // Duplicate '1' here
        {'4','.','.','5','.','.','.','.','.'},
        {'.','9','8','.','.','.','.','.','3'},
        {'5','.','.','.','6','.','.','.','4'},
        {'.','.','.','8','.','3','.','.','5'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','.','.','.','.','.','2','.','.'},
        {'.','.','.','4','1','9','.','.','8'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    // Run tests
    cout << boolalpha; // Prints true/false instead of 1/0
    cout << "Test Case 1 (Valid Board): " << solver.isValidSudoku(validBoard) << " (Expected: true)" << endl;
    cout << "Test Case 2 (Invalid Board): " << solver.isValidSudoku(invalidBoard) << " (Expected: false)" << endl;

    return 0;
}
