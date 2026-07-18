/*
Given a 2-D grid of characters board and a list of strings words, return all words that are present in the grid.

For a word to be present it must be possible to form the word with a path in the board with horizontally or vertically neighboring cells. The same cell may not be used more than once in a word.

Example 1:

Input:
board = [
  ["a","b","c","d"],
  ["s","a","a","t"],
  ["a","c","k","e"],
  ["a","c","d","n"]
],
words = ["bat","cat","back","backend","stack"]

Output: ["cat","back","backend"]

Example 2:

Input:
board = [
  ["x","o"],
  ["x","o"]
],
words = ["xoxo"]

Output: []

Constraints:

    1 <= board.length, board[i].length <= 12
    board[i] consists only of lowercase English letter.
    1 <= words.length <= 30,000
    1 <= words[i].length <= 10
    words[i] consists only of lowercase English letters.
    All strings within words are distinct.

Time Complexity: 
   O(W*L+M*N*4*3^(L-1)  where 
       W is the number of words;
       L is the maximum lenght of a word
       M is the number of rows 
       N is the number of columns
       M*N*4*3^(L-1)  // M*N starting positions, first step has 4 avaiable 
                      // directions, remaining steps have 3 avaiable directions.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Trie Node definition
struct TrieNode {
    TrieNode* children[26] = {nullptr};
    string word = ""; // Stores the complete word at the leaf node
};

class Solution {
private:
    void insertWord(TrieNode* root, const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->word = word; // Mark the end of a valid word
    }

    void dfs(vector<vector<char>>& board, int r, int c, TrieNode* node, vector<string>& result) {
        char ch = board[r][c];
        int idx = ch - 'a';
        
        // If the character doesn't exist in the current Trie branch, stop
        if (!node->children[idx]) return;
        
        node = node->children[idx];
        
        // If a valid word is found, add it to the results
        if (!node->word.empty()) {
            result.push_back(node->word);
            node->word = ""; // Avoid duplicate entries of the same word
        }
        
        // Mark the current cell as visited using a placeholder character
        board[r][c] = '#';
        
        // Explore 4 directional neighbors
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < board.size() && nc >= 0 && nc < board[0].size() && board[nr][nc] != '#') {
                dfs(board, nr, nc, node, result);
            }
        }
        
        // Restore the original character (backtrack)
        board[r][c] = ch;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode();
        
        // 1. Build the Trie
        for (const string& word : words) {
            insertWord(root, word);
        }
        
        vector<string> result;
        int rows = board.size();
        if (rows == 0) return result;
        int cols = board[0].size();
        
        // 2. Start DFS from every cell in the grid
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                dfs(board, r, c, root, result);
            }
        }
        
        // (Optional) Code to clean up Trie memory could be added here
        return result;
    }
};

// Driver Program
int main() {
    // Initialize Example 1 data
    vector<vector<char>> board = {
        {'a', 'b', 'c', 'd'},
        {'s', 'a', 'a', 't'},
        {'a', 'c', 'k', 'e'},
        {'a', 'c', 'd', 'n'}
    };
    
    vector<string> words = {"bat", "cat", "back", "backend", "stack"};

    // Print input configuration
    cout << "--- Grid ---" << endl;
    for (const auto& row : board) {
        for (char ch : row) {
            cout << ch << " ";
        }
        cout << endl;
    }
    cout << "\nTarget Words: ";
    for (const string& w : words) cout << "[" << w << "] ";
    cout << "\n\n";

    // Run the solver
    Solution solver;
    vector<string> matchedWords = solver.findWords(board, words);

    // Print final results
    cout << "--- Found Words ---" << endl;
    if (matchedWords.empty()) {
        cout << "No matching words found." << endl;
    } else {
        for (const string& word : matchedWords) {
            cout << "-> " << word << endl;
        }
    }

    return 0;
}

