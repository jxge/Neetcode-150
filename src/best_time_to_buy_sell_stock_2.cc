#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// allowinng 2 transactions
class Solution {
public:
    int maxProfitTwoTransactions(vector<int>& prices) {
        if (prices.empty()) return 0;
        
        // Track lowest costs (represented as negative cash flows or absolute costs)
        int first_buy = INT_MAX;
        int first_sell = 0;
        int second_buy = INT_MAX;
        int second_sell = 0;
        
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

// Allowing K transactions
class Solution {
public:
    int maxProfitKTransactions(int k, const vector<int>& prices) {
        if (prices.empty() || k == 0) return 0;
        
        int n = prices.size();
        
        // Optimization: If K is larger than half the days, it becomes equivalent 
        // to an infinite transaction problem because you can trade every single day.
        if (k >= n / 2) {
            int max_profit = 0;
            for (int i = 1; i < n; ++i) {
                if (prices[i] > prices[i - 1]) {
                    max_profit += prices[i] - prices[i - 1];
                }
            }
            return max_profit;
        }
        
        // buy[j] stores max balance after buying j-th asset
        // sell[j] stores max profit after selling j-th asset
        // 1-indexed to keep mapping intuitive (1 to k)
        vector<int> buy(k + 1, INT_MIN);
        vector<int> sell(k + 1, 0);
        
        for (int price : prices) {
            for (int j = 1; j <= k; ++j) {
                // Balance after buying the j-th asset:
                // Either keep previous state, or use profit from (j-1)th sale to buy today
                buy[j] = max(buy[j], sell[j - 1] - price);
                
                // Profit after selling the j-th asset:
                // Either keep previous state, or sell current asset at today's price
                sell[j] = max(sell[j], buy[j] + price);
            }
        }
        
        return sell[k];
    }
};


// Driver Code
int main() {
    Solution solver;
    
    // Test Case 1: K = 2, identical to our previous scenario
    vector<int> prices1 = {3, 2, 6, 5, 0, 3};
    int k1 = 2;
    cout << "Test Case 1 (k = " << k1 << "):\nInput: prices = ";
    printVector(prices1);
    // Buy at 2, sell at 6 (profit 4). Buy at 0, sell at 3 (profit 3). Total = 7.
    cout << "\nOutput: " << solver.maxProfitKTransactions(k1, prices1) << "\n\n";

    // Test Case 2: K = 1, handles standard single transaction limits
    vector<int> prices2 = {1, 4, 2, 7};
    int k2 = 1;
    cout << "Test Case 2 (k = " << k2 << "):\nInput: prices = ";
    printVector(prices2);
    // Buy at 1, sell at 7 (profit 6). 
    cout << "\nOutput: " << solver.maxProfitKTransactions(k2, prices2) << "\n\n";

    // Test Case 3: K is large, but limited price peaks
    vector<int> prices3 = {3, 3, 5, 0, 3, 1, 4};
    int k3 = 7;
    cout << "Test Case 3 (k = " << k3 << "):\nInput: prices = ";
    printVector(prices3);
    cout << "\nOutput: " << solver.maxProfitKTransactions(k3, prices3) << "\n";

    return 0;
}


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
    
    // Test Case 1: Multiple ups and downs where 2 distinct transactions are best
    vector<int> prices1 = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "Test Case 1:\nInput: prices = ";
    printVector(prices1);
    // Best: Buy at 0, sell at 3 (profit 3). Then buy at 1, sell at 4 (profit 3). Total = 6.
    cout << "\nOutput: " << solver.maxProfitTwoTransactions(prices1) << "\n\n";

    // Test Case 2: Monotonically increasing (1 transaction covers the whole range)
    vector<int> prices2 = {1, 2, 3, 4, 5};
    cout << "Test Case 2:\nInput: prices = ";
    printVector(prices2);
    // Best: Buy at 1, sell at 5 (profit 4). Second transaction is redundant. Total = 4.
    cout << "\nOutput: " << solver.maxProfitTwoTransactions(prices2) << "\n\n";

    // Test Case 3: Decreasing prices
    vector<int> prices3 = {7, 6, 4, 3, 1};
    cout << "Test Case 3:\nInput: prices = ";
    printVector(prices3);
    cout << "\nOutput: " << solver.maxProfitTwoTransactions(prices3) << "\n";

    return 0;
}
