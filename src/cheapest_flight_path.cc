/*
Cheapest Flights Within K Stops

There are n airports, labeled from 0 to n - 1, which are connected by some
flights. You are given an array flights where flights[i] = [from_i, to_i,
price_i] represents a one-way flight from airport from_i to airport to_i with
cost price_i. You may assume there are no duplicate flights and no flights from
an airport to itself.

You are also given three integers src, dst, and k where:
    src is the starting airport
    dst is the destination airport
    src != dst
    k is the maximum number of stops you can make (not including src and dst)

Return the cheapest price from src to dst with at most k stops, or return -1 if
it is impossible.

Example 1:
Input: n = 4, flights = [[0,1,200],[1,2,100],[1,3,300],[2,3,100]], src = 0, dst = 3, k = 1
Output: 500

Explanation:
The optimal path with at most 1 stop from airport 0 to 3 is shown in red, with total cost 200 + 300 = 500.
Note that the path [0 -> 1 -> 2 -> 3] costs only 400, and thus is cheaper, but it requires 2 stops, which is more than k.

Example 2:
Input: n = 3, flights = [[1,0,100],[1,2,200],[0,2,100]], src = 1, dst = 2, k = 1
Output: 200

Explanation:
The optimal path with at most 1 stop from airport 1 to 2 is shown in red and has cost 200.

Constraints:

    1 <= n <= 100
    fromi != toi
    1 <= pricei <= 1000
    0 <= src, dst, k < n
*/

/* 
Algorithm 1: Use the Bellman-Ford Algorithm to solve the cheapest flights within k stops Problem. 
This is the most efficent algorithm for this problem.
Complexity: O(K*E)

Algorithm 2: Use a modified BFS. We track the mininum cost to reach each city
at the i'th level,  i=1,...,k+1 (more efficient in practice)
Complexity: O(K*E)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution1 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Initialize the prices array with infinity
        vector<int> prices(n, INT_MAX);
        prices[src] = 0;

        // Loop k + 1 times (k stops means at most k + 1 flights)
        for (int i = 0; i <= k; ++i) {
            // Create a copy to avoid using updated prices within the same iteration
            // Consider e1=[0,1,100], e2=[1,2,100], and prices[]=[0, INF, INF]
            // If we process e1 and e2, and update prices immediately, then 
            // prices[]=[0,100,200]. This is the result of 2 flights.
            vector<int> tmpPrices = prices;

            for (const auto& flight : flights) {
                int u = flight[0];     // Source of flight
                int v = flight[1];     // Destination of flight
                int price = flight[2]; // Cost of flight

                // If the source node is reachable, try to relax the edge
                if (prices[u] != INT_MAX && prices[u] + price < tmpPrices[v]) {
                    tmpPrices[v] = prices[u] + price;
                }
            }
            // Update the main prices array for the next stop iteration
            prices = tmpPrices;
        }

        // Return the price if destination is reachable, otherwise -1
        return prices[dst] == INT_MAX ? -1 : prices[dst];
    }
};

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution2 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Step 1: Build the adjacency list
        // adj[u] = list of pairs (neighbor_v, price)
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }

        // Step 2: Initialize prices array and BFS queue
        vector<int> prices(n, INT_MAX);
        prices[src] = 0;

        // Queue stores pairs of: {current_city, cost_to_reach_this_city}
        queue<pair<int, int>> q;
        q.push({src, 0});

        int stops = 0;

        // Step 3: Standard BFS layered traversal restricted by k stops
        while (!q.empty() && stops <= k) {
            int size = q.size();
            
            // Process all nodes at the current level of stops
            for (int i = 0; i < size; ++i) {
                auto [curr_node, curr_cost] = q.front();
                q.pop();

                // Explore all neighboring flights
                for (const auto& neighbor : adj[curr_node]) {
                    int next_node = neighbor.first;
                    int flight_price = neighbor.second;

                    // Optimization: Only proceed if this path yields a cheaper price
                    if (curr_cost + flight_price < prices[next_node]) {
                        prices[next_node] = curr_cost + flight_price;
                        q.push({next_node, prices[next_node]});
                    }
                }
            }
            // Increment stops after processing one full level of flights
            stops++;
        }

        // Return the final price if destination is reachable, otherwise -1
        return prices[dst] == INT_MAX ? -1 : prices[dst];
    }
};

int test1() {
    Solution1 solver;

    // Test Case 1: Multiple paths, constraint forces the cheaper but longer path out
    int n1 = 4;
    vector<vector<int>> flights1 = {{0,1,100},{1,2,100},{2,3,200},{0,2,500}};
    int src1 = 0, dst1 = 3, k1 = 1;
    cout << "Test Case 1 Output: " << solver.findCheapestPrice(n1, flights1, src1, dst1, k1) << endl; 
    // Expected: 700 (0 -> 2 -> 3)

    // Test Case 2: Exact constraint limit
    int n2 = 3;
    vector<vector<int>> flights2 = {{0,1,100},{1,2,100},{0,2,500}};
    int src2 = 0, dst2 = 2, k2 = 1;
    cout << "Test Case 2 Output: " << solver.findCheapestPrice(n2, flights2, src2, dst2, k2) << endl; 
    // Expected: 200 (0 -> 1 -> 2)

    return 0;
}

int test2() {
    Solution2 solver;

    // Test Case 1: Multiple paths, constraint forces the cheaper but longer path out
    int n1 = 4;
    vector<vector<int>> flights1 = {{0,1,100},{1,2,100},{2,3,200},{0,2,500}};
    int src1 = 0, dst1 = 3, k1 = 1;
    cout << "Test Case 1 Output: " << solver.findCheapestPrice(n1, flights1, src1, dst1, k1) << endl; 
    // Expected: 700 (0 -> 2 -> 3)

    // Test Case 2: Exact constraint limit
    int n2 = 3;
    vector<vector<int>> flights2 = {{0,1,100},{1,2,100},{0,2,500}};
    int src2 = 0, dst2 = 2, k2 = 1;
    cout << "Test Case 2 Output: " << solver.findCheapestPrice(n2, flights2, src2, dst2, k2) << endl; 
    // Expected: 200 (0 -> 1 -> 2)

    return 0;
}

// Driver program to test the solution
int main() {
    test1();
    test2();
    return 0;
}

