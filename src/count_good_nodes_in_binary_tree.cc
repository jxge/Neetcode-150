#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Required for std::max
#include <optional>

/*******************************************************************************************
To count the number of "good" nodes in a binary tree, we will pass the maximum value
seen so during a Depth-First Search (DFS) traversal.
*******************************************************************************************/
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    int dfs(TreeNode* node, int maxSoFar) {
        if (node == nullptr) {
            return 0;
        }

        int count = 0;
        // A node is "good" if its value is >= the maximum value seen on the path from root
        if (node->val >= maxSoFar) {
            count = 1;
        }

        // Update the maximum value seen so far for child paths
        maxSoFar = std::max(maxSoFar, node->val);

        // Accumulate good nodes found in left and right subtrees
        count += dfs(node->left, maxSoFar);
        count += dfs(node->right, maxSoFar);

        return count;
    }

public:
    int goodNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        // Start DFS traversal using the root node's value as the initial maximum path value
        return dfs(root, root->val);
    }
};

// --- Driver Code Functions ---

// Helper function to build a tree from a level-order vector containing optional values
TreeNode* insertLevelOrder(const std::vector<std::optional<int>>& arr) {
    if (arr.empty() || !arr.has_value()) return nullptr;
    
    TreeNode* root = new TreeNode(arr.value());
    std::queue<TreeNode*> q;
    q.push(root);
    
    size_t i = 1;
    while (!q.empty() && i < arr.size()) {
        TreeNode* curr = q.front();
        q.pop();
        
        // Process left child
        if (i < arr.size()) {
            if (arr[i].has_value()) {
                curr->left = new TreeNode(arr[i].value());
                q.push(curr->left);
            }
            i++;
        }
        
        // Process right child
        if (i < arr.size()) {
            if (arr[i].has_value()) {
                curr->right = new TreeNode(arr[i].value());
                q.push(curr->right);
            }
            i++;
        }
    }
    return root;
}

// Helper function to free memory
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    Solution solution;
    
    // Example 1: root = [2, 1, 1, 3, null, 1, 5]
    // Good nodes: 2 (root), 3 (path: 2->1->3), 5 (path: 2->1->5)
    std::vector<std::optional<int>> input1 = {2, 1, 1, 3, std::nullopt, 1, 5};
    TreeNode* root1 = insertLevelOrder(input1);
    std::cout << "Example 1 Good Nodes: " << solution.goodNodes(root1) << " (Expected: 3)\n";
    freeTree(root1);
    
    // Example 2: root = [1, 2, -1, 3, 4]
    // Good nodes: 1, 2, 3, 4
    std::vector<std::optional<int>> input2 = {1, 2, -1, 3, 4};
    TreeNode* root2 = insertLevelOrder(input2);
    std::cout << "Example 2 Good Nodes: " << solution.goodNodes(root2) << " (Expected: 4)\n";
    freeTree(root2);
    
    return 0;
}
