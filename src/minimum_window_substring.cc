#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

// Version 1: O(N+M), where N is the length of string 's', and M is the length of string 't'
class Solution1 {
public:
    string minWindow(string s, string t) {
        // Use a single frequency array for counts
        vector<int> counts(128, 0);
        for (char c : t) counts[c]++;

        int remaining_chars = t.length();
        int left = 0, start_idx = 0, min_len = INT_MAX;

        for (int right = 0; right < s.length(); ++right) {
            // If s[right] is a character we still need from t, decrement remaining_chars
            if (counts[s[right]] > 0) {
                remaining_chars--;
            }
            // Decrement the count for the character in our map
            counts[s[right]]--;

            // When the window is valid (contains all characters of t)
            while (remaining_chars == 0) {
                int current_len = right - left + 1;
                if (current_len < min_len) {
                    min_len = current_len;
                    start_idx = left;
                }

                // Move left pointer to shrink the window
                counts[s[left]]++;
                // If s[left] becomes positive, it means we now lack a required character from t
                if (counts[s[left]] > 0) {
                    remaining_chars++;
                }
                left++;
            }
        }

        return (min_len == INT_MAX) ? "" : s.substr(start_idx, min_len);
    }
};

// Version 2:
#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.length() < t.length()) {
            return "";
        }

        // Frequency array for characters needed from string t
        vector<int> target_counts(128, 0);
        for (char c : t) {
            target_counts[c]++;
        }

        // Frequency array for characters in the current window
        vector<int> window_counts(128, 0);

        int required_unique_chars = 0;
        for (int count : target_counts) {
            if (count > 0) required_unique_chars++;
        }

        int formed_unique_chars = 0;
        int left = 0;
        
        // Track the best window dimensions
        int min_len = INT_MAX;
        int start_idx = 0;

        // Expand the right boundary of the window
        for (int right = 0; right < s.length(); ++right) {
            char current_char = s[right];
            window_counts[current_char]++;

            // If the character frequency matches the target requirement, update formed count
            if (target_counts[current_char] > 0 && 
                window_counts[current_char] == target_counts[current_char]) {
                formed_unique_chars++;
            }

            // Shrink the left boundary as long as the window remains valid
            while (formed_unique_chars == required_unique_chars) {
                int current_window_len = right - left + 1;
                
                // Update our global minimum window if the current one is shorter
                if (current_window_len < min_len) {
                    min_len = current_window_len;
                    start_idx = left;
                }

                char left_char = s[left];
                window_counts[left_char]--;

                // If removing left_char breaks the required match count, update formed count
                if (target_counts[left_char] > 0 && 
                    window_counts[left_char] < target_counts[left_char]) {
                    formed_unique_chars--;
                }

                left++; // Slide left pointer forward
            }
        }

        return (min_len == INT_MAX) ? "" : s.substr(start_idx, min_len);
    }
};

int main() {
    Solution solver;
    cout << "Example 1: \"" << solver.minWindow("OUZODYXAZV", "XYZ") << "\"\n";
    cout << "Example 2: \"" << solver.minWindow("xyz", "xyz") << "\"\n";
    cout << "Example 3: \"" << solver.minWindow("x", "xy") << "\"\n";
    return 0;
}
