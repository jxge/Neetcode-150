#include <iostream>
#include <stack>
#include <algorithm>
#include <string>

using namespace std;

class MinStack {
private:
    // Pair structure: {element_value, minimum_value_at_this_level}
    stack<pair<int, int>> st;

public:
    MinStack() {
        // Constructor initializes an empty stack object
    }
    
    void push(int val) {
        if (st.empty()) {
            // If empty, the current value is automatically the minimum
            st.push({val, val});
        } else {
            // Find the new minimum by comparing the input with the current top's minimum
            int current_min = min(val, st.top().second);
            st.push({val, current_min});
        }
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};

// Driver program to verify the example run
int main() {
    MinStack minStack;
    
    cout << "Executing sequence..." << endl;
    minStack.push(1);
    minStack.push(2);
    minStack.push(0);
    
    cout << "getMin(): " << minStack.getMin() << " (Expected: 0)" << endl;
    minStack.pop();
    cout << "top():    " << minStack.top()    << " (Expected: 2)" << endl;
    cout << "getMin(): " << minStack.getMin() << " (Expected: 1)" << endl;
    
    return 0;
}
