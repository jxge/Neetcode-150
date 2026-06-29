#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// allowing one transaction
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        
        int min_price = prices[0];
        int max_profit = 0;
        
        for (size_t i = 1; i < prices.size(); ++i) {
            if (prices[i] < min_price) {
                // Update the minimum price seen so far
                min_price = prices[i];
            } else {
                // Calculate potential profit and update max_profit
                max_profit = max(max_profit, prices[i] - min_price);
            }
        }
        
        return max_profit;
    }
};

/*
 * Allowing 2 transactions
 */
class Solution2 {
public:
    int maxProfitTwoTransactions(vector<int>& prices) {
        if (prices.empty()) return 0;
        
        // Track lowest costs (represented as negative cash flows or absolute costs)
        int first_buy = INT_MAX;   // lowest price to buy the first coin so far
        int first_sell = 0;        // the maximum profit after the first tranaction
        int second_buy = INT_MAX;  // minimum effective cost to by the 2nd coin so far
        int second_sell = 0;       // the maximum totoal profit after 2 transactions
        
        for (int price : prices) {
            // 1. Minimize cost of first purchase
            first_buy = min(first_buy, price);
            
            // 2. Maximize profit of first sale
            first_sell = max(first_sell, price - first_buy);
            
            // 3. Minimize cost of second purchase by factoring in first transaction's profit
            second_buy = min(second_buy, price - first_sell);
            
            // 4. Maximize total final profit
            second_sell = max(second_sell, price - second_buy);
        }
        
        return second_sell;
    }
};
// Helper function to print an array layout nicely
void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Driver Code
int main() {
    Solution solver;
    
    // Test Case 1: Standard case from problem text
    vector<int> prices1 = {10, 1, 5, 6, 7, 1};
    cout << "Test Case 1:\nInput: prices = ";
    printVector(prices1);
    cout << "\nOutput: " << solver.maxProfit(prices1) << "\n\n";

    // Test Case 2: Strictly decreasing prices (no profit possible)
    vector<int> prices2 = {10, 8, 7, 5, 2};
    cout << "Test Case 2:\nInput: prices = ";
    printVector(prices2);
    cout << "\nOutput: " << solver.maxProfit(prices2) << "\n\n";

    // Test Case 3: Flat prices (no profit possible)
    vector<int> prices3 = {5, 5, 5, 5};
    cout << "Test Case 3:\nInput: prices = ";
    printVector(prices3);
    cout << "\nOutput: " << solver.maxProfit(prices3) << "\n\n";

    // Test Case 4: Price spikes at the end
    vector<int> prices4 = {2, 4, 1, 10};
    cout << "Test Case 4:\nInput: prices = ";
    printVector(prices4);
    cout << "\nOutput: " << solver.maxProfit(prices4) << "\n";

    return 0;
}
