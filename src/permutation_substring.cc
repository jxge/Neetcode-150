#include <iostream>
#include <string>
#include <vector>

using namespace std;
// Time complexity: O(N) - N is the size of s2
// Space complexity: O(1)
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.length();
        int n2 = s2.length();
        
        if (n1 > n2) return false;
        
        vector<int> s1_counts(26, 0);
        vector<int> s2_counts(26, 0);
        
        // Count frequencies for s1 and the first window of s2
        for (int i = 0; i < n1; i++) {
            s1_counts[s1[i] - 'a']++;
            s2_counts[s2[i] - 'a']++;
        }
        
        // Count how many character frequencies match initially
        int matches = 0;
        for (int i = 0; i < 26; i++) {
            if (s1_counts[i] == s2_counts[i]) {
                matches++;
            }
        }
        
        // Early return if the first window is a perfect permutation match
        if (matches == 26) return true;
        
        // Slide the window across s2
        for (int i = n1; i < n2; i++) {
            int r_idx = s2[i] - 'a';       // Right character entering
            int l_idx = s2[i - n1] - 'a';  // Left character leaving
            
            // Skip updates if the window boundary elements are identical
            if (r_idx == l_idx) continue;
            
            // 1. Process the incoming character (Right)
            s2_counts[r_idx]++;
            if (s2_counts[r_idx] == s1_counts[r_idx]) {
                matches++; // Count became equal
            } else if (s2_counts[r_idx] == s1_counts[r_idx] + 1) {
                matches--; // Count was equal, but now it overshot
            }
            
            // 2. Process the outgoing character (Left)
            s2_counts[l_idx]--;
            if (s2_counts[l_idx] == s1_counts[l_idx]) {
                matches++; // Count became equal
            } else if (s2_counts[l_idx] == s1_counts[l_idx] - 1) {
                matches--; // Count was equal, but now it undershot
            }
            
            // O(1) Check: immediately return if all 26 frequencies match
            if (matches == 26) return true;
        }
        
        return false;
    }
};

// Test driver program
int main() {
    Solution solution;
    
    // Test Case 1
    string s1_1 = "abc", s2_1 = "lecabee";
    cout << "Test Case 1:" << endl;
    cout << "s1: \"" << s1_1 << "\", s2: \"" << s2_1 << "\"" << endl;
    cout << "Expected: true, Actual: " << (solution.checkInclusion(s1_1, s2_1) ? "true" : "false") << endl;
    cout << "-----------------------------------" << endl;

    // Test Case 2
    string s1_2 = "abc", s2_2 = "lecaabee";
    cout << "Test Case 2:" << endl;
    cout << "s1: \"" << s1_2 << "\", s2: \"" << s2_2 << "\"" << endl;
    cout << "Expected: false, Actual: " << (solution.checkInclusion(s1_2, s2_2) ? "true" : "false") << endl;
    cout << "-----------------------------------" << endl;

    // Test Case 3 (Edge Case: s1 is longer than s2)
    string s1_3 = "hello", s2_3 = "ohe";
    cout << "Test Case 3 (s1 > s2):" << endl;
    cout << "s1: \"" << s1_3 << "\", s2: \"" << s2_3 << "\"" << endl;
    cout << "Expected: false, Actual: " << (solution.checkInclusion(s1_3, s2_3) ? "true" : "false") << endl;
    
    return 0;
}
