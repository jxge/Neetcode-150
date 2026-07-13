/*
Time Complexity: O(M * N * 4^L),  where M * N is the grid size and L is the length of the word. S
Space Complexity: O(L) used for the stack used by dfs

Optimization idea:
  (1) If the last character of the string is rarer on the board than the the first character, reverse the string.
  (2) If a letter frequency in the string is greater than the letter frequency on the bard, return false immediately.
  (3) Instead of replace the visited letter with '#', use XOR: board[r][c] ^= 128.
  (4) Use a direction array:
      const array<int, 5> dirs = {0, 1, 0, -1, 0};
      for (int i = 0; i < 4; ++i) 
         if (dfs(board, word, r + dirs[i], c + dirs[i + 1], index + 1)) 
             return true; 
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    int rows;
    int cols;

    bool dfs(vector<vector<char>>& board, const string& word, int r, int c, int index) {
        // Base case: if all characters are successfully matched
        if (index == word.length()) {
            return true;
        }

        // Boundary conditions and character mismatch checks
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != word[index]) {
            return false;
        }

        // Mark the current cell as visited
        char temp = board[r][c];
        board[r][c] = '#';

        // Explore all 4 orthogonal directions
        bool found = dfs(board, word, r + 1, c, index + 1) || // Down
                     dfs(board, word, r - 1, c, index + 1) || // Up
                     dfs(board, word, r, c + 1, index + 1) || // Right
                     dfs(board, word, r, c - 1, index + 1);   // Left

        // Backtrack: restore the original character
        board[r][c] = temp;

        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty() || word.empty()) {
            return false;
        }

        rows = board.size();
        cols = board[0].size();

        // Iterate through every cell to find the starting letter
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (board[r][c] == word[0]) {
                    if (dfs(board, word, r, c, 0)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

// Driver Program
int main() {
    Solution solver;

    // Test Case Grid
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'D'},
        {'S', 'A', 'A', 'T'},
        {'A', 'C', 'A', 'E'}
    };

    // Example 1
    string word1 = "CAT";
    cout << "Word: \"" << word1 << "\" -> " 
         << (solver.exist(board, word1) ? "true" : "false") << endl;

    // Example 2
    string word2 = "BAT";
    cout << "Word: \"" << word2 << "\" -> " 
         << (solver.exist(board, word2) ? "true" : "false") << endl;

    return 0;
}

