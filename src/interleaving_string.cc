/*
Interleaving String

You are given three strings s1, s2, and s3. Return true if s3 is formed by
interleaving s1 and s2 together or false otherwise.

Interleaving two strings s and t is done by dividing s and t into n and m
substrings respectively, where the following conditions are met

    |n - m| <= 1, i.e. the difference between the number of substrings of s and t is at most 1.
    s = s1 + s2 + ... + sn
    t = t1 + t2 + ... + tm
    Interleaving s and t is s1 + t1 + s2 + t2 + ... or t1 + s1 + t2 + s2 + ...

You may assume that s1, s2 and s3 consist of lowercase English letters.

Example 1:
Input: s1 = "aaaa", s2 = "bbbb", s3 = "aabbbbaa"
Output: true
Explanation: We can split s1 into ["aa", "aa"], s2 can remain as "bbbb" and s3
is formed by interleaving ["aa", "aa"] and "bbbb".

Example 2:
Input: s1 = "", s2 = "", s3 = ""
Output: true
Example 3:

Input: s1 = "abc", s2 = "xyz", s3 = "abxzcy"
Output: false

Explanation: We can't split s3 into ["ab", "xz", "cy"] as the order of characters is not maintained.

Constraints:
    0 <= s1.length, s2.length <= 100
    0 <= s3.length <= 200
*/

/*
Solution 1: Top-down BP with memoization
    Let bp(i,j) be true if s1[0...i-1] and s2[0...j-1] for form t[0...i+j-1] by interleaving.

    bp(0,0) = true
    bp(i,j) = i>0 && bp(i-1,j) && s1[i-1]==t[i+j-1] || 
              j>0 && bp(i,j-1) && s2[j-1]==t[i+j-1] 

    answer = bp(m,n)

Solution 2: Bottom-up with 2D DP array
Solution 3: Bottom-up with Space optimized DP array
*/

#include <string>
#include <vector>

// Top-down DP with memoization
class Solution1 {
private:
    // Memoization table: -1 = unvisited, 0 = false, 1 = true
    std::vector<std::vector<int>> memo;

    bool dfs(const std::string& s1, int i, const std::string& s2, int j, const std::string& s3) {
        // Base case: dp(0,0) = true (reached the beginning of both strings successfully)
        if (i == 0 && j == 0) {
            return true;
        }

        // Return cached result if already calculated
        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        bool match_s1 = false;
        bool match_s2 = false;

        // Branch 1: i > 0 && bp(i-1, j) && s1[i-1] == s3[i+j-1]
        if (i > 0 && s1[i - 1] == s3[i + j - 1]) {
            match_s1 = dfs(s1, i - 1, s2, j, s3);
        }

        // Branch 2: j > 0 && bp(i, j-1) && s2[j-1] == s3[i+j-1]
        if (j > 0 && s2[j - 1] == s3[i + j - 1]) {
            match_s2 = dfs(s1, i, s2, j - 1, s3);
        }

        // Combine using logical OR, cache it, and return
        return memo[i][j] = (match_s1 || match_s2);
    }

public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {
        int n = s1.length();
        int m = s2.length();

        // Quick length optimization check
        if (n + m != s3.length()) {
            return false;
        }

        // Size the memo table to fit indices from 0 up to n and m
        memo.assign(n + 1, std::vector<int>(m + 1, -1));

        // Start top-down traversal from the end of the prefixes
        return dfs(s1, n, s2, m, s3);
    }
};

// Bottom-up DP with 2D array
class Solution2 {
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {
        int n = s1.length();
        int m = s2.length();

        // Quick length check: s3 must be exactly the combined length of s1 and s2
        if (n + m != s3.length()) {
            return false;
        }

        // dp[i][j] represents your bp(i, j) state
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));

        // Base case: bp(0,0) = true
        dp[0][0] = true;

        // Iterative bottom-up calculation
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                // Skip the base case cell since it's already set
                if (i == 0 && j == 0) {
                    continue;
                }

                // Implementing your exact compact formula:
                // bp(i,j) = (i > 0 && bp(i-1,j) && s1[i-1] == t[i+j-1]) || 
                //           (j > 0 && bp(i,j-1) && s2[j-1] == t[i+j-1])
                bool match_s1 = (i > 0) && dp[i - 1][j] && (s1[i - 1] == s3[i + j - 1]);
                bool match_s2 = (j > 0) && dp[i][j - 1] && (s2[j - 1] == s3[i + j - 1]);

                dp[i][j] = match_s1 || match_s2;
            }
        }

        // Return the final state bp(n, m)
        return dp[n][m];
    }
};

