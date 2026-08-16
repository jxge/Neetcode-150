/*
Palindromic Substrings

Given a string s, return the number of substrings within s that are palindromes.

A palindrome is a string that reads the same forward and backward.

Example 1:

Input: s = "abc"
Output: 3
Explanation: "a", "b", "c".

Example 2:
Input: s = "aaa"
Output: 6
Explanation: "a", "a", "a", "aa", "aa", "aaa". Note that different substrings are counted as different palindromes even if the string contents are the same.

Constraints:
    1 <= s.length <= 1000
    s consists of lowercase English letters.
*/

/*
Solution 1: Brute Force - O(n^3)
    for (int i = 0; i < s.size(); i++) 
        for (int j = i; j < s.size(); j++) 
            check s[i...j] is palindromic

Solution 2: DP  - O(n^2)
  Let dp(i,j) be true if s[i...j] is palindromic
      dp(i,j) = true                        if i >= j
      dp(i,j) = s[i]==s[j] && dp(i+1,j-1)   if i <  j

Solution 3: Two pointers
  starting from index i count how many j  s[i-j]==s[i+j] and
                           how many j  s[i-j]==s[i+1j]
Solution 4: Manacher's Algorithm
  1. Normalize the string by inserting "#" between characters: "abba" -> #a#b#b#a#"
  2. Reuse information using a "current best palindromes window"
     (a) Matian a palindrome window [l,r] - the farthest-reaching palindrome found so far.
     (b) For a new position i inside [l,r], find the mirror
         mirror = l + (r - i).
     (c) the palindrome radius at i can be at least the smaller of:
         - how much space remains inside the window (r-i)
         - the palindrome radius at mirror (p[mirror])
*/

#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;

class Solution1 {
public:
    int countSubstrings(string s) {
        int res = 0;

        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                int l = i, r = j;
                while (l < r && s[l] == s[r]) {
                    l++;
                    r--;
                }
                res += (l >= r);
            }
        }

        return res;
    }
};

class Solution2 {
public:
    int countSubstrings(string s) {
        int n = s.length();
        int count = 0;
        
        // dp[i][j] will be 1 (true) if s[i...j] is a palindrome, else 0 (false)
        // Vector is used for safe dynamic sizing up to 1000
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Loop backwards for i, and forwards for j
        // This ensures dp[i+1][j-1] is always computed before dp[i][j]
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                
                // Base case: if length is 1 (i==j) or length is 2 and characters match
                if (i >= j - 1) {
                    dp[i][j] = (s[i] == s[j]);
                } 
                // General case: outer characters match and inner substring is a palindrome
                else {
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
                }
                
                // If it's a valid palindrome, increment total count
                if (dp[i][j]) {
                    count++;
                }
            }
        }
        
        return count;
    }
};

class Solution3 {
public:
    int countSubstrings(string s) {
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            res += countPali(s, i, i);
            res += countPali(s, i, i + 1);
        }
        return res;
    }

private:
    int countPali(string s, int l, int r) {
        int res = 0;
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            res++;
            l--;
            r++;
        }
        return res;
    }
};

class Solution4 {
public:
    vector<int> manacher(string& s) {
        if (!s.size()) return {};
        string t = "#" + string(1, s[0]);
        for (int i = 1; i < s.size(); ++i)
            t += "#" + string(1, s[i]);
        t += "#";
        int n = t.size();
        vector<int> p(n, 0);
        int l = 0, r = 0;
        for (int i = 0; i < n; i++) {
            p[i] = (i < r) ? min(r - i, p[l + (r - i)]) : 0;
            while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 &&
                   t[i + p[i] + 1] == t[i - p[i] - 1])
                p[i]++;
            if (i + p[i] > r)
                l = i - p[i], r = i + p[i];
        }
        return p;
    }

    int countSubstrings(string s) {
        vector<int> p = manacher(s);
        int res = 0;
        for (int i : p) {
            res += (i + 1) / 2;
        }
        return res;
    }
};

// Struct to store test cases
struct TestCase {
    string input;
    int expectedOutput;
};

template<typename Solution>
int test() {
    Solution solver;
    
    cout << "#### Testing " << typeid(solver).name() << endl;

    // Define a robust suite of test cases
    vector<TestCase> testCases = {
        {"abc", 3},       // Example 1: Distinct characters ("a", "b", "c")
        {"aaa", 6},       // Example 2: Repeating characters ("a", "a", "a", "aa", "aa", "aaa")
        {"a", 1},         // Single character
        {"abccba", 9},    // Perfect even palindrome ("a", "b", "c", "c", "b", "a", "cc", "bccb", "abccba")
        {"aba", 4},       // Perfect odd palindrome ("a", "b", "a", "aba")
        {"racecar", 10},  // Complex nested palindrome
        {"", 0}           // Edge case: Empty string
    };

    bool allPassed = true;
    cout << "--- Starting Self-Checking Tests ---\n" << endl;

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& test = testCases[i];
        int actualOutput = solver.countSubstrings(test.input);
        
        cout << "Test Case " << i + 1 << ": Input = \"" << test.input << "\"" << endl;
        cout << "  Expected: " << test.expectedOutput << ";\t";
        cout << "  Actual:   " << actualOutput << ";\t";

        if (actualOutput == test.expectedOutput) {
            cout << "  Result:   [PASSED] ✅" << endl;
        } else {
            cout << "  Result:   [FAILED] ❌" << endl;
            allPassed = false;
        }
        cout << "------------------------------------" << endl;
    }

    // Final summary
    if (allPassed) {
        cout << "\nAll test cases passed successfully! 🎉" << endl;
    } else {
        cout << "\nSome test cases failed. Please review the output above. ⚠️" << endl;
    }

    return allPassed ? 0 : 1;
}

int main() {
    test<Solution1>();
    test<Solution2>();
    test<Solution3>();
    test<Solution4>();
}
