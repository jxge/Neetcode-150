#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
private:
    void backtrack(int startIndex, const std::vector<int>& nums, std::vector<int>& current, std::vector<std::vector<int>>& result) {
        // Every state reached in this tree represents a valid, unique subset
        result.push_back(current);

        for (int i = startIndex; i < nums.size(); ++i) {
            // DUPLICATE SKIP: If this element is identical to the previous one
            // within the same recursion layer, skip it to avoid duplicate branches.
            if (i > startIndex && nums[i] == nums[i - 1]) {
                continue;
            }

            // Choice 1: Include the element at index i
            current.push_back(nums[i]);

            // Recurse to find further combinations moving forward
            backtrack(i + 1, nums, current, result);

            // Backtrack: Remove the element to explore other choices in the loop
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;

        // 1. Sort the array so that identical numbers are adjacent
        std::sort(nums.begin(), nums.end());

        // 2. Start backtracking from index 0
        backtrack(0, nums, current, result);
        return result;
    }
};

// Helper function to print subsets cleanly
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
    std::vector<int> nums1 = {1, 2, 1};
    std::cout << "Example 1 Output:\n";
    std::vector<std::vector<int>> res1 = solution.subsetsWithDup(nums1);
    printResult(res1);
    
    std::cout << "\n";

    // Example 2
    std::vector<int> nums2 = {7, 7};
    std::cout << "Example 2 Output:\n";
    std::vector<std::vector<int>> res2 = solution.subsetsWithDup(nums2);
    printResult(res2);

    return 0;
}

