/*
Number of Connected Components in an Undirected Graph

You have a graph of n nodes. You are given an integer n and an array edges
where edges[i] = [aᵢ, bᵢ] indicates that there is an edge between aᵢ and bᵢ in
the graph.

Return the number of connected components in the graph.

Example 1: Input: n = 5, edges = [[0,1],[1,2],[3,4]]
Output: 2

Example 2: Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
Output: 1

Constraints:
    1 <= n <= 2000
    1 <= edges.length <= 5000
    edges[i].length == 2
    0 <= aᵢ <= bᵢ < n
    aᵢ != bᵢ
    There are no repeated edges.
*/

/*
Approach 1: Use DFS to find connected components.
Approach 2: Use BFS to find connected components.
Approach 3: Use Union-Set to find connected components.
*/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution1 {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        // Build the adjacency list for the undirected graph
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Track visited nodes
        vector<bool> visited(n, false);
        int componentCount = 0;

        // Loop through all nodes from 0 to n - 1
        for (int i = 0; i < n; ++i) {
            // If the node is not visited, it belongs to a new connected component
            if (!visited[i]) {
                componentCount++;
                dfs(i, adj, visited); // Visit all nodes in this component
            }
        }

        return componentCount;
    }

private:
    // Helper function to perform Depth-First Search
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
    int countComponents(int n, vector<vector<int>>& edges) {
        // Initially, every node is its own separate component
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
        
        // rank[i] is the strict upper bound of the height of the tree 
        // rooted at i. If i is not a root, rank[i] is irrelevant.
        vector<int> rank(n, 1); 

        int componentCount = n;

        // Process each edge
        for (const auto& edge : edges) {
            int node1 = edge[0];
            int node2 = edge[1];
            
            // If the nodes belong to different sets, merge them
            if (unionSets(node1, node2, parent, rank)) {
                componentCount--; // A merge means one less independent component
            }
        }

        return componentCount;
    }

private:
    // Find operation with path compression optimization
    int findParent(int node, vector<int>& parent) {
        if (node == parent[node]) {
            return node;
        }
        // Path compression: points node directly to the root representative
        return parent[node] = findParent(parent[node], parent);
    }

    // Union operation with union-by-rank optimization
    // Returns true if a merge happened, false if they were already in the same set
    bool unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
        int rootU = findParent(u, parent);
        int rootV = findParent(v, parent);

        if (rootU == rootV) {
            return false; // Already in the same connected component
        }

        // Union by rank: attach the smaller depth tree under the larger depth tree
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }

        return true;
    }
};



// Driver program to execute test cases
int main() {
    Solution1 sol1;
    Solution2 sol2;

    // Test Example 1
    int n1 = 5;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {3, 4}};
    cout << "Example 1 Output: " << sol1.countComponents(n1, edges1) << " (Expected: 2)" << endl;
    cout << "Example 1 Output: " << sol2.countComponents(n1, edges1) << " (Expected: 2)" << endl;

    // Test Example 2
    int n2 = 5;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    cout << "Example 2 Output: " << sol1.countComponents(n2, edges2) << " (Expected: 1)" << endl;
    cout << "Example 2 Output: " << sol2.countComponents(n2, edges2) << " (Expected: 1)" << endl;

    return 0;
}


