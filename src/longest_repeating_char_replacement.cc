#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(26, 0); // Stores frequency of uppercase English letters
        int left = 0;
        int max_frequency = 0;
        int max_length = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            // Add current character to the window frequency count
            count[s[right] - 'A']++;
            
            // Track the highest frequency of any single character seen in the current window
            max_frequency = max(max_frequency, count[s[right] - 'A']);
            
            // Current window size is (right - left + 1)
            // Cells to replace = window size - max_frequency
            while ((right - left + 1) - max_frequency > k) {
                // Shrink the window from the left if we need more than k replacements
                count[s[left] - 'A']--;
                left++;
            }
            
            // Update the maximum valid window length found so far
            max_length = max(max_length, right - left + 1);
        }
        
        return max_length;
    }
};

// Driver Code
int main() {
    Solution solver;
    
    // Test Case 1: Standard replacement from description
    string s1 = "XYYX";
    int k1 = 2;
    cout << "Test Case 1:\n";
    cout << "Input: s = \"" << s1 << "\", k = " << k1 << "\n";
    cout << "Output: " << solver.characterReplacement(s1, k1) << "\n\n";

    // Test Case 2: Interleaved character repetitions
    string s2 = "AAABABB";
    int k2 = 1;
    cout << "Test Case 2:\n";
    cout << "Input: s = \"" << s2 << "\", k = " << k2 << "\n";
    cout << "Output: " << solver.characterReplacement(s2, k2) << "\n\n";

    // Test Case 3: k = 0 (No replacements allowed, find longest consecutive block)
    string s3 = "AABCCBB";
    int k3 = 0;
    cout << "Test Case 3:\n";
    cout << "Input: s = \"" << s3 << "\", k = " << k3 << "\n";
    cout << "Output: " << solver.characterReplacement(s3, k3) << "\n\n";

    // Test Case 4: k is larger than the string length
    string s4 = "ABC";
    int k4 = 5;
    cout << "Test Case 4:\n";
    cout << "Input: s = \"" << s4 << "\", k = " << k4 << "\n";
    cout << "Output: " << solver.characterReplacement(s4, k4) << "\n";

    return 0;
}
