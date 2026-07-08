#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

/************************************************************************************************************************
Summary of Traversal Capabilities

Traversal Type    Can it Serialize/Deserialize    Reason
                  alone (with nulls)? 
Pre-Order         Yes                             Root is always at the front; child subtrees immediately follow.
Post-Order        Yes                             Root is always at the end; parsing backwards functions like pre-order.
Level-Order(BFS)  Yes                             Naturally maps parent-to-child indexing level by level.
In-Order          No                              Root is trapped in the middle, leaving subtree boundaries ambiguous.

For in-order consider the serialized string: #2#1#
If you pick 2 as the root:        2
                                   \
                                    1
                                    
If you pick 1 as the root:         1
                                 /
                                2
************************************************************************************************************************/
using namespace std;

// Definition for a binary tree node provided in the prompt.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class PreorderCodec {
private:
    // Helper function for preorder serialization.
    void serializeDFS(TreeNode* root, ostringstream& out) {
        if (root == nullptr) {
            out << "#,";
            return;
        }
        out << root->val << ",";
        serializeDFS(root->left, out);
        serializeDFS(root->right, out);
    }

    // Helper function for preorder deserialization.
    TreeNode* deserializeDFS(stringstream& in) {
        string valStr;
        if (!getline(in, valStr, ',')) {
            return nullptr;
        }
        
        if (valStr == "#") {
            return nullptr;
        }

        // Reconstruct the node and recursively link children
        TreeNode* node = new TreeNode(stoi(valStr));
        node->left = deserializeDFS(in);
        node->right = deserializeDFS(in);
        return node;
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serializeDFS(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream in(data);
        return deserializeDFS(in);
    }
};

class PostorderCodec {
private:
    // Helper for post-order serialization: Left -> Right -> Root
    void serializeDFS(TreeNode* root, ostringstream& out) {
        if (root == nullptr) {
            out << "#,";
            return;
        }
        serializeDFS(root->left, out);
        serializeDFS(root->right, out);
        out << root->val << ","; // Root is placed at the end
    }

    // Helper for post-order deserialization: Reads backwards (Root -> Right -> Left)
    TreeNode* deserializeDFS(vector<string>& tokens, int& index) {
        if (index < 0) {
            return nullptr;
        }

        string valStr = tokens[index--]; // Read current token and move cursor left
        
        if (valStr == "#") {
            return nullptr;
        }

        // Reconstruct the root node
        TreeNode* node = new TreeNode(stoi(valStr));
        
        // CRITICAL: Must build the RIGHT child before the LEFT child 
        // because we are reading the post-order array from back to front.
        node->right = deserializeDFS(tokens, index);
        node->left = deserializeDFS(tokens, index);
        
        return node;
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serializeDFS(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        // Tokenize the comma-separated string into a vector
        vector<string> tokens;
        stringstream ss(data);
        string token;
        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }

        // Start processing tokens from the very last element (the root)
        int index = tokens.size() - 1;
        return deserializeDFS(tokens, index);
    }
};


class LevelOrderCodec {
public:
    // Encodes a tree to a single string using BFS.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }

        string result = "";
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();

            if (curr == nullptr) {
                result += "#,";
            } else {
                result += to_string(curr->val) + ",";
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        return result;
    }

    // Decodes your encoded data to a tree using BFS.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }

        // Tokenize the comma-separated string into a vector
        vector<string> tokens;
        stringstream ss(data);
        string token;
        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }

        // Reconstruct the root node
        TreeNode* root = new TreeNode(stoi(tokens[0]));
        queue<TreeNode*> q;
        q.push(root);

        int i = 1; // Pointer to traverse the token vector
        while (!q.empty() && i < tokens.size()) {
            TreeNode* curr = q.front();
            q.pop();

            // Process left child
            if (tokens[i] != "#") {
                curr->left = new TreeNode(stoi(tokens[i]));
                q.push(curr->left);
            }
            i++;

            // Ensure we don't out-of-bound check, then process right child
            if (i < tokens.size() && tokens[i] != "#") {
                curr->right = new TreeNode(stoi(tokens[i]));
                q.push(curr->right);
            }
            i++;
        }

        return root;
    }
};

// Helper function to print tree in level-order format for verification.
void printLevelOrder(TreeNode* root) {
    if (!root) {
        cout << "[]" << endl;
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    vector<string> result;

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr) {
            result.push_back(to_string(curr->val));
            q.push(curr->left);
            q.push(curr->right);
        } else {
            result.push_back("null");
        }
    }

    // Trim trailing "null" strings to match clean visualization formatting
    while (!result.empty() && result.back() == "null") {
        result.pop_back();
    }

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : ",");
    }
    cout << "]" << endl;
}

int main() {
    Codec codec;

    // Manually constructing Example 1: root = [1,2,3,null,null,4,5]
    //       1
    //      / \
    //     2   3
    //        / \
    //       4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    cout << "--- Initial State ---" << endl;
    cout << "Original tree (Level-Order Layout): ";
    printLevelOrder(root);

    // 1. Run Serialization Pipeline
    string serializedData = codec.serialize(root);
    cout << "\n--- Serialized Data String ---" << endl;
    cout << "Encoded Output: " << serializedData << endl;

    // 2. Run Deserialization Pipeline
    TreeNode* deserializedRoot = codec.deserialize(serializedData);
    cout << "\n--- Deserialized State ---" << endl;
    cout << "Reconstructed Tree (Level-Order Layout): ";
    printLevelOrder(deserializedRoot);

    // Clean up dynamic memory
    delete root->right->right;
    delete root->right->left;
    delete root->right;
    delete root->left;
    delete root;
    
    // Note: In production code, deserializedRoot nodes would also be freed.

    return 0;
}

