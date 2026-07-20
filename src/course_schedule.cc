/*
You are given an array prerequisites where prerequisites[i] = [a, b] indicates
that you must take course b first if you want to take course a.

There are a total of numCourses courses you are required to take, labeled from
0 to numCourses - 1.

Return true if it is possible to finish all courses, otherwise return false.

Example 1:

Input: numCourses = 2, prerequisites = [[0,1]]

Output: true

Explanation: First take course 1 (no prerequisites) and then take course 0.

Example 2:

Input: numCourses = 2, prerequisites = [[0,1],[1,0]]

Output: false

Explanation: In order to take course 1 you must take course 0, and to take course 0 you must take course 1. So it is impossible.

Constraints:

    1 <= numCourses <= 1000
    0 <= prerequisites.length <= 1000
    prerequisites[i].length == 2
    0 <= a[i], b[i] < numCourses
    All prerequisite pairs are unique.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution1 {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Step 1: Build adjacency list and in-degree array
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);

        for (const auto& pre : prerequisites) {
            int course = pre[0];
            int prereq = pre[1];
            // Direction: prereq -> course (must take prereq first)
            adj[prereq].push_back(course);
            inDegree[course]++;
        }

        // Step 2: Initialize queue with courses having 0 prerequisites
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        // Step 3: Process the courses layer-by-layer
        int completedCourses = 0;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            completedCourses++;

            // Reduce dependency for next courses
            for (int neighbor : adj[curr]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // Step 4: If we processed all courses, no cycle exists
        return completedCourses == numCourses;
    }
};

class Solution2 {
private:
    // Helper function to detect cycles using DFS
    bool hasCycle(int node, const vector<vector<int>>& adj, vector<int>& state, vector<int>& topoOrder) {
        // If the node is currently being visited in the current path, we found a cycle!
        if (state[node] == 1) return true;
        // If the node has already been completely processed, skip it
        if (state[node] == 2) return false;

        // Mark the node as "Visiting"
        state[node] = 1;

        // Recursively visit all dependencies
        for (int neighbor : adj[node]) {
            if (hasCycle(neighbor, adj, state, topoOrder)) {
                return true;
            }
        }

        // Mark the node as "Fully Visited"
        state[node] = 2;
        
        // Post-order processing: add to topological order after all dependencies are done
        topoOrder.push_back(node);

        return false;
    }

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Build adjacency list
        vector<vector<int>> adj(numCourses);
        for (const auto& pre : prerequisites) {
            // prereq -> course
            adj[pre[1]].push_back(pre[0]);
        }

        // State vector: 0 = Unvisited, 1 = Visiting, 2 = Visited
        vector<int> state(numCourses, 0);
        vector<int> topoOrder;

        // Check each course (handles disconnected graphs)
        for (int i = 0; i < numCourses; ++i) {
            if (state[i] == 0) {
                if (hasCycle(i, adj, state, topoOrder)) {
                    return false; // Cycle detected, cannot finish
                }
            }
        }

        // Optional: If you actually need the course order, reverse the collected nodes
        // reverse(topoOrder.begin(), topoOrder.end());
        
        return true;
    }
};

// Driver Program
int main() {
    Solution1 sol1;
    Solution2 sol2;

    // Example 1: No cycle
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{0, 1}};
    cout << "Example 1 (Can Finish?): " << (sol1.canFinish(numCourses1, prerequisites1) ? "true" : "false") << endl;
    cout << "Example 1 (Can Finish?): " << (sol2.canFinish(numCourses1, prerequisites1) ? "true" : "false") << endl;

    // Example 2: Has cycle
    int numCourses2 = 2;
    vector<vector<int>> prerequisites2 = {{0, 1}, {1, 0}};
    cout << "Example 2 (Can Finish?): " << (sol1.canFinish(numCourses2, prerequisites2) ? "true" : "false") << endl;
    cout << "Example 2 (Can Finish?): " << (sol2.canFinish(numCourses2, prerequisites2) ? "true" : "false") << endl;

    return 0;
}

