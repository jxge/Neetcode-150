/*
Target Sum

You are given an array of integers nums and an integer target.
For each number in the array, you can choose to either add or subtract it to a total sum.

    For example, if nums = [1, 2], one possible sum would be "+1-2=-1".

If nums=[1,1], there are two different ways to sum the input numbers to get a sum of 0: "+1-1" and "-1+1".

Return the number of different ways that you can build the expression such that the total sum equals target.

Example 1:

Input: nums = [2,2,2], target = 2

Output: 3

Explanation: There are 3 different ways to sum the input numbers to get a sum of 2.
+2 +2 -2 = 2
+2 -2 +2 = 2
-2 +2 +2 = 2

Constraints:

    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    -1000 <= target <= 1000
*/

/*

Solution 1: top-down BP with memoization

let dp(i,k) be the number of different ways to form k using nums[0...i-1]
    dp(0,0) = 1
    dp(0,k) = 0   for k!=0
    dp(i,k) = dp(i-1, k + nums[i-1]) + dp(i-1, k - nums[i-1])   for i > 0

Solution 2: Bottom-up BP with space optimization (left to right)
Solution 3: Bottom-up BP with space optimization (right to left)
*/

#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <cassert>
#include <unordered_map>

class Solution1 {
public:
    int findTargetSumWays(std::vector<int>& nums, int target) {
        int n = nums.size();
        
        // dp[i][k] represents the number of ways to form sum k using nums[0...i-1]
        // Using an array of hash maps to handle negative 'k' keys seamlessly.
        std::vector<std::unordered_map<int, int>> dp(n + 1);
        
        // Base case: dp(0,0) = 1
        dp[0][0] = 1;
        // Note: dp(0, k) for k != 0 is implicitly 0 because map keys default to 0.
        
        // Outer loop: iterate over the size of prefix subset (i from 1 to n)
        for (int i = 1; i <= n; ++i) {
            int current_num = nums[i - 1];
            
            // To find valid targets 'k' for step 'i', look at the sums achieved at step 'i-1'
            for (auto& entry : dp[i - 1]) {
                int prev_k = entry.first;
                
                // If we can reach 'prev_k' at step 'i-1', then at step 'i' we can transition:
                // From your formula: dp(i, k) = dp(i-1, k + num) + dp(i-1, k - num)
                // This means prev_k acts as the (k + num) or (k - num) states.
                
                // 1. If prev_k was (k + current_num), then the new k is (prev_k - current_num)
                int k1 = prev_k - current_num;
                dp[i][k1] += entry.second;
                
                // 2. If prev_k was (k - current_num), then the new k is (prev_k + current_num)
                int k2 = prev_k + current_num;
                dp[i][k2] += entry.second;
            }
        }
        
        // Return the number of ways to form 'target' using nums[0...n-1]
        return dp[n][target];
    }
};

#include <vector>
#include <numeric>

class Solution2 {
public:
    int findTargetSumWays(std::vector<int>& nums, int target) {
        // Calculate the total sum of all elements
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        
        // Edge cases where no valid subset partition exists:
        // 1. Target is strictly greater than the absolute maximum possible sum
        // 2. (sum + target) must be even and non-negative
        if (std::abs(target) > sum || (sum + target) % 2 != 0 || (sum + target) < 0) {
            return 0;
        }
        
        // Calculate the target sum for the positive subset
        //    P: the sum of the numbers assigned a positive sign
        //    N: the sum of the numbers assigned a negative sign
        //      P + N = sum
        //      P - N = target
        //      -> 
        //      P = (sum + target) / 2
        //
        int positiveSubsetTarget = (sum + target) / 2;
        
        // Initialize DP array with 0s, size is positiveSubsetTarget + 1
        std::vector<int> dp(positiveSubsetTarget + 1, 0);
        
        // Base case: There is 1 way to form a sum of 0 (using an empty subset)
        dp[0] = 1;
        
        // Transition: Process each number
        for (int num : nums) {
            // Iterate backwards to prevent using the same element multiple times
            for (int i = positiveSubsetTarget; i >= num; --i) {
                dp[i] += dp[i - num];
            }
        }
        
        return dp[positiveSubsetTarget];
    }
};

