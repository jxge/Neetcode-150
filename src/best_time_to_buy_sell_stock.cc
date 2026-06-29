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

// Method 2: Kadane's Algorithm (Max Subarray Sum): Complexity: Time O(N), Space O(1)
//     L[i] = maximum subarray sum ending at position i.
//     L[i] = max(A[i], L[i-1] + A[i])
// 
class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) return 0;
        
        int current_difference_sum = 0;
        int max_profit = 0;
        
        for (size_t i = 1; i < prices.size(); ++i) {
            // Find daily price changes
            int gain = prices[i] - prices[i - 1];
            
            // Kadane's core choice: Extend current streak or start fresh
            current_difference_sum = max(0, current_difference_sum + gain);
            max_profit = max(max_profit, current_difference_sum);
        }
        
        return max_profit;
    }
};

// Divide and Conquer. Complexity is O(N log(N))
class Solution {
private:
    int helper(const vector<int>& prices, int low, int high) {
        if (low >= high) return 0;
        
        int mid = low + (high - low) / 2;
        
        // 1. Max profit completely in left or right regions
        int left_profit = helper(prices, low, mid);
        int right_profit = helper(prices, mid + 1, high);
        
        // 2. Cross region profit: Min in left half, Max in right half
        int min_left = prices[low];
        for (int i = low + 1; i <= mid; ++i) {
            min_left = min(min_left, prices[i]);
        }
        
        int max_right = prices[mid + 1];
        for (int i = mid + 2; i <= high; ++i) {
            max_right = max(max_right, prices[i]);
        }
        
        int cross_profit = max_right - min_left;
        
        return max({left_profit, right_profit, cross_profit});
    }

public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        return helper(prices, 0, prices.size() - 1);
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
