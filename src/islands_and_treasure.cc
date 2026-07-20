/*
You are given a m×nm×n 2D grid initialized with these three possible values:

    -1 - A water cell that can not be traversed.
    0 - A treasure chest.
    INF - A land cell that can be traversed. We use the integer 2^31 - 1 = INF to represent INF.

Fill each land cell with the distance to its nearest treasure chest. If a land cell cannot reach a treasure chest then the value should remain INF.

Assume the grid can only be traversed up, down, left, or right.

Modify the grid in-place.

Example 1:

Input: [
  [INF, -1,  0,   INF],
  [INF, INF, INF, -1],
  [INF, -1,  INF, -1],
  [0,   -1,  INF, INF]
]

Output: [
  [3,-1,0,1],
  [2,2,1,-1],
  [1,-1,2,-1],
  [0,-1,3,4]
]

Example 2:

Input: [
  [0,  -1],
  [INF,INF]
]

Output: [
  [0,-1],
  [1,2]
]
*/

/*
 * Approach 1: Single Source BFS
 * Approach 2: Multi-Source BFS (much more optimized)
 */
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class Solution1 {
private:
    // Constants for 4-directional moves (Up, Down, Left, Right)
    static constexpr int dr[] = {-1, 1, 0, 0};
    static constexpr int dc[] = {0, 0, -1, 1};
    static constexpr int INF = 2147483647;

    // Helper function to run a single-source BFS outward from a specific treasure chest
    void expandFromTreasure(vector<vector<int>>& grid, int start_r, int start_c, int rows, int cols) {
        queue<pair<int, int>> q;
        q.push({start_r, start_c});

        while (!q.empty()) {
            auto [curr_r, curr_c] = q.front();
            q.pop();

            // Check all 4 orthogonal neighboring directions
            for (int i = 0; i < 4; ++i) {
                int nr = curr_r + dr[i];
                int nc = curr_c + dc[i];

                // Boundary verification and path safety check
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] != -1) {
                    // Update the cell only if the current path offers a strictly SHORTER distance
                    if (grid[nr][nc] > grid[curr_r][curr_c] + 1) {
                        grid[nr][nc] = grid[curr_r][curr_c] + 1;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }

public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return;

        int rows = grid.size();
        int cols = grid[0].size();

        // Scan through the grid to locate each treasure chest source
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 0) {
                    // Outsource the BFS wavefront traversal for this specific chest
                    expandFromTreasure(grid, r, c, rows, cols);
                }
            }
        }
    }
};


class Solution2 {
private:
    // Direction tracking vectors for up, down, left, right moves
    static constexpr int dr[] = {-1, 1, 0, 0};
    static constexpr int dc[] = {0, 0, -1, 1};

public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return;

        int m = grid.size();
        int n = grid[0].size();
        int INF = 2147483647;

        queue<pair<int, int>> q;

        // Step 1: Locate all treasure chests (0) and add them as starting sources
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 0) {
                    q.push({r, c});
                }
            }
        }

        // Step 2: Expand outward layer-by-layer using multi-source BFS
        while (!q.empty()) {
            auto [curr_r, curr_c] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int next_r = curr_r + dr[i];
                int next_c = curr_c + dc[i];

                // Check boundaries and make sure the target cell is unvisited land (INF)
                if (next_r >= 0 && next_r < m && next_c >= 0 && next_c < n && grid[next_r][next_c] == INF) {
                    // Update distance: Current cell distance + 1
                    grid[next_r][next_c] = grid[curr_r][curr_c] + 1;
                    q.push({next_r, next_c});
                }
            }
        }
    }
};


// Utility function to print the 2D grid matrix
void printGrid(const vector<vector<int>>& grid) {
    cout << "[\n";
    for (const auto& row : grid) {
        cout << "  [";
        for (size_t i = 0; i < row.size(); ++i) {
            if (row[i] == 2147483647) cout << "INF";
            else cout << row[i];
            if (i + 1 < row.size()) cout << ", ";
        }
        cout << "]\n";
    }
    cout << "]\n";
}

int main() {
    Solution1 sol1;
    Solution2 sol2;
    int INF = 2147483647;

    // Example 1 Matrix Input
    vector<vector<int>> grid1 = {
        {INF, -1, 0, INF},
        {INF, INF, INF, -1},
        {INF, -1, INF, -1},
        {0, -1, INF, INF}
    };
    vector<vector<int>> grid2 = grid1;

    cout << "Original Grid 1:";
    printGrid(grid1);

    sol1.islandsAndTreasure(grid1);
    cout << "\nProcessed Grid 1 (Shortest Distances):";
    printGrid(grid1);

    sol2.islandsAndTreasure(grid2);
    cout << "\nProcessed Grid 1 (Shortest Distances):";
    printGrid(grid1);

    return 0;
}

