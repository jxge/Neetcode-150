/*
Regular Expression Matching

You are given an input string s consisting of lowercase english letters, and a
pattern p consisting of lowercase english letters, as well as '.', and '*'
characters.

Return true if the pattern matches the entire input string, otherwise return false.

    '.' Matches any single character
    '*' Matches zero or more of the preceding element.

Example 1:
Input: s = "aa", p = ".b"
Output: false
Explanation: Regardless of which character we choose for the '.' in the
pattern, we cannot match the second character in the input string.

Example 2:
Input: s = "nnn", p = "n*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'n'. We choose 'n' to repeat three times.

Example 3:
Input: s = "xyz", p = ".*z"
Output: true
Explanation: The pattern ".*" means zero or more of any character, so we choose
".." to match "xy" and "z" to match "z".

Constraints:
    1 <= s.length <= 20
    1 <= p.length <= 20
    Each appearance of '*', will be preceded by a valid character or '.'.
*/

/*
Solution 1: Recursive
  Let dp(i,j) be true if s[i...M-1] matches p[j...N-1] , where M=s.length() and N=p.length()


  Case 1: when p[j+1]='*'
    dp(i,j) = dp(i,j+2) or first_match && dp(i+1,j)
  Case 2: when p[j+1] != '*'
    dp(i,j) = first_match && dp(i+1,j+1) 

  where first_match = (i < M && s[i] == p[j] || p[j]=='.'

  Base cases:
    (1) j == N (pattern is fully exhausted)
        dp[i][N] = (i == M)
    (2) i == M (string is fully exhausted, but pattern is not)
        The matching will still sucessfuly if the remaining part the the pattern is 
        a oncatenation of 'c*'.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <typeinfo>

using namespace std;

class Solution1 {
private:
    // bp[i][j] stores: -1 for unvisited, 0 for false, 1 for true
    vector<vector<int>> bp;

    bool solve(int i, int j, const string& s, const string& p) {
        // Base Case 1: If pattern is completely consumed, string must also be fully consumed
        if (j == p.length()) {
            return i == s.length();
        }

        // Return bpized result if already calculated
        if (bp[i][j] != -1) {
            return bp[i][j];
        }

        // Check if the current characters match (handling the '.' wildcard safely)
        bool first_match = (i < s.length() && (p[j] == s[i] || p[j] == '.'));

        bool ans = false;

        // Lookahead Case: If the next character in the pattern is '*'
        if (j + 1 < p.length() && p[j + 1] == '*') {
            // Choice 1: Skip the '*' group (0 occurrences)
            // Choice 2: Consume current character from s and keep '*' active (1+ occurrences)
            ans = solve(i, j + 2, s, p) || (first_match && solve(i + 1, j, s, p));
        } else {
            // Standard Case: No '*' ahead, characters must match and we advance both
            ans = first_match && solve(i + 1, j + 1, s, p);
        }

        return bp[i][j] = ans;
    }

public:
    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        
        // Size matrix to (n + 1) x (m + 1) to safely accommodate the empty suffix configurations
        bp.assign(n + 1, vector<int>(m + 1, -1));
        
        return solve(0, 0, s, p);
    }
};

class Solution2 {
public:
    bool isMatch(string s, string p) {
        int s_len = s.length();
        int p_len = p.length();
        
        // dp[j] represents whether s[i...] matches p[j...]
        vector<bool> dp(p_len + 1, false);
        
        // Base Case: Both s and p are empty suffixes
        dp[p_len] = true;
        
        // Base Case Initialization: Populate matching combinations for an empty string 's'
        // An empty 's' can only match patterns like "a*", "a*b*", etc.
        for (int j = p_len - 2; j >= 0; j--) {
            if (p[j + 1] == '*') {
                dp[j] = dp[j + 2];
            }
        }
        
        // Iterate backwards through the string s
        for (int i = s_len - 1; i >= 0; i--) {
            // Track the diagonal state value dp[i+1][j+1] using a trailing variable
            // Before starting the inner loop, the element at dp[p_len] corresponds to (i+1, p_len)
            bool next_row_next_col = dp[p_len]; 
            
            // For an empty pattern suffix matching a non-empty string suffix, it's always false
            dp[p_len] = false; 
            
            // Iterate backwards through the pattern p
            for (int j = p_len - 1; j >= 0; j--) {
                // Temporarily save the value representing dp[i+1][j] before overwriting it
                bool temp = dp[j];
                
                bool first_match = (p[j] == s[i] || p[j] == '.');
                
                if (j + 1 < p_len && p[j + 1] == '*') {
                    // dp[j+2] represents matching 0 occurrences (current row, column j+2)
                    // (first_match && dp[j]) represents matching 1+ occurrences 
                    // Note: dp[j] here still holds the value from the previous loop iteration (i+1, j)
                    dp[j] = dp[j + 2] || (first_match && dp[j]);
                } else {
                    // Standard matching: characters must align and next suffixes must align
                    // next_row_next_col represents dp[i+1][j+1]
                    dp[j] = first_match && next_row_next_col;
                }
                
                // Rotate the preserved old cell value to serve as the diagonal state for the next step (j-1)
                next_row_next_col = temp;
            }
        }
        
        return dp[0];
    }
};


template<typename Solution>
int test()
{
    Solution solver;

    cout << endl;

    // Test Case 1: Example 1 from problem description
    string s1 = "aa", p1 = ".b";
    bool res1 = solver.isMatch(s1, p1);
    cout << "Test 1 Passed -> Input: s=\"" << s1 << "\", p=\"" << p1 << "\" | Output: " << boolalpha << res1 << endl;
    assert(res1 == false);

    // Test Case 2: Example 2 from problem description
    string s2 = "nnn", p2 = "n*";
    bool res2 = solver.isMatch(s2, p2);
    cout << "Test 2 Passed -> Input: s=\"" << s2 << "\", p=\"" << p2 << "\" | Output: " << boolalpha << res2 << endl;
    assert(res2 == true);

    // Test Case 3: Example 3 from problem description
    string s3 = "xyz", p3 = ".*z";
    bool res3 = solver.isMatch(s3, p3);
    cout << "Test 3 Passed -> Input: s=\"" << s3 << "\", p=\"" << p3 << "\" | Output: " << boolalpha << res3 << endl;
    assert(res3 == true);

    // Test Case 4: Skipping mismatching character with *
    string s4 = "aab", p4 = "c*a*b";
    bool res4 = solver.isMatch(s4, p4);
    cout << "Test 4 Passed -> Input: s=\"" << s4 << "\", p=\"" << p4 << "\" | Output: " << boolalpha << res4 << endl;
    assert(res4 == true); // c* is skipped as 0 occurrences

    // Test Case 5: Complex wildcards matching completely empty string configurations
    string s5 = "", p5 = "a*b*.*";
    bool res5 = solver.isMatch(s5, p5);
    cout << "Test 5 Passed -> Input: s=\"" << s5 << "\", p=\"" << p5 << "\" | Output: " << boolalpha << res5 << endl;
    assert(res5 == true);

    cout << "All Regular Expression matching top-down tests passed successfully with " << typeid(Solution).name() <<endl;
    return 0;
}

int main() 
{
    test<Solution1>();
    test<Solution2>();
    return 0;
}
