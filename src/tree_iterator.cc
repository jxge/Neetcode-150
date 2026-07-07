#include <stack>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// ============================================================
// Pre-order: root -> left -> right
// Key idea: Stack; pop node, push right then left
// ============================================================
class PreOrderIterator {
public:
    explicit PreOrderIterator(TreeNode* root) {
        if (root) {
            stack_.push(root);
        }
    }
    bool hasNext() const {
        return !stack_.empty();
    }
    TreeNode* next() {
        if (!hasNext()) {
            return nullptr;
        }
        TreeNode* node = stack_.top();
        stack_.pop();
        // Push right first so left is processed first
        if (node->right) stack_.push(node->right);
        if (node->left)  stack_.push(node->left);
        return node;
    }
private:
    std::stack<TreeNode*> stack_;
};

// ============================================================
// In-order: left -> root -> right
// Key Idea: Stack; go left as far as possible, visit, then right
// ============================================================
class InOrderIterator {
public:
    explicit InOrderIterator(TreeNode* root) {
        pushLeftPath(root);
    }
    bool hasNext() const {
        return !stack_.empty();
    }
    TreeNode* next() {
        if (!hasNext()) {
            return nullptr;
        }
        TreeNode* node = stack_.top();
        stack_.pop();
        // Current node is visited; move to right subtree
        pushLeftPath(node->right);
        return node;
    }
private:
    std::stack<TreeNode*> stack_;
    void pushLeftPath(TreeNode* node) {
        while (node) {
            stack_.push(node);
            node = node->left;
        }
    }
};
// ============================================================
// Post-order: left -> right -> root
// Key Idea: Stack + lastVisited_; visit only after both subtrees done
// ============================================================
class PostOrderIterator {
public:
    explicit PostOrderIterator(TreeNode* root) : lastVisited_(nullptr) {
        pushLeftPath(root);
    }

    bool hasNext() const {
        return !stack_.empty();
    }

    TreeNode* next() {
        if (!hasNext()) {
            return nullptr;
        }

        // Loop until we find a node ready to be popped
        while (!stack_.empty()) {
            TreeNode* cur = stack_.top();

            // If right subtree exists and isn't processed, traverse it
            if (cur->right && cur->right != lastVisited_) {
                pushLeftPath(cur->right);
                continue;
            }
            
            // Both subtrees are processed, safe to pop and return
            stack_.pop();
            lastVisited_ = cur;
            return cur;
        }
        return nullptr;
    }

private:
    std::stack<TreeNode*> stack_;
    TreeNode* lastVisited_;

    void pushLeftPath(TreeNode* node) {
        while (node) {
            stack_.push(node);
            node = node->left;
        }
    }
};



