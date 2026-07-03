#include <iostream>
#include <vector>


// Time: O(log N)
// Space: O(1)
class Solution {
public:
    int search(const std::vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            // Prevent potential overflow compared to (left + right) / 2
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid; // Target found
            } else if (nums[mid] < target) {
                left = mid + 1; // Search the right half
            } else {
                right = mid - 1; // Search the left half
            }
        }

        return -1; // Target not found
    }
};

// Driver program to test the solution
int main() {
    Solution solver;

    // Example 1
    std::vector<int> nums1 = {-1, 0, 2, 4, 6, 8};
    int target1 = 4;
    int result1 = solver.search(nums1, target1);
    std::cout << "Example 1 Output: " << result1 << " (Expected: 3)\n";

    // Example 2
    std::vector<int> nums2 = {-1, 0, 2, 4, 6, 8};
    int target2 = 3;
    int result2 = solver.search(nums2, target2);
    std::cout << "Example 2 Output: " << result2 << " (Expected: -1)\n";

    return 0;
}
