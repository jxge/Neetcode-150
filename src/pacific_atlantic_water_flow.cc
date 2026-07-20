/*
You are given a rectangular island heights where heights[r][c] represents the
height above sea level of the cell at coordinate (r, c).

The islands borders the Pacific Ocean from the top and left sides, and borders
the Atlantic Ocean from the bottom and right sides.

Water can flow in four directions (up, down, left, or right) from a cell to a
neighboring cell with height equal or lower. Water can also flow into the ocean
from cells adjacent to the ocean.

Find all cells where water can flow from that cell to both the Pacific and
Atlantic oceans. Return it as a 2D list where each element is a list [r, c]
representing the row and column of the cell. You may return the answer in any
order.

Example 1:

Input: heights = [
  [4,2,7,3,4],
  [7,4,6,4,7],
  [6,3,5,3,6]
]

Output: [[0,2],[0,4],[1,0],[1,1],[1,2],[1,3],[1,4],[2,0]]

Example 2:

Input: heights = [[1],[1]]

Output: [[0,0],[1,0]]

Constraints:

    1 <= heights.length, heights[r].length <= 100
    0 <= heights[r][c] <= 1000
*/


/*
Approach: Brutal BFS or DFS with backtracking from every cell.
Approach: From border cell run multi-source BFS uphill.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


class Solution1 {
public:
    int ROWS, COLS;
    bool pacific, atlantic;
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        ROWS = heights.size();
        COLS = heights[0].size();
        vector<vector<int>> res;

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                pacific = false;
                atlantic = false;
                dfs(heights, r, c, INT_MAX);
                if (pacific && atlantic) {
                    res.push_back({r, c});
                }
            }
        }

        return res;
    }

    void dfs(vector<vector<int>>& heights, int r, int c, int prevVal) {
        if (r < 0 || c < 0) {
            pacific = true;
            return;
        }
        if (r >= ROWS || c >= COLS) {
            atlantic = true;
            return;
        }
        if (heights[r][c] > prevVal) {
            return;
        }

        int tmp = heights[r][c];
        heights[r][c] = INT_MAX;
        for (auto& dir : directions) {
            dfs(heights, r + dir[0], c + dir[1], tmp);
            if (pacific && atlantic) {
                break;
            }
        }
        heights[r][c] = tmp;
    }
};

class Solution2 {
private:
    int numRows;
    int numCols;
    // Four directions: up, down, left, right
    const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    void bfs(const vector<vector<int>>& heights, queue<pair<int, int>>& q, vector<vector<bool>>& reachable) {
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (const auto& [dr, dc] : directions) {
                int newRow = r + dr;
                int newCol = c + dc;

                // Check boundaries
                if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
                    // Check if already visited or if the water cannot flow uphill from current to neighbor
                    if (!reachable[newRow][newCol] && heights[newRow][newCol] >= heights[r][c]) {
                        reachable[newRow][newCol] = true;
                        q.push({newRow, newCol});
                    }
                }
            }
        }
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};

        numRows = heights.size();
        numCols = heights[0].size();

        vector<vector<bool>> pacific(numRows, vector<bool>(numCols, false));
        vector<vector<bool>> atlantic(numRows, vector<bool>(numCols, false));

        queue<pair<int, int>> pacificQueue;
        queue<pair<int, int>> atlanticQueue;

        // Initialize queues with ocean borders
        for (int r = 0; r < numRows; ++r) {
            // Left border (Pacific)
            pacific[r][0] = true;
            pacificQueue.push({r, 0});

            // Right border (Atlantic)
            atlantic[r][numCols - 1] = true;
            atlanticQueue.push({r, numCols - 1});
        }

        for (int c = 0; c < numCols; ++c) {
            // Top border (Pacific)
            pacific[0][c] = true;
            pacificQueue.push({0, c});

            // Bottom border (Atlantic)
            atlantic[numRows - 1][c] = true;
            atlanticQueue.push({numRows - 1, c});
        }

        // Run BFS for both oceans
        bfs(heights, pacificQueue, pacific);
        bfs(heights, atlanticQueue, atlantic);

        // Find cells reachable by both oceans
        vector<vector<int>> result;
        for (int r = 0; r < numRows; ++r) {
            for (int c = 0; c < numCols; ++c) {
                if (pacific[r][c] && atlantic[r][c]) {
                    result.push_back({r, c});
                }
            }
        }

        return result;
    }
};

// Driver Program
int main() {
    Solution1 sol1;
    Solution2 sol2;

    // Example 1
    vector<vector<int>> heights1 = {
        {4, 2, 7, 3, 4},
        {7, 4, 6, 4, 7},
        {6, 3, 5, 3, 6}
    };
    vector<vector<int>> heights2 = heights1;

    cout << "Example 1 Output:" << endl;
    vector<vector<int>> result1 = sol1.pacificAtlantic(heights1);
    cout << "[";
    for (size_t i = 0; i < result1.size(); ++i) {
        cout << "[" << result1[i][0] << "," << result1[i][1] << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl << endl;

    cout << "Example 1 Output:" << endl;
    result1 = sol2.pacificAtlantic(heights2);
    cout << "[";
    for (size_t i = 0; i < result1.size(); ++i) {
        cout << "[" << result1[i][0] << "," << result1[i][1] << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl << endl;

    return 0;
}

