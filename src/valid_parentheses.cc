#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution1 {
public:
    bool isValid(string s) {
        stack<char> st;
        
        for (char c : s) {
            // 1. If it's an opening bracket, push its corresponding closing bracket
            if (c == '(') {
                st.push(')');
            } else if (c == '{') {
                st.push('}');
            } else if (c == '[') {
                st.push(']');
            } 
            // 2. If it's a closing bracket, check for matching validity
            else {
                // If the stack is empty, we have a closing bracket with no opening partner
                // If the top element doesn't match 'c', the order is invalid
                if (st.empty() || st.top() != c) {
                    return false;
                }
                st.pop(); // Matching pair found, remove it
            }
        }
        
        // 3. If the stack is empty, all brackets were correctly matched
        return st.empty();
    }
};


// Solution 2: In-Place String modification 
class Solution2 {
public:
    bool isValid(string s) {
        int top = -1; // Acts as our stack pointer inside the string
        
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                top++;
                s[top] = c; // Overwrite current position to reuse s as a stack
            } else {
                if (top == -1) return false; // Closing bracket with no open match
                
                // Validate match conditions
                if ((c == ')' && s[top] != '(') ||
                    (c == '}' && s[top] != '{') ||
                    (c == ']' && s[top] != '[')) {
                    return false;
                }
                top--; // Valid match found, simulate a pop
            }
        }
        return top == -1;
    }
};

// Driver program to test the solution
int main() {
    Solution solver;

    // Example 1
    string s1 = "[]";
    cout << "Example 1 Output: " << (solver.isValid(s1) ? "true" : "false") << "\n";

    // Example 2
    string s2 = "([{}])";
    cout << "Example 2 Output: " << (solver.isValid(s2) ? "true" : "false") << "\n";

    // Example 3
    string s3 = "[(])";
    cout << "Example 3 Output: " << (solver.isValid(s3) ? "true" : "false") << "\n";

    return 0;
}
