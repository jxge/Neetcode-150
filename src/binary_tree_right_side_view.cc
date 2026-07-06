#include <iostream>
#include <vector>
#include <queue>
#include <optional>

/*******************************************************************************
Solution 1 (Modified DFS Apporach): A modified DFS keeps track of the current depth.
If the current depth equals the size of our result array, it means this is the first
time we are visiting a node at this depth level. Because we visit right children 
first, this node is guaranteed to be the rightmost visible node for that level.

Solution 2 (BFS Apporach): To extract the right side view using a Breadth-First 
Search (BFS) / Level-Order traversal approach, we process the tree level by level
using a queue. For each level, we find the number of nodes present, loop through
them, and capture the value of the very last node at that level before moving on 
to the next
********************************************************************************/

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
    void dfs(TreeNode* node, int depth, std::vector<int>& view) {
        if (node == nullptr) {
            return;
        }

        // If this is the first time visiting this depth, it's the rightmost node
        if (depth == view.size()) {
            view.push_back(node->val);
        }

        // Prioritize the right subtree first, then the left subtree
        dfs(node->right, depth + 1, view);
        dfs(node->left, depth + 1, view);
    }

public:
    std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> view;
        dfs(root, 0, view);
        return view;
    }
};

class Solution2 {
public:
    std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> view;
        if (root == nullptr) {
            return view;
        }

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            
            // Iterate through all nodes at the current level
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* curr = q.front();
                q.pop();

                // If this is the last node in the current level, it is visible from the right
                if (i == levelSize - 1) {
                    view.push_back(curr->val);
                }

                // Add children to the queue for the next level
                if (curr->left != nullptr) {
                    q.push(curr->left);
                }
                if (curr->right != nullptr) {
                    q.push(curr->right);
                }
            }
        }

        return view;
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

// Helper function to print vectors
void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
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
    
    // Example 1: root = [1, 2, 3, null, 4, null, 5]
    std::vector<std::optional<int>> input1 = {1, 2, 3, std::nullopt, 4, std::nullopt, 5};
    TreeNode* root1 = insertLevelOrder(input1);
    std::vector<int> result1 = solution.rightSideView(root1);
    std::cout << "Example 1 View: ";
    printVector(result1); // Expected: [1, 3, 5]
    freeTree(root1);
    
    // Example 2: root = [1, 2, 3, 4, null, null, null, 5]
    std::vector<std::optional<int>> input2 = {1, 2, 3, 4, std::nullopt, std::nullopt, std::nullopt, 5};
    TreeNode* root2 = insertLevelOrder(input2);
    std::vector<int> result2 = solution.rightSideView(root2);
    std::cout << "Example 2 View: ";
    printVector(result2); // Expected: [1, 3, 4, 5]
    freeTree(root2);

    // Example 3: root = [1, null, 2]
    std::vector<std::optional<int>> input3 = {1, std::nullopt, 2};
    TreeNode* root3 = insertLevelOrder(input3);
    std::vector<int> result3 = solution.rightSideView(root3);
    std::cout << "Example 3 View: ";
    printVector(result3); // Expected: [1, 2]
    freeTree(root3);

    // Example 4: root = []
    std::vector<std::optional<int>> input4 = {};
    TreeNode* root4 = insertLevelOrder(input4);
    std::vector<int> result4 = solution.rightSideView(root4);
    std::cout << "Example 4 View: ";
    printVector(result4); // Expected: []
    freeTree(root4);
    
    return 0;
}
