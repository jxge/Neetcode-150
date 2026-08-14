/*
Coin Change II

You are given an integer array coins representing coins of different
denominations (e.g. 1 dollar, 5 dollars, etc) and an integer amount
representing a target amount of money.

Return the number of distinct combinations that total up to amount. If it's
impossible to make up the amount, return 0.

You may assume that you have an unlimited number of each coin and that each
value in coins is unique.

Example 1:

Input: amount = 4, coins = [1,2,3]

Output: 4
Explanation:
    1+1+1+1 = 4
    1+1+2 = 4
    2+2 = 4
    1+3 = 4

Example 2:
Input: amount = 7, coins = [2,4]
Output: 0
Constraints:

    1 <= coins.length <= 100
    1 <= coins[i] <= 5000
    0 <= amount <= 5000
*/

/*
DP problem:
  Let DP(i,k) the number of unique ways to form amount k using only coins[0..i-1]

              /  1     if k=0 and i >= 0
    DP(i,k) = |  0     if k<0 
              |  0     if i=0 and k > 0
              \  DP(i-1,k) + DP(i, k-coins[i-1])  i > 0
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include <vector>

class Solution1 {
private:
    // Helper function to perform top-down memoization based on the new model
    int computeDP(int i, int k, const std::vector<int>& coins, std::vector<std::vector<int>>& memo) {
        // Base Condition 1: Target amount achieved (k == 0) -> 1 valid way
        if (k == 0) {
            return 1;
        }
        
        // Base Condition 2: No coins available (i == 0) and k > 0 -> 0 valid ways
        if (i == 0) {
            return 0;
        }

        // Return cached result if this exact state has already been calculated
        if (memo[i][k] != -1) {
            return memo[i][k];
        }

        // The current coin available is coins[i-1] (due to 0-indexing)
        int current_coin = coins[i - 1];

        // Choice 1: Exclude the current coin, look at options using only the first i-1 coins
        int excludeCoin = computeDP(i - 1, k, coins, memo);

        // Choice 2: Include the current coin (only if it fits within the remaining amount k)
        int includeCoin = 0;
        if (k >= current_coin) {
            includeCoin = computeDP(i, k - current_coin, coins, memo);
        }

        // Combine both decisions, store them in the memo table, and return
        memo[i][k] = excludeCoin + includeCoin;
        return memo[i][k];
    }

public:
    int coinChange(int amount, const std::vector<int>& coins) {
        int n = coins.size();
        
        // Initialize the 2D memo table with -1 (representing unvisited states)
        // Rows: 0 to n (size n + 1)
        // Columns: 0 to amount (size amount + 1)
        std::vector<std::vector<int>> memo(n + 1, std::vector<int>(amount + 1, -1));
        
        // Find DP(n, amount): Ways to form 'amount' using all 'n' coins
        return computeDP(n, amount, coins, memo);
    }
};


/* Bottom-Up DP */

class Solution2 {
public:
    int coinChange(int amount, const std::vector<int>& coins) {
        // Create a DP table initialized to 0. 
        // Using unsigned int prevents undefined behavior from signed integer overflow.
        std::vector<unsigned int> dp(amount + 1, 0);

        // Base Case: There is exactly 1 way to make an amount of 0 (choosing no coins).
        dp[0] = 1;

        // Outer loop must be 'coins' to ensure we only process combinations, not permutations.
        for (int coin : coins) {
            // Inner loop moves forward from the current coin's value up to the target amount.
            for (int i = coin; i <= amount; ++i) {
                dp[i] += dp[i - coin];
            }
        }

        // Cast the final result back to a standard int to match the function signature.
        return static_cast<int>(dp[amount]);
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
        int result = solver.coinChange(tc.amount, tc.coins);
        
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
