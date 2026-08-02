/*
Min Cost Climbing Stairs

You are given an array of integers cost where cost[i] is the cost of taking a
step from the ith floor of a staircase. After paying the cost, you can step to
either the (i + 1)th floor or the (i + 2)th floor.

You may choose to start at the index 0 or the index 1 floor.

Return the minimum cost to reach the top of the staircase, i.e. just past the last index in cost.

Example 1:

Input: cost = [1,2,3]

Output: 2

Explanation: We can start at index = 1 and pay the cost of cost[1] = 2 and take two steps to reach the top. The total cost is 2.

Example 2:

Input: cost = [1,2,1,2,1,1,1]

Output: 4

Explanation: Start at index = 0.

    Pay the cost of cost[0] = 1 and take two steps to reach index = 2.
    Pay the cost of cost[2] = 1 and take two steps to reach index = 4.
    Pay the cost of cost[4] = 1 and take two steps to reach index = 6.
    Pay the cost of cost[6] = 1 and take one step to reach the top.
    The total cost is 4.

Constraints:

    2 <= cost.length <= 100
    0 <= cost[i] <= 100
*/

/*
 * Option A:
 *   Let DP(k) be the minimal cost to reach floor k (k=0,..., n-1)
 *      DP(0) = cost[0] // start at Step 0, pay its cost
 *      DP(2) = cost[2] // start at Step 1, pay its cost
 *      DP(k) = min(DP[k-1], DP[k-2]) + cost[k] // coming from Step k-1 or k-2, pay the price for Step k.
 *   The final answer is min(DP(n-1), DP(n-2)) since the last step can take 2 steps
 *   from floor n-2 and skip floor n-1. 
 *   If we expand cost by adding 0 at the end, then DP[n] will be answer.
 * 
 * Option B:
 *   Let DP(k) be the minimal cost to reach floor k (k=0,..., n-1) without paying for follor k.
 *      DP(0) = 0
 *      DP(0) = 0
 *      DP(k) = min(DP(k-1) + cost(k-1), DP(k-2) + cost(k-2))
 *   In this case, DP(n-1) is the final answer.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

/* Option A: Bottom-up DP (Tabulation)*/
class Solution1 {
public:
    int minCostClimbingStairs(std::vector<int>& cost) {
        // Append 0 to represent the top of the stairs
        cost.push_back(0);
        int n = cost.size();
        
        std::vector<int> dp(n);
        dp[0] = cost[0];
        dp[1] = cost[1];
        
        for (int i = 2; i < n; ++i) {
            dp[i] = std::min(dp[i-1], dp[i-2]) + cost[i];
        }

        cost.pop_back();    // restore the cost array
        
        // DP[n] of the original array is now DP[n-1] of the expanded array
        return dp[n - 1]; 
    }
};

/* Option A : Top-down DP with Memoization. */
class Solution2 {
private:
    std::vector<int> DP;
    
    int solve(int i, const std::vector<int>& cost) {
        if (i < 0) return 0;
        if (i == 0 || i == 1) return cost[i];
        if (DP[i] != -1) return DP[i];
        
        return DP[i] = cost[i] + std::min(solve(i - 1, cost), solve(i - 2, cost));
    }

public:
    int minCostClimbingStairs(std::vector<int>& cost) {
        int n = cost.size();
        DP.assign(n, -1);
        
        // You can land at the top by jumping from either index n-1 or n-2
        return std::min(solve(n - 1, cost), solve(n - 2, cost));
    }
};

/* Space optimized version of Option A */
class Solution3 {
public:
    int minCostClimbingStairs(std::vector<int>& cost) {
        int first = cost[0];
        int second = cost[1];
        
        for (size_t i = 2; i < cost.size(); ++i) {
            int current = cost[i] + std::min(first, second);
            first = second;
            second = current;
        }
        
        return std::min(first, second);
    }
};

/* Space optimized version of Option B */
class Solution4 {
public:
    int minCostClimbingStairs(std::vector<int>& cost) {
        for (size_t i = 2; i < cost.size(); ++i) {
            cost[i] += std::min(cost[i - 1], cost[i - 2]);
        }
        return std::min(cost[cost.size() - 1], cost[cost.size() - 2]);
    }
};


template<class Solution> 
int test() {
    Solution solver;
    std::cout << "Solver: " << typeid(Solution).name() << std::endl;
    std::vector<int> cost1 = {1, 2, 3};
    std::cout << "Minimum Cost: " << solver.minCostClimbingStairs(cost1) << std::endl;
    std::vector<int> cost2 = {1,2,1,2,1,1,1};
    std::cout << "Minimum Cost: " << solver.minCostClimbingStairs(cost2) << std::endl;
    return 0;
}

int main()
{
    test<Solution1>();
    test<Solution2>();
    test<Solution3>();
    test<Solution4>();
    return 0;
}

