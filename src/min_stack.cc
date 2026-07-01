#include <iostream>
#include <stack>
#include <algorithm>
#include <string>

using namespace std;

#include <iostream>
#include <vector>

using namespace std;

// Solution 1: Using 2 stacks
class MinStack {
private:
    vector<int> data_stack;
    // Stores pairs of {minimum_value, duplicate_count}
    vector<pair<int, int>> min_stack; 

public:
    MinStack() {}
    
    void push(int val) {
        data_stack.push_back(val);
        
        // Strict '<' condition used here
        if (min_stack.empty() || val < min_stack.back().first) {
            min_stack.push_back({val, 1}); // New minimum discovered
        } else if (val == min_stack.back().first) {
            min_stack.back().second++;     // Increment frequency count for duplicate
        }
    }
    
    void pop() {
        // If the item leaving matches our current minimum
        if (data_stack.back() == min_stack.back().first) {
            min_stack.back().second--; // Decrement the duplicate count
            
            // If no more duplicates of this minimum remain, remove it entirely
            if (min_stack.back().second == 0) {
                min_stack.pop_back();
            }
        }
        data_stack.pop_back();
    }
    
    int top() { return data_stack.back(); }
    int getMin() { return min_stack.back().first; }
};

// Solution 2: Using one stack
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
