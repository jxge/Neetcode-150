/*
Min Cost to Connect Points

You are given a 2-D integer array points, where points[i] = [xi, yi]. Each
points[i] represents a distinct point on a 2-D plane.

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan
distance between the two points, i.e. |xi - xj| + |yi - yj|.

Return the minimum cost to connect all points together, such that there exists
exactly one path between each pair of points.

Example 1:
  Input: points = [[0,0],[2,2],[3,3],[2,4],[4,2]]
  Output: 10

Constraints:
    1 <= points.length <= 1000
    -1,000,000 <= xi, yi <= 1,000,000
    All pairs (xi, yi) are distinct.
*/

/* Add an edge between any point pair Pi, Pj with the weight Dist(Pi,Pj).
The problem is equivalent to finding the minimum spanning tree (MST).

Algorithm 1: Using Prim's algorithm
    Prim(G, w, r)
    for each vertex v in V
        dist[v]= INF
        prev[v] = nil
    dist[r] = 0
    Q = {}
    for each v in V
        INSERT(Q, v);
    while Q is not empty
        u = EXTRACT-MIN(Q)      // add u to the tree
        for each vertext v in adj[u]
            if v is in Q and w(u,v) < dist[v]
                prev[v] = u
                dist[v] = w(u,v)
                DECREASE-KEY(Q, v, w(u,v))
    Complexity: O(E * lg(V))

Algorithm 2: Using Kruskal's algorithm

1    Kruskal(G,w)
2    A = {}
3    for each vertex v in V
4        MAKE-SET(v)
5    sort the list of edges into monotonically increasing order by weight w
6    for each edge (u,v) in the sorted list
7        if FIND-SET(u) != FIND-SET(v)   // u and v are not connected
8            A = A + {u,v}
9            UNION(u, v);
10   retrun A
Complexity: 
    O(1)         line 2
    O(V)         line 3
    O(E * lg(V) line 4
    O(E * lg(V) line 7 h(V) is a very slowly growing function 
    O(E)         line 9
    O(V * lg(V) line 7 h(V) is a very slowly growing function 
    total: O(E * lg(V)
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

class Solution {
public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points) {
        int n = points.size();
        int min_cost = 0;
        int edges_used = 0;
        
        // Track nodes included in the MST
        std::vector<bool> in_mst(n, false);
        // Track the minimum distance from the MST to each node
        std::vector<int> min_dist(n, INT_MAX);
        
        // Start from the first node
        min_dist[0] = 0;
        
        while (edges_used < n) {
            int curr_node = -1;
            int curr_min_dist = INT_MAX;
            
            // Find the node with the minimum distance that is not yet in the MST
            for (int i = 0; i < n; ++i) {
                if (!in_mst[i] && min_dist[i] < curr_min_dist) {
                    curr_min_dist = min_dist[i];
                    curr_node = i;
                }
            }
            
            // Add the selected node to the MST
            in_mst[curr_node] = true;
            min_cost += curr_min_dist;
            edges_used++;
            
            // Update the distances of the neighbor nodes
            for (int next_node = 0; next_node < n; ++next_node) {
                if (!in_mst[next_node]) {
                    int weight = std::abs(points[curr_node][0] - points[next_node][0]) + 
                                 std::abs(points[curr_node][1] - points[next_node][1]);
                    
                    if (weight < min_dist[next_node]) {
                        min_dist[next_node] = weight;
                    }
                }
            }
        }
        
        return min_cost;
    }
};

// Driver Program
int main() {
    Solution solver;
    
    // Test Case: Example 1 from description
    std::vector<std::vector<int>> points = {{0,0}, {2,2}, {3,3}, {2,4}, {4,2}};
    
    // Print input coordinates
    std::cout << "Input Points: ";
    for (const auto& point : points) {
        std::cout << "[" << point[0] << "," << point[1] << "] ";
    }
    std::cout << "\n";
    
    // Compute result
    int result = solver.minCostConnectPoints(points);
    
    // Output expected vs actual result
    std::cout << "Expected Output: 10\n";
    std::cout << "Actual Output:   " << result << "\n";
    
    return 0;
}


