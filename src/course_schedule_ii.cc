/*
You are given an array prerequisites where prerequisites[i] = [a, b] indicates
that you must take course b first if you want to take course a.

There are a total of numCourses courses you are required to take, labeled from
0 to numCourses - 1.

Return a valid ordering of courses you can take to finish all courses. If there
are many valid answers, return any of them. If it's not possible to finish all
courses, return an empty array.

Example 1:
Input: numCourses = 3, prerequisites = [[1,0]]
Output: [0,1,2]

Explanation: We must ensure that course 0 is taken before course 1.

Example 2:
Input: numCourses = 3, prerequisites = [[0,1],[1,2],[2,0]]
Output: []
Explanation: It's impossible to finish all courses.

Constraints:

    1 <= numCourses <= 1000
    0 <= prerequisites.length <= 1000
    All prerequisite pairs are unique.
*/


/*
 * Approach 1: Use Kahn's Algorithm for Topological Sort. This approach uses
 * the in-degrees of nodes to safely detect cycles and determine the correct
 * course sequence. 
 * Time Complexity: O(V+E) where V is the number of sources, and E is the number
 *     of prerequsites.
 *
 * Apprach 2: Use DFS (Use 3 state: Unvisited, Visiting, Visited).
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


using namespace std;

class Solution1 {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        vector<int> order;
        
        // Build the adjacency list and calculate in-degrees
        for (const auto& pre : prerequisites) {
            int course = pre[0];
            int prerequisite = pre[1];
            adj[prerequisite].push_back(course);
            inDegree[course]++;
        }
        
        // Push all courses with no prerequisites into the queue
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        // Process courses
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            order.push_back(curr);
            
            for (int nextCourse : adj[curr]) {
                inDegree[nextCourse]--;
                if (inDegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        
        // If order contains all courses, a valid schedule exists
        if (order.size() == numCourses) {
            return order;
        }
        
        return {}; // Return empty array if a cycle exists
    }
};

class Solution2 {
private:
    // Strongly-typed enum for clear state tracking
    enum class State {
        UNVISITED,
        VISITING,
        VISITED
    };

    bool hasCycle(int node, const vector<vector<int>>& adj, vector<State>& state, vector<int>& order) {
        state[node] = State::VISITING; // Mark as currently in the recursion stack
        
        for (int nextCourse : adj[node]) {
            if (state[nextCourse] == State::VISITING) {
                return true; // Cycle detected
            }
            if (state[nextCourse] == State::UNVISITED) {
                if (hasCycle(nextCourse, adj, state, order)) {
                    return true;
                }
            }
        }
        
        state[node] = State::VISITED; // Mark as completely processed
        order.push_back(node);       // Post-order tracking
        return false;
    }

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        
        // Build graph: prerequisite -> course
        for (const auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
        }
        
        // Initialize all nodes as UNVISITED
        vector<State> state(numCourses, State::UNVISITED); 
        vector<int> order;
        
        // Run DFS from each unvisited node
        for (int i = 0; i < numCourses; i++) {
            if (state[i] == State::UNVISITED) {
                if (hasCycle(i, adj, state, order)) {
                    return {}; // Return empty array if a cycle is found
                }
            }
        }
        
        // Post-order processing produces reverse topological sort, so reverse it
        reverse(order.begin(), order.end());
        return order;
    }
};


// Driver program to test the solution
int main() {
    Solution1 sol1;
    Solution2 sol2;
    
    // Test Case 1
    int numCourses1 = 3;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    vector<int> result1 = sol1.findOrder(numCourses1, prerequisites1);
    cout << "Test Case 1 Output: [";
    for (size_t i = 0; i < result1.size(); ++i) {
        cout << result1[i] << (i < result1.size() - 1 ? "," : "");
    }
    cout << "]" << endl;

    // Test Case 1
    result1 = sol2.findOrder(numCourses1, prerequisites1);
    cout << "Test Case 1 Output: [";
    for (size_t i = 0; i < result1.size(); ++i) {
        cout << result1[i] << (i < result1.size() - 1 ? "," : "");
    }
    cout << "]" << endl;

    // Test Case 2 (Cycle detection)
    int numCourses2 = 3;
    vector<vector<int>> prerequisites2 = {{0, 1}, {1, 2}, {2, 0}};
    vector<int> result2 = sol1.findOrder(numCourses2, prerequisites2);
    
    cout << "Test Case 2 Output: [";
    for (size_t i = 0; i < result2.size(); ++i) {
        cout << result2[i] << (i < result2.size() - 1 ? "," : "");
    }
    cout << "]" << endl;

    return 0;
}

