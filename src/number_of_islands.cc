/*
Given a 2D grid grid where '1' represents land and '0' represents water, count and return the number of islands.

An island is formed by connecting adjacent lands horizontally or vertically and is surrounded by water. You may assume water is surrounding the grid (i.e., all the edges are water).

Example:

Input: grid = [
    ["1","1","0","0","1"],
    ["1","1","0","0","1"],
    ["0","0","1","0","0"],
    ["0","0","0","1","1"]
  ]
Output: 4

Constraints:
    1 <= grid.length, grid[i].length <= 100
    grid[i][j] is '0' or '1'.

*/


/*
Use a Depth-First Search (DFS) algorithm to traverse and mark connected land cells. 
Time Complexity: O(M * N), where M is the number of row and N is columns.

Algorithm 1: Recusive DFS 
Algorithm 2: Iterative DFS
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution1 {
private:
    // Helper function to perform DFS and mark visited land cells
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int nr = grid.size();
        int nc = grid[0].size();

        // Base case: check for out-of-bounds or water cell
        if (r < 0 || c < 0 || r >= nr || c >= nc || grid[r][c] == '0') {
            return;
        }

        // Mark the current cell as visited by setting it to '0'
        grid[r][c] = '0';

        // Explore all 4 adjacent directions (up, down, left, right)
        dfs(grid, r - 1, c);
        dfs(grid, r + 1, c);
        dfs(grid, r, c - 1);
        dfs(grid, r, c + 1);
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int nr = grid.size();
        int nc = grid[0].size();
        int num_islands = 0;

        // Iterate through every cell in the grid
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                // If a land cell is found, it indicates a new island
                if (grid[r][c] == '1') {
                    ++num_islands;
                    // Run DFS to sink the entire island
                    dfs(grid, r, c);
                }
            }
        }

        return num_islands;
    }
};

#include <iostream>
#include <vector>
#include <stack>
#include <utility> // For std::pair

using namespace std;

class Solution2 {
private:
    // FIXED: Changed to 'static constexpr' so it compiles legally inside class scope
    static constexpr int dr[4] = {-1, 1, 0, 0};
    static constexpr int dc[4] = {0, 0, -1, 1};

    void sinkIsland(vector<vector<char>>& grid, int start_r, int start_c) {
        int nr = grid.size();
        int nc = grid[0].size();
        
        stack<pair<int, int>> st;
         
        st.push({start_r, start_c});
        grid[start_r][start_c] = '0';

        while (!st.empty()) {
            auto [curr_r, curr_c] = st.top();
            st.pop();

            for (int i = 0; i < 4; ++i) {
                int next_r = curr_r + dr[i];
                int next_c = curr_c + dc[i];

                if (next_r >= 0 && next_r < nr && next_c >= 0 && next_c < nc && grid[next_r][next_c] == '1') {
                    grid[next_r][next_c] = '0'; 
                    st.push({next_r, next_c});
                }
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        int nr = grid.size();
        int nc = grid[0].size();
        int num_islands = 0;

        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                    sinkIsland(grid, r, c); 
                }
            }
        }

        return num_islands;
    }
};


// Driver program to test the solution
int main() {
    Solution1 sol1;
    Solution2 sol2;

    // Test Case 1
    vector<vector<char>> grid1 = {
        {'0', '1', '1', '1', '0'},
        {'0', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    vector<vector<char>> grid11 = {
        {'0', '1', '1', '1', '0'},
        {'0', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    cout << "Example 1 Output: " << sol1.numIslands(grid1) << " (Expected: 1)" << endl;
    cout << "Example 1 Output: " << sol2.numIslands(grid11) << " (Expected: 1)" << endl;

    // Test Case 2
    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '1'},
        {'1', '1', '0', '0', '1'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    vector<vector<char>> grid22 = {
        {'1', '1', '0', '0', '1'},
        {'1', '1', '0', '0', '1'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    cout << "Example 2 Output: " << sol1.numIslands(grid2) << " (Expected: 4)" << endl;
    cout << "Example 2 Output: " << sol2.numIslands(grid22) << " (Expected: 4)" << endl;

    return 0;
}


