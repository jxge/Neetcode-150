#include <iostream>
#include <vector>
#include <queue>
#include <utility> // Required for std::swap

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
    TreeNode* invertTree(TreeNode* root) {
        // Base case: if the tree is empty, return nullptr
        if (root == nullptr) {
            return nullptr;
        }
        
        // Swap the left and right pointer targets using std::swap
        std::swap(root->left, root->right);
        
        // Recursively invert the subtrees
        invertTree(root->left);
        invertTree(root->right);
        
        return root;
    }
};

// --- Driver Code Functions ---

// Helper function to insert nodes in level-order fashion
TreeNode* insertLevelOrder(const std::vector<int>& arr) {
    if (arr.empty()) return nullptr;
    
    TreeNode* root = new TreeNode(arr[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    
    size_t i = 1;
    while (!q.empty() && i < arr.size()) {
        TreeNode* curr = q.front();
        q.pop();
        
        // Left child
        if (i < arr.size()) {
            curr->left = new TreeNode(arr[i]);
            q.push(curr->left);
            i++;
        }
        
        // Right child
        if (i < arr.size()) {
            curr->right = new TreeNode(arr[i]);
            q.push(curr->right);
            i++;
        }
    }
    return root;
}

// Helper function to print tree in level-order (BFS)
void printLevelOrder(TreeNode* root) {
    if (!root) {
        std::cout << "[]\n";
        return;
    }
    
    std::queue<TreeNode*> q;
    q.push(root);
    std::vector<int> result;
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (curr) {
            result.push_back(curr->val);
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << (i == result.size() - 1 ? "" : ", ");
    }
    std::cout << "]\n";
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
    
    // Example 1: Input: root = [1,2,3,4,5,6,7]
    std::vector<int> input1 = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root1 = insertLevelOrder(input1);
    
    std::cout << "Original Tree: ";
    printLevelOrder(root1);
    
    root1 = solution.invertTree(root1);
    
    std::cout << "Inverted Tree: ";
    printLevelOrder(root1); // Expected: [1, 3, 2, 7, 6, 5, 4]
    
    freeTree(root1);
    return 0;
}
