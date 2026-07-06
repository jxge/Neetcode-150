#include <iostream>
#include <vector>
#include <queue>
#include <climits>   // Required for LLONG_MIN and LLONG_MAX
#include <optional>

/********************************************************************************************* 
We must ensure that every node in a left subtree is strictly less than the ancestor node, and 
every node in a right subtree is strictly greater than the ancestor node. To do this we need
to pass a range in DFS traversal.
    DFS (n, min, max)
       DFS(n->left, min, n->value);
       DFS(n->right, n->value, max);
*********************************************************************************************/
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
    // Helper function that strictly validates boundaries using long long to avoid INT overflow
    bool validate(TreeNode* node, long long minBound, long long maxBound) {
        if (node == nullptr) {
            return true;
        }

        // Current node's value must fall strictly within the allowed range
        if (node->val <= minBound || node->val >= maxBound) {
            return false;
        }

        // Left child must be smaller than node->val (updates maxBound)
        // Right child must be larger than node->val (updates minBound)
        return validate(node->left, minBound, node->val) && 
               validate(node->right, node->val, maxBound);
    }

public:
    bool isValidBST(TreeNode* root) {
        // Evaluate the tree using absolute boundaries
        return validate(root, LLONG_MIN, LLONG_MAX);
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
    std::cout << std::boolalpha; // Print true/false instead of 1/0
    
    // Example 1: root = [2, 1, 3] -> Valid BST
    std::vector<std::optional<int>> input1 = {2, 1, 3};
    TreeNode* root1 = insertLevelOrder(input1);
    std::cout << "Example 1: " << solution.isValidBST(root1) << " (Expected: true)\n";
    freeTree(root1);
    
    // Example 2: root = [1, 2, 3] -> Invalid BST (left child 2 is larger than root 1)
    std::vector<std::optional<int>> input2 = {1, 2, 3};
    TreeNode* root2 = insertLevelOrder(input2);
    std::cout << "Example 2: " << solution.isValidBST(root2) << " (Expected: false)\n";
    freeTree(root2);
    
    return 0;
}
