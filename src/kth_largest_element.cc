/***************************************************************
Time Complexity:
   Constructor: O(N log k) where N is the initial array size.
   Add method: O(log k) per insertion.
Space Complexity: O(k) to store up to k elements.
***************************************************************/


#include <iostream>
#include <vector>
#include <queue>

class KthLargest {
private:
    // Min-heap to store the k largest elements
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    int maxSize;

public:
    // Constructor initializes the heap with the k largest elements
    KthLargest(int k, std::vector<int>& nums) {
        maxSize = k;
        for (int num : nums) {
            add(num);
        }
    }
    
    // Adds a value and maintains the heap size at exactly k
    int add(int val) {
        minHeap.push(val);
        
        // If the heap exceeds size k, pop the smallest element
        if (minHeap.size() > maxSize) {
            minHeap.pop();
        }
        
        // The top of the min-heap is the kth largest element
        return minHeap.top();
    }
};

// Driver Program
int main() {
    std::vector<int> initialNums = {1, 2, 3, 3};
    int k = 3;
    
    std::cout << "Initializing KthLargest with k = " << k << " and stream [1, 2, 3, 3]\n";
    KthLargest* kthLargest = new KthLargest(k, initialNums);
    
    // Array of elements to add sequentially
    std::vector<int> streamUpdates = {3, 5, 6, 7, 8};
    
    for (int val : streamUpdates) {
        int result = kthLargest->add(val);
        std::cout << "Added: " << val << " -> " << k << "-th Largest is: " << result << "\n";
    }
    
    delete kthLargest;
    return 0;
}