class Solution3 {
public:
    int findTargetSumWays(std::vector<int>& nums, int target) {
        // Calculate the total sum of all elements (guaranteed non-negative)
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        
        // Edge cases where no valid subset partition exists:
        // 1. Target is strictly greater than the maximum possible sum
        // 2. (sum + target) must be even and non-negative
        if (target > sum || target < -sum || (sum + target) % 2 != 0) {
            return 0;
        }
        
        // Calculate the target sum for the positive subset
        int positiveSubsetTarget = (sum + target) / 2;
        
        // Initialize DP array with 0s
        std::vector<int> dp(positiveSubsetTarget + 1, 0);
        
        // Base case: There is 1 way to form the full positive subset target initially
        dp[positiveSubsetTarget] = 1;
        
        // Transition: Process each non-negative number
        for (int num : nums) {
            // Loop forwards from 0 to look up higher elements (i + num).
            // This safely pulls values from unmodified states down to lower targets.
            for (int i = 0; i <= positiveSubsetTarget - num; ++i) {
                dp[i] += dp[i + num];
            }
        }
        
        // The final result cascades down to index 0
        return dp[0];
    }
};


#include <vector>
#include <unordered_map>

class Solution4 {
public:
    int findTargetSumWays(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> dp = {{0, 1}}; // Start with 1 way to make 0
        
        for (int num : nums) {
            std::unordered_map<int, int> next_dp;
            for (auto& [sum, count] : dp) {
                next_dp[sum + num] += count;
                next_dp[sum - num] += count;
            }
            dp = std::move(next_dp); // Elegant swap, zero memory allocation overhead
        }
        
        return dp[target];
    }
};



// Structure to define automation test cases
struct TestCase {
    std::vector<int> nums;
    int target;
    int expected;
    std::string description;
};

template<class Solution>
void test ()
{
    Solution solver;
    
    // Define evaluation suite covering constraints and variations
    std::vector<TestCase> testSuite = {
        { {2, 2, 2}, 2, 3, "Standard example case" },
        { {1, 1, 1, 1, 1}, 3, 5, "LeetCode standard test" },
        { {1}, 2, 0, "Target out of bounds (too large)" },
        { {0, 0, 0, 0, 1}, 1, 16, "Multiple zeros maximizing permutations" },
        { {1, 2, 3}, 5, 0, "Odd sum mismatch (Parity boundary check)" }
    };
    
    std::cout << "===========================================\n";
    std::cout << " Running Target Sum Driver Verification Suite \n";
    std::cout << "===========================================\n";
    
    int passedCount = 0;
    
    for (size_t i = 0; i < testSuite.size(); ++i) {
        auto& tc = testSuite[i];
        int result = solver.findTargetSumWays(tc.nums, tc.target);
        
        std::cout << "[Test " << i + 1 << "] " << tc.description << "\n";
        std::cout << "  Input: target=" << tc.target << ", nums=[";
        for (size_t j = 0; j < tc.nums.size(); ++j) {
            std::cout << tc.nums[j] << (j + 1 < tc.nums.size() ? ", " : "");
        }
        std::cout << "]\n";
        std::cout << "  Expected Output: " << tc.expected << " | Got: " << result << "\n";
        
        if (result == tc.expected) {
            std::cout << "  Status:  PASS \n\n";
            passedCount++;
        } else {
            std::cout << "  Status:  FAIL ❌\n\n";
        }
    }
    
    std::cout << "===========================================\n";
    std::cout << "Result: " << passedCount << " / " << testSuite.size() << " Tests Passed.\n";
    std::cout << "===========================================\n";
    
    // Fail hard if something broke natively
    assert(passedCount == testSuite.size());
}

int main()
{
    test<Solution1>();
    test<Solution2>();
    test<Solution3>();
    test<Solution4>();
}

       
