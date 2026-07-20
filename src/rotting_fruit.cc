/*
You are given a 2-D matrix grid. Each cell can have one of three possible values:

    0 representing an empty cell
    1 representing a fresh fruit
    2 representing a rotten fruit

Every minute, if a fresh fruit is horizontally or vertically adjacent to a rotten fruit, then the fresh fruit also becomes rotten.

Return the minimum number of minutes that must elapse until there are zero fresh fruits remaining. If this state is impossible within the grid, return -1.

Example 1:

Input: grid = [[1,1,0],[0,1,1],[0,1,2]]

Output: 4

Example 2:

Input: grid = [[1,0,1],[0,2,0],[1,0,1]]

Output: -1

Constraints:

    1 <= grid.length, grid[i].length <= 10
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        int rows = grid.size();
        int cols = grid[0].size();
        
        queue<pair<int, int>> q;
        int fresh_fruits = 0;

        // Step 1: Scan grid to count fresh fruits and queue up all starting rotten fruits
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 2) {
                    q.push({r, c});
                } else if (grid[r][c] == 1) {
                    fresh_fruits++;
                }
            }
        }

        // If there are no fresh fruits to rot from the start, 0 minutes have elapsed
        if (fresh_fruits == 0) return 0;

        int minutes = 0;
        
        // Direction updates for navigating up, down, left, right
        const int dr[] = {-1, 1, 0, 0};
        const int dc[] = {0, 0, -1, 1};

        // Step 2: Expand outward layer-by-layer (minute-by-minute)
        while (!q.empty()) {
            int current_layer_size = q.size();
            bool rotted_any_this_minute = false;

            // Process all fruits that are rotting neighbors during this specific minute
            for (int i = 0; i < current_layer_size; ++i) {
                auto [curr_r, curr_c] = q.front();
                q.pop();

                for (int d = 0; d < 4; ++d) {
                    int nr = curr_r + dr[d];
                    int nc = curr_c + dc[d];

                    // Verify boundaries and check if neighbor is a fresh fruit
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // Infect the fruit (acts as the visited marker)
                        fresh_fruits--;
                        rotted_any_this_minute = true;
                        q.push({nr, nc});
                    }
                }
            }

            // Only increment time if this round actually managed to spread rot further
            if (rotted_any_this_minute) {
                minutes++;
            }
        }

        // Return time if all fresh fruits are gone, otherwise return -1
        return (fresh_fruits == 0) ? minutes : -1;
    }
};

// Utility function to print matrix states
void printGrid(const vector<vector<int>>& grid) {
    cout << "[\n";
    for (const auto& row : grid) {
        cout << "  [";
        for (size_t i = 0; i < row.size(); ++i) {
            cout << row[i];
            if (i + 1 < row.size()) cout << ", ";
        }
        cout << "]\n";
    }
    cout << "]\n";
}

int main() {
    Solution solution;

    // Test Case 1
    vector<vector<int>> grid1 = {
        {1, 1, 0},
        {0, 1, 1},
        {0, 1, 2}
    };
    cout << "Example 1 Input:";
    printGrid(grid1);
    cout << "Minutes Elapsed: " << solution.orangesRotting(grid1) << " (Expected: 4)\n\n";

    // Test Case 2
    vector<vector<int>> grid2 = {
        {1, 0, 1},
        {0, 2, 0},
        {1, 0, 1}
    };
    cout << "Example 2 Input:";
    printGrid(grid2);
    cout << "Minutes Elapsed: " << solution.orangesRotting(grid2) << " (Expected: -1)\n";

    return 0;
}

