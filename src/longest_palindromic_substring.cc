/*
Longest Palindromic Substring

Given a string s, return the longest substring of s that is a palindrome.

A palindrome is a string that reads the same forward and backward.

If there are multiple palindromic substrings that have the same length, return any one of them.

Example 1: Input: s = "ababd"       Output: "bab"
Explanation: Both "aba" and "bab" are valid answers.

Example 2: Input: s = "abbc"        Output: "bb"

Constraints:
    1 <= s.length <= 1000
    s contains only digits and English letters.
*/

/**************************************************************************************
1. Brutal Force
   for each pair (i,j)      // i = 0, 1, ..., n-1, j=i, i+1, ..., n-1
      if s[i:j] is a palindrome
        update the result

    Complexity: O(N^3)

2. 2D dynamic Programming
   Let DP(i,j) = true if s[i:j] is a palindrome; false otherwise. // i = 0, 1, ..., n-1, j=i, i+1, ..., n-1
        DP(i,i)     = true              // length=1, 0 <= i < n
        DP(i,i+1)   = s[i]==s[i+1]      // length=2, 0 <= i < n - 1
        DP(i, j)    = s[i]==s[j] && DP(i+1,j-1)    // length>2, 0<=i<n-2, i + 2 <= j  < n - 1
   Complexity: O(N^2)

3. Two pointers
   Any string has 2*N-1 centers, where N is the length of the string.
   Start from any center, expand to both side until the substring is not a palindrome.

4. Manacher's Algorith:

*/
        

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>

using namespace std;


/* 1. Brutal Force */
class Solution1 {
public:
    string longestPalindrome(string s) {
        string res = "";
        int resLen = 0;

        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                int l = i, r = j;
                while (l < r && s[l] == s[r]) {
                    l++;
                    r--;
                }
                if (l >= r && resLen < (j - i + 1)) {
                    res = s.substr(i, j - i + 1);
                    resLen = j - i + 1;
                }
            }
        }

        return res;
    }
};

/* 2. DP matrix (along diagnals pushing up-right) */
class Solution2 {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n <= 1) return s;

        // 2D DP Table initialized to false
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        int maxLength = 1;
        int start = 0;

        // Compute DP along the diagnals
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1; // Ending index
                if (s[i] == s[j]) {
                    if (len < 3 || dp[i + 1][j - 1]) {
                        dp[i][j] = true;
                        maxLength = len;
                        start = i;
                    }
                }
            }
        }

        // Return the longest palindromic substring found
        return s.substr(start, maxLength);
    }
};

/* 3. DP matrix (row by row from the bottom to the top) */

class Solution3 {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n <= 1) return s;

        // Allocate the 2D DP table initialized to false
        vector<vector<bool>> DP(n, vector<bool>(n, false));

        int maxLength = 1;
        int start = 0;

        // Your row-backward loop evaluation order
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                
                if (i == j) {
                    // Case 1: Length == 1
                    DP[i][j] = true;
                } 
                else if (j == i + 1) {
                    // Case 2: Length == 2
                    DP[i][j] = (s[i] == s[j]);
                } 
                else {
                    // Case 3: Length >= 3
                    DP[i][j] = (s[i] == s[j] && DP[i + 1][j - 1]);
                }
                
                // Track your longest palindrome slice here if DP[i][j] is true
                // CRITICAL: Explicit check is required here because 'len' is not monotonically increasing!
                if (DP[i][j]) {
                    int currentLength = j - i + 1;
                    if (currentLength > maxLength) {
                        maxLength = currentLength;
                        start = i;
                    }
                }
            }
        }

        return s.substr(start, maxLength);
    }
};

/*
Expanding around every center of the string
*/

class Solution4 {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int start = 0;
        int maxLength = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            // Case 1: Odd-length palindromes (e.g., "aba", center is 'b')
            int len1 = expandAroundCenter(s, i, i);
            
            // Case 2: Even-length palindromes (e.g., "abba", center is between 'b' and 'b')
            int len2 = expandAroundCenter(s, i, i + 1);
            
            // Track the maximum length found so far
            int currentMax = max(len1, len2);
            if (currentMax > maxLength) {
                maxLength = currentMax;
                // Calculate starting index of this palindrome substring
                start = i - (currentMax - 1) / 2;
            }
        }
        
        return s.substr(start, maxLength);
    }

private:
    // Helper function to expand outward from a given center
    int expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            --left;
            ++right;
        }
        // Returns the length of the valid palindrome found
        return right - left - 1;
    }
};

class Solution5 {
public:
    std::string longestPalindrome(std::string s) {
        if (s.empty()) return "";

        // 1. Transform the string to handle even-length palindromes uniformally
        // e.g., "aba" -> "^#a#b#a#$"
        std::string t = "^";
        for (char c : s) {
            t += "#" + std::string(1, c);
        }
        t += "#$";

        int n = t.length();
        std::vector<int> P(n, 0); // Array to store palindrome radii
        int C = 0; // Center of the current furthest-reaching palindrome
        int R = 0; // Right boundary of the current furthest-reaching palindrome

        int max_len = 0;
        int center_index = 0;

        // 2. Process the transformed string
        for (int i = 1; i < n - 1; i++) {
            int i_mirror = 2 * C - i; // Mirror of i relative to center C

            // Mirroring optimization
            if (R > i) {
                P[i] = std::min(R - i, P[i_mirror]);
            } else {
                P[i] = 0;
            }

            // Attempt to expand the palindrome centered at i
            while (t[i + 1 + P[i]] == t[i - 1 - P[i]]) {
                P[i]++;
            }

            // Update center and right boundary if the palindrome expands past R
            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }

            // Track the globally longest palindrome found
            if (P[i] > max_len) {
                max_len = P[i];
                center_index = i;
            }
        }

        // 3. Map back to the original string indices
        int start = (center_index - 1 - max_len) / 2;
        return s.substr(start, max_len);
    }
};


template <class Solution>
void test ()
{
    Solution solver;
    cout << "Solver - " << typeid(Solution).name() << endl;

    // Define test cases (Input string, Expected valid length/answer)
    vector<pair<string, string>> testCases = {
        {"ababd", "bab"},       // Example 1 ("aba" is also valid)
        {"abbc", "bb"},         // Example 2
        {"racecar", "racecar"}, // Entire string is a palindrome
        {"a", "a"},             // Single character edge case
        {"ac", "a"},            // Two distinct characters
        {"cbbd", "bb"}          // Even length palindrome case
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        string s = testCases[i].first;
        string expected = testCases[i].second;
        string result = solver.longestPalindrome(s);

        // Palindromes can match by length if there are multiple correct options
        bool isCorrect = (result.length() == expected.length());

        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "  Input String : \"" << s << "\"" << endl;
        cout << "  Result       : \"" << result << "\"" << endl;
        cout << "  Status       : " << (isCorrect ? "✅ PASS" : "❌ FAIL") << endl;
        cout << "--------------------------------------------------" << endl;
    }
    cout << endl;
}

int main() {
    test<Solution1>();
    test<Solution2>();
    test<Solution3>();
    test<Solution4>();
    test<Solution5>();
    return 0;
}

