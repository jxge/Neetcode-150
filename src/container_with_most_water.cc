#include <iostream>
#include <vector>
#include <algorithm>

/***
 * We must prove that
 *   (1) moving the pointer at the shorter bar never loses a better solution.
 *   (2) moving the pointer at the taller bar can never find a better solution. 
 * Assume H[L] <= H[R] and we choose to move the taller bar(R), then we have a new 
 * position R': L < R' < R. The new are is:
 *   A(L,R') = min(H[L],H[R'])*(R'-L) < H[L]*(R-L) = A(L,R)
 * This implies that moving the taller bar will result an strictly inferior solution. 
 */

using namespace std;

// Time complexity: O(N)
// Space complexity: O(1)
class Solution {
public:
    int maxArea(vector<int>& heights) {
        int max_water = 0;
        int left = 0;
        int right = heights.size() - 1;
        
        while (left < right) {
            int width = right - left;
            int current_height = min(heights[left], heights[right]);
            
            int current_water = current_height * width;
            max_water = max(max_water, current_water);
            
            // Optimization: Move pointers based on height relationships
            if (heights[left] < heights[right]) {
                left++;
            } else if (heights[left] > heights[right]) {
                right--;
            } else {
                // When equal, both historical boundaries are exhausted.
                // Move both pointers inward simultaneously.
                left++;
                right--;
            }
        }
        
        return max_water;
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
    vector<int> heights1 = {1, 7, 2, 5, 4, 7, 3, 6};
    cout << "Test Case 1:\nInput: heights = ";
    printVector(heights1);
    cout << "\nOutput: " << solver.maxArea(heights1) << "\n\n";

    // Test Case 2: Uniform heights
    vector<int> heights2 = {2, 2, 2};
    cout << "Test Case 2:\nInput: heights = ";
    printVector(heights2);
    cout << "\nOutput: " << solver.maxArea(heights2) << "\n\n";

    // Test Case 3: Ascending heights
    vector<int> heights3 = {1, 2, 3, 4, 5, 6};
    cout << "Test Case 3:\nInput: heights = ";
    printVector(heights3);
    cout << "\nOutput: " << solver.maxArea(heights3) << "\n\n";

    // Test Case 4: Steeper inner boundaries
    vector<int> heights4 = {10, 1, 1, 1, 10};
    cout << "Test Case 4:\nInput: heights = ";
    printVector(heights4);
    cout << "\nOutput: " << solver.maxArea(heights4) << "\n";

    return 0;
}
