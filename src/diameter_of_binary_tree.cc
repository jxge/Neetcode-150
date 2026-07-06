#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Required for std::max
#include <optional>

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
    // Helper function that returns the height of the tree and updates maxDiameter
    int calculateDepth(TreeNode* node, int& maxDiameter) {
        if (node == nullptr) {
            return 0;
        }

        // Recursively find the height of left and right subtrees
        int leftHeight = calculateDepth(node->left, maxDiameter);
        int rightHeight = calculateDepth(node->right, maxDiameter);

        // Update the maximum diameter found so far
        maxDiameter = std::max(maxDiameter, leftHeight + rightHeight);

        // Return the height of the current node
        return 1 + std::max(leftHeight, rightHeight);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maxDiameter = 0;
        calculateDepth(root, maxDiameter);
        return maxDiameter;
    }
};

// --- Driver Code Functions ---

// Helper function to build a tree from a level-order vector containing optional values
TreeNode* insertLevelOrder(const std::vector<std::optional<int>>& arr) {
    if (arr.empty() || !arr[0].has_value()) return nullptr;
    
    TreeNode* root = new TreeNode(arr[0].value());
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
    
    // Example 1: Input: root = [1, null, 2, 3, 4, 5]
    // Max path is between 5 and 4 (Edges: 5 -> 3 -> 2 -> 4) which equals 3
    std::vector<std::optional<int>> input1 = {1, std::nullopt, 2, 3, 4, 5};
    TreeNode* root1 = insertLevelOrder(input1);
    
    int result1 = solution.diameterOfBinaryTree(root1);
    std::cout << "Example 1 Diameter: " << result1 << " (Expected: 3)\n";
    
    freeTree(root1);
    return 0;
}
