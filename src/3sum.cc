#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 2; ++i) {
            if (nums[i] > 0) break; // nums[i] is the smallest and greater than 0, the sum will be greater than 0.
            if (i > 0 && nums[i] == nums[i - 1]) continue;  // the nums[i] has been processed before
            
            int left = i + 1;
            int right = n - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return result;
    }
};

// Helper function to print a list of triplets
void printTriplets(const vector<vector<int>>& triplets) {
    cout << "[";
    for (size_t i = 0; i < triplets.size(); ++i) {
        cout << "[" << triplets[i][0] << "," << triplets[i][1] << "," << triplets[i][2] << "]";
        if (i < triplets.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

// Driver Code
int main() {
    Solution solver;
    
    // Test Case 1: Standard case with positive, negative, and duplicates
    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    cout << "Test Case 1:\nInput: [-1, 0, 1, 2, -1, -4]\nOutput: ";
    printTriplets(solver.threeSum(nums1));
    cout << "\n";

    // Test Case 2: No valid triplet
    vector<int> nums2 = {0, 1, 1};
    cout << "Test Case 2:\nInput: [0, 1, 1]\nOutput: ";
    printTriplets(solver.threeSum(nums2));
    cout << "\n";

    // Test Case 3: All zeros case
    vector<int> nums3 = {0, 0, 0};
    cout << "Test Case 3:\nInput: [0, 0, 0]\nOutput: ";
    printTriplets(solver.threeSum(nums3));
    cout << "\n";

    // Test Case 4: Larger array with multiple duplicate sequences
    vector<int> nums4 = {-2, 0, 0, 2, 2};
    cout << "Test Case 4:\nInput: [-2, 0, 0, 2, 2]\nOutput: ";
    printTriplets(solver.threeSum(nums4));
    
    return 0;
}
