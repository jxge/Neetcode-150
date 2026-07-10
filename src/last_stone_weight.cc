/****************************************************************************************************
Time Complexity: O(N log k), where N is the total number of points. 
Space Complexity: O(k) to store the k closest elements inside the heap.
*****************************************************************************************************/
#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
    int lastStoneWeight(std::vector<int>& stones) {
        // Max-heap to always keep the heaviest stones at the top
        std::priority_queue<int> maxHeap(stones.begin(), stones.end());
        
        // Process until at most 1 stone is left
        while (maxHeap.size() > 1) {
            int y = maxHeap.top(); // Heaviest stone
            maxHeap.pop();
            
            int x = maxHeap.top(); // Second heaviest stone
            maxHeap.pop();
            
            // If x != y, the remaining piece (y - x) is put back
            if (x != y) {
                maxHeap.push(y - x);
            }
        }
        
        // Return the weight of the last stone, or 0 if no stones are left
        return maxHeap.empty() ? 0 : maxHeap.top();
    }
};

// Driver Program
int main() {
    Solution solver;
    
    // Test Case 1
    std::vector<int> stones1 = {2, 3, 6, 2, 4};
    std::cout << "Test Case 1 Input: [2, 3, 6, 2, 4]\n";
    std::cout << "Result: " << solver.lastStoneWeight(stones1) << " (Expected: 1)\n\n";
    
    // Test Case 2
    std::vector<int> stones2 = {1, 2};
    std::cout << "Test Case 2 Input: [1, 2]\n";
    std::cout << "Result: " << solver.lastStoneWeight(stones2) << " (Expected: 1)\n";
    
    return 0;
}
