class Solution {
public:
    int maxDepth(TreeNode* root) {
        // Base case: An empty tree has a depth of 0
        if (root == nullptr) {
            return 0;
        }
        
        // Recursively find the depth of left and right subtrees
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        
        // The overall depth is 1 (current node) + the maximum of the two subtrees
        return 1 + std::max(leftDepth, rightDepth);
    }
};
