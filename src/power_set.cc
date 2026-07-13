/*
 * Approach 1: Using a integer to repreent the mask: bit i of the mask is 1, nums[i] is added to the result.
 *
 * Approach 2: Using bit vector to represent the mask: mask[i] is 1, nums[i] is added to the result.
 *
 * Approach 3: Using a backtracking method
 * In phase i, there are 2 choices:
 *   (a) add nums[i] in the result
 *   (b) do not add nums[i] in the result
 * 
 * Approach 4: Using a backtracking method (handle duplicates)
 * Two steps:
 *   (a) Sort the array.
 *   (b) In pase i when you decide to skip nums[i], you need to skip nums[j] that nums[i]=nums[j] where j=i+1, ....
 *
 * Time complexity: O(N * 2^N), where N is the size of the array
 * Space complexity: O(N * 2^N), to store the result
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


class Solution1 {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        int n = nums.size();
        
        // Total number of subsets is 2^n
        int totalSubsets = 1 << n; // Equivalent to pow(2, n)
        
        for (int mask = 0; mask < totalSubsets; ++mask) {
            std::vector<int> currentSubset;
            
            for (int i = 0; i < n; ++i) {
                // If the ith bit of mask is set, include nums[i]
                if ((mask & (1 << i)) != 0) {
                    currentSubset.push_back(nums[i]);
                }
            }
            result.push_back(currentSubset);
        }
        
        return result;
    }
};

class Solution2 {
private:
    // Simulates a binary increment operation (mask++) on a vector of booleans.
    // Returns false when the binary counter rolls over (overflows), meaning all subsets are done.
    bool incrementMask(std::vector<bool>& mask) {
        int n = mask.size();
        for (int i = 0; i < n; ++i) {
            if (!mask[i]) {
                mask[i] = true; // Flips 0 to 1, carrying stops
                return true;
            }
            mask[i] = false; // Flips 1 to 0, carrying continues to next bit
        }
        return false; // Wrapped back around to all zeros (overflow)
    }

public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        int n = nums.size();
        
        // Initialize an arbitrary-precision mask with all bits set to false
        std::vector<bool> mask(n, false);
        bool hasNext = true;

        while (hasNext) {
            std::vector<int> currentSubset;
            
            // Build the current subset based on the active bits in the mask
            for (int i = 0; i < n; ++i) {
                if (mask[i]) {
                    currentSubset.push_back(nums[i]);
                }
            }
            result.push_back(currentSubset);
            
            // Increment the custom binary mask for the next iteration
            hasNext = incrementMask(mask);
        }
        
        return result;
    }
};


class Solution3 {
private:
    void generateSubsets(int index, const std::vector<int>& nums, std::vector<int>& current, std::vector<std::vector<int>>& result) {
        // Base Case: If we have made a choice for every element, store the subset
        if (index == nums.size()) {
            result.push_back(current);
            return;
        }

        // Choice 1: Include the element at the current index
        current.push_back(nums[index]);
        generateSubsets(index + 1, nums, current, result);

        // Choice 2: Exclude the element at the current index (Backtrack)
        current.pop_back();
        generateSubsets(index + 1, nums, current, result);
    }

public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        
        // Start backtracking from index 0
        generateSubsets(0, nums, current, result);
        return result;
    }
};

/* 

N=3, nums=[1,2,2]

└─ Solution4(index=0, current=[])  <- Element is 1
   │
   ├── [INC 1] -> current=[1]
   │   └─ Solution4(index=1, current=[1])  <- Element is 2
   │      │
   │      ├── [INC 2] -> current=[1,2]
   │      │   └─ Solution4(index=2, current=[1,2])  <- Element is 2
   │      │      │
   │      │      ├── [INC 2] -> current=[1,2,2]
   │      │      │   └─ Solution4(index=3, current=[1,2,2]) -> [Saves]
   │      │      │
   │      │      └── [EXC 2] -> (Skips duplicate index 2 -> nextIndex=3)
   │      │          └─ Solution4(index=3, current=[1,2])   -> [Saves]
   │      │
   │      └── [EXC 2] -> (Skips duplicate index 2 -> nextIndex=3)
   │          └─ Solution4(index=3, current=[1])     -> [Saves]
   │
   └── [EXC 1] -> current=[] (nextIndex=1)
       └─ Solution4(index=1, current=[])  <- Element is 2
          │
          ├── [INC 2] -> current=[2]
          │   └─ Solution4(index=2, current=[2])  <- Element is 2
          │      │
          │      ├── [INC 2] -> current=[2,2]
          │      │   └─ Solution4(index=3, current=[2,2])   -> [Saves]
          │      │
          │      └── [EXC 2] -> (Skips duplicate index 2 -> nextIndex=3)
          │          └─ Solution4(index=3, current=[2])     -> [Saves]
          │
          └── [EXC 2] -> (Skips duplicate index 2 -> nextIndex=3)
              └─ Solution4(index=3, current=[])      -> [Saves []]
*/

