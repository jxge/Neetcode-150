/*
Partition Equal Subset Sum

You are given an array of positive integers nums.

Return true if you can partition the array into two subsets, subset1 and
subset2 where sum(subset1) == sum(subset2). Otherwise, return false.

Example 1:

Input: nums = [1,2,3,4]

Output: true

Explanation: The array can be partitioned as [1, 4] and [2, 3].

Example 2:

Input: nums = [1,2,3,4,5]

Output: false

Constraints:

    1 <= nums.length <= 100
    1 <= nums[i] <= 50
*/

/* 
Solution 1: 2D DP Formula (Full State track)

Let dp(i,j) to a boolean value representing if a valid subset can be chosen 
from nums[0...i-1] that can sum up exactly to value j.
    i=0...n j=0...target, where target = total_sum / 2

1. Base Cases
    dp(0,0) = true      // empty subset always form a sum of 0
    dp(0,j) = false     // empty subset cannot form a sum greater than 0

2. for i=1...n and j=0...target
    if (j < nums[i-1])
        dp(i,j) = dp(i-1, j)
    else 
        dp(i,j) = dp(i-1, j) or dp(i-1, j-nums[i-1]) 

Final result : dp(n, target)
Time complexity: O(N * T)   where N is the size of nums array, T is the target, which equals totalSum/2

Solution 2: Space optimized 1D DP array

2. for i=1...n and j=0...target

  Base: dp(j) = (j == 0) ? 1 : 0
  for i = 1...n
     for (j = targe; j >= 0; j--) 
       if (j < nums[i-1])
         dp(j) = dp(j)
       else 
         dp(j) = dp(j) or dp(j-nums[i-1]) 

3. Use bit-set

*/
    
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution1 {
public:
    bool canPartition(vector<int>& nums) {
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        // If the total sum is odd, equal integer partition is impossible
        if (totalSum % 2 != 0) {
            return false;
        }

        int target = totalSum / 2;
        int n = nums.size();

        // dp[i][j] represents if a sum of j can be formed using the first i elements
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        // Base case: A sum of 0 is always possible with an empty subset
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = true;
        }

        // Fill the 2D DP table
        for (int i = 1; i <= n; ++i) {
            int currentNum = nums[i - 1];
            for (int j = 1; j <= target; ++j) {
                // Scenario A: Do not include the current number
                if (j < currentNum) {
                    dp[i][j] = dp[i - 1][j];
                } 
                // Scenario B: Choose between including or excluding the current number
                else {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - currentNum];
                }
            }
        }

        // The answer sits at the bottom-right corner of the grid
        return dp[n][target];
    }
};

class Solution2 {
public:
    bool canPartition(vector<int>& nums) {
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        // Odd sums cannot be divided into two equal integer subsets
        if (totalSum % 2 != 0) {
            return false;
        }

        int target = totalSum / 2;

        // dp[j] is true if a subset can form the exact sum j
        vector<bool> dp(target + 1, false);
        dp[0] = true; // Base case: an empty subset forms a sum of 0

        // Process each number one by one
        for (int num : nums) {
            // CRITICAL: Traverse backwards so we don't reuse the current 'num' 
            // in the same round (prevents 0/1 knapsack from becoming unbounded)
            for (int j = target; j >= num; --j) {
                if (dp[j - num]) {
                    dp[j] = true;
                }
            }
            
            // Fast Optimization: If we found a way to reach the target early, exit
            if (dp[target]) return true;
        }

        return dp[target];
    }
};

#include <bitset>


class Solution3 {
public:
    bool canPartition(vector<int>& nums) {
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        // Odd sums cannot be partitioned into two equal integer subsets
        if (totalSum % 2 != 0) {
            return false;
        }

        int target = totalSum / 2;

        // Constraint boundaries: max 100 elements * max value 50 = max total sum 5000.
        // Therefore, the maximum possible target sum is 5000 / 2 = 2500.
        // Bitset size must be statically defined at compile time.
        // For non-fixed size, use boost::dynamic_bitset
        //
        const int MAX_TARGET = 2501; 
        bitset<MAX_TARGET> bits;
        
        bits[0] = 1; // Base case: sum of 0 is always achievable

        // Process each number
        for (int num : nums) {
            bits |= (bits << num);
            
            // Fast Optimization: If target bit becomes 1 early, exit immediately
            if (bits[target]) return true;
        }

        return bits[target];
    }
};


// Helper function to execute and validate test cases
template<class Solution>
void runTestCase(int caseNum, vector<int> nums, bool expected) {
    Solution solver;
    bool result = solver.canPartition(nums);
    
    cout << "Test Case " << caseNum << ": ";
    if (result == expected) {
        cout << "✅ PASSED\n";
    } else {
        cout << "❌ FAILED (Expected " << (expected ? "true" : "false") 
             << ", got " << (result ? "true" : "false") << ")\n";
    }
}


template<class Solution>
int test() {
    cout << "\n" << typeid(Solution).name()  << ": Running 2D DP Partition Subset Sum Self-Check ---\n\n";

    // Example 1: Standard partitionable case
    runTestCase<Solution> (1, {1, 2, 3, 4}, true);

    // Example 2: Odd sum execution bypass
    runTestCase<Solution> (2, {1, 2, 3, 4, 5}, false);

    // Example 3: Small test case traced in the visualization grid
    runTestCase<Solution> (3, {2, 3, 5}, true);

    // Example 4: Large impossible balance element
    runTestCase<Solution> (4, {1, 2, 11}, false);

    // Example 5: Minimal structural boundary test case
    runTestCase<Solution> (5, {5, 5}, true);

    cout << "\n--- Self-Check Complete ---\n";
    return 0;
}

int main()
{
    test<Solution1>();
    test<Solution2>();
    test<Solution3>();
    return 0;
}
