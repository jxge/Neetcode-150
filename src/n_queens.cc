/*
backtracking (DFS):
Time Complexity: O(N!)
Space Complexity: O(N)

N-Queens II - return the number of solutions
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    void backtrack(int row, int n, vector<string>& board, 
                   vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2, 
                   vector<vector<string>>& result) {
        
        // Base case: If all queens are successfully placed
        if (row == n) {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; ++col) {
            // Check if placing a queen here is safe
            if (cols[col] || diag1[row + col] || diag2[row - col + n]) {
                continue; 
            }

            // Choose: Place the queen
            board[row][col] = 'Q';
            cols[col] = diag1[row + col] = diag2[row - col + n] = true;

            // Explore: Move to the next row
            backtrack(row + 1, n, board, cols, diag1, diag2, result);

            // Unchoose: Backtrack and remove the queen
            board[row][col] = '.';
            cols[col] = diag1[row + col] = diag2[row - col + n] = false;
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        
        // Initialize an empty board filled with '.'
        vector<string> board(n, string(n, '.'));
        
        // Vectors to track attacks in O(1) time
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n, false); // For row + col
        vector<bool> diag2(2 * n, false); // For row - col + n (offset to keep index positive)

        backtrack(0, n, board, cols, diag1, diag2, result);
        return result;
    }
};

// Driver Program
int main() {
    Solution solver;
    int n = 4;
    vector<vector<string>> solutions = solver.solveNQueens(n);

    cout << "Total distinct solutions for " << n << "-Queens: " << solutions.size() << "\n\n";
    
    for (size_t i = 0; i < solutions.size(); ++i) {
        cout << "Solution " << i + 1 << ":\n";
        for (const string& row : solutions[i]) {
            cout << row << "\n";
        }
        cout << "\n";
    }

    return 0;
}


// Find the number of solutions to the N-Queens problem

class Solution {
private:
    int count = 0;

    void backtrack(int row, int n, int cols, int diag1, int diag2) {
        // Base case: If we successfully placed queens in all rows
        if (row == n) {
            count++;
            return;
        }

        // '1' bits represent available positions across columns and diagonals.
        // ((1 << n) - 1) creates a mask of length n containing all 1s.
        //    cols[i]=1  - it's safe to place a queen on the i'th column
        //    diag1[i]=1 - it's safe to place a queen on the i'th column
        //
        int available_slots = ((1 << n) - 1) & ~(cols | diag1 | diag2);  // available_slots[i]=1 if column i is safe to palce a queen

        while (available_slots > 0) {
            // Extract the lowest set bit (the rightmost available slot)
            int position = available_slots & -available_slots;
            
            // Remove this slot from the available pool
            available_slots -= position;

            // Move to the next row:
            // - Shift diag1 left because the diagonal moves left on the next row
            // - Shift diag2 right because the diagonal moves right on the next row
            // Row 0: . Q . .  -> diag1 mask: 0010
            // Row 1: . . \ .  -> Shift left: 0100 (Column 2 is now blocked)
            // Row 2: . . . \  -> Shift left: 1000 (Column 3 is now blocked)

            backtrack(row + 1, n, cols | position, (diag1 | position) << 1, (diag2 | position) >> 1);
        }
    }

public:
    int totalNQueens(int n) {
        count = 0;
        backtrack(0, n, 0, 0, 0);
        return count;
    }
};

// Driver Program
int main() {
    Solution solver;
    
    int n1 = 4;
    cout << "Input: n = " << n1 << "\nOutput: " << solver.totalNQueens(n1) << "\n\n";

    int n2 = 1;
    cout << "Input: n = " << n2 << "\nOutput: " << solver.totalNQueens(n2) << "\n";

    return 0;
}

