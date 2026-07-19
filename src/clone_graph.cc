/*
Given a node in a connected undirected graph, return a deep copy of the graph.

Each node in the graph contains an integer value and a list of its neighbors.

class Node {
    public int val;
    public List<Node> neighbors;
}

The graph is shown in the test cases as an adjacency list. An adjacency list is a mapping of nodes to lists, used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.

For simplicity, nodes values are numbered from 1 to n, where n is the total number of nodes in the graph. The index of each node within the adjacency list is the same as the node's value (1-indexed).

The input node will always be the first node in the graph and have 1 as the value.

Example 1:

Input: adjList = [[2],[1,3],[2]]

Output: [[2],[1,3],[2]]

Explanation: There are 3 nodes in the graph.
Node 1: val = 1 and neighbors = [2].
Node 2: val = 2 and neighbors = [1, 3].
Node 3: val = 3 and neighbors = [2].

Example 2:

Input: adjList = [[]]

Output: [[]]

Explanation: The graph has one node with no neighbors.

Example 3:

Input: adjList = []

Output: []

Explanation: The graph is empty.

Constraints:

    0 <= The number of nodes in the graph <= 100.
    1 <= Node.val <= 100
    There are no duplicate edges and no self-loops in the graph.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

/*
 * Iterative BFS traversal
 */
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        // Hash map to map the original node pointer to the new cloned node pointer
        unordered_map<Node*, Node*> visited;

        // Queue for BFS traversal
        queue<Node*> q;

        // Clone the starting node and register it in the map
        visited[node] = new Node(node->val);
        q.push(node);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            // Iterate through all neighbors of the current original node
            for (Node* neighbor : curr->neighbors) {
                // If the neighbor hasn't been cloned yet
                if (visited.find(neighbor) == visited.end()) {
                    // Create a deep copy of the neighbor
                    visited[neighbor] = new Node(neighbor->val);
                    // Push the original neighbor to the queue to process its connections later
                    q.push(neighbor);
                }
                // Append the cloned neighbor to the cloned current node's neighbor list
                visited[curr]->neighbors.push_back(visited[neighbor]);
            }
        }

        return visited[node];
    }
};

/*
 * Iterative DFS traversal
 */
class Solution2 {
private:
    // Hash map to track original nodes and their matching deep copies
    unordered_map<Node*, Node*> visited;
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        // If the node has already been cloned, return its deep copy directly
        if (visited.find(node) != visited.end()) {
            return visited[node];
        }

        // Clone the node (without its neighbors for now) and save to our map
        Node* clone = new Node(node->val);
        visited[node] = clone;

        // Recursively clone and link all of its neighbors
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(cloneGraph(neighbor));
        }

        return clone;
    }
};


