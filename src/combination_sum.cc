#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
private:
    void backtrack(int index, int target, const std::vector<int>& nums, 
                   std::vector<int>& current, std::vector<std::vector<int>>& result) {
        // Base Case: If remaining target reaches exactly 0, we found a valid combination
        if (target == 0) {
            result.push_back(current);
            return;
        }

#ifdef USE_FOR_LOOP
        // more efficient
        for (int i = index; i < nums.size(); ++i) {
            // Optimization / Pruning: Since the array is sorted, if nums[i] exceeds 
            // the remaining target, no future elements can possibly fit either.
            if (nums[i] > target) {
                break;
            }

            // Action: Choose the element
            current.push_back(nums[i]);

            // Recurse: Pass 'i' instead of 'i + 1' to allow reusing the same element
            backtrack(i, target - nums[i], nums, current, result);

            // Backtrack: Remove the element to explore other combinations
            current.pop_back();
        }
#else
        // Base Case 2: Out of bounds 
        if (index >= nums.size()) {
            return;
        }

        // CRUCIAL PRUNING STEP:
        // Since 'nums' is sorted, if the current element is greater than the remaining target,
        // no future elements can possibly fit either. We abort this entire branch early.
        if (nums[index] > remainingTarget) {
            return; 
        }

        // PATH 1: "PICK" the element (stay at the same index 'i' to allow reuse)
        current.push_back(nums[index]);
        backtrackExplicit(index, remainingTarget - nums[index], nums, current, result);
        current.pop_back(); // Backtrack / Undo choice

        // PATH 2: "DON'T PICK" the element (move directly to the next index 'i + 1')
        backtrackExplicit(index + 1, remainingTarget, nums, current, result);
#endif
    }

public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& nums, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;

        // Sorting allows us to prune unviable branches inside the loop
        std::sort(nums.begin(), nums.end());

        backtrack(0, target, nums, current, result);
        return result;
    }
};

// Helper function to print the combination matrix clearly
void printResult(const std::vector<std::vector<int>>& result) {
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j];
            if (j + 1 < result[i].size()) std::cout << ",";
        }
        std::cout << "]";
        if (i + 1 < result.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Driver Program
int main() {
    Solution solution;

    // Example 1
    std::vector<int> nums1 = {2, 5, 6, 9};
    int target1 = 9;
    std::cout << "Example 1 Output:\n";
    printResult(solution.combinationSum(nums1, target1)); // Expected: [[2,2,5],[9]]
    std::cout << "\n";

    // Example 2
    std::vector<int> nums2 = {3, 4, 5};
    int target2 = 16;
    std::cout << "Example 2 Output:\n";
    printResult(solution.combinationSum(nums2, target2)); // Expected combinations summing to 16
    std::cout << "\n";

    // Example 3
    std::vector<int> nums3 = {3};
    int target3 = 5;
    std::cout << "Example 3 Output:\n";
    printResult(solution.combinationSum(nums3, target3)); // Expected: []

    return 0;
}

