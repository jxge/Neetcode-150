/*
Network Delay Time

You are given a network of n directed nodes, labeled from 1 to n. You are also
given times, a list of directed edges where times[i] = (ui, vi, ti).

    ui is the source node (an integer from 1 to n)
    vi is the target node (an integer from 1 to n)
    ti is the time it takes for a signal to travel from ui to vi, ti is non-negative.

You are also given an integer k, representing the node that we will send a
signal from.

Return the minimum time it takes for all of the n nodes to receive the signal.
If it is impossible for all the nodes to receive the signal, return -1 instead.

Example 1: Input: times = [[1,2,1],[2,3,1],[1,4,4],[3,4,1]], n = 4, k = 1
Output: 3

Example 2: Input: times = [[1,2,1],[2,3,1]], n = 3, k = 2
Output: -1

Constraints:
    1 <= k <= n <= 100
    1 <= times.length <= 1000
*/

/*
Approach 1: Since the weights are non-negative, we can use Dijkstra's algorithm
with a min-priority queue to find the shortest path from the source to all other
nodes.
Time Complexisity: O(E log(V)), where E is the number of edges and V is the
number of vertices.

Approach 2: Bellman-Ford Algorithm (Edge relaxation by |V|-1 times)
Complexity: O(|V|*|E})
    
    dist[0:N-1] = INF;      // N is the number of vertices
    pred[0:N-1] = NULL;
    dist[source] = 0
    repeat (N - 1) times {
        for each e=(u,v);
        if (dist[u] + w < dist[v]) then
            dist[v] = dist[u] + w;
            prev[v] = u;
        }
    }
    // check negative-weight cycles
    for each e=(u,v) do
        if (dist[u]+w < dist[v]) 
            prev[v] = u;
            visisted[0:n-1] = false;
        visisted[v] = true;
        while not visited[u] do
            visited[u] = true;
            u = prev[u]
        ncycle = {u}
        v = prev[u];
        while v != u
            ncycle += v;
            v = prev[v]
        error "negative weight cycle");

Approach 3: Floyd-Warshal Algorithm
  Define SP(i,j,k) as the shortest path from i to j using vertices only from {1,2, .., k}.
    SP(i,j,k) = min(SP(i,j,k-1), SP(i,k, k-1) +_ SP(k,j,k-1)
    SP9i,j,0) = w(i,j)

    procedure FloydWarshallWithPathReconstruction() is
        let dist be a |V| × |V| array of minimum distances initialized to ∞ (infinity)
        let prev be a |V| x |V| array of vertext indices initialized to null
        for each edge (u, v) do
            dist[u][v] = w(u, v)  // The weight of the edge (u, v)
            prev[u][v] = u
        for each vertex v do
            dist[v][v] = 0
            prev[v][v] = v
        for k from 1 to |V| do
            for i from 1 to |V| do
                for j from 1 to |V| do
                    if dist[i][j] > dist[i][k] + dist[k][j]
                        dist[i][j] = dist[i][k] + dist[k][j]
                        prev[i][j] = prev[k][j]
                    end if    
    procedure Path(u, v) is
        if prev[u][v] = null then
            return []
        path = [v]
        while u ≠ v do
            v = prev[u][v]
            path.prepend(v)
        return path

    If there's a negative cycle, then there's a vertex i in the cycle so that
       dist[i][i] < 0.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Zero-based indexing: allocate exactly size n
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& time : times) {
            int u = time[0] - 1; // Convert to 0-based index
            int v = time[1] - 1; // Convert to 0-based index
            int t = time[2];
            adj[u].push_back({v, t});
        }

        // Distance array initialized to a large value (infinity)
        vector<int> dist(n, INT_MAX);
        
        // Convert starting node k to 0-based index
        int startNode = k - 1;
        dist[startNode] = 0;

        // Min-heap tracking pairs of {current_distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, startNode});

        while (!pq.empty()) {
            auto [current_dist, node] = pq.top();
            pq.pop();

            // The same node may occur in the queue with different distances
            // This avoids using an array to indicate if the shortest path
            // has been found for a node.
            if (current_dist > dist[node]) {
                continue;
            }

            // Traverse all directed neighbors
            for (const auto& [neighbor, time] : adj[node]) {
                int next_dist = current_dist + time;
                
                // Relaxation step: if a shorter path is found, update and push to heap
                if (next_dist < dist[neighbor]) {
                    dist[neighbor] = next_dist;
                    pq.push({next_dist, neighbor});
                }
            }
        }

        // Find the maximum time taken among all 0-indexed nodes
        int max_delay = 0;
        for (int i = 0; i < n; ++i) {
            if (dist[i] == INT_MAX) {
                return -1; // At least one node is unreachable
            }
            max_delay = max(max_delay, dist[i]);
        }

        return max_delay;
    }
};

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class SolutionBellmanFord {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Distance array initialized to infinity
        vector<int> dist(n, INT_MAX);
        
        // Convert starting node k to 0-based index
        int startNode = k - 1;
        dist[startNode] = 0;

        // Relax all edges n - 1 times
        for (int i = 0; i < n - 1; ++i) {
            bool updated = false;
            for (const auto& time : times) {
                int u = time[0] - 1; // Convert to 0-based
                int v = time[1] - 1; // Convert to 0-based
                int t = time[2];

                // If source node is reachable, try to relax the edge
                if (dist[u] != INT_MAX && dist[u] + t < dist[v]) {
                    dist[v] = dist[u] + t;
                    updated = true;
                }
            }
            // Optimization: If no distances change during a round, we can stop early
            if (!updated) break;
        }

        // Find the maximum time taken among all nodes
        int max_delay = 0;
        for (int i = 0; i < n; ++i) {
            if (dist[i] == INT_MAX) {
                return -1; // Node is unreachable
            }
            max_delay = max(max_delay, dist[i]);
        }

        return max_delay;
    }
};

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class SolutionFloydWarshall {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Initialize an n x n cost matrix with infinity
        // Using a safe upper bound (1e7) prevents integer overflow during addition
        const int INF = 1e7;
        vector<vector<int>> dist(n, vector<int>(n, INF));

        // Base cases: distance to self is 0
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }

        // Populate direct edge weights from the input
        for (const auto& time : times) {
            int u = time[0] - 1;
            int v = time[1] - 1;
            int t = time[2];
            dist[u][v] = t;
        }

        // Core Floyd-Warshall DP updates: intermediate node 'mid' goes first
        for (int mid = 0; mid < n; ++mid) {
            for (int src = 0; src < n; ++src) {
                for (int dest = 0; dest < n; ++dest) {
                    if (dist[src][mid] + dist[mid][dest] < dist[src][dest]) {
                        dist[src][dest] = dist[src][mid] + dist[mid][dest];
                    }
                }
            }
        }

        // Find the maximum time taken from our specific start node (k - 1)
        int startNode = k - 1;
        int max_delay = 0;
        for (int i = 0; i < n; ++i) {
            if (dist[startNode][i] == INF) {
                return -1; // Node is unreachable from startNode
            }
            max_delay = max(max_delay, dist[startNode][i]);
        }

        return max_delay;
    }
};


// Driver program
int main() {
    Solution solver;

    // Test Example 1
    vector<vector<int>> times1 = {{1, 2, 1}, {2, 3, 1}, {1, 4, 4}, {3, 4, 1}};
    int n1 = 4, k1 = 1;
    cout << "Example 1 Output: " << solver.networkDelayTime(times1, n1, k1) 
         << " (Expected: 3)" << endl;

    // Test Example 2
    vector<vector<int>> times2 = {{1, 2, 1}, {2, 3, 1}};
    int n2 = 3, k2 = 2;
    cout << "Example 2 Output: " << solver.networkDelayTime(times2, n2, k2) 
         << " (Expected: -1)" << endl;

    return 0;
}

