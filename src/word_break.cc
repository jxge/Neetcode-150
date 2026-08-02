/*
Word Break

Given a string s and a dictionary of strings wordDict, return true if s can be
segmented into a space-separated sequence of dictionary words.

You are allowed to reuse words in the dictionary an unlimited number of times.
You may assume all dictionary words are unique.

Example 1:
Input: s = "neetcode", wordDict = ["neet","code"]
Output: true
Explanation: Return true because "neetcode" can be split into "neet" and "code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple","pen","ape"]
Output: true
Explanation: Return true because "applepenapple" can be split into "apple",
  "pen" and "apple". Notice that we can reuse words and also not use all the
  words.

Example 3:
Input: s = "catsincars", wordDict = ["cats","cat","sin","in","car"]
Output: false

Constraints:
    1 <= s.length <= 200
    1 <= wordDict.length <= 100
    1 <= wordDict[i].length <= 20
    s and wordDict[i] consist of only lowercase English letters.
*/

/*
Solution 1: Top-down DP with memoization

    DP(s, i) {
        if i >= s.size()
            return true;
        for each w in wordDict {
            if (w is a prefix && DP(s, i+w.size()) {
                return true;
            }
        }
        return false
}

Solution 2: Bottom-up DP
  Let DP(i) a boolean value indicating if s[0..i-1] can be sucessfully 
  segmented.
    DP(0) = 1  (empty string)
    DP(i) = there exist w in wordDict and  w is a suffix of s[0:i] and
        DP(i - w.size())==1

Solution 3: Bottom-up DP with 4 optimizations
    1. Use a tri for work lookup (finding a suffix string that starts with 
       dictionary word.
    2. Prune by word length (if all the word has the same size 5, no need
       to seach a prefix with other length).
    3. Replace substring copying with std::string_view
    4. Early exit via character filtering (if the word searched contain
       a character that does not occur in any dictionary word).,
*/

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <cassert>

using namespace std;


class Solution1 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        // memo[i] = -1  → not computed yet
        // memo[i] =  0  → s[i:] cannot be segmented
        // memo[i] =  1  → s[i:] can be segmented
        vector<int> memo(n, -1);

        // Recursive lambda with memoization
        function<bool(int)> dp = [&](int i) -> bool {
            // Reached the end: empty suffix is always segmentable
            if (i == n) return true;

            // Return cached result if available
            if (memo[i] != -1) return memo[i] == 1;

            // Try every word in the dictionary as a possible match
            for (const string& w : wordDict) {
                int len = w.size();
                // Check if w matches s[i : i+len] without creating a temporary substring
                if (i + len <= n && s.compare(i, len, w) == 0) {
                    // Recurse on the remaining suffix
                    if (dp(i + len)) {
                        memo[i] = 1;
                        return true;
                    }
                }
            }

            // No word could start a valid segmentation from position i
            memo[i] = 0;
            return false;
        };

        return dp(0);
    }
};


class Solution2 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true; // Base case: empty string

        for (int i = 0; i < n; ++i) {
            if (!dp[i]) continue; 
            
            for (const string& w : wordDict) {
                if (i + w.size() <= n && s.compare(i, w.size(), w) == 0) {
                    dp[i + w.size()] = true;
                }
            }
        }

        return dp[n];
    }
};

// A lightweight Trie node structured for performance
struct TrieNode {
    TrieNode* children[26] = {nullptr};
    bool isWordEnd = false;
};

class Solution3 {
private:
    TrieNode* root;

    // Helper to insert a word into the Trie
    void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = new TrieNode();
            }
            curr = curr->children[idx];
        }
        curr->isWordEnd = true;
    }

    // Helper to clear heap memory allocated for the Trie
    void clearTrie(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                clearTrie(node->children[i]);
            }
        }
        delete node;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        
        // --- OPTIMIZATION 4: Early Exit Character Filter ---
        bool dictChars[26] = {false};
        for (const string& w : wordDict) {
            for (char c : w) dictChars[c - 'a'] = true;
        }
        for (char c : s) {
            if (!dictChars[c - 'a']) return false; // Impossible to match
        }

        // --- OPTIMIZATION 1: Build the Trie ---
        root = new TrieNode();
        for (const string& w : wordDict) {
            insert(w);
        }

        // --- OPTIMIZATION 3: Zero-Allocation String Views ---
        // string_view is not needed here since we are using a tri.
        // If we use a hash to store the dictionary, then we need
        // a substring (length should be no more than the longest
        // word in the dictionary.
        //
        string_view sv(s);

        // dp[i] means s[0...i-1] can be segmented
        vector<bool> dp(n + 1, false);
        dp[0] = true; // Base case

        // --- CORE ALGORITHM ---
        for (int i = 0; i < n; ++i) {
            if (!dp[i]) continue;

            // Traverse the Trie forward from the valid position 'i'
            TrieNode* curr = root;
            for (int j = i; j < n; ++j) {
                int idx = sv[j] - 'a';
                curr = curr->children[idx];
                
                // If the prefix branch doesn't exist, we stop immediately
                if (!curr) break; 
                
                // Found a valid dictionary word ending at index j
                if (curr->isWordEnd) {
                    dp[j + 1] = true;
                }
            }
        }

        // Cleanup memory and return result
        bool result = dp[n];
        clearTrie(root);
        return result;
    }
};

// Helper function to print test results clearly
template<class Solution>
void runTestCase(int caseNum, string s, vector<string> wordDict, bool expected) {
    Solution solver;
    bool result = solver.wordBreak(s, wordDict);
    
    cout << "Test Case " << caseNum << ": ";
    if (result == expected) {
        cout << "✅ PASSED\n";
    } else {
        cout << "❌ FAILED (Expected " << (expected ? "true" : "false") 
             << ", got " << (result ? "true" : "false") << ")\n";
    }
}

int main() {
    cout << "--- Running Word Break Self-Check Driver ---\n\n";

    // Example 1
    runTestCase<Solution1>(1, "neetcode", {"neet", "code"}, true);
    runTestCase<Solution2>(1, "neetcode", {"neet", "code"}, true);

    // Example 2
    runTestCase<Solution1>(2, "applepenapple", {"apple", "pen", "ape"}, true);
    runTestCase<Solution2>(2, "applepenapple", {"apple", "pen", "ape"}, true);

    // Example 3
    runTestCase<Solution1>(3, "catsincars", {"cats", "cat", "sin", "in", "car"}, false);
    runTestCase<Solution2>(3, "catsincars", {"cats", "cat", "sin", "in", "car"}, false);

    // Additional Edge Case: Single character match
    runTestCase<Solution1>(4, "a", {"a"}, true);
    runTestCase<Solution2>(4, "a", {"a"}, true);

    // Additional Edge Case: No valid match possible
    runTestCase<Solution1>(5, "b", {"a"}, false);
    runTestCase<Solution2>(5, "b", {"a"}, false);

    cout << "\n--- Self-Check Complete ---\n";
    return 0;
}


