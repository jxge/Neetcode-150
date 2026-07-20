/*
You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:

- Connect: A cell is connected to adjacent cells horizontally or vertically.
- Region: To form a region connect every 'O' cell. Regions can have any
  shape; they do not need to be squares or rectangles.
- Surround: A region is surrounded if none of the 'O' cells in that region
  are on the edge of the board. Such regions are completely enclosed by 'X'
  cells.

To capture a surrounded region, replace all 'O's with 'X's in-place within the
original board. You do not need to return anything.

Example 1:

Input: board = [
  ["X","X","X","X"],
  ["X","O","O","X"],
  ["X","X","O","X"],
  ["X","O","X","X"]
]

Output: [
  ["X","X","X","X"],
  ["X","X","X","X"],
  ["X","X","X","X"],
  ["X","O","X","X"]
]

Explanation: The bottom 'O' region is not captured because it touches the edge
of the board, so it cannot be surrounded.

Example 2:
Input: board = [["X"]]
Output: [["X"]]
*/


/* 
 * Approach 1: Multi-BFS from '0' cell on the borders
 *   (1) Push all '0' cells on the borders to the queue.
 *   (2) Run BFS on these '0' cells, mark cells visited as 'E' (for escape).
 *   (3) Scan all the cells, replace '0' with 'X', and 'E' with '0'
 * Complexity: O(M * N) where M is the number of rows and N is the number of columns.
 * 
 * Approach 2: 
 *   (1) Start BFS/DFS from any unvisited '0' cell.
 *   (2) During traversal, save the coordinates of the cell in a list.
 *       Replace '0' with '*' as visited.
 *       If the cell is at the border, set a global variable 'isSurrounded' to false.
 *   (3) After the traversal, if 'isSurrounded' is true, loop the coordinate list
 *       and set the cells in the list 'X'.
 *   (4) Once all the '0' cells are visited, restore all '*' cells with '0'. 
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;

        int numRows = board.size();
        int numCols = board[0].size();
        queue<pair<int, int>> q;

        // Step 1: Add all border 'O's to the queue and mark them as Escaped ('E')
        for (int r = 0; r < numRows; ++r) {
            // Left border
            if (board[r][0] == 'O') {
                board[r][0] = 'E';
                q.push({r, 0});
            }
            // Right border
            if (board[r][numCols - 1] == 'O') {
                board[r][numCols - 1] = 'E';
                q.push({r, numCols - 1});
            }
        }

        for (int c = 0; c < numCols; ++c) {
            // Top border
            if (board[0][c] == 'O') {
                board[0][c] = 'E';
                q.push({0, c});
            }
            // Bottom border
            if (board[numRows - 1][c] == 'O') {
                board[numRows - 1][c] = 'E';
                q.push({numRows - 1, c});
            }
        }

        // Step 2: Multi-source BFS to expand inward and mark all reachable 'O's as 'E'
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (const auto& [dr, dc] : directions) {
                int newRow = r + dr;
                int newCol = c + dc;

                // Check boundaries and if the neighbor is a connected 'O'
                if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
                    if (board[newRow][newCol] == 'O') {
                        board[newRow][newCol] = 'E'; // Mark as safe
                        q.push({newRow, newCol});
                    }
                }
            }
        }

        // Step 3: Flip surrounded 'O's to 'X's, and restore safe 'E's back to 'O's
        for (int r = 0; r < numRows; ++r) {
            for (int c = 0; c < numCols; ++c) {
                if (board[r][c] == 'O') {
                    board[r][c] = 'X';
                } else if (board[r][c] == 'E') {
                    board[r][c] = 'O';
                }
            }
        }
    }
};

// Helper function to print the matrix
void printBoard(const vector<vector<char>>& board) {
    cout << "[" << endl;
    for (const auto& row : board) {
        cout << "  [";
        for (size_t i = 0; i < row.size(); ++i) {
            cout << "'" << row[i] << "'";
            if (i < row.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}

// Driver Program
int main() {
    Solution solver;

    // Example 1
    vector<vector<char>> board1 = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };

    cout << "Example 1 Input:" << endl;
    printBoard(board1);

    solver.solve(board1);

    cout << "\nExample 1 Output:" << endl;
    printBoard(board1);

    // Example 2
    vector<vector<char>> board2 = {{'X'}};

    cout << "\nExample 2 Input:" << endl;
    printBoard(board2);

    solver.solve(board2);

    cout << "\nExample 2 Output:" << endl;
    printBoard(board2);

    return 0;
}

