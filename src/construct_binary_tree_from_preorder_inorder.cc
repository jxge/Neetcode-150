#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>

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
    unordered_map<int, int> inorderMap;
    int preorderIndex = 0;

    TreeNode* arrayToTree(vector<int>& preorder, int left, int right) {
        // If there are no elements to construct the subtree
        if (left > right) return nullptr;

        // Select the preorderIndex element as the root and increment it
        int rootValue = preorder[preorderIndex++];
        TreeNode* root = new TreeNode(rootValue);

        // Build left and right subtrees
        // Excluding rootValueMap[rootValue] element because it's the root
        root->left = arrayToTree(preorder, left, inorderMap[rootValue] - 1);
        root->right = arrayToTree(preorder, inorderMap[rootValue] + 1, right);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        preorderIndex = 0;
        inorderMap.clear();
        
        // Build a hashmap to store value -> its index relations
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }

        return arrayToTree(preorder, 0, inorder.size() - 1);
    }
};

// Driver program to test the code
void printLevelOrder(TreeNode* root) {
    if (!root) {
        cout << "[]" << endl;
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    vector<string> result;

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node) {
            result.push_back(to_string(node->val));
            q.push(node->left);
            q.push(node->right);
        } else {
            result.push_back("null");
        }
    }

    // Remove trailing "null" elements to match standard output format
    while (!result.empty() && result.back() == "null") {
        result.pop_back();
    }

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // Example 1
    vector<int> preorder1 = {1, 2, 3, 4};
    vector<int> inorder1 = {2, 1, 3, 4};
    TreeNode* root1 = solution.buildTree(preorder1, inorder1);
    cout << "Example 1 Output: ";
    printLevelOrder(root1); // Expected: [1,2,3,null,null,null,4]

    // Example 2
    vector<int> preorder2 = {1};
    vector<int> inorder2 = {1};
    TreeNode* root2 = solution.buildTree(preorder2, inorder2);
    cout << "Example 2 Output: ";
    printLevelOrder(root2); // Expected: [1]

    return 0;
}
