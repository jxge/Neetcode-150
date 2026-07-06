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
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr = root;
        
        while (curr != nullptr) {
            // If both p and q are greater than parent, LCA must be in right subtree
            if (p->val > curr->val && q->val > curr->val) {
                curr = curr->right;
            }
            // If both p and q are less than parent, LCA must be in left subtree
            else if (p->val < curr->val && q->val < curr->val) {
                curr = curr->left;
            }
            // We have found the split point or one of the nodes matches curr.
            // This node is the Lowest Common Ancestor.
            else {
                return curr;
            }
        }
        
        return nullptr;
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

// Helper function to find a node by value in the tree
TreeNode* findNode(TreeNode* root, int target) {
    if (!root || root->val == target) return root;
    if (target < root->val) return findNode(root->left, target);
    return findNode(root->right, target);
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
    
    // Shared setup for Examples 1 & 2
    // Tree representation: [5,3,8,1,4,7,9,null,2]
    std::vector<std::optional<int>> inputTree = {5, 3, 8, 1, 4, 7, 9, std::nullopt, 2};
    
    // --- Example 1 ---
    TreeNode* root1 = insertLevelOrder(inputTree);
    TreeNode* p1 = findNode(root1, 3);
    TreeNode* q1 = findNode(root1, 8);
    
    TreeNode* lca1 = solution.lowestCommonAncestor(root1, p1, q1);
    if (lca1) {
        std::cout << "Example 1 LCA: " << lca1->val << " (Expected: 5)\n";
    }
    freeTree(root1);
    
    // --- Example 2 ---
    TreeNode* root2 = insertLevelOrder(inputTree);
    TreeNode* p2 = findNode(root2, 3);
    TreeNode* q2 = findNode(root2, 4);
    
    TreeNode* lca2 = solution.lowestCommonAncestor(root2, p2, q2);
    if (lca2) {
        std::cout << "Example 2 LCA: " << lca2->val << " (Expected: 3)\n";
    }
    freeTree(root2);
    
    return 0;
}
