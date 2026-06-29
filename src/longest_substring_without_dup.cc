#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // ASCII character set size is 128. Initialize all positions to -1.
        vector<int> charMap(128, -1);
        
        int maxLength = 0;
        int left = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            char currentChar = s[right];
            
            // If the character is a duplicate and exists inside the current window,
            // slide the left boundary past its previous occurrence.
            if (charMap[currentChar] >= left) {
                left = charMap[currentChar] + 1;
            }
            
            // Update the last seen position of the character
            charMap[currentChar] = right;
            
            // Calculate and track the maximum window size seen so far
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};

// Driver Code
int main() {
    Solution solver;
    
    // Test Case 1: Standard case from description
    string s1 = "zxyzxyz";
    cout << "Test Case 1:\nInput: \"" << s1 << "\"\n";
    cout << "Output: " << solver.lengthOfLongestSubstring(s1) << "\n\n";

    // Test Case 2: All identical characters
    string s2 = "xxxx";
    cout << "Test Case 2:\nInput: \"" << s2 << "\"\n";
    cout << "Output: " << solver.lengthOfLongestSubstring(s2) << "\n\n";

    // Test Case 3: Empty string edge case
    string s3 = "";
    cout << "Test Case 3:\nInput: \"" << s3 << "\"\n";
    cout << "Output: " << solver.lengthOfLongestSubstring(s3) << "\n\n";

    // Test Case 4: Longest substring at the end
    string s4 = "pwwkew";
    cout << "Test Case 4:\nInput: \"" << s4 << "\"\n";
    cout << "Output: " << solver.lengthOfLongestSubstring(s4) << "\n";

    return 0;
}
