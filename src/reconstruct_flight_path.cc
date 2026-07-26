/*
Reconstruct Flight Path

You are given a list of flight tickets tickets where tickets[i] = [from, to]
represent the source airport and the destination airport.

Each from and to consists of three uppercase English letters.

Reconstruct the itinerary in order and return it.

All of the tickets belong to someone who originally departed from "JFK". Your
objective is to reconstruct the flight path that this person took, assuming
each ticket was used exactly once.

If there are multiple valid flight paths, return the lexicographically smallest one.

For example, the itinerary ["JFK", "SEA"] has a smaller lexical order than ["JFK", "SFO"].

You may assume all the tickets form at least one valid flight path.

Example 1:
Input: tickets = [["BUF","HOU"],["HOU","SEA"],["JFK","BUF"]]
Output: ["JFK","BUF","HOU","SEA"]

Example 2:
Input: tickets = [["HOU","JFK"],["SEA","JFK"],["JFK","SEA"],["JFK","HOU"]]
Output: ["JFK","HOU","JFK","SEA","JFK"]

Explanation: Another possible reconstruction is ["JFK","SEA","JFK","HOU","JFK"] but it is lexicographically larger.

Constraints:

    1 <= tickets.length <= 300
    from_i != to_i
*/

/*
The problem can be model as finding an Eulerian path in a directed pgraph. A connected
graph has an Eulerian path if and only if it following the 2 degreee rules:

(1) Eulerian Circuit: Every vertex in the graph must have an even degree. 
(2) Eulerian Path: Exactly two vertices must have an odd degree.

To find the Eulerian path, the standard algorith is Hierholzer's algorithm.
(1) Count the number of odd-degree vertices. If it's zero, pick any vertex.
    If it's 2, start the path at one of the odd-degree.
(2) Trace edges randomly, deleting edges as you visit them. When you hit
    a dead edn, backtrack and add vertices to your path.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Map to store the graph: departure -> min-heap of arrivals
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> graph;
    vector<string> itinerary;

    void dfs(const string& airport) {
        // While there are remaining flights from the current airport
        while (!graph[airport].empty()) {
            string next = graph[airport].top();
            graph[airport].pop(); // Use the ticket
            dfs(next);
        }
        // Post-order append
        itinerary.push_back(airport);
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // 1. Build the graph
        for (const auto& ticket : tickets) {
            graph[ticket[0]].push(ticket[1]);
        }
        
        // 2. Start Eulerian path DFS from "JFK"
        dfs("JFK");
        
        // 3. Reverse the post-order result to get the actual itinerary
        reverse(itinerary.begin(), itinerary.end());
        
        return itinerary;
    }
};

// Driver program to test the solution
int main() {
    Solution solver;

    // Test Case 1
    vector<vector<string>> tickets1 = {
        {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}
    };
    cout << "Test Case 1 Expected: JFK -> MUC -> LHR -> SFO -> SJC" << endl;
    vector<string> result1 = solver.findItinerary(tickets1);
    cout << "Output: ";
    for (size_t i = 0; i < result1.size(); ++i) {
        cout << result1[i] << (i == result1.size() - 1 ? "" : " -> ");
    }
    cout << "\n\n";

    // Test Case 2 (Requires backtracking to handle dead ends correctly)
    Solution solver2;
    vector<vector<string>> tickets2 = {
        {"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}
    };
    cout << "Test Case 2 Expected: JFK -> ATL -> JFK -> SFO -> ATL -> SFO" << endl;
    vector<string> result2 = solver2.findItinerary(tickets2);
    cout << "Output: ";
    for (size_t i = 0; i < result2.size(); ++i) {
        cout << result2[i] << (i == result2.size() - 1 ? "" : " -> ");
    }
    cout << endl;

    return 0;
}

