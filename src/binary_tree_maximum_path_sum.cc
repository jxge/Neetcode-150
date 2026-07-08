#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>
#include <string>

//  let P(n) be the maximum sum from node 'n' to some child node
//      The the currentPathSum = n->val + P(n->left) + P(n->right)
//      P(n) = MAX(MAX(P(n->left), 0), MAX(P(n->right, 0))) + n->val
using namespace std;

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
    int globalMaxSum;

    int calculateMaxGain(TreeNode* node) {
        if (!node) return 0;

        // Recursively fetch the max sum from left and right subtrees.
        // If a subtree path sum is negative, ignore it by clamping to 0.
        int leftGain = max(calculateMaxGain(node->left), 0);
        int rightGain = max(calculateMaxGain(node->right), 0);

        // Price of the path starting at leftGain, peaking at current node, and ending at rightGain
        int currentPathSum = node->val + leftGain + rightGain;

        // Update the global maximum if the current path is better
        globalMaxSum = max(globalMaxSum, currentPathSum);

        // For the parent node call, return the max path going down one branch
        return node->val + max(leftGain, rightGain);
    }

public:
    int maxPathSum(TreeNode* root) {
        globalMaxSum = INT_MIN;
        calculateMaxGain(root);
        return globalMaxSum;
    }
};

// Helper function to build a tree from level-order vector input
TreeNode* buildTreeFromVector(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return nullptr;

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);

    size_t i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* current = q.front();
        q.pop();

        if (i < nodes.size() && nodes[i] != "null") {
            current->left = new TreeNode(stoi(nodes[i]));
            q.push(current->left);
        }
        i++;

        if (i < nodes.size() && nodes[i] != "null") {
            current->right = new TreeNode(stoi(nodes[i]));
            q.push(current->right);
        }
        i++;
    }
    return root;
}

// Driver program to test the solution
int main() {
    Solution solution;

    // Example 1: root = [1,2,3]
    vector<string> tree1 = {"1", "2", "3"};
    TreeNode* root1 = buildTreeFromVector(tree1);
    cout << "Example 1 Output: " << solution.maxPathSum(root1) << " (Expected: 6)" << endl;

    // Example 2: root = [-15,10,20,null,null,15,5,-5]
    // Note: To match the structural representation in the prompt:
    // -15 is root. Left child is 10, Right child is 20.
    // 20's left child is 15, right child is 5.
    // 15's left child is -5.
    vector<string> tree2 = {"-15", "10", "20", "null", "null", "15", "5", "-5"};
    TreeNode* root2 = buildTreeFromVector(tree2);
    cout << "Example 2 Output: " << solution.maxPathSum(root2) << " (Expected: 40)" << endl;

    return 0;
}
