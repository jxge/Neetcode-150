#include <stack>

class BSTIterator {
private:
    std::stack<TreeNode*> s;

    // Helper function to push all left children of a node onto the stack
    void pushAllLeft(TreeNode* node) {
        while (node != nullptr) {
            s.push(node);
            node = node->left;
        }
    }

public:
    // Constructor initializes the iterator by pointing to the smallest element
    BSTIterator(TreeNode* root) {
        pushAllLeft(root);
    }
    
    // Returns the next smallest number
    int next() {
        TreeNode* topNode = s.top();
        s.pop();
        
        // If the popped node has a right child, process its left branch
        if (topNode->right != nullptr) {
            pushAllLeft(topNode->right);
        }
        
        return topNode->val;
    }
    
    // Returns whether we have a next smallest number
    bool hasNext() {
        return !s.empty();
    }
};
