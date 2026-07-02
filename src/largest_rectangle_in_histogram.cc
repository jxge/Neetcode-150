#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Find the maximal rectangle in a histogram
//
// Solution 1: Stack approach      Time: O(N), Space: O(N)
// To find the largest rectangle, we need to determine the maximum area possible for each bar 
// treating it as the shortest bar (the height bottleneck) of the rectangle.
//  - To do this, we find the first bar to its left that is shorter, and the first bar to its right that is shorter.
//  - A monotonic stack allows us to find these boundary indices efficiently in a single pass.
//  - We push indices onto the stack as long as the current bar is taller than or equal to the bar at the top of the stack.
//  - When we see a shorter bar, it means the bar at the top of the stack can no longer extend to the right. 
//    We pop it, calculate its area using the current index as the right boundary and the new stack top as the 
//    left boundary, and update our maximum area.

// Solution 2: The Boundary-Array Approach    Time: O(N), Space: O(N)    (less efficient in practice) 
// We compute two arrays: left_less and right_less.
//  - left_less[i]:  the index of the first bar to the left of bar i that is strictly shorter than heights[i].
//  - right_less[i]: the index of the first bar to the right of bar i that is strictly shorter than heights[i].
// Once these boundaries are known, the maximum width for bar i is simply:
//    width=right_less}[i]-left_less}[i]-1

// Extend the alogrithm to the maximal rectangle in a 2D binary matrix problem. 
// For each row i from 0 to N-1
//    - if M[i][j]==1 then heights[j]++
//    - if [ M][j]==0 then height[j] = 0 (the chain is broken)


class Solution1 {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s;
        int max_area = 0;
        int n = heights.size();

        // Loop up to 'n' to process remaining elements inside the stack at the end
        for (int i = 0; i <= n; ++i) {
            // Use a dummy height of 0 at index 'n' to clear out the stack
            int current_height = (i == n) ? 0 : heights[i];

            // Maintain a monotonic increasing stack (find the left bound)
            while (!s.empty() && current_height < heights[s.top()]) {
                int height = heights[s.top()];
                s.pop();

                // If the stack is empty, this bar can extend all the way to index 0
                int width = s.empty() ? i : (i - s.top() - 1);
                
                max_area = max(max_area, height * width);
            }
            s.push(i);
        }

        return max_area;
    }
};


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution2 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        if (n == 0) return 0;

        vector<int> left_less(n);
        vector<int> right_less(n);

        // Calculate left boundaries
        left_less[0] = -1; // No element to the left
        for (int i = 1; i < n; ++i) {
            int p = i - 1;
            // Jump left using previously computed boundaries
            while (p >= 0 && heights[p] >= heights[i]) {
                p = left_less[p];
            }
            left_less[i] = p;
        }

        // Calculate right boundaries
        right_less[n - 1] = n; // No element to the right
        for (int i = n - 2; i >= 0; --i) {
            int p = i + 1;
            // Jump right using previously computed boundaries
            while (p < n && heights[p] >= heights[i]) {
                p = right_less[p];
            }
            right_less[i] = p;
        }

        // Calculate maximum area
        int max_area = 0;
        for (int i = 0; i < n; ++i) {
            int width = right_less[i] - left_less[i] - 1;
            max_area = max(max_area, heights[i] * width);
        }

        return max_area;
    }
};

// Driver program to test the solution
int main() {
    Solution solver;

    // Test Case 1
    vector<int> heights1 = {7, 1, 7, 2, 2, 4};
    cout << "Test Case 1 Output: " << solver.largestRectangleArea(heights1) << " (Expected: 8)" << endl;

    // Test Case 2
    vector<int> heights2 = {1, 3, 7};
    cout << "Test Case 2 Output: " << solver.largestRectangleArea(heights2) << " (Expected: 7)" << endl;

    return 0;
}


