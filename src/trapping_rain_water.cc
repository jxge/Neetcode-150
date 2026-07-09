#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;


/*****************************************************************************
Solution 1: Two pointers (Optimimal)
  Water trapped above bar i is =  min(maxLeft[i], maxRight[i]) -  height[i]

  The trick is: if height[left] < height[right], then the left side is the
  bottleneck. We know some bar on the right is taller, so whatever leftMax
  we have seen is guaranteed to hold water on the left -  we don't need to
  know the exact right max, just that it's larger. So we can safely process
  the left bar. Symmetric logic for the right side.

Solution 2: Stack based apporach
  Keep a stack of indices whose heights are monotonically decreasing. When we 
  hit a bar taller than the top of the stack, that bar becomes a right wall. 
  The popped bar is the valley floor (bottom), and the new stack top is the
  left wall. Water sits in the rectangle between them:
    width = i - left - 1
    height = min(height[left], height[i])-height[bottom]
    water slab = width * height

Solution 3: Prefix / Suffix method
  Define the following:
    maxLeft[i] as the tallest bar on the left side up to index i, and
    maxRight[i] as the tallest bar on the right side up to index i.
    Water above bar i = min(L[i], R[i]) - height[i];

    maxLeft[i] = max(maxLeft[i - 1], height[i]); maxLeft[0]=height[0]
    maxRight[i] = max(maxRight[i + 1], height[i]); R[n-1]=height[n-1]

Complexity:
  Method               Time  Space Passes    Extra Memory
  ---------------------------------------------------------
  Prefix/Suffix array  O(N)  O(N)  3         2 arrays of size n  
  Two Pointer          O(N)  O(1)  1         a few scalars
  Monotonic Stack      O(N)  O(N)  1         1 stack of size n
******************************************************************************/

class TwoPointers {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                // Left bar is the limiting side
                leftMax = max(leftMax, height[left]);
                water += leftMax - height[left];
                ++left;
            } else {
                // Right bar is the limiting side
                rightMax = max(rightMax, height[right]);
                water += rightMax - height[right];
                --right;
            }
        }
        return water;
    }
};

class MonotonicStack {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int water = 0;
        stack<int> st;

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && height[i] >= height[st.top()]) {  // >= now
                int bottom = st.top();
                st.pop();

                if (st.empty()) break;

                int left = st.top();
                int width = i - left - 1;
                int boundedHeight =
                    min(height[left], height[i]) - height[bottom];

                water += width * boundedHeight;
            }
            st.push(i);
        }

        return water;
    }
};

class PrefixSuffix {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) return 0;

        vector<int> leftMax(n);   // leftMax[i]  = tallest bar in height[0..i]
        vector<int> rightMax(n);  // rightMax[i] = tallest bar in height[i..n-1]

        // Prefix max (left to right)
        leftMax[0] = height[0];
        for (int i = 1; i < n; ++i) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }

        // Suffix max (right to left)
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        // Water above each bar = min(leftMax, rightMax) - height[i]
        int water = 0;
        for (int i = 0; i < n; ++i) {
            water += min(leftMax[i], rightMax[i]) - height[i];
        }

        return water;
    }
};


// Helper function to print an array layout nicely
void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Driver Code
int main() {
    Solution solver;
    
    // Test Case 1: Standard case from problem text
    //vector<int> height1 = {0, 2, 0, 3, 1, 0, 1, 3, 2, 1};
    vector<int> height1 = {4,2,1,3,5,4};
    cout << "Test Case 1:\nInput: height = ";
    printVector(height1);
    cout << "\nOutput: " << solver.trap(height1) << "\n\n";

    // Test Case 2: Strictly decreasing terrain (no water trapped)
    vector<int> height2 = {4, 3, 2, 1};
    cout << "Test Case 2:\nInput: height = ";
    printVector(height2);
    cout << "\nOutput: " << solver.trap(height2) << "\n\n";

    // Test Case 3: A simple valley configuration
    vector<int> height3 = {3, 0, 3};
    cout << "Test Case 3:\nInput: height = ";
    printVector(height3);
    cout << "\nOutput: " << solver.trap(height3) << "\n\n";

    // Test Case 4: Flat terrain (no water trapped)
    vector<int> height4 = {2, 2, 2, 2};
    cout << "Test Case 4:\nInput: height = ";
    printVector(height4);
    cout << "\nOutput: " << solver.trap(height4) << "\n";

    return 0;
}
