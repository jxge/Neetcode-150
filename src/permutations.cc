/*

Solution 1: Recursive bracktracing 

  P(A, k)
    (1) Base case: if (i == n - 1) print (A);
    (2) Recursive case: k = i, .., n - 1
        swap(A[k], A[i]); P(A, k+1); swap(A[k], A[i]);

Solution 2: iterative

  (1) Find the pivot – find the first i from right so that A[i] < A[i+1];
      If no such element exists, the sequence is in descending order (last permutation).
  (2) Find the successor – find the first j from the right so that A[j] > A[i] (such j exists since A[i] < A[i+1]).
  (3) Swap A[i] and A[j];
  (4) Reverse A[i+1] ... A[n-1]
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

class Solution1 {
private:
    void backtrack(int startIndex, std::vector<int>& nums, std::vector<std::vector<int>>& result) {
        // OPTIMIZED BASE CASE: If only one element remains, its permutation is fixed.
        if (startIndex == nums.size() - 1) {
            result.push_back(nums);
            return;
        }

        // Note when i == startIndex, we will keey nums[i] unchanged, and do the permutation for
        // the rest of numbers
        for (int i = startIndex; i < nums.size(); ++i) {
            std::swap(nums[startIndex], nums[i]);
            backtrack(startIndex + 1, nums, result);
            std::swap(nums[startIndex], nums[i]);
        }
    }
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        
        // Start the recursive backtracking tree from index 0
        backtrack(0, nums, result);
        return result;
    }
};

class Solution2 {
private:
    // Helper function that matches the behavior of std::next_permutation under the hood
    bool getNextPermutation(std::vector<int>& nums) {
        if (nums.size() <= 1) return false;
        
        int i = nums.size() - 2;
        // Step 1: Scan right-to-left to find the first decreasing element (the pivot)
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        
        // If i < 0, the sequence is completely sorted in descending order (final state)
        if (i < 0) {
            return false;
        }
        
        // Step 2: Scan right-to-left to find the first element strictly larger than our pivot
        int j = nums.size() - 1;
        while (nums[j] <= nums[i]) {
            j--;
        }
        
        // Step 3: Swap the pivot with its successor
        std::swap(nums[i], nums[j]);
        
        // Step 4: Reverse the suffix sequence to the right of index i
        std::reverse(nums.begin() + i + 1, nums.end());
        
        return true;
    }

public:
    // Using your exact requested API
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        
        if (nums.empty()) {
            return result;
        }

        // 1. Sort the vector initially to establish the smallest lexicographical starting point
        std::sort(nums.begin(), nums.end());
        
        // 2. Add the initial sorted state to our results map
        result.push_back(nums);
        
        // 3. Iteratively generate and collect every subsequent permutation
        while (getNextPermutation(nums)) {
            result.push_back(nums);
        }
        
        return result;
    }
};

// Helper function to print permutation structures clearly
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
    Solution1 sol1;
    Solution2 sol2;
    std::vector<std::vector<int>> res;

    // Example 1
    std::vector<int> nums1 = {1, 2, 3};
    std::cout << "Example 1 Output:" << std::endl;
    res = sol1.permute(nums1);
    printResult(res);
    res = sol2.permute(nums1);
    printResult(res);
    
    std::cout << std::endl;

    // Example 2
    std::vector<int> nums2 = {7};
    std::cout << "Example 2 Output:" << std::endl;
    res = sol1.permute(nums2);
    printResult(res);
    res = sol2.permute(nums2);
    printResult(res);

    return 0;
}

