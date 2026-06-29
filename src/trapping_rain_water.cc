#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        
        int left = 0;
        int right = height.size() - 1;
        int left_max = 0;
        int right_max = 0;
        int total_water = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                // If current height is greater than or equal to left_max, update it
                if (height[left] >= left_max) {
                    left_max = height[left];
                } else {
                    // Water can be trapped because left_max acts as a boundary
                    total_water += left_max - height[left];
                }
                left++;
            } else {
                // If current height is greater than or equal to right_max, update it
                if (height[right] >= right_max) {
                    right_max = height[right];
                } else {
                    // Water can be trapped because right_max acts as a boundary
                    total_water += right_max - height[right];
                }
                right--;
            }
        }
        
        return total_water;
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
    vector<int> height1 = {0, 2, 0, 3, 1, 0, 1, 3, 2, 1};
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