class Solution4 {
private:
    void generateSubsetsWithDup(int index, const std::vector<int>& nums, std::vector<int>& current, std::vector<std::vector<int>>& result) {
        // Base Case: If we reach the end of the array, save the current subset
        if (index == nums.size()) {
            result.push_back(current);
            return;
        }

        // Choice 1: Include the element at the current index
        current.push_back(nums[index]);
        generateSubsetsWithDup(index + 1, nums, current, result);
        current.pop_back(); // Backtrack

        // Choice 2: Exclude the element at the current index
        // Crucial Step: Skip all adjacent duplicates to prevent duplicate subsets
        int nextIndex = index + 1;
        while (nextIndex < nums.size() && nums[nextIndex] == nums[index]) {
            nextIndex++;
        }
        
        generateSubsetsWithDup(nextIndex, nums, current, result);
    }

public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        
        // 1. Sort the array so duplicates are adjacent
        std::sort(nums.begin(), nums.end());
        
        // 2. Start backtracking
        generateSubsetsWithDup(0, nums, current, result);
        return result;
    }
};

/*

N=2, nums=[1,2]

└─ generateSubsetsWithDup(startIndex=0, current=[])  [Adds [] to result: result=[[]]]
   │
   ├─── i = 0 (Element: 1)
   │    └─ generateSubsetsWithDup(startIndex=1, current=[1])  [Adds [1] to result]: result=[[],[1]]
   │       │
   │       ├─── i = 1 (Element: 2)
   │       │    └─ generateSubsetsWithDup(startIndex=2, current=[1, 2])  [Adds [1, 2] to result]: result=[[],[1],[1,2]]
   │       │         └─ (Loop i=2 < 2 is false -> Returns immediately)
   │       │
   │       └─── i = 2 (Loop i=2 < 2 is false -> Returns/Backtracks)
   │
   ├─── i = 1 (Element: 2)
   │    └─ generateSubsetsWithDup(startIndex=2, current=[2])  [Adds [2] to result]
   │         └─ (Loop i=2 < 2 is false -> Returns immediately)
   │
   └─── i = 2 (Loop i=2 < 2 is false -> End of Root Call)
*/

class Solution5 {
private:
    void generateSubsetsWithDup(int startIndex, const std::vector<int>& nums, std::vector<int>& current, std::vector<std::vector<int>>& result) {
        // Base Case: Every valid state reached is a unique subset
        result.push_back(current);

        for (int i = startIndex; i < nums.size(); ++i) {
            // FIX: Only skip duplicates if 'i' is beyond the starting point of THIS recursive call
            if (i > startIndex && nums[i - 1] == nums[i]) {
                continue;
            }

            // Choice: Include the element at the current index
            current.push_back(nums[i]);
            
            // Recurse to find subsets with this element included
            generateSubsetsWithDup(i + 1, nums, current, result);
            
            // Backtrack
            current.pop_back(); 
        }
    }

public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;

        // 1. Sort the array so duplicates are adjacent
        std::sort(nums.begin(), nums.end());

        // 2. Start backtracking
        generateSubsetsWithDup(0, nums, current, result);
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
    Solution1 sol1;
    Solution2 sol2;
    Solution3 sol3;
    Solution4 sol4;
    Solution5 sol5;
    std::vector<std::vector<int>> res;
    
    // Example 1
    std::vector<int> nums1 = {1, 2, 3};
    std::cout << "Example 1 Output: " << std::endl;
    res = sol1.subsets(nums1);
    printResult(res);
    std::cout << std::endl;

    res = sol2.subsets(nums1);
    printResult(res);
    std::cout << std::endl;

    res = sol3.subsets(nums1);
    printResult(res);
    std::cout << std::endl;

    res = sol4.subsetsWithDup(nums1);
    printResult(res);
    std::cout << std::endl;

    res = sol5.subsetsWithDup(nums1);
    printResult(res);
    std::cout << std::endl;

    // Example 2
    std::vector<int> nums2 = {7};
    std::cout << "Example 2 Output: " << std::endl;
    std::vector<std::vector<int>> res2 = sol5.subsetsWithDup(nums2);
    printResult(res2);

    return 0;
}
