/************************************************************************************************
The k-th smallest value in a Binary Search Tree (BST) can be found efficiently by performing an 
in-order traversal, which visits the nodes in ascending order. By maintaining a counter during 
the traversal, we can stop and return the node's value as soon as we visit the k-th node.
*************************************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

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
public:
    int kthSmallest(TreeNode* root, int k) {
        int count = 0;
        int result = -1;
        inorder(root, k, count, result);
        return result;
    }

private:
    void inorder(TreeNode* node, int k, int& count, int& result) {
        if (!node || count >= k) {
            return;
        }
        
        inorder(node->left, k, count, result);
        
        count++;
        if (count == k) {
            result = node->val;
            return;
        }
        
        inorder(node->right, k, count, result);
    }
};

class Solution2 {
public:
    int kthSmallest(TreeNode* root, int k) {
        std::stack<TreeNode*> s;
        TreeNode* curr = root;
        
        while (curr != nullptr || !s.empty()) {
            // 1. Go to the leftmost node of the current subtree
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            
            // 2. Process the top node in the stack
            curr = s.top();
            s.pop();
            
            k--;
            if (k == 0) {
                return curr->val;
            }
            
            // 3. Move to the right subtree
            curr = curr->right;
        }
        
        return -1; // Fallback case if k is out of bounds
    }
};


// Helper function to build a binary tree from a level-order vector (using -1 for null)
TreeNode* buildTree(const std::vector<int>& arr) {
    if (arr.empty() || arr[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(arr[0]);
    std::queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < arr.size()) {
        TreeNode* curr = q.front();
        q.pop();

        // Left child
        if (i < arr.size() && arr[i] != -1) {
            curr->left = new TreeNode(arr[i]);
            q.push(curr->left);
        }
        i++;

        // Right child
        if (i < arr.size() && arr[i] != -1) {
            curr->right = new TreeNode(arr[i]);
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// Helper function to free the allocated tree memory
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    Solution solution;

    // --- Example 1 ---
    // Input: root =, k = 1
    std::vector<int> tree1 = {2, 1, 3};
    int k1 = 1;
    TreeNode* root1 = buildTree(tree1);
    
    std::cout << "Example 1 Output: " << solution->kthSmallest(root1, k1) << " (Expected: 1)" << std::endl;
    freeTree(root1);

    // --- Example 2 ---
    // Input: root = [4,3,5,2,-1], k = 4  (-1 replaces null)
    std::vector<int> tree2 = {4, 3, 5, 2, -1};
    int k2 = 4;
    TreeNode* root2 = buildTree(tree2);
    
    std::cout << "Example 2 Output: " << solution->kthSmallest(root2, k2) << " (Expected: 5)" << std::endl;
    freeTree(root2);

    return 0;
}
