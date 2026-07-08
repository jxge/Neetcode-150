class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // If both nodes are null, they are structurally identical.
        if (p == nullptr && q == nullptr) {
            return true;
        }
        
        // If only one node is null, or if their values differ, they are not identical.
        if (p == nullptr || q == nullptr || p->val != q->val) {
            return false;
        }
        
        // Recursively check if the left subtrees and right subtrees match.
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
