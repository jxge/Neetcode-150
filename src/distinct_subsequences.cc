/*
Distinct Subsequences

You are given two strings s and t, both consisting of english letters.
Return the number of distinct subsequences of s which are equal to t.

Example 1:
Input: s = "caaat", t = "cat"
Output: 3
Explanation: There are 3 ways you can generate "cat" from s.
    (c)aa(at)
    (c)a(a)a(t)
    (ca)aa(t)

Example 2:
Input: s = "xxyxy", t = "xy"
Output: 5
Explanation: There are 5 ways you can generate "xy" from s.
    (x)x(y)xy
    (x)xyx(y)
    x(x)(y)xy
    x(x)yx(y)
    xxy(x)(y)
Constraints:
    1 <= s.length, t.length <= 1000
    s and t consist of English letters.
*/

/*
Solution 1: Bottom-up DP (prefix, left-to-right)

  Let dp[i][j] be the number of distinct subsequences of the 
  prefix s[0...i-1] which equal the prefix t[0...j-1].
    dp(i,0) = 1     // prefix of t is empty
    dp(0,j) = 0     // prefix of s is empty
    dp(i,j) = dp(i-1,j) + dp(i-1,j-1)    if s[i-1]==t[j-1]
    dp(i,j) = dp(i-1,j)                  if s[i-1]!=t[j-1]

    final answer = dp(M,N)  where M=s1.size() and N=t.size()

Solution 2: Bottom-up DP (suffix, left-to-right)
  Let dp[i][j] be the number of distinct subsequences of the 
  suffix s[i...M-1] which equal the suffix t[j...N-1].
    dp(i,N) = 1     // suffix of t is empty
    dp(M,j) = 0     // suffix of s is empty
    dp(i,j) = dp(i+1,j) + dp(i+1,j+1)    if s[i]==t[j]
    dp(i,j) = dp(i+1,j)                  if s[i]!=t[j]

Solution 3: Space optimized 1D Bottom-up DP
*/

#include <vector>
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

class Solution1 {
private:
    vector<vector<int>> memo;

    // return the number of unique subsequences in s[i...M-1] that
    // match t[j..N-1]
    //
    int solve(int i, int j, const string& s, const string& t) {
        // Base case: If we successfully matched all characters of t
        if (j == t.length()) {
            return 1;
        }
        // Base case: If s is exhausted but t still has remaining characters
        if (i == s.length()) {
            return 0;
        }

        // If the state has already been calculated, return it
        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        // Option 1: We can always skip the current character of s
        long long ways = solve(i + 1, j, s, t);

        // Option 2: If characters match, we can choose to use the character of s
        if (s[i] == t[j]) {
            ways += solve(i + 1, j + 1, s, t);
        }

        // Store the result in the memoization table and return
        return memo[i][j] = ways;
    }

public:
    int numDistinct(string s, string t) {
        int n = s.length();
        int m = t.length();
        
        // Initialize memo table with -1
        memo.assign(n, vector<int>(m, -1));
        
        return solve(0, 0, s, t);
    }
};

class Solution2 {
public:
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // If s is shorter than t, it's impossible to form t
        if (m < n) return 0;

        // dp[j] stores the number of distinct subsequences of s that form t[0...j-1]
        // Using unsigned long long to elegantly prevent integer overflow
        vector<unsigned long long> dp(n + 1, 0);
        
        // Base case: an empty target string 't' can always be formed in 1 way
        dp[0] = 1;

        // Iterate through each character of s
        for (int i = 1; i <= m; i++) {
            // Traverse t backwards to avoid overwriting values from the current row
            for (int j = n; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return dp[n];
    }
};


template<class Solution>
int test() {
    Solution solver;

    // Test Case 1: Example from problem description
    string s1 = "caaat";
    string t1 = "cat";
    int result1 = solver.numDistinct(s1, t1);
    cout << "Test 1 -> Input: s = \"" << s1 << "\", t = \"" << t1 << "\" | Output: " << result1 << endl;
    assert(result1 == 3);

    // Test Case 2: Example from problem description
    string s2 = "xxyxy";
    string t2 = "xy";
    int result2 = solver.numDistinct(s2, t2);
    cout << "Test 2 -> Input: s = \"" << s2 << "\", t = \"" << t2 << "\" | Output: " << result2 << endl;
    assert(result2 == 5);

    // Test Case 3: No matching subsequences
    string s3 = "abc";
    string t3 = "de";
    int result3 = solver.numDistinct(s3, t3);
    cout << "Test 3 -> Input: s = \"" << s3 << "\", t = \"" << t3 << "\" | Output: " << result3 << endl;
    assert(result3 == 0);

    // Test Case 4: Target string is longer than source string
    string s4 = "cat";
    string t4 = "cats";
    int result4 = solver.numDistinct(s4, t4);
    cout << "Test 4 -> Input: s = \"" << s4 << "\", t = \"" << t4 << "\" | Output: " << result4 << endl;
    assert(result4 == 0);

    // Test Case 5: Exact identical matches
    string s5 = "same";
    string t5 = "same";
    int result5 = solver.numDistinct(s5, t5);
    cout << "Test 5 -> Input: s = \"" << s5 << "\", t = \"" << t5 << "\" | Output: " << result5 << endl;
    assert(result5 == 1);

    cout << "\n All self-checking tests passed successfully!" << endl;
    return 0;
}

int main() {
    test<Solution1>();
    test<Solution2>();
    return 0;
}

