/*
Longest Increasing Subsequence (LIS)

Given an integer array nums, return the length of the longest strictly increasing subsequence.

A subsequence is a sequence that can be derived from the given sequence by
deleting some or no elements without changing the relative order of the
remaining characters.

    For example, "cat" is a subsequence of "crabt".

Example 1:
Input: nums = [9,1,4,2,3,3,7]

Output: 4
Explanation: The longest increasing subsequence is [1,2,3,7], which has a length of 4.

Example 2:
Input: nums = [0,3,1,3,2,3]
Output: 4

Constraints:
    1 <= nums.length <= 1000
    -1000 <= nums[i] <= 1000
*/

/*
Solution 1: Bottom-up DP
  Let dp(k) be the length of the LIS ending at index k.
    dp(0) = 1
    dp(k) = max(1, dp(j)) | 0<=j<k and nums[j] < nums[k]
  Complexity: O(N^2)

Solution 2: The length-Tracking Array Method
  The method tracks "For a sequence of lenght L, what's the absolute smalltest ending number".

  Let tails[k] be the smallest possible ending value of an increase subsequence
  of length k+1 found so far.

  For each number x in the input array
    find the first element tail[i] that is greater than or equal to x;
    if such an element can be found
      tail[i] = x
    else
      append x to the end of tail

  Property 1: values in tails are strictly increasing.
  Property 2: tails[k] is the smallest possible ending value of an increasing
    subsequence whose lenght is k+1.
  Property 3: The number of elements in tails is exactly equal to the
    length of the Longest Increasing Subsequence.

  This is exactly the same as the Patience sort.
    (1) The first card dealt forms a new pile consisting of the single card.
    (2) Place a card on the leftmost pile whose top is ≥ the current card.
    (3) If no such pile exists, start a new pile on the far right.
  Complexity: O(N * lg(N))
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

class Solution1 {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        vector<int> dp(nums.size(), 1);     // all ones
        int globalMax = 1;

        for (int k = 1; k < nums.size(); ++k) {
            for (int j = 0; j < k; ++j) {
                // If we allow duplicates in the increasing subsequence 
                // use the following condition
                // if (nums[j] <= nums[k]) {
                if (nums[j] < nums[k]) {
                    dp[k] = max(dp[k], dp[j] + 1);
                }
            }
            globalMax = max(globalMax, dp[k]);
        }
        
        return globalMax;
    }
};

class Solution2 {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;

        // tails[i] stores the smallest tail of all valid subsequences of length (i + 1)
        vector<int> tails;

        for (int x : nums) {
            // Perform binary search to find the first element >= x
            // If the increasing sequence allows duplicates, then use the upper_bound
            //
            // auto it = upper_bound(tails.begin(), tails.end(), x);
            //
            auto it = lower_bound(tails.begin(), tails.end(), x);

            if (it == tails.end()) {
                // x is larger than any existing tail -> extends the maximum LIS length
                tails.push_back(x);
            } else {
                // x is smaller than an existing tail -> optimize that length with a smaller tail
                *it = x;
            }
        }

        // The size of the tails array matches the length of the LIS exactly
        return tails.size();
    }
};



// Helper function to print test results clearly
template <class Solution> 
void runTestCase(int caseNum, vector<int> nums, int expected) {
    Solution solver;
    int result = solver.lengthOfLIS(nums);
    
    cout << "Test Case " << caseNum << ": ";
    if (result == expected) {
        cout << "✅ PASSED\n";
    } else {
        cout << "❌ FAILED (Expected " << expected << ", got " << result << ")\n";
    }
}

int main() {
    cout << "--- Running Longest Increasing Subsequence Self-Check ---\n\n";

    // Example 1: Original prompt example
    runTestCase<Solution1>(1, {9, 1, 4, 2, 3, 3, 7}, 4); 
    runTestCase<Solution2>(1, {9, 1, 4, 2, 3, 3, 7}, 4); 
    // Explanation: The LIS is [1, 2, 3, 7] (Length 4)

    // Example 2: Strictly increasing array
    runTestCase<Solution1>(2, {1, 2, 3, 4, 5}, 5);
    runTestCase<Solution2>(2, {1, 2, 3, 4, 5}, 5);

    // Example 3: Strictly decreasing array
    runTestCase<Solution1>(3, {5, 4, 3, 2, 1}, 1);
    runTestCase<Solution2>(3, {5, 4, 3, 2, 1}, 1);

    // Example 4: All elements are identical (Strictly increasing must skip duplicates)
    runTestCase<Solution1>(4, {7, 7, 7, 7}, 1);
    runTestCase<Solution2>(4, {7, 7, 7, 7}, 1);

    // Example 5: Random mix with negative values
    runTestCase<Solution1>(5, {10, 9, 2, 5, 3, 7, 101, 18}, 4);
    runTestCase<Solution2>(5, {10, 9, 2, 5, 3, 7, 101, 18}, 4);
    // Explanation: The LIS is [2, 3, 7, 101] or [2, 5, 7, 18] (Length 4)

    // Example 6: Edge Case: Single element
    runTestCase<Solution1>(6, {42}, 1);
    runTestCase<Solution2>(6, {42}, 1);

    cout << "\n--- Self-Check Complete ---\n";
    return 0;
}

