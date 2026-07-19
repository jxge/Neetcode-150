/*
You are given a matrix grid where grid[i] is either a 0 (representing water) or 1 (representing land).

An island is defined as a group of 1's connected horizontally or vertically. You may assume all four edges of the grid are surrounded by water.

The area of an island is defined as the number of cells within the island.

Return the maximum area of an island in grid. If no island exists, return 0.

Example 1:

Input: grid = [
  [0,1,1,0,1],
  [1,0,1,0,1],
  [0,1,1,0,1],
  [0,1,0,0,1]
]

Output: 6

Explanation: 1's cannot be connected diagonally, so the maximum area of the island is 6.

Constraints:

    1 <= grid.length, grid[i].length <= 50

*/

/* 
Complexity: O(M*N) where M is is the number of rows and N is the number of columns.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm> // For std::max
#include <utility>   // For std::pair

using namespace std;


/*
Solution 1:  recursive BFS
*/

class Solution1 {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ROWS = grid.size(), COLS = grid[0].size();
        int area = 0;

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (grid[r][c] == 1) {
                    area = max(area, dfs(grid, r, c));
                }
            }
        }

        return area;
    }

    int dfs(vector<vector<int>>& grid, int r, int c) {
        if (r < 0 || c < 0 || r >= grid.size() ||
            c >= grid[0].size() || grid[r][c] == 0) {
            return 0;
        }

        grid[r][c] = 0;
        int res = 1;
        for (int i = 0; i < 4; i++) {
            res += dfs(grid, r + directions[i][0],
                             c + directions[i][1]);
        }
        return res;
    }
};

/*
Solution 2:  iteractive BFS
*/
class Solution2 {
private:
    // Direction tracking arrays for 4-directional traversal
    static constexpr int dr[4] = {-1, 1, 0, 0};
    static constexpr int dc[4] = {0, 0, -1, 1};

    // Helper function to iteratively traverse an island and return its total area
    int calculateIslandArea(vector<vector<int>>& grid, int start_r, int start_c) {
        int nr = grid.size();
        int nc = grid[0].size();
        int area = 0;

        stack<pair<int, int>> st;
        
        // Push starting node, sink it immediately, and increment area
        st.push({start_r, start_c});
        grid[start_r][start_c] = 0; 
        area++;

        while (!st.empty()) {
            auto [curr_r, curr_c] = st.top();
            st.pop();

            // Explore all 4 orthogonal neighboring directions
            for (int i = 0; i < 4; ++i) {
                int next_r = curr_r + dr[i];
                int next_c = curr_c + dc[i];

                // Boundary verification and active land cell check
                if (next_r >= 0 && next_r < nr && next_c >= 0 && next_c < nc && grid[next_r][next_c] == 1) {
                    grid[next_r][next_c] = 0; // Sink neighbor immediately to avoid duplicate pushes
                    st.push({next_r, next_c});
                    area++; // Increment area for every newly discovered land cell
                }
            }
        }
        return area;
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        int nr = grid.size();
        int nc = grid[0].size();
        int max_area = 0;

        // Scan through every cell in the grid
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                // When an unvisited piece of land is found
                if (grid[r][c] == 1) {
                    // Update max_area if the current island's area is larger
                    max_area = max(max_area, calculateIslandArea(grid, r, c));
                }
            }
        }

        return max_area;
    }
};


/* 
 * Iterative BFS
 */
class Solution3 {
    int directions[4][2] = {{1, 0}, {-1, 0},
                            {0, 1}, {0, -1}};
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ROWS = grid.size(), COLS = grid[0].size();
        int area = 0;

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (grid[r][c] == 1) {
                    area = max(area, bfs(grid, r, c));
                }
            }
        }

        return area;
    }

    int bfs(vector<vector<int>>& grid, int r, int c) {
        queue<pair<int, int>> q;
        grid[r][c] = 0;
        q.push({r, c});
        int res = 1;

        while (!q.empty()) {
            auto node = q.front();q.pop();
            int row = node.first, col = node.second;
            for (int i = 0; i < 4; i++) {
                int nr = row + directions[i][0];
                int nc = col + directions[i][1];
                if (nr >= 0 && nc >= 0 && nr < grid.size() &&
                    nc < grid[0].size() && grid[nr][nc] == 1) {
                    q.push({nr, nc});
                    grid[nr][nc] = 0;
                    res++;
                }
            }
        }
        return res;
    }
};


/*
 * Disjoint Set Union (DSU) 
 */
class DSU {
    vector<int> Parent;     // Parent node 
    vector<int> Size;       // for root node r, Size[r] is the number of node in the union set.
public:
    DSU(int n) {
        Parent.resize(n + 1);
        Size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            Parent[i] = i;
            Size[i] = 1;
        }
    }

    int find(int node) {
        if (node != Parent[node]) {
            Parent[node] = find(Parent[node]);
        }
        return Parent[node];
    }

    bool unionBySize(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv) return false;
        if (Size[pu] >= Size[pv]) {
            Size[pu] += Size[pv];
            Parent[pv] = pu;
        } else {
            Size[pv] += Size[pu];
            Parent[pu] = pv;
        }
        return true;
    }

    int getSize(int node) {
        return Size[find(node)];
    }
};

class Solution4 {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ROWS = grid.size();
        int COLS = grid[0].size();
        DSU dsu(ROWS * COLS);

        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int area = 0;

        auto index = [&](int r, int c) {
            return r * COLS + c;
        };

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (grid[r][c] == 1) {
                    for (auto& d : directions) {
                        int nr = r + d[0];
                        int nc = c + d[1];
                        if (nr >= 0 && nc >= 0 && nr < ROWS &&
                            nc < COLS && grid[nr][nc] == 1) {
                            dsu.unionBySize(index(r, c), index(nr, nc));
                        }
                    }
                    area = max(area, dsu.getSize(index(r, c)));
                }
            }
        }

        return area;
    }
};

// Define static variables outside the class to conform with C++ standards
constexpr int Solution2::dr[];
constexpr int Solution2::dc[];


// Driver program to test the solution
int main() {
    Solution1 sol1;
    Solution2 sol2;
    Solution3 sol3;
    Solution4 sol4;

    // Test Case from the example
    vector<vector<int>> grid1 = {
        {0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {0, 1, 1, 0, 1},
        {0, 1, 0, 0, 1}
    };
    vector<vector<int>> grid2 = grid1;
    vector<vector<int>> grid3 = grid1;
    vector<vector<int>> grid4 = grid1;

    cout << "Example Output: " << sol1.maxAreaOfIsland(grid1) << " (Expected: 6)" << endl;
    cout << "Example Output: " << sol2.maxAreaOfIsland(grid2) << " (Expected: 6)" << endl;
    cout << "Example Output: " << sol3.maxAreaOfIsland(grid3) << " (Expected: 6)" << endl;
    cout << "Example Output: " << sol4.maxAreaOfIsland(grid4) << " (Expected: 6)" << endl;

    return 0;
}

