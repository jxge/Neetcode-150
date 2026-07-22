/*
Redundant Connection

You are given a connected undirected graph with n nodes labeled from 1 to n.
Initially, it contained no cycles and consisted of n-1 edges.

We have now added one additional edge to the graph. The edge has two different
vertices chosen from 1 to n, and was not an edge that previously existed in the
graph.

The graph is represented as an array edges of length n where edges[i] = [ai,
bi] represents an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the graph is still a connected
non-cyclical graph. If there are multiple answers, return the edge that appears
last in the input edges.

Example 1: Input: edges = [[1,2],[1,3],[3,4],[2,4]]
Output: [2,4]

Example 2: Input: edges = [[1,2],[1,3],[1,4],[3,4],[4,5]]
Output: [3,4]

Constraints:
    n == edges.length
    3 <= n <= 100
    1 <= edges[i][0] < edges[i][1] <= edges.length
    There are no repeated edges and no self-loops in the input.
*/


/*
Algorithm 1: Use Union-Find (Disjoint Set Union.
  For each edge e=(u,v), if u and v share the same parent, then adding the edge
  will introduce a cycle.
  Time Complexity: O(N * f(N)), where N is number of veritices, f(N) is cost of findParent.

Algorithm 2: Adding every edge e=(u,v) to the graph until v is reachable from u.

Algorithm 3: Full Graph DFS solution: Construct the full graph and use DFS to detect a cycle.
  Note that because the problem asks for the edge that appears last in the input,
  you must collect all the edges involved causing a cycle, and then look back at
  your input array to see which of those cycle edges appeared last.
*/ 

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution1 {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        
        // Zero-based indexing: allocate exactly size n
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
        
        vector<int> rank(n, 1);

        for (const auto& edge : edges) {
            // Convert 1-based input nodes to 0-based indices
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            
            // If they share the same root, this edge forms the cycle
            if (!unionSets(u, v, parent, rank)) {
                return edge; // Return original 1-based edge values
            }
        }
        
        return {};
    }

private:
    // Find operation with path compression
    int findParent(int node, vector<int>& parent) {
        if (node == parent[node]) {
            return node;
        }
        return parent[node] = findParent(parent[node], parent);
    }

    // Union operation with union-by-rank
    bool unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
        int rootU = findParent(u, parent);
        int rootV = findParent(v, parent);

        if (rootU == rootV) {
            return false; // Cycle detected
        }

        // Keep trees balanced using rank as the upper bound height
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

class Solution2 {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        
        // Zero-based indexing for graph representation
        vector<vector<int>> adj(n);

        for (const auto& edge : edges) {
            int u = edge[0] - 1; // Convert to 0-based index
            int v = edge[1] - 1; // Convert to 0-based index
            
            // Track visited nodes for each independent path search
            vector<bool> visited(n, false);
            
            // If u and v are already connected, this edge is the redundant one
            if (hasPath(u, v, adj, visited)) {
                return edge; // Return the original 1-based edge values
            }
            
            // Otherwise, safely add the undirected edge to our graph
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        return {};
    }

private:
    // Helper function to check if a path exists between 'curr' and 'target'
    bool hasPath(int curr, int target, const vector<vector<int>>& adj, vector<bool>& visited) {
        if (curr == target) {
            return true;
        }
        
        visited[curr] = true;
        
        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                if (hasPath(neighbor, target, adj, visited)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

#include <algorithm>
#include <map>

class Solution3 {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<vector<int>> adj(n);
        
        // Map to keep track of the original input index of each edge
        // Keys are stored as min/max pairs to easily look up undirected edges
        map<pair<int, int>, int> edgeToIndex;
        for (int i = 0; i < n; ++i) {
            int u = edges[i][0] - 1;
            int v = edges[i][1] - 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
            edgeToIndex[{min(u, v), max(u, v)}] = i;
        }

        vector<bool> visited(n, false);
        vector<int> parent(n, -1);
        int cycleStart = -1;
        int cycleEnd = -1;

        // Find the cycle using DFS
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                if (findCycleDFS(i, -1, adj, visited, parent, cycleStart, cycleEnd)) {
                    break;
                }
            }
        }

        // Trace the cycle path back using our parent array
        vector<pair<int, int>> cycleEdges;
        int curr = cycleEnd;
        while (curr != cycleStart) {
            int p = parent[curr];
            cycleEdges.push_back({min(curr, p), max(curr, p)});
            curr = p;
        }
        // Don't forget the closing edge that completed the cycle
        cycleEdges.push_back({min(cycleStart, cycleEnd), max(cycleStart, cycleEnd)});

        // Find which edge in the cycle appeared last in the input
        int maxIndex = -1;
        for (const auto& edge : cycleEdges) {
            maxIndex = max(maxIndex, edgeToIndex[edge]);
        }

        return edges[maxIndex];
    }

private:
    bool findCycleDFS(int node, int p, const vector<vector<int>>& adj, 
                      vector<bool>& visited, vector<int>& parent, 
                      int& cycleStart, int& cycleEnd) {
        visited[node] = true;
        parent[node] = p;

        for (int neighbor : adj[node]) {
            if (neighbor == p) continue; // Skip immediate parent tracking link

            if (visited[neighbor]) {
                // If neighbor is visited and not the parent, a cycle is found!
                cycleStart = neighbor;
                cycleEnd = node;
                return true;
            }

            if (findCycleDFS(neighbor, node, adj, visited, parent, cycleStart, cycleEnd)) {
                return true;
            }
        }
        return false;
    }
};



// Driver program
int main() {
    Solution1 sol1;
    Solution2 sol2;
    Solution3 sol3;

    // Test Example 1
    vector<vector<int>> edges1 = {{1, 2}, {1, 3}, {3, 4}, {2, 4}};
    vector<int> result1 = sol1.findRedundantConnection(edges1);
    cout << "Example 1 Output: [" << result1[0] << ", " << result1[1] << "] (Expected: [2, 4])" << endl;
    result1 = sol2.findRedundantConnection(edges1);
    cout << "Example 1 Output: [" << result1[0] << ", " << result1[1] << "] (Expected: [2, 4])" << endl;
    result1 = sol3.findRedundantConnection(edges1);
    cout << "Example 1 Output: [" << result1[0] << ", " << result1[1] << "] (Expected: [2, 4])" << endl;

    // Test Example 2
    vector<vector<int>> edges2 = {{1, 2}, {1, 3}, {1, 4}, {3, 4}, {4, 5}};
    vector<int> result2 = sol1.findRedundantConnection(edges2);
    cout << "Example 2 Output: [" << result2[0] << ", " << result2[1] << "] (Expected: [3, 4])" << endl;
    result2 = sol2.findRedundantConnection(edges2);
    cout << "Example 2 Output: [" << result2[0] << ", " << result2[1] << "] (Expected: [3, 4])" << endl;
    result2 = sol3.findRedundantConnection(edges2);
    cout << "Example 2 Output: [" << result2[0] << ", " << result2[1] << "] (Expected: [3, 4])" << endl;

    return 0;
}

