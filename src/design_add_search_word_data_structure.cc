/*
Time Complexity:
  addWord: O(M) where M is the length of the string
  search:  O(M) if the string does not contain '.'
Space Complexity: O(T) where T is the total number of characters in all words added to build the tree.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Definition of the Trie Node structure
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }

    // Destructor to clean up memory automatically
    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (children[i] != nullptr) {
                delete children[i];
            }
        }
    }
};

class WordDictionary {
private:
    TrieNode* root;

    // Helper function for recursive backtracking search
    bool searchInNode(const string& word, int index, TrieNode* current) {
        // Base case: If we reached the end of the word, check if it forms a full word
        if (index == word.length()) {
            return current->isEndOfWord;
        }

        char ch = word[index];

        // Handle wildcard '.'
        if (ch == '.') {
            // Check all 26 possible child paths
            for (int i = 0; i < 26; i++) {
                if (current->children[i] != nullptr) {
                    if (searchInNode(word, index + 1, current->children[i])) {
                        return true;
                    }
                }
            }
            return false; // None of the paths matched
        } 
        // Handle regular character 'a' - 'z'
        else {
            int childIndex = ch - 'a';
            if (current->children[childIndex] == nullptr) {
                return false;
            }
            return searchInNode(word, index + 1, current->children[childIndex]);
        }
    }

public:
    WordDictionary() {
        root = new TrieNode();
    }

    ~WordDictionary() {
        delete root;
    }
    
    // Adds a word into the data structure
    void addWord(string word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }
    
    // Returns true if there is any string matching the word
    bool search(string word) {
        return searchInNode(word, 0, root);
    }
};

// Driver Program
int main() {
    WordDictionary* wordDictionary = new WordDictionary();
    
    cout << "Executing actions matching the example scenario:\n\n";

    wordDictionary->addWord("day");
    cout << "Added: \"day\"" << endl;
    wordDictionary->addWord("bay");
    cout << "Added: \"bay\"" << endl;
    wordDictionary->addWord("may");
    cout << "Added: \"may\"" << endl;

    // Run search operations
    cout << "Search \"say\": " << (wordDictionary->search("say") ? "true" : "false") << " (Expected: false)" << endl;
    cout << "Search \"day\": " << (wordDictionary->search("day") ? "true" : "false") << " (Expected: true)" << endl;
    cout << "Search \".ay\": " << (wordDictionary->search(".ay") ? "true" : "false") << " (Expected: true)" << endl;
    cout << "Search \"b..\": " << (wordDictionary->search("b..") ? "true" : "false") << " (Expected: true)" << endl;

    delete wordDictionary;
    return 0;
}

