/*
Time Complexity: 
  insert: O(N)
  search: O(N)
  startWith: O(N)
Space Complexity: O(M), where M is the lenght of the string prefix
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Definition of the Trie Node structure
struct TrieNode {
    // Array to store pointers to child nodes (for 26 lowercase English letters)
    TrieNode* children[26];
    // Flag to indicate if the node represents the end of a valid word
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
    
    // Destructor to automatically clean up dynamically allocated memory
    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (children[i] != nullptr) {
                delete children[i];
            }
        }
    }
};

class PrefixTree {
private:
    TrieNode* root;

public:
    // Initializes the prefix tree object
    PrefixTree() {
        root = new TrieNode();
    }

    // Destructor to prevent memory leaks
    ~PrefixTree() {
        delete root;
    }
    
    // Inserts the string word into the prefix tree
    void insert(string word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a'; // Convert character to index 0-25
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }
    
    // Returns true if the string word is in the prefix tree, and false otherwise
    bool search(string word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                return false;
            }
            current = current->children[index];
        }
        return current->isEndOfWord;
    }
    
    // Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise
    bool startsWith(string prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                return false;
            }
            current = current->children[index];
        }
        return true;
    }
};

// Driver Program
int main() {
    // Instantiate the Trie
    PrefixTree* prefixTree = new PrefixTree();
    
    cout << "Executing actions matching the example scenario:\n\n";

    // 1. Insert "dog"
    prefixTree->insert("dog");
    cout << "Inserted: \"dog\" -> null" << endl;

    // 2. Search "dog"
    cout << "Search \"dog\": " << (prefixTree->search("dog") ? "true" : "false") << endl;

    // 3. Search "do"
    cout << "Search \"do\": " << (prefixTree->search("do") ? "true" : "false") << endl;

    // 4. StartsWith "do"
    cout << "StartsWith \"do\": " << (prefixTree->startsWith("do") ? "true" : "false") << endl;

    // 5. Insert "do"
    prefixTree->insert("do");
    cout << "Inserted: \"do\" -> null" << endl;

    // 6. Search "do"
    cout << "Search \"do\": " << (prefixTree->search("do") ? "true" : "false") << endl;

    // Clean up
    delete prefixTree;
    return 0;
}

