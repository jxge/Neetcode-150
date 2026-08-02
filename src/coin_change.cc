/*
Coin Change

You are given an integer array coins representing coins of different
denominations (e.g. 1 dollar, 5 dollars, etc) and an integer amount
representing a target amount of money.

Return the fewest number of coins that you need to make up the exact target
amount. If it is impossible to make up the amount, return -1.

You may assume that you have an unlimited number of each coin.

Example 1:
Input: coins = [1,5,10], amount = 12
Output: 3
Explanation: 12 = 10 + 1 + 1. Note that we do not have to use every kind coin available.

Example 2:
Input: coins = [2], amount = 3
Output: -1
Explanation: The amount of 3 cannot be made up with coins of 2.

Example 3:
Input: coins = [1], amount = 0
Output: 0
Explanation: Choosing 0 coins is a valid way to make up 0.

Constraints:
    1 <= coins.length <= 10
    1 <= coins[i] <= 2^31 - 1
    0 <= amount <= 10000
*/

/*
DP problem:
    DP(k) = INF  for n < 0
    DP(0) = 0    
    DP(k) = 1 + min(k - conins[i])     i = 0...m-1  (m=coin.size())
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Top-down DP with memoization */
class Solution1 {
private:
    // Helper function for the top-down recursive strategy
    int dfs(vector<int>& coins, int k, int INF, vector<int>& memo) {
        // Base Case 1: An amount of 0 requires exactly 0 coins
        if (k == 0) return 0;
        
        // Base Case 2: Negative amount is an invalid path
        if (k < 0) return INF;
        
        // If memo[k] != -1, this subproblem has already been evaluated
        if (memo[k] != -1) {
            return memo[k];
        }
        
        int minCoins = INF;
        
        // Try taking every coin denomination one by one
        for (int coin : coins) {
            int result = dfs(coins, k - coin, INF, memo);
            
            // Safety check: Only minimize if the subpath returned a valid combination
            if (result != INF) {
                minCoins = min(minCoins, 1 + result);
            }
        }
        
        // Cache the calculated state configuration into memory
        memo[k] = minCoins;
        return memo[k];
    }

public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 0) return -1;
        
        // Setting INF strictly relative to the current target amount.
        // It is physically impossible to use more than 'amount' coins.
        int INF = amount + 1;
        
        // Initialize memo table with -1 to indicate uncomputed states
        vector<int> memo(amount + 1, -1);
        
        int result = dfs(coins, amount, INF, memo);
        
        // Convert internal INF representation back to the problem's expected -1
        return (result == INF) ? -1 : result;
    }
};

/* Bottom-Up DP */
class Solution2 {
public:
    int coinChange(vector<int>& coins, int amount) {
        // Create a DP table up to 'amount' size.
        // Initialize all indices with a placeholder for infinity (amount + 1).
        // Using amount + 1 is safe because the maximum possible coins needed for 
        // any valid amount 'n' can never exceed 'n' itself (e.g., using all 1-dollar coins).
        vector<int> dp(amount + 1, amount + 1);
        
        // Base Case: 0 coins are needed to make an amount of 0.
        dp[0] = 0;
        
        // Iteratively calculate the minimum coins for every amount from 1 up to target
        for (int n = 1; n <= amount; ++n) {
            for (int coin : coins) {
                // Check if the current coin denomination can fit into amount 'n'
                // This implicitly filters out the negative index check (n - coin < 0)
                if (n - coin >= 0) {
                    dp[n] = min(dp[n], 1 + dp[n - coin]);
                }
            }
        }
        
        // If the value remains at our infinity placeholder, the amount cannot be made.
        return (dp[amount] > amount) ? -1 : dp[amount];
    }
};

// Driver program to test the implementation
template<class Solution>
int test() {
    Solution solver;
    
    // Struct to organize test inputs and expectations
    struct TestCase {
        vector<int> coins;
        int amount;
        int expected;
        string description;
    };
    
    vector<TestCase> testCases = {
        {{1, 5, 10}, 12, 3, "Standard greedy-friendly match (10 + 1 + 1)"},
        {{2}, 3, -1, "Impossible configuration (cannot form odd with even)"},
        {{1}, 0, 0, "Zero amount base case"},
        {{186, 419, 83, 408}, 6249, 20, "Large amount with tricky combinations"},
        {{2, 5, 10, 1}, 27, 4, "Combination utilizing multiple sizes (10 + 10 + 5 + 2)"}
    };
    
    cout << endl << "######## Running Coin Change Tests " << typeid(solver).name() << endl;
    
    int passed = 0;
    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& tc = testCases[i];
        int result = solver.coinChange(const_cast<vector<int>&>(tc.coins), tc.amount);
        
        cout << "Test Case " << i + 1 << ": " << tc.description << endl;
        cout << "Coins available: [";
        for (size_t j = 0; j < tc.coins.size(); ++j) {
            cout << tc.coins[j] << (j == tc.coins.size() - 1 ? "" : ", ");
        }
        cout << "]" << endl;
        cout << "Target Amount:   " << tc.amount << endl;
        cout << "Expected Coins:  " << tc.expected << endl;
        cout << "Result Coins:    " << result << endl;
        
        if (result == tc.expected) {
            cout << "Status:          [SUCCESS]" << endl;
            passed++;
        } else {
            cout << "Status:          [FAILED]" << endl;
        }
        cout << "---------------------------------" << endl;
    }
    
    cout << endl << "Summary: Passed " << passed << " / " << testCases.size() << " tests." << endl;
    
    return 0;
}

int main()
{
    test<Solution1>();
    test<Solution2>();
    return 0;
}
