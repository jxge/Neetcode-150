/*
Longest Common Subsequence

Given two strings text1 and text2, return the length of the longest common
subsequence between the two strings if one exists, otherwise return 0.

A subsequence is a sequence that can be derived from the given sequence by
deleting some or no elements without changing the relative order of the
remaining characters.

For example, "cat" is a subsequence of "crabt".

A common subsequence of two strings is a subsequence that exists in both strings.

Example 1:
Input: text1 = "cat", text2 = "crabt" 
Output: 3 

Explanation: The longest common subsequence is "cat" which has a length of 3.

Example 2:

Input: text1 = "abcd", text2 = "abcd"

Output: 4

Example 3:

Input: text1 = "abcd", text2 = "efgh"

Output: 0

Constraints:

    1 <= text1.length, text2.length <= 1000
*/

/*
Approach 1: Bottom-up DP with optimized space
 Let dp(i,j) the largest common sequence between text1[0...i-1] and text2[0...j-1].

             /  0                           if i=0 or j=0
    d(i,j) = |  d(i-1,j-1) + 1              if i,j>0 and text1[i-1] = text2[j-1]
             \  max(dp(i-1,j), dp(i, j-1)   if i,j>0 and text1[i-1]!= text2[j-]

 Complexity: O(M*N)

Approach 2: Hunt-Szmanski Algorithm (solve the LCS problem by converting it to LIS)

 Step 1: find all (i,j) such that text1[i]=text2[j]
 Step 2: Sort i coordinates in assending order
 Step 3: Sort j coordinates in descending order for matching order
 Step 4: Once all matching pairs are collected and sorted, discard i coordinate.
 Step 5: Find the LIS from the remaining j coordinates
 
 Complexity: O(R+n)lg(n)) where R is the totoal number of matching pairs.

         a  c  b  d  d
        ---------------
     c |    *          |  (0,1)
     a | *             |  (1,0)
     b |       *       |  (2,2)
     a | *             |  (3,0)
     d |          *  * |  (4,4), (4,3)  => after Step 4, we have [1,0,2,0,4,3]
        ---------------                 => after Step 5, LIS=[0,2,3]

Approach 3: Hirschberg's Algorithm
  Improved the regular space-optimized DP that can only find the length of the LCS,
  Hirschbery's algorithm can reconstruct the actual matching string using 
  O(min(m,n)) space. 

Approach 4: The Bit-Parallelism 
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // Optimization: Ensure text2 is the shorter string to minimize space
        if (text1.length() < text2.length()) {
            swap(text1, text2);
        }
        
        int m = text1.length();
        int n = text2.length();
        
        // dp array represents the results for the previous row
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= m; ++i) {
            // 'prev' stores the value of dp[i-1][j-1] before it gets overwritten
            int prev = 0;   // dp(i,0) = 0
            
            for (int j = 1; j <= n; ++j) {
                // Save the current dp[j] value (which is dp[i-1][j] for the next loop iteration)
                int temp = dp[j];
                
                if (text1[i - 1] == text2[j - 1]) {
                    // Match found: current diagonal value + 1
                    dp[j] = prev + 1;
                } else {
                    // No match: max of top cell (dp[j]) and left cell (dp[j-1])
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                
                // Update 'prev' for the next column item
                prev = temp;
            }
        }
        
        return dp[n];
    }
};

int main() {
    Solution solver;

    // Test Case 1: Standard match with deletions
    string t1_1 = "cat", t2_1 = "crabt";
    int ans1 = solver.longestCommonSubsequence(t1_1, t2_1);
    cout << "Test 1 Passed: LCS(\"" << t1_1 << "\", \"" << t2_1 << "\") = " << ans1 << " (Expected: 3)\n";
    assert(ans1 == 3);

    // Test Case 2: Identical strings
    string t1_2 = "abcd", t2_2 = "abcd";
    int ans2 = solver.longestCommonSubsequence(t1_2, t2_2);
    cout << "Test 2 Passed: LCS(\"" << t1_2 << "\", \"" << t2_2 << "\") = " << ans2 << " (Expected: 4)\n";
    assert(ans2 == 4);

    // Test Case 3: Complete mismatch
    string t1_3 = "abcd", t2_3 = "efgh";
    int ans3 = solver.longestCommonSubsequence(t1_3, t2_3);
    cout << "Test 3 Passed: LCS(\"" << t1_3 << "\", \"" << t2_3 << "\") = " << ans3 << " (Expected: 0)\n";
    assert(ans3 == 0);

    // Test Case 4: One string is empty
    string t1_4 = "", t2_4 = "abc";
    int ans4 = solver.longestCommonSubsequence(t1_4, t2_4);
    cout << "Test 4 Passed: LCS(\"" << t1_4 << "\", \"" << t2_4 << "\") = " << ans4 << " (Expected: 0)\n";
    assert(ans4 == 0);

    // Test Case 5: Out of order interleaving
    string t1_5 = "abcde", t2_5 = "ace";
    int ans5 = solver.longestCommonSubsequence(t1_5, t2_5);
    cout << "Test 5 Passed: LCS(\"" << t1_5 << "\", \"" << t2_5 << "\") = " << ans5 << " (Expected: 3)\n";
    assert(ans5 == 3);

    cout << "\n All validation assertions passed successfully!\n";
    return 0;
}

