

#include <iostream>
#include <vector>
#include <span> // Requires C++20

// Time: O(log(N)) if there are no duplicates in the array
//       O(N)      if duplicates are allowed

class Solution {
public:
    [[nodiscard]] int findMin(std::span<const int> nums) const noexcept {
        if (nums.empty()) return -1;

        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int mid = left + ((right - left) >> 1);

            if (nums[mid] > nums[right]) {
                // Minimum must be in the right half
                left = mid + 1;
            } 
            else if (nums[mid] < nums[right]) {
                // Minimum must be at 'mid' or to its left
                right = mid;
            } 
            else {
                // Critical Addition: nums[mid] == nums[right]
                // We cannot safely eliminate half the array.
                // Narrow the search space by shifting the right boundary inward.
                right--;
            }
        }

        return nums[left];
    }

    int findMin(std::vector<int>& nums) {
        return findMin(std::span<const int>(nums));
    }
};


int main() {
    // Fast I/O optimization
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solver;

    // --- Example 1 ---
    std::vector<int> nums1 = {3, 4, 5, 6, 1, 2};
    std::cout << "Example 1 Output: " << solver.findMin(nums1) << " (Expected: 1)\n";

    // --- Example 2 ---
    std::vector<int> nums2 = {4, 5, 0, 1, 2, 3};
    std::cout << "Example 2 Output: " << solver.findMin(nums2) << " (Expected: 0)\n";

    // --- Example 3 ---
    std::vector<int> nums3 = {4, 5, 6, 7};
    std::cout << "Example 3 Output: " << solver.findMin(nums3) << " (Expected: 4)\n";

    // --- Case 3: Trapped minimum inside duplicate blocks ---
    std::vector<int> nums1 = {2, 2, 2, 0, 2, 2};
    std::cout << "Case 1 Output: " << solver.findMin(nums1) << " (Expected: 0)\n";

    // --- Case 4: Minimum at the boundary edge of duplicate blocks ---
    std::vector<int> nums2 = {10, 1, 10, 10, 10};
    std::cout << "Case 2 Output: " << solver.findMin(nums2) << " (Expected: 1)\n";

    // --- Case 5: Fully unified duplicate sequence ---
    std::vector<int> nums3 = {4, 4, 4, 4, 4};
    std::cout << "Case 3 Output: " << solver.findMin(nums3) << " (Expected: 4)\n";

    return 0;
}

