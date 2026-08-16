/*
Longest Increasing Path in Matrix

You are given a 2-D grid of integers matrix, where each integer is greater than or equal to 0.

Return the length of the longest strictly increasing path within matrix.

From each cell within the path, you can move either horizontally or vertically. You may not move diagonally.

Example 1:

Input: matrix = [[5,5,3],
                 [2,3,6],
                 [1,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 3, 6] or [1, 2, 3, 5].

Example 2:
Input: matrix = [[1,2,3],
                 [2,1,4],
                 [7,6,5]]
Output: 7

Explanation: The longest increasing path is [1, 2, 3, 4, 5, 6, 7].

Constraints:
    1 <= matrix.length, matrix[i].length <= 100
*/


/*
Solution 1: DFS with memoization
  time complexity: O(m * n) where m is the number of rows and n is the number of columns.

Solution 2: Topolotical sort (Kahn's algorithm)
  1. Consider each cell as a vertex. For each vertex and its neighboring
     vertices, add an edge from the vertex to the neighboring vertex if the 
     cell is greater than the neighboring vertex.
  2. Run Kahn's Algorithm (starting vertices with zero out-degree and use 
     BFS to peel layers. 
  3. The total layers peeled off is the length of the longest increasing path.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution1 {
private:
    int rows, cols;
    // Direction vectors for moving up, down, left, and right
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int dfs(int r, int c, vector<vector<int>>& matrix, vector<vector<int>>& memo) {
        // Return the result if it has already been calculated
        if (memo[r][c] != 0) {
            return memo[r][c];
        }

        int max_len = 1; // Minimum path length for any cell is 1

        // Explore all 4 neighbor directions
        for (auto& dir : dirs) {
            int nr = r + dir[0];
            int nc = c + dir[1];

            // Check boundaries and ensure the next step is strictly greater
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && matrix[nr][nc] > matrix[r][c]) {
                max_len = max(max_len, 1 + dfs(nr, nc, matrix, memo));
            }
        }

        // Cache the result before returning
        return memo[r][c] = max_len;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        rows = matrix.size();
        cols = matrix[0].size();
        
        // Memoization table initialized to 0
        vector<vector<int>> memo(rows, vector<int>(cols, 0));
        int longest_path = 0;

        // Run DFS from every cell in the grid
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                longest_path = max(longest_path, dfs(r, c, matrix, memo));
            }
        }

        return longest_path;
    }
};

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

class Solution2 {
private:
    int rows, cols;
    // Direction vectors for moving up, down, left, and right
    const array<array<int, 2>, 4> dirs = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

    int dfs(int r, int c, vector<vector<int>>& matrix, vector<vector<int>>& memo) {
        if (memo[r][c] != 0) {
            return memo[r][c];
        }

        int max_len = 1;

        for (const auto& dir : dirs) {
            int nr = r + dir[0];
            int nc = c + dir[1];

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && matrix[nr][nc] > matrix[r][c]) {
                max_len = max(max_len, 1 + dfs(nr, nc, matrix, memo));
            }
        }

        return memo[r][c] = max_len;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        rows = matrix.size();
        cols = matrix[0].size();
        
        vector<vector<int>> memo(rows, vector<int>(cols, 0));
        int longest_path = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                longest_path = max(longest_path, dfs(r, c, matrix, memo));
            }
        }

        return longest_path;
    }
};

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int rows = matrix.size();
        int cols = matrix[0].size();
        
        // Outdegree table to track how many strictly smaller neighbors a cell has
        vector<vector<int>> outdegree(rows, vector<int>(cols, 0));
        
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        queue<pair<int, int>> q;

        // Step 1: Calculate outdegree for every cell
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                for (auto& dir : dirs) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    // If neighbor is strictly smaller, current cell points to it
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && matrix[nr][nc] < matrix[r][c]) {
                        outdegree[r][c]++;
                    }
                }
                // Step 2: If a cell points to nothing smaller, it's a leaf node
                if (outdegree[r][c] == 0) {
                    q.push({r, c});
                }
            }
        }

        // Step 3: Peel the graph layer by layer using BFS
        int path_length = 0;
        while (!q.empty()) {
            int layer_size = q.size();
            path_length++; // Each layer processed increases our path length
            
            for (int i = 0; i < layer_size; ++i) {
                auto [r, c] = q.front();
                q.pop();
                
                // Look at neighbors that might be pointing TO the current cell
                for (auto& dir : dirs) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    // If the neighbor is strictly larger, it means neighbor -> current
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && matrix[nr][nc] > matrix[r][c]) {
                        outdegree[nr][nc]--; // Break the connection
                        
                        if (outdegree[nr][nc] == 0) {
                            q.push({nr, nc}); // Neighbor becomes a new leaf
                        }
                    }
                }
            }
        }

        return path_length;
    }
};


// Helper function to print a 2D matrix cleanly
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        cout << "  [ ";
        for (int val : row) {
            cout << val << " ";
        }
        cout << "]\n";
    }
}

// Test Case Struct
struct TestCase {
    int id;
    vector<vector<int>> matrix;
    int expected;
};

template<class Solution>
int test() {
    Solution solver;

    // Define test scenarios
    vector<TestCase> testCases = {
        {
            1, 
            {{5, 5, 3}, {2, 3, 6}, {1, 1, 1}}, 
            4
        },
        {
            2, 
            {{1, 2, 3}, {2, 1, 4}, {7, 6, 5}}, 
            7
        },
        {
            3, 
            {{1}}, 
            1
        }
    };

    bool allPassed = true;

    cout << "==========================================\n";
    cout << "RUNNING LONGEST INCREASING PATH TEST CASES\n";
    cout << "==========================================\n\n";

    for (const auto& tc : testCases) {
        cout << "Test Case #" << tc.id << ":\n";
        cout << "Input Matrix:\n";
        printMatrix(tc.matrix);
        
        int result = solver.longestIncreasingPath(const_cast<vector<vector<int>>&>(tc.matrix));
        
        cout << "Expected Output: " << tc.expected << "\n";
        cout << "Actual Output:   " << result << "\n";

        if (result == tc.expected) {
            cout << "Result:          [PASSED]\n";
        } else {
            cout << "Result:          [FAILED]\n";
            allPassed = false;
        }
        cout << "------------------------------------------\n";
    }

    if (allPassed) {
        cout << "SUCCESS: All test cases passed successfully!\n";
    } else {
        cout << "FAILURE: Some test cases failed.\n";
    }

    return 0;
}

int main()
{
    test<Solution1>();
    test<Solution2>();
    return 0;
}
