/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

 class Solution {
private:
    // Helper function that returns the height of the tree if balanced, or -1 if unbalanced.
    int checkHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        // Check left subtree
        int leftHeight = checkHeight(node->left);
        if (leftHeight == -1) return -1; // Left subtree is already unbalanced

        // Check right subtree
        int rightHeight = checkHeight(node->right);
        if (rightHeight == -1) return -1; // Right subtree is already unbalanced

        // If current node is unbalanced, return -1
        if (std::abs(leftHeight - rightHeight) > 1) {
            return -1;
        }

        // Return the actual height of this node
        return 1 + std::max(leftHeight, rightHeight);
    }

public:
    bool isBalanced(TreeNode* root) {
        // If the helper returns -1, the tree is unbalanced; otherwise it is balanced.
        return checkHeight(root) != -1;
    }
};
