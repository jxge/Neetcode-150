#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
