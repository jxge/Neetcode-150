/*
Decode Ways

A string consisting of uppercase english characters can be encoded to a number using the following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"

To decode a message, digits must be grouped and then mapped back into letters
using the reverse of the mapping above. There may be multiple ways to decode a
message. For example, "1012" can be mapped into:

    "JAB" with the grouping (10 1 2)
    "JL" with the grouping (10 12)

The grouping (1 01 2) is invalid because 01 cannot be mapped into a letter
since it contains a leading zero.

Given a string s containing only digits, return the number of ways to decode
it. You can assume that the answer fits in a 32-bit integer.

Example 1:
Input: s = "12"
Output: 2
Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).

Example 2:
Input: s = "01"
Output: 0
Explanation: "01" cannot be decoded because "01" cannot be mapped into a letter.

Constraints:
    1 <= s.length <= 100
    s consists of digits
*/

/* Solution: Prefix based DP (bottom up, left to right)

Let dp[i] be the number of ways to decode the prefix s[0...i].

dp(0) = 1
dp(1) = (s[0]==0) ? 0 : 1

for k = 1 to n-1 do
    dp(i) = validSignle(s[i]) * dp(i-1) + validDouble(s[i-1...i] * dp(i-2)

finalAnswer = dp(n-1)

validSingle(s[i]) = s[i] != 0 ? 1 : 0;
validDouble(s[i-1:i]) = (9 < stoi(s[i-1:i]) < 27) ? 1 : 0;

Solution 2: Suffix based DP (top-down, right-to-left)
Let dp[i] be the number of ways to decode the suffix s[i...n-1].

    dp(n)= 1                                // an empty string 
    dp(n-1) = validSingle(s[n-1]) ? 1 : 0   // single character suffix
    dp(i) = validSingle(s[i]) * dp(i+1) + validDouble(s[i...i+1]) * dp(i+2)  (i = n-2, n-3, ..., 0)
    Final answer = dp(0)
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <typeinfo>

using namespace std;

int validSingle(char c) {
    return (c != '0') ? 1 : 0;
}

// Returns 1 if the two characters form a valid letter mapping between 10 and 26
int validDouble(char c1, char c2) {
    int value = (c1 - '0') * 10 + (c2 - '0');
    return (value >= 10 && value <= 26) ? 1 : 0;
}

class Solution1 {
public:
    int numDecodings(string s) {
        // Empty string or leading zero cannot be decoded
        if (s.empty() || s[0] == '0') {
            return 0;
        }
        
        int n = s.length();
        int prev2 = 1; // Tracks dp[i-2]
        int prev1 = 1; // Tracks dp[i-1]
        
        for (int i = 1; i < n; ++i) {
            int current = 0;
            
            // Single-digit valid check
            if (s[i] != '0') {
                current += prev1;
            }
            
            // Two-digit valid check
            int twoDigit = stoi(s.substr(i - 1, 2));
            if (twoDigit >= 10 && twoDigit <= 26) {
                current += prev2;
            }
            
            // Update state variables for the next iteration
            prev2 = prev1;
            prev1 = current;
            
            // If no decodings are possible, terminate early
            if (prev1 == 0) {
                return 0;
            }
        }
        
        return prev1;
    }
};

class Solution2 {
public:
    int numDecodings(string s) {
        if (s.empty()) return 0;
        
        int n = s.length();
        // dp[i] stores the number of ways to decode the suffix s[i...n-1]
        vector<int> dp(n + 1, 0);
        
        // Base cases
        dp[n] = 1; 
        dp[n - 1] = validSingle(s[n - 1]);
        
        // Build the DP table from right to left (n-2 down to 0)
        for (int i = n - 2; i >= 0; --i) {
            // A suffix starting with '0' cannot be decoded at all
            if (s[i] == '0') {
                dp[i] = 0;
                continue;
            }
            
            // Apply the formulation:
            // dp[i] = validSingle(s[i]) * dp[i+1] + validDouble(s[i...i+1]) * dp[i+2]
            dp[i] = dp[i + 1] + validDouble(s[i], s[i + 1]) * dp[i + 2];
        }
        
        // Final answer is the number of ways to decode the suffix starting at index 0
        return dp[0];
    }
};


// Driver function to test the implementation
template<class Solution>
int test() {
    Solution solver;
    
    // Struct to hold test inputs and expected outputs
    struct TestCase {
        string input;
        int expected;
        string description;
    };
    
    vector<TestCase> testCases = {
        {"12", 2, "Standard case (1 2 -> AB, 12 -> L)"},
        {"226", 3, "Multiple combinations (2 2 6 -> BBF, 22 6 -> VF, 2 26 -> BZ)"},
        {"06", 0, "Leading zero (Invalid)"},
        {"10", 1, "Valid zero combination (10 -> J)"},
        {"2101", 1, "Zero inside string (2 10 1 -> BJA)"},
        {"30", 0, "Invalid zero combination (> 26)"},
        {"1", 1, "Single valid character"},
        {"27", 1, "Out of bounds two-digit pair (2 7 -> BG)"}
    };
    
    cout << "--- Running Decode Ways Tests: " << typeid(solver).name() << endl << endl;
    
    int passed = 0;
    for (const auto& tc : testCases) {
        int result = solver.numDecodings(tc.input);
        
        cout << "Input:       \"" << tc.input << "\"" << endl;
        cout << "Description: " << tc.description << endl;
        cout << "Expected:    " << tc.expected << endl;
        cout << "Result:      " << result << endl;
        
        if (result == tc.expected) {
            cout << "Status:      [SUCCESS]" << endl;
            passed++;
        } else {
            cout << "Status:      [FAILED]" << endl;
        }
        cout << "---------------------------------" << endl;
    }
    
    cout << endl << "Tests Passed: " << passed << " / " << testCases.size() << endl;
    
    return 0;
}

int main()
{
    test<Solution1>();
    test<Solution2>();
    return 0;
}
