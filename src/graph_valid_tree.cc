/*
Graph Valid Tree

Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge
is a pair of nodes), write a function to check whether these edges make up a
valid tree.

Example 1:

Input:
n = 5,  edges = [[0, 1], [0, 2], [0, 3], [1, 4]]
Output: true

Example 2:
Input: n = 5, edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]]
Output: false

Note: You can assume that no duplicate edges will appear in edges. Since all
edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear
together in edges.

Constraints:
    1 <= n <= 100
    0 <= edges.length <= n * (n - 1) / 2
*/

/*
Approach 1: return True if 
  (1) |E| = n - 1, where n = |V|
  (2) The graph is connected

Proof: 
(1) If G is a tree, then |E| = n - 1, and G is connected.
(2) if G=(V,E) is connected and |E| = |V| - 1, then G is a tree. Use induction:
    (a) When n = 1, the graph is a single node without any edge. The proof is obvious;
    (b) Assume the result is true when such a graph is k vertices and k - 1 edge, where k >= 1.
    (c) Induction step: G is a connected graph with k+1 nodes and k edges.
        For each vertex v, degree(v)>=1 or it's an isolcated vertex (G is not connected).
        Then there must be a node whose degree is 1, otherwise the sum of degrees are 2|E| >= 2|V|.
        Let v is the node whose degree is 1. Remove v and its incident edge. The result
        graph G' = (E', V') is connected and satisfy |E'| = |V'| - 1. By assumption G' is
        a tree. Now adding v and the deleted edge back, it's still a connected graph without
        cycle (to form a cycle you need to add an edge connecting 2 vertices in G').

Approach 2: Use DFS to detect a cycle.
  Note that when we check if a neighbor has been visited, we need to rule out the parent node.

Approach 3: Use BFS to detect a cycle.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution1 {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // A valid tree must have exactly n - 1 edges
        if (edges.size() != n - 1) {
            return false;
        }

        // Build the adjacency list
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Track visited nodes
        vector<bool> visited(n, false);

        // Start DFS from node 0
        dfs(0, adj, visited);

        // Check if all nodes were reached
        for (bool v : visited) {
            if (!v) return false;
        }

        return true;
    }

private:
    void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited);
            }
        }
    }
};


class Solution2 {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // Build the adjacency list
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Track visited nodes
        vector<bool> visited(n, false);

        // Start DFS from node 0. Set parent as -1.
        // If a cycle is detected, it is not a valid tree.
        if (!dfs(0, -1, adj, visited)) {
            return false;
        }

        // Check if the graph is fully connected
        for (bool v : visited) {
            if (!v) return false;
        }

        return true;
    }

private:
    // Returns false if a cycle (an already visited node) is detected
    bool dfs(int node, int parent, const vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;

        for (int neighbor : adj[node]) {
            // Ignore the edge leading directly back to the parent node
            if (neighbor == parent) {
                continue;
            }

            // If the neighbor is already visited, a cycle exists
            if (visited[neighbor]) {
                return false;
            }

            // Recursively visit the neighbor and propagate cycle detection
            if (!dfs(neighbor, node, adj, visited)) {
                return false;
            }
        }

        return true;
    }
};


class Solution3 {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // Condition 1: A valid tree must have exactly n - 1 edges
        if (edges.size() != n - 1) {
            return false;
        }

        // Build the adjacency list
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Track visited nodes
        vector<bool> visited(n, false);
        
        // BFS Setup
        queue<int> q;
        q.push(0);
        visited[0] = true;
        int visitedCount = 0;

        // Traverse the graph
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            visitedCount++; // Increment count of reached nodes

            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // Condition 2: Check if all nodes were reached (fully connected)
        return visitedCount == n;
    }
};



// Driver program
int main() {
    Solution1 sol1;
    Solution2 sol2;
    Solution2 sol3;

    // Test Example 1
    int n1 = 5;
    vector<vector<int>> edges1 = {{0, 1}, {0, 2}, {0, 3}, {1, 4}};
    cout << "Example 1 Output: " << (sol1.validTree(n1, edges1) ? "true" : "false") << endl;
    cout << "Example 1 Output: " << (sol2.validTree(n1, edges1) ? "true" : "false") << endl;
    cout << "Example 1 Output: " << (sol3.validTree(n1, edges1) ? "true" : "false") << endl;

    // Test Example 2
    int n2 = 5;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}};
    cout << "Example 2 Output: " << (sol1.validTree(n2, edges2) ? "true" : "false") << endl;
    cout << "Example 2 Output: " << (sol2.validTree(n2, edges2) ? "true" : "false") << endl;
    cout << "Example 2 Output: " << (sol3.validTree(n2, edges2) ? "true" : "false") << endl;

    return 0;
}

