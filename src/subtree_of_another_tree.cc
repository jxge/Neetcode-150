#include <iostream>
#include <vector>
#include <queue>
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
    // Helper function to check if two trees are exactly identical
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        }
        if (p == nullptr || q == nullptr || p->val != q->val) {
            return false;
        }
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // Base case: If root is null, it cannot contain a non-empty subRoot
        if (root == nullptr) {
            return false;
        }
        
        // Check if the tree starting at the current root node matches subRoot
        if (isSameTree(root, subRoot)) {
            return true;
        }
        
        // Otherwise, search for a match in the left or right subtrees
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};