// Bottom-up DP with optimized 1D array
class Solution3 {
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {
        int n = s1.length(), m = s2.length();
        if (n + m != s3.length()) return false;

        // Space optimized: Only keep track of one row at a time
        std::vector<bool> dp(m + 1, false);
        dp[0] = true; // Base case: bp(0,0) = true

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (i == 0 && j == 0) continue;

                // dp[j] currently holds the value from the previous row: bp(i-1, j)
                // dp[j-1] holds the value from the current row's left cell: bp(i, j-1)
                bool match_s1 = (i > 0) && dp[j] && (s1[i - 1] == s3[i + j - 1]);
                bool match_s2 = (j > 0) && dp[j - 1] && (s2[j - 1] == s3[i + j - 1]);

                dp[j] = match_s1 || match_s2;
            }
        }
        return dp[m];
    }
};

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class Solution {
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {
        int n = s1.length();
        int m = s2.length();
        
        // Quick structural length check
        if (n + m != s3.length()) {
            return false;
        }

        // Space optimized 1D DP row layout
        std::vector<bool> dp(m + 1, false);
        
        // Base case: bp(0,0) = true
        dp[0] = true; 

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }

                // Apply the guarded structural logic from your formula
                bool match_s1 = (i > 0) && dp[j] && (s1[i - 1] == s3[i + j - 1]);
                bool match_s2 = (j > 0) && dp[j - 1] && (s2[j - 1] == s3[i + j - 1]);

                dp[j] = match_s1 || match_s2;
            }
        }
        return dp[m];
    }
};

// Test structure definition for automated validation
struct TestCase {
    std::string s1;
    std::string s2;
    std::string s3;
    bool expected;
    std::string description;
};

#include <typeinfo>

template<class Solution>
void test()
{
    Solution solver;

    // Comprehensive evaluation test suite
    std::vector<TestCase> testSuite = {
        { "aaaa", "bbbb", "aabbbbaa", true, "Standard alternating interleaving" },
        { "", "", "", true, "All strings completely empty (Base Case)" },
        { "a", "", "a", true, "One source string is completely empty" },
        { "abc", "xyz", "abxzcy", false, "Character order preservation failure" },
        { "aabcc", "dbbca", "aadbbcbcac", true, "LeetCode standard matching puzzle" },
        { "aabcc", "dbbca", "aadbbbaccc", false, "Valid characters but invalid sequence" },
        { "abc", "def", "abcdefg", false, "Length mismatch optimization boundary" }
    };

    std::cout << "========================================================\n";
    std::cout << " Running Interleaving String Verification Suite by " << typeid(solver).name() << std::endl;
    std::cout << "========================================================\n";

    int passedCount = 0;

    for (size_t i = 0; i < testSuite.size(); ++i) {
        const auto& tc = testSuite[i];
        bool result = solver.isInterleave(tc.s1, tc.s2, tc.s3);

        std::cout << "[Test " << i + 1 << "] " << tc.description << "\n";
        std::cout << "  Inputs: s1=\"" << tc.s1 << "\", s2=\"" << tc.s2 << "\", s3=\"" << tc.s3 << "\"\n";
        std::cout << "  Expected: " << (tc.expected ? "true" : "false") 
                  << " | Got: " << (result ? "true" : "false") << "\n";

        if (result == tc.expected) {
            std::cout << "  Status:   PASS \n\n";
            passedCount++;
        } else {
            std::cout << "  Status:   FAIL ❌\n\n";
        }
    }

    std::cout << "========================================================\n";
    std::cout << "Result: " << passedCount << " / " << testSuite.size() << " Tests Passed.\n";
    std::cout << "========================================================\n";

    // Hard assert to flag failures immediately during builds
    assert(passedCount == testSuite.size());
}

int main()
{
    test<Solution1>();
    test<Solution2>();
    test<Solution3>();
    return 0;
}
