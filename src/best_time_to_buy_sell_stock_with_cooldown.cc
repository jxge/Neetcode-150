/*
Best Time to Buy and Sell Stock with Cooldown
Medium Topics Company Tags
Hints

You are given an integer array prices where prices[i] is the price of NeetCoin
on the ith day.

You may buy and sell one NeetCoin multiple times with the following
restrictions:

After you sell your NeetCoin, you cannot buy another one on the next day
(i.e., there is a cooldown period of one day).  You may only own at most one
NeetCoin at a time.

You may complete as many transactions as you like.

Return the maximum profit you can achieve.

Example 1:
Input: prices = [1,3,4,0,4]
Output: 6
Explanation: Buy on day 0 (price = 1) and sell on day 1 (price = 3), profit =
3-1 = 2. Then buy on day 3 (price = 0) and sell on day 4 (price = 4), profit =
4-0 = 4. Total profit is 2 + 4 = 6.

Example 2:
Input: prices = [1]
Output: 0
*/

/*
Approach 1: Top-down recursive with cache

Approach 1: State Machine DP
  (1) Hold - maximum profit on the current day if we own a share (i.e., we
      have bought and not yet sold).
  (2) sold - maximum profit on the current day if we do not own a share
      and we are in colddown (i.e., we sold the share on the previous day)
  (3) rest - maximum profit on the current day if we do not own a share 
      and we are not in cooldown (we are free to buy today).

Transitions:
  (1) Sold day: we either stay in Sold or sell the share we held yesterday:
      sold[i] = max(sold[i], hold[i-1] + prices[i]
  (2) Hold day: we are either keep holding from yesterday or buy today
      hold[i] =  max(hold[i-1], rest[i-1] - prices[i])
  (3) Rest day: we either stay in rest or the cooldown from yesterday is over 
      (we can come from sold yesterday)
      rest[i] = max(est[i-1, sold[i-1)
   Base case (day0):
       hold = -prices[9]    // we buy on day -
       sold = 0             // no selling yet (cooldown is not active)
       rest = 0             // no tranaction, can buy
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution1 {
public:
    int maxProfit(vector<int>& prices) {
        // Allocate a 1D array to handle both states: index (i * 2 + buying)
        vector<int> memo(prices.size() * 2, -1);
        return dfs(0, 1, prices, memo.data());
    }

private:
    int dfs(int i, int buying, const vector<int>& prices, int* memo) {
        if (i >= prices.size()) return 0;

        // Calculate unique 1D key index
        int key = (i << 1) | buying; 
        if (memo[key] != -1) return memo[key];

        // Option 1: Always available (Skip / Cooldown)
        int cooldown = dfs(i + 1, buying, prices, memo);

        if (buying) {
            // Option 2: Buy stock
            int buy = dfs(i + 1, 0, prices, memo) - prices[i];
            return memo[key] = max(buy, cooldown);
        } else {
            // Option 2: Sell stock (Jump i+2 to enforce the cooldown day)
            int sell = dfs(i + 2, 1, prices, memo) + prices[i];
            return memo[key] = max(sell, cooldown);
        }
    }
};


class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;

        // Base cases representing Day 0 options
        int held = -prices[0]; // Bought stock on Day 0
        int sold = 0;          // Concluded a sale today (impossible on Day 0)
        int reset = 0;         // Doing nothing on Day 0

        // Iterate forward through the prices starting from Day 1
        for (size_t i = 1; i < prices.size(); ++i) {
            int prev_held = held;
            int prev_sold = sold;
            int prev_reset = reset;

            // 1. Recursive 'buy' branch transforms into updating the 'held' state
            held = max(prev_held, prev_reset - prices[i]);

            // 2. Recursive 'sell' branch transforms into updating the 'sold' state
            sold = prev_held + prices[i];

            // 3. Recursive 'cooldown' branch transforms into updating the 'reset' state
            reset = max(prev_reset, prev_sold);
        }

        // The maximum profit at the end will either be a lingering sale or resting state
        return max(sold, reset);
    }
};

template<class Solution>
int  test()
{
    Solution solver;

    cout << "######## " << typeid(solver).name() << ": start testing ########" << endl;
    // Test Case 1: Example 1 configuration from the problem statement
    vector<int> prices1 = {1, 3, 4, 0, 4};
    int ans1 = solver.maxProfit(prices1);
    cout << "Test 1 Passed: maxProfit = " << ans1 << " (Expected: 6)\n";
    assert(ans1 == 6);

    // Test Case 2: Minimal array bounds (single item)
    vector<int> prices2 = {1};
    int ans2 = solver.maxProfit(prices2);
    cout << "Test 2 Passed: maxProfit = " << ans2 << " (Expected: 0)\n";
    assert(ans2 == 0);

    // Test Case 3: Empty inputs array
    vector<int> prices3 = {};
    int ans3 = solver.maxProfit(prices3);
    cout << "Test 3 Passed: maxProfit = " << ans3 << " (Expected: 0)\n";
    assert(ans3 == 0);

    // Test Case 4: Monotonically decreasing prices (Never buy, no profit possible)
    vector<int> prices4 = {5, 4, 3, 2, 1};
    int ans4 = solver.maxProfit(prices4);
    cout << "Test 4 Passed: maxProfit = " << ans4 << " (Expected: 0)\n";
    assert(ans4 == 0);

    // Test Case 5: Standard up-down market where skipping an immediate trade pays off due to cooldown rules
    vector<int> prices5 = {1, 2, 3, 0, 2};
    int ans5 = solver.maxProfit(prices5);
    cout << "Test 5 Passed: maxProfit = " << ans5 << " (Expected: 3)\n";
    assert(ans5 == 3);
    cout << "\n🌟 All self-checking driver validation assertions passed successfully! 🌟\n";
    return 0;
}

int main() 
{
    test<Solution1>();
    test<Solution2>();
    return 0;
}

