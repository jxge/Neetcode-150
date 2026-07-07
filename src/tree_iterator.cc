#include <stack>

/***********************************************************************************************
1. In-Order Iterator (Left → Root → Right)
2. Pre-Order Iterator (Root → Left → Right)
3. Post-Order Iterator (Left → Right → Root)
************************************************************************************************/
    
class InOrderIterator {
private:
    std::stack<TreeNode*> s;

    // Internal helper to push a node and all of its left descendants
    void pushLeftChildren(TreeNode* node) {
        while (node != nullptr) {
            s.push(node);
            node = node->left;
        }
    }

public:
    // Constructor prepares the stack pointing to the smallest node
    InOrderIterator(TreeNode* root) {
        pushLeftChildren(root);
    }
    
    // Checks if there are more elements left to visit
    bool hasNext() {
        return !s.empty();
    }
    
    // Returns the next smallest element value in the BST
    int next() {
        // The top of the stack is the current in-order element
        TreeNode* curr = s.top();
        s.pop();
        
        // If a right child exists, find the leftmost element in that subtree
        if (curr->right != nullptr) {
            pushLeftChildren(curr->right);
        }
        
        return curr->val;
    }
};


class PreOrderIterator {
private:
    std::stack<TreeNode*> s;

public:
    PreOrderIterator(TreeNode* root) {
        if (root != nullptr) {
            s.push(root);
        }
    }
    
    bool hasNext() {
        return !s.empty();
    }
    
    int next() {
        TreeNode* curr = s.top();
        s.pop();
        
        // Push right first so left sits on top and gets processed next
        if (curr->right != nullptr) {
            s.push(curr->right);
        }
        if (curr->left != nullptr) {
            s.push(curr->left);
        }
        
        return curr->val;
    }
};


/**********************************************************************************************************************************
Most challenging. To track our movement dynamically without modifying the tree structure, we keep track of the previously popped 
node. This allows the iterator to know if it is diving down into a child or backtracking up from a completed subtree.

The tracking variable prev acts as a directional compass:
  (1) prev == parent (Moving Down): Keep diving until you hit a leaf node.
  (2) curr->left == prev (Moving Up from Left): Stop! Check if there is a right sibling to process before you can print the parent.
  (3) curr->right == prev (Moving Up from Right): Both children are done. It is finally safe to pop and return the parent node.
***********************************************************************************************************************************/
class PostOrderIterator {
private:
    std::stack<TreeNode*> s;
    TreeNode* prev; // Keeps track of the last processed node

    // Helper to find the leftmost leaf node of the current path
    void findNextLeaf(TreeNode* curr) {
        while (curr != nullptr) {
            s.push(curr);
            if (curr->left != nullptr) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
    }

public:
    PostOrderIterator(TreeNode* root) {
        prev = nullptr;
        findNextLeaf(root);
    }
    
    bool hasNext() {
        return !s.empty();
    }
    
    int next() {
        while (!s.empty()) {
            TreeNode* curr = s.top();
            
            // Check if we are moving down the tree or coming back up
            if (prev == nullptr || prev->left == curr || prev->right == curr) {
                if (curr->left != nullptr) {
                    findNextLeaf(curr->left);
                } else if (curr->right != nullptr) {
                    findNextLeaf(curr->right);
                }
            } 
            // Check if we just came up from the left child
            else if (curr->left == prev) {
                if (curr->right != nullptr) {
                    findNextLeaf(curr->right);
                }
            } 
            // If we came up from the right child (or left child if no right child exists)
            else {
                s.pop();
                prev = curr;
                return curr->val;
            }
            
            // Re-read current top after updating the stack path
            curr = s.top();
            s.pop();
            prev = curr;
            return curr->val;
        }
        return -1;
    }
};






