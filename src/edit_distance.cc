/*
Edit Distance

You are given two strings word1 and word2, each consisting of lowercase English
letters.

You are allowed to perform three operations on word1 an unlimited number of
times:

    Insert a character at any position
    Delete a character at any position
    Replace a character at any position

Return the minimum number of operations to make word1 equal word2.

Example 1:
Input: word1 = "monkeys", word2 = "money"
Output: 2
Explanation:
monkeys -> monkey (remove s)
monkey -> money (remove k)

Example 2:
Input: word1 = "neatcdee", word2 = "neetcode"
Output: 3
Explanation:
neatcdee -> neetcdee (replace a with e)
neetcdee -> neetcde (remove last e)
neetcde -> neetcode (insert o)

Constraints:
    0 <= word1.length, word2.length <= 100
    word1 and word2 consist of lowercase English letters.
*/

/*
Solution 1: 
  Let dp(i,j) be the edit distance between s1[0:i-1] and s2[0:j-1].
    dp(0,j) = j
    dp(i,0) = i
    dp(i,j) = dp(i-1,j-1) if s1[i-1]==s2[j-1]
    dp(i,j) = min(dp(i-1,j), dp(i,j-1), dp(i-1,j-1)) + 1 if s1[i-1]!=s2[j-1]
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution1 {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        // dp[i][j] stores the edit distance between word1[0...i-1] and word2[0...j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Base cases: transforming a string to/from an empty string
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i; // Deleting all characters from word1
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j; // Inserting all characters from word2
        }
        
        // Fill the DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    // Characters match, no operation needed
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // Characters mismatch, take minimum of Delete, Insert, or Replace
                    dp[i][j] = min({
                        dp[i - 1][j],    // Delete
                        dp[i][j - 1],    // Insert
                        dp[i - 1][j - 1] // Replace
                    }) + 1;
                }
            }
        }
        
        return dp[m][n];
    }
};

class Solution2 {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        // dp[j] will store the edit distance for the current prefix of word1 and word2[0...j-1]
        vector<int> dp(n + 1, 0);
        
        // Base case initialization for the 0th row (empty word1)
        for (int j = 0; j <= n; j++) {
            dp[j] = j;
        }
        
        // Iterate through each character of word1
        for (int i = 1; i <= m; i++) {
            // pre tracks the diagonal value: dp[i-1][j-1]
            int pre = dp[0]; 
            dp[0] = i; // Base case for column 0: dp[i][0] = i
            
            for (int j = 1; j <= n; j++) {
                // Save the current dp[j] before it gets overwritten. 
                // This saved value becomes the diagonal 'pre' for the next step (j + 1).
                int temp = dp[j];
                
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = pre; // Inherit from diagonal without adding operation cost
                } else {
                    dp[j] = min({
                        dp[j],     // Delete (value from previous row i-1, same column j)
                        dp[j - 1], // Insert (value from current row i, previous column j-1)
                        pre        // Replace (value from diagonal i-1, j-1)
                    }) + 1;
                }
                
                // Move the saved old state into pre for the next loop iteration
                pre = temp;
            }
        }
        
        return dp[n];
    }
};

template<class Solution>
int test() {
    Solution solver;

    // Test Case 1: Example 1 from description
    string w1_1 = "monkeys";
    string w1_2 = "money";
    int res1 = solver.minDistance(w1_1, w1_2);
    cout << "Test 1 -> Input: \"" << w1_1 << "\", \"" << w1_2 << "\" | Output: " << res1 << endl;
    assert(res1 == 2);

    // Test Case 2: Example 2 from description (Validates the Replace operation fix)
    string w2_1 = "neatcdee";
    string w2_2 = "neetcode";
    int res2 = solver.minDistance(w2_1, w2_2);
    cout << "Test 2 -> Input: \"" << w2_1 << "\", \"" << w2_2 << "\" | Output: " << res2 << endl;
    assert(res2 == 3);

    // Test Case 3: Completely empty strings
    string w3_1 = "";
    string w3_2 = "";
    int res3 = solver.minDistance(w3_1, w3_2);
    cout << "Test 3 -> Input: \"" << w3_1 << "\", \"" << w3_2 << "\" | Output: " << res3 << endl;
    assert(res3 == 0);

    // Test Case 4: One completely empty string (All insertions)
    string w4_1 = "";
    string w4_2 = "abc";
    int res4 = solver.minDistance(w4_1, w4_2);
    cout << "Test 4 -> Input: \"" << w4_1 << "\", \"" << w4_2 << "\" | Output: " << res4 << endl;
    assert(res4 == 3);

    // Test Case 5: Completely different strings of the same length
    string w5_1 = "abc";
    string w5_2 = "xyz";
    int res5 = solver.minDistance(w5_1, w5_2);
    cout << "Test 5 -> Input: \"" << w5_1 << "\", \"" << w5_2 << "\" | Output: " << res5 << endl;
    assert(res5 == 3);

    cout << "\n All edit distance verification tests passed!" << endl;
    return 0;
}

int main()
{
    test<Solution1>();
    test<Solution2>();
    return 0;
}
