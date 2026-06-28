#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

class Solution {
public:
    bool isPalindrome(const string& s) {
        int left = 0;
        int right = s.length() - 1;
        
        while (left < right) {
            // Skip non-alphanumeric characters from the left
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            // Skip non-alphanumeric characters from the right
            while (left < right && !isalnum(s[right])) {
                right--;
            }
            
            // Compare characters after converting to lowercase
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            
            left++;
            right--;
        }
        
        return true;
    }
};

// Driver Code
int main() {
    Solution solver;
    
    // Define test cases
    vector<string> testCases = {
        "Was it a car or a cat I saw?",
        "tab a cat",
        "A man, a plan, a canal: Panama",
        "race a car",
        " "
    };
    
    // Run and display results
    cout << boolalpha; // Prints true/false instead of 1/0
    for (size_t i = 0; i < testCases.size(); ++i) {
        cout << "Test Case " << i + 1 << ": \"" << testCases[i] << "\"\n";
        cout << "Result: " << solver.isPalindrome(testCases[i]) << "\n\n";
    }
    
    return 0;
}