/*
Memory-optimized in-place graph cloning algorithm. 
Time complexity: O(V+E)

Core Concept: Instead of external memory tracking, you embed the newly created 
CloneNode directly into the end of its original node’s neighbors list. You then
 stamp each CloneNode with a shared GLOBAL_MARKER to denote its visited state,
 and safely pop/restore the original pointers as you traverse.

Pass 1: Creating and Embedding Clones

   1. Initialize: Create a single GLOBAL_MARKER node to use as a unique
      tracking stamp. Push the starting node into a BFS queue. [1] 
   2. Clone & Embed Head: Instantiate a clone of the initial node. Push the
      GLOBAL_MARKER into the clone's neighbors list, and append this clone to the end
      of the original node's neighbors list. [2] 
   3. Traverse: Pop a node from the queue and loop through its original
      neighbors (ignoring the embedded clone at the end). [3] 
   4. Visited Check: For each neighbor, look at its last element. If that
      element's own last neighbor is the GLOBAL_MARKER, it has already been cloned.
   5. Action for Unvisited Nodes: If unvisited, create its clone, push the
      GLOBAL_MARKER into the clone, append the clone to the original neighbor's list,
      and add the original neighbor to the queue. [4, 5] 

## Pass 2: Reconstructing Neighbors AND Restoring Original Graph

   1. Initialize: Reset the BFS queue with the starting node. Unstamp the
      initial clone by popping the GLOBAL_MARKER from its neighbors list. [6, 7] 
   2. Retrieve Clone: Pop a node (curr) from the queue. Fetch its corresponding
      clone (curr_clone) from the end of its neighbors list.
   3. Rebuild Relationships: Loop through curr's original neighbors. Fetch
      their corresponding clones from the end of their respective lists, and append
      them to curr_clone's neighbors list.
   4. Visited Check & Queueing: Check if a neighbor's clone still holds the
      GLOBAL_MARKER.
      (a) If present: The node has not been queued in Pass 2 yet. Pop the marker
          from the clone (marking it visited), and push the original neighbor to the queue.
      (b) If absent: Skip queueing it (prevents infinite loops). [8, 9, 10, 11, 12] 
   5. In-place Cleanup: Immediately after finishing the neighbor loop for curr,
      execute curr->neighbors.pop_back(). This instantly removes the embedded clone
      pointer and restores the original node to its pristine state.
   6. Return: Once the queue is empty, return the pointer to the very first cloned node.

[1] [https://www.interviewcake.com](https://www.interviewcake.com/concept/java/dijkstras-algorithm)
[2] [https://www2.cs.sfu.ca](https://www2.cs.sfu.ca/CourseCentral/225/gsheikhs/labs/lab2/2-copy-constructor.html)
[3] [https://medium.com](https://medium.com/@shrutitech98/clone-graph-why-this-problem-isnt-as-simple-as-it-looks-43c0c5079c43)
[4] [https://dhruvs.space](https://dhruvs.space/posts/understanding-the-a-star-algorithm/)
[5] [https://medium.com](https://medium.com/@shrutitech98/clone-graph-why-this-problem-isnt-as-simple-as-it-looks-43c0c5079c43)
[6] [https://www.phoenixdata.ai](https://www.phoenixdata.ai/glossary/breadth-first-search-bfs)
[7] [https://www.scribd.com](https://www.scribd.com/presentation/818927020/1018450515278-Breadth-First-Search-BFS-and-Depth-First-Search)
[8] [https://hyperskill.org](https://hyperskill.org/learn/step/35510)
[9] [https://algo.monster](https://algo.monster/problems/topo_intro)
[10] [https://www.cliffsnotes.com](https://www.cliffsnotes.com/study-notes/27637578)
[11] [https://www.interviewcake.com](https://www.interviewcake.com/concept/java/bfs)
[12] [https://medium.com](https://medium.com/@shrutitech98/clone-graph-why-this-problem-isnt-as-simple-as-it-looks-43c0c5079c43)
[13] [https://codesignal.com](https://codesignal.com/learn/courses/getting-deep-into-complex-algorithms-for-interviews-with-ruby/lessons/mastering-graph-algorithms)
[14] [https://herovired.com](https://herovired.com/learning-hub/blogs/difference-between-bfs-and-dfs)
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() : val(0), neighbors(vector<Node*>()) {}
    Node(int _val) : val(_val), neighbors(vector<Node*>()) {}
};

class Solution {
private:
    Node* GLOBAL_MARKER = new Node(-999);

    bool isVisited(Node* node) {
        if (!node || node->neighbors.empty()) return false;
        Node* last_item = node->neighbors.back();
        if (last_item && !last_item->neighbors.empty() && last_item->neighbors.back() == GLOBAL_MARKER) {
            return true;
        }
        return false;
    }

public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        // --- PASS 1: Same as before (Clone & Embed) ---
        queue<Node*> q1;
        q1.push(node);
        
        Node* initial_clone = new Node(node->val);
        initial_clone->neighbors.push_back(GLOBAL_MARKER);
        node->neighbors.push_back(initial_clone);

        while (!q1.empty()) {
            Node* curr = q1.front();
            q1.pop();

            int original_size = curr->neighbors.size() - 1; 
            for (int i = 0; i < original_size; ++i) {
                Node* neighbor = curr->neighbors[i];
                if (!isVisited(neighbor)) {
                    Node* neighbor_clone = new Node(neighbor->val);
                    neighbor_clone->neighbors.push_back(GLOBAL_MARKER);
                    neighbor->neighbors.push_back(neighbor_clone);
                    q1.push(neighbor);
                }
            }
        }

        // --- PASS 2: Rebuild AND Clean up simultaneously ---
        queue<Node*> q2;
        q2.push(node);
        
        initial_clone->neighbors.pop_back(); // Unstamp head clone

        while (!q2.empty()) {
            Node* curr = q2.front();
            q2.pop();

            // 1. Grab the clone from the back
            Node* curr_clone = curr->neighbors.back();
            
            // 2. original_size excludes the embedded clone pointer
            int original_size = curr->neighbors.size() - 1;

            for (int i = 0; i < original_size; ++i) {
                Node* neighbor = curr->neighbors[i];
                Node* neighbor_clone = neighbor->neighbors.back();

                // Build the cloned graph's edge
                curr_clone->neighbors.push_back(neighbor_clone);

                // Check Pass 2 visited status via the neighbor's clone
                if (!neighbor_clone->neighbors.empty() && neighbor_clone->neighbors.back() == GLOBAL_MARKER) {
                    neighbor_clone->neighbors.pop_back(); // Unstamp
                    q2.push(neighbor); // Enqueue neighbor
                }
            }

            // 3. CRITICAL STEP: We are completely done reading curr->neighbors.
            // Pop the embedded clone pointer NOW to repair the original node!
            curr->neighbors.pop_back();
        }

        return initial_clone;
    }

    ~Solution() { delete GLOBAL_MARKER; }
};



// Helper function to print adjacency list representation of a graph (for verification)
void printGraph(Node* node, int total_nodes) {
    if (!node) {
        cout << "[]" << endl;
        return;
    }
    
    // Collect all nodes into an ordered array based on their 1-indexed values
    vector<Node*> nodes(total_nodes + 1, nullptr);
    unordered_map<Node*, bool> seen;
    queue<Node*> q;
    
    q.push(node);
    seen[node] = true;
    
    while(!q.empty()) {
        Node* curr = q.front();
        q.pop();
        if(curr->val <= total_nodes) {
            nodes[curr->val] = curr;
        }
        for(Node* n : curr->neighbors) {
            if(!seen[n]) {
                seen[n] = true;
                q.push(n);
            }
        }
    }

    cout << "[";
    for (int i = 1; i <= total_nodes; ++i) {
        cout << "[";
        if (nodes[i]) {
            for (size_t j = 0; j < nodes[i]->neighbors.size(); ++j) {
                cout << nodes[i]->neighbors[j]->val;
                if (j + 1 < nodes[i]->neighbors.size()) cout << ",";
            }
        }
        cout << "]";
        if (i < total_nodes) cout << ",";
    }
    cout << "]" << endl;
}

// Driver program to test the solution
int main() {
    // Manually construct Example 1 graph:
    // Node 1 linked to Node 2
    // Node 2 linked to Node 1 and Node 3
    // Node 3 linked to Node 2
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);

    node1->neighbors = {node2};
    node2->neighbors = {node1, node3};
    node3->neighbors = {node2};

    cout << "Original Graph Adjacency List: ";
    printGraph(node1, 3);

    Solution solution;
    Node* clonedHead = solution.cloneGraph(node1);

    cout << "Cloned Graph Adjacency List:   ";
    printGraph(clonedHead, 3);

    // Basic address verification to ensure deep copy integrity
    if (node1 != clonedHead && node1->neighbors[0] != clonedHead->neighbors[0]) {
        cout << "Verification Success: Graphs reside at entirely distinct memory addresses." << endl;
    } else {
        cout << "Verification Failure: Detected shallow pointer copying." << endl;
    }

    // Free memory allocations
    delete node1; delete node2; delete node3;
    // (In production, you would recursively free the cloned graph nodes as well)

    return 0;
}

