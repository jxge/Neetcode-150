/*
Burst Balloons

You are given an array of integers nums of size n. The ith element represents a
balloon with an integer value of nums[i]. You must burst all of the balloons.

If you burst the ith balloon, you will receive nums[i - 1] * nums[i] * nums[i +
1] coins. If i - 1 or i + 1 goes out of bounds of the array, then assume the
out of bounds value is 1.

Return the maximum number of coins you can receive by bursting all of the
balloons.

Example 1:
Input: nums = [4,2,3,7]
Output: 143

Explanation:
nums = [4,2,3,7] --> [4,3,7] --> [4,7] --> [7] --> []
coins =  4*2*3    +   4*3*7   +  1*4*7  + 1*7*1 = 143

Constraints:
    n == nums.length
    1 <= n <= 300
    0 <= nums[i] <= 100
*/

/*
Solution 1: Top-down recursive method

Solution 2: DP Formula
  Extend the number array by adding 1 at both ends.

  Let dp(i,j) be the maximum coins obtained by buring all ballons within
  the index range. Let k be the last ballon burst.

  d(i,j) = 0   for all i > j
  d(i,i) = nums[i-1] * nums[i] * nums[i+1]
  d(i,j) = max_{k=i}^j (dp(i,k-1) + dp(k+1,j) + nums[i-1]*nums[k]*nums[j+1))
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <typeinfo>

using namespace std;

class Solution1 {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        return dfs(nums);
    }

    int dfs(vector<int>& nums) {
        if (nums.size() == 2) return 0;

        int maxCoins = 0;
        for (int i = 1; i < nums.size() - 1; i++) {
            int coins = nums[i - 1] * nums[i] * nums[i + 1];
            vector<int> newNums = nums;
            newNums.erase(newNums.begin() + i);
            coins += dfs(newNums);
            maxCoins = max(maxCoins, coins);
        }
        return maxCoins;
    }
};

class Solution2 {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        
        // Pad the original array boundaries with 1s
        vector<int> extended_nums(n + 2, 1);
        for (int i = 0; i < n; i++) {
            extended_nums[i + 1] = nums[i];
        }
        
        // dp[i][j] tracks max coins for the range of indices from i to j
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        
        // Iterate through all possible subproblem window lengths
        for (int length = 1; length <= n; length++) {
            for (int i = 1; i <= n - length + 1; i++) {
                int j = i + length - 1; // Ending index of the window
                
                // Track max coins by trying each balloon 'k' as the LAST to burst in [i, j]
                for (int k = i; k <= j; k++) {
                    int coins = extended_nums[i - 1] * extended_nums[k] * extended_nums[j + 1];
                    int total = dp[i][k - 1] + dp[k + 1][j] + coins;
                    
                    dp[i][j] = max(dp[i][j], total);
                }
            }
        }
        
        return dp[1][n];
    }
};

template<typename Solution>
int test() {
    Solution solver;
    cout << "Testing " << typeid(Solution).name() << endl;
    // Test Case 1: Standard example case from description
    vector<int> nums1 = {4, 2, 3, 7};
    int res1 = solver.maxCoins(nums1);
    cout << "Test 1 Passed -> Input: {4, 2, 3, 7} | Output: " << res1 << endl;
    assert(res1 == 143);

    // Test Case 2: Minimal single-balloon edge case
    vector<int> nums2 = {9};
    int res2 = solver.maxCoins(nums2);
    cout << "Test 2 Passed -> Input: {9}          | Output: " << res2 << endl;
    assert(res2 == 9); // 1 * 9 * 1 = 9

    // Test Case 3: Zero handling (cannot collect coins *from* the zero balloon directly, 
    // but it acts as a boundary element multiplier until it bursts)
    vector<int> nums3 = {3, 0, 5};
    int res3 = solver.maxCoins(nums3);
    cout << "Test 3 Passed -> Input: {3, 0, 5}       | Output: " << res3 << endl;
    assert(res3 == 20); // Optimal: burst 0 first (3*0*5=0), then 3 (1*3*5=15), then 5 (1*5*1=5)

    // Test Case 4: Multi-element matching duplicates
    vector<int> nums4 = {2, 2, 2};
    int res4 = solver.maxCoins(nums4);
    cout << "Test 4 Passed -> Input: {2, 2, 2}       | Output: " << res4 << endl;
    assert(res4 == 14); // Burst middle: 2*2*2=8 -> Remaining: {2, 2}. Burst left: 1*2*2=4 -> Burst last: 1*2*1=2 -> Total = 8+4+2=14 (Suboptimal)
                        // Burst end first: 2*2*1=4 -> Remaining {2, 2}. Burst left: 1*2*2=4 -> Burst last: 1*2*1=2 -> Total = 4+4+2=10 (Suboptimal)
                        // Burst left first: 1*2*2=4 -> Remaining {2, 2}. Burst right: 2*2*1=4 -> Burst last: 1*2*1=2 -> Total = 4+4+2=10 (Suboptimal)
                        // Optimal order: Burst middle last. Left first (1*2*2=4) -> Right next (2*2*1=4) -> Middle last (1*2*1=8) -> Total = 4+4+8=16

    // Test Case 5: Descending order profile
    vector<int> nums5 = {5, 4, 3};
    int res5 = solver.maxCoins(nums5);
    cout << "Test 5 Passed -> Input: {5, 4, 3}       | Output: " << res5 << endl;
    assert(res5 == 80); // Burst 4 first (5*4*3=60) -> Burst 3 (5*3*1=15) -> Burst 5 (1*5*1=5) -> Total = 69+15+5 = 80

    cout << "\n🌟 All self-checking driver tests executed and passed successfully!" << endl;
    return 0;
}


int main() {
    test<Solution1>();
    test<Solution2>();
    return 0;
}
