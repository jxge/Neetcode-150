// Consider the range [left, right], and mid = left + (right - left) / 2
// There are 3 cases:
// 
//                  Is nums[left] == nums[mid] == nums[right]?
//                                 /          \
//                               YES           NO
//                               /              \
//       [Triggers Linear Shrink]                Is nums[left] <= nums[mid]?
//       Pointers shift inward safely:                      /          \
//       left++ and right--                                YES          NO
//                                                         /              \
//                                      [Left Half is Sorted]      [Right Half is sortd]

// Time: average O(log(N)), Worst case: O(N)

#include <iostream>
#include <vector>
#include <span>

class Solution {
public:
    [[nodiscard]] int search(std::span<const int> nums, int target) const noexcept {
        if (nums.empty()) return -1;

        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            int mid = left + ((right - left) >> 1);

            if (nums[mid] == target) {
                return mid; // Target found
            }

            // CRITICAL DUPLICATE CHECK: 
            // If boundaries and mid are identical, we cannot determine orientation.
            // Shrink the search window from both ends.
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                left++;
                right--;
                continue;
            }

            // Case 1: The left half is sorted
            if (nums[left] <= nums[mid]) {
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } 
            // Case 2: The right half is sorted
            else {
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1; // Target not found
    }

    int search(std::vector<int>& nums, int target) {
        return search(std::span<const int>(nums), target);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solver;

    // Test Case 1: Target is in the left section of a duplicate sequence
    std::vector<int> nums1 = {1, 0, 1, 1, 1};
    std::cout << "Test 1 Output: " << solver.search(nums1, 0) << " (Expected: 1)\n";

    // Test Case 2: Target is in the right section of a duplicate sequence
    std::vector<int> nums2 = {1, 1, 1, 0, 1};
    std::cout << "Test 2 Output: " << solver.search(nums2, 0) << " (Expected: 3)\n";

    return 0;
}
