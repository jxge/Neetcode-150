/*
Approach 1: Using backtracking
Time Complexity: O(N 2^N)
Space Complexity: O(N) (for the stack)

Approach 2: Dynamic programming
    DP[i][j]=true if s[i..j] is a palindrome (i<=j).

    dp[i][i]=1 // single characters are always palindromes (lenght 1)
    // Check substrings of length 2 and greater
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                // Length 2 strings only need outer match; longer strings need inner match too
                if (len == 2 || dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                }
            }
        }
    }

*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution1 {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> currentPartition;
        backtrack(0, s, currentPartition, result);
        return result;
    }

private:
    void backtrack(int start, const string& s, vector<string>& currentPartition, vector<vector<string>>& result) {
        // If we reach the end of the string, a valid partition is found
        if (start == s.length()) {
            result.push_back(currentPartition);
            return;
        }

        for (int end = start; end < s.length(); ++end) {
            // Check if the substring s[start...end] is a palindrome
            if (isPalindrome(s, start, end)) {
                // Choose: add the current substring to the partition
                currentPartition.push_back(s.substr(start, end - start + 1));
                
                // Explore: move to the next characters
                backtrack(end + 1, s, currentPartition, result);
                
                // Unchoose: backtrack for other possibilities
                currentPartition.pop_back();
            }
        }
    }

    bool isPalindrome(const string& s, int low, int high) {
        while (low < high) {
            if (s[low++] != s[high--]) {
                return false;
            }
        }
        return true;
    }
};


class Solution2 {
public:
    vector<vector<string>> partition(string s) {
        int n = s.length();
        // dp[i][j] will be true if substring s[i...j] is a palindrome
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        
        // Fill the DP table
        // Single characters are always palindromes (length 1)
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
        }
        
        // Check substrings of length 2 and greater
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    // Length 2 strings only need outer match; longer strings need inner match too
                    if (len == 2 || dp[i + 1][j - 1]) {
                        dp[i][j] = true;
                    }
                }
            }
        }

        vector<vector<string>> result;
        vector<string> currentPartition;
        backtrack(0, s, currentPartition, result, dp);
        return result;
    }

private:
    void backtrack(int start, const string& s, vector<string>& currentPartition, 
                   vector<vector<string>>& result, const vector<vector<bool>>& dp) {
        // If we reach the end of the string, a valid partition is found
        if (start == s.length()) {
            result.push_back(currentPartition);
            return;
        }

        for (int end = start; end < s.length(); ++end) {
            // O(1) palindrome check using the precomputed DP table
            if (dp[start][end]) {
                // Choose
                currentPartition.push_back(s.substr(start, end - start + 1));
                
                // Explore
                backtrack(end + 1, s, currentPartition, result, dp);
                
                // Unchoose
                currentPartition.pop_back();
            }
        }
    }
};



// Driver Program
int main() {
    Solution solver;
    
    // Test Case 1
    string s1 = "aab";
    cout << "Input: s = \"" << s1 << "\"\nOutput:\n";
    vector<vector<string>> result1 = solver.partition(s1);
    for (const auto& partition : result1) {
        cout << "  [ ";
        for (const auto& str : partition) {
            cout << "\"" << str << "\" ";
        }
        cout << "]\n";
    }
    
    cout << "\n-------------------\n\n";

    // Test Case 2
    string s2 = "a";
    cout << "Input: s = \"" << s2 << "\"\nOutput:\n";
    vector<vector<string>> result2 = solver.partition(s2);
    for (const auto& partition : result2) {
        cout << "  [ ";
        for (const auto& str : partition) {
            cout << "\"" << str << "\" ";
        }
        cout << "]\n";
    }

    return 0;
}

