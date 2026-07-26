/*
Alien Dictionary

There is a new alien language that uses the English alphabet, but the order of
the letters is unknown.

You are given a list of strings words from the alien language's dictionary. It
is claimed that the strings in words are sorted lexicographically by the rules
of this new language.

If this claim is incorrect, and the given arrangement of strings in words
cannot correspond to any order of letters, return "".

Otherwise, return a string of the unique letters in the new alien language
sorted in lexicographically increasing order by the new language's rules. If
there are multiple solutions, return any of them.

A string a is lexicographically smaller than a string b if either of the
following is true:

The first letter where they differ is smaller in a than in b.  a is a
prefix of b and a.length < b.length.


Example 1:

Input: words = ["z","o"]
Output: "zo"
Explanation:
From "z" and "o", we know 'z' < 'o', so return "zo".

Example 2:
Input: words = ["hrn","hrf","er","enn","rfnn"]
Output: "hernf"
Explanation:
    from "hrn" and "hrf", we know 'n' < 'f'
    from "hrf" and "er", we know 'h' < 'e'
    from "er" and "enn", we know 'r' < 'n'
    from "enn" and "rfnn" we know 'e' < 'r'
    so one possible solution is "hernf"
*/


/*
 * (1) Create a directed graph.
 *     For each pair of adjacent words w1 and w2. If they differ at
 *     w1[j] and w2[j], add an edge from w1[j] to w2[j].
 * (2) Run topological sort (Kahn's Algorithm) on the directed graph.
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    string foreignDictionary(vector<string>& words) {
        // Step 1: Initialize graph and in-degree structures
        unordered_map<char, unordered_set<char>> adj;
        unordered_map<char, int> inDegree;
        
        // Put all unique characters in the structures
        for (const string& word : words) {
            for (char c : word) {
                if (inDegree.find(c) == inDegree.end()) {
                    inDegree[c] = 0;
                    adj[c] = unordered_set<char>();
                }
            }
        }
        
        // Step 2: Build the graph by comparing adjacent words
        // Note: we only need to compare adjacent words since
        // Lexicographical order transitive. If A<B and B<C, 
        // then A<C.
        for (size_t i = 0; i < words.size() - 1; ++i) {
            string w1 = words[i];
            string w2 = words[i + 1];
            size_t minLen = min(w1.length(), w2.length());
            
            // Check invalid prefix edge case (e.g., "abc" comes before "ab")
            if (w1.length() > w2.length() && w1.substr(0, minLen) == w2) {
                return "";
            }
            
            // Find the first differing character
            for (size_t j = 0; j < minLen; ++j) {
                if (w1[j] != w2[j]) {
                    char u = w1[j];
                    char v = w2[j];
                    // If edge u -> v doesn't exist yet, add it
                    if (adj[u].find(v) == adj[u].end()) {
                        adj[u].insert(v);
                        inDegree[v]++;
                    }
                    break; // Only the first differing character provides order
                }
            }
        }
        
        // Step 3: Kahn's Algorithm for Topological Sort
        queue<char> q;
        for (auto const& [ch, degree] : inDegree) {
            if (degree == 0) {
                q.push(ch);
            }
        }
        
        string result = "";
        while (!q.empty()) {
            char curr = q.front();
            q.pop();
            result += curr;
            
            for (char neighbor : adj[curr]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // Step 4: If result length matches unique characters, order is valid
        if (result.length() < inDegree.size()) {
            return "";
        }
        
        return result;
    }
};

// Driver program to test the solution
int main() {
    Solution solver;

    // Test Case 1
    vector<string> words1 = {"z", "o"};
    cout << "Test Case 1 Output: " << solver.foreignDictionary(words1) << endl; 
    // Expected: "zo"

    // Test Case 2
    vector<string> words2 = {"hrn", "hrf", "er", "enn", "rfnn"};
    cout << "Test Case 2 Output: " << solver.foreignDictionary(words2) << endl; 
    // Expected: "hernf" (or another valid topological order)

    // Test Case 3: Invalid order due to cycle (a < b and b < a)
    vector<string> words3 = {"abc", "bca", "abc"};
    cout << "Test Case 3 Output: " << solver.foreignDictionary(words3) << endl; 
    // Expected: ""

    // Test Case 4: Invalid prefix edge case
    vector<string> words4 = {"abc", "ab"};
    cout << "Test Case 4 Output: " << solver.foreignDictionary(words4) << endl; 
    // Expected: ""

    return 0;
}
