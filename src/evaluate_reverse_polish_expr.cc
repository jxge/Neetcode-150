#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;

        for (const string& token : tokens) {
            // Check if the token is an operator
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                // Pop the operands in reverse order
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();

                // Perform operation and push result
                if (token == "+") st.push(a + b);
                else if (token == "-") st.push(a - b);
                else if (token == "*") st.push(a * b);
                else if (token == "/") st.push(a / b); // C++ division naturally truncates toward zero
            } else {
                // Convert string to integer and push onto the stack
                st.push(stoi(token));
            }
        }

        // The final remaining element on the stack is the total evaluation result
        return st.top();
    }
};

// Driver program to test the solution
int main() {
    Solution solver;

    // Example 1
    vector<string> tokens = {"1", "2", "+", "3", "*", "4", "-"};
    cout << "Output: " << solver.evalRPN(tokens) << " (Expected: 5)" << endl;

    return 0;
}
