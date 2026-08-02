/*
House Robber II

You are given an integer array nums where nums[i] represents the amount of
money the ith house has. The houses are arranged in a circle, i.e. the first
house and the last house are neighbors.

You are planning to rob money from the houses, but you cannot rob two adjacent
houses because the security system will automatically alert the police if two
adjacent houses were both broken into.

Return the maximum amount of money you can rob without alerting the police.

Example 1:
Input: nums = [3,4,3]
Output: 4
Explanation: You cannot rob nums[0] + nums[2] = 6 because nums[0] and nums[2]
are adjacent houses. The maximum you can rob is nums[1] = 4.

Example 2:
Input: nums = [2,9,8,3,6]
Output: 15
Explanation: You cannot rob nums[0] + nums[2] + nums[4] = 16 because nums[0]
and nums[4] are adjacent houses. The maximum you can rob is nums[1] + nums[4] =
15.

Constraints:
    1 <= nums.length <= 100
    0 <= nums[i] <= 200
*/

/*
Consider non-circular case first. Let DP(i,j) be the max amount of money 
that can be robbed from house i to house j (0<=i<=j<n).

        DP(i,i) = nums[i]
        DP(i,i+1) = max (nums[i], nums[i+1])
        DP(i,j) = max(DP(i,j-1), DP(i, j-2)+nums[j]) for all j >=i+2

When the houses are arranged in a circle, the max amount of money will be
    max(DP(0, n-2), DP(1, n-1))     // houses are numbered from 0 to n-1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        // Circular logic split into two linear sub-problems
        return max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
    }

private:
    int robLinear(const vector<int>& nums, int start, int end) {
        int prev2 = 0; // Tracks DP(i, j-2)
        int prev1 = 0; // Tracks DP(i, j-1)
        
        for (int i = start; i <= end; ++i) {
            int current = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};

// Helper function to print the test inputs nicely
void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution solver;

    // Define test cases
    vector<pair<vector<int>, int>> testCases = {
        {{3, 4, 3}, 4},          // Example 1
        {{2, 9, 8, 3, 6}, 15},   // Example 2
        {{7}, 7},                // Edge case: Single house
        {{2, 3}, 3},             // Edge case: Two houses
        {{1, 2, 3, 1}, 4}        // General case
    };

    cout << "--- Running House Robber II Tests ---" << endl << endl;

    for (size_t i = 0; i < testCases.size(); ++i) {
        vector<int> nums = testCases[i].first;
        int expected = testCases[i].second;
        int result = solver.rob(nums);

        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "  Input Houses : ";
        printVector(nums);
        cout << endl;
        cout << "  Expected Max : " << expected << endl;
        cout << "  Calculated   : " << result << endl;
        cout << "  Status       : " << (result == expected ? "✅ PASS" : "❌ FAIL") << endl;
        cout << "-----------------------------------" << endl;
    }

    return 0;
}
