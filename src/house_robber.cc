/*
House Robber

You are given an integer array nums where nums[i] represents the amount of
money the ith house has. The houses are arranged in a straight line, i.e. the
ith house is the neighbor of the (i-1)th and (i+1)th house.

You are planning to rob money from the houses, but you cannot rob two adjacent
houses because the security system will automatically alert the police if two
adjacent houses were both broken into.

Return the maximum amount of money you can rob without alerting the police.

Example 1:

Input: nums = [1,1,3,3]

Output: 4

Explanation: nums[0] + nums[2] = 1 + 3 = 4.

Example 2:

Input: nums = [2,9,8,3,6]

Output: 16

Explanation: nums[0] + nums[2] + nums[4] = 2 + 8 + 6 = 16.

Constraints:

    1 <= nums.length <= 100
    0 <= nums[i] <= 100
*/

/* Let D(k) be the maximum amount of money to rob house 0,1, up to k.
    DP(0) = sums[0]
    DP(1) = max (nums[0], num[1]);
    DP(k) = max (DP(k-1), DP(k-2) + num[k])
*/

#include <iostream>
#include <vector>
#include <algorithm>

/*
 *  Bottom up (Tabulation)
 */
class Solution1 {
public:
    int rob(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        // Base cases mapped to variables for O(1) space
        int prev2 = nums[0];
        int prev1 = std::max(nums[0], nums[1]);
        
        for (int i = 2; i < n; ++i) {
            int current = std::max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};

#include <iostream>
#include <vector>
#include <algorithm>

class Solution2 {
private:
    std::vector<int> memo;

    // Recursive helper function that works backward from house 'i'
    int solve(int i, const std::vector<int>& nums) {
        // Base Cases
        if (i < 0) return 0;
        if (i == 0) return nums[0];
        if (i == 1) return std::max(nums[0], nums[1]);

        // Return cached result if already calculated
        if (memo[i] != -1) return memo[i];

        // Apply your exact DP formula top-down
        int skip_house = solve(i - 1, nums);
        int rob_house = solve(i - 2, nums) + nums[i];

        return memo[i] = std::max(skip_house, rob_house);
    }

public:
    int rob(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        // Initialize memoization array with -1
        memo.assign(n, -1);

        // Start from the last house (top-down)
        return solve(n - 1, nums);
    }
};

template<class Solution>
void test()
{
    Solution solver;
    std::vector<int> nums = {2, 9, 8, 3, 6};
    std::cout << typeid(solver).name() << ": max money robbed is " << solver.rob(nums) << std::endl; // Output: 16
}

int main() {
    test<Solution1>();
    test<Solution2>();
    return 0;
}

