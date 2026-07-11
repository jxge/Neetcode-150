

/* 
 * Maintain a min-heap of size k. The smallest element in this heap will always stay at the top.
 * Iteration: Loop through each number in the array.
 *   - Push the current number into the min-heap.
 *   - if the size of the heap exceeds \(k\), pop the top element.
 */

#include <iostream>
#include <vector>
#include <queue>

class Solution1 {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        // Create a min-heap to keep track of the k largest elements
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
        
        for (int num : nums) {
            min_heap.push(num);
            
            // If the heap size exceeds k, remove the smallest element
            if (min_heap.size() > k) {
                min_heap.pop();
            }
        }
        
        // The top of the heap is now the kth largest element
        return min_heap.top();
    }
};

class Solution2 {
private:
    // Standard Lomuto partition scheme
    int partition(std::vector<int>& nums, int left, int right) {
        // Randomize pivot to prevent O(N^2) worst-case on sorted data
        int pivotIndex = left + rand() % (right - left + 1);
        std::swap(nums[pivotIndex], nums[right]);
        
        int pivot = nums[right];
        int i = left;
        
        for (int j = left; j < right; ++j) {
            if (nums[j] <= pivot) {
                std::swap(nums[i], nums[j]);
                i++;
            }
        }
        std::swap(nums[i], nums[right]);
        return i; // Return the final sorted index of the pivot
    }

    int quickSelect(std::vector<int>& nums, int left, int right, int targetIndex) {
        if (left == right) return nums[left];
        
        int pivotIndex = partition(nums, left, right);
        
        if (pivotIndex == targetIndex) {
            return nums[pivotIndex];
        } else if (pivotIndex > targetIndex) {
            return quickSelect(nums, left, pivotIndex - 1, targetIndex);
        } else {
            return quickSelect(nums, pivotIndex + 1, right, targetIndex);
        }
    }

public:
    int findKthLargest(std::vector<int>& nums, int k) {
        // Seed the random number generator
        std::srand(std::time(nullptr));
        
        // The kth largest element is at index (N - k) in a fully sorted array
        int targetIndex = nums.size() - k;
        return quickSelect(nums, 0, nums.size() - 1, targetIndex);
    }
};

// Driver Program
int main() {
    Solution solution1;
    
    // Example 1
    std::vector<int> nums1 = {2, 3, 1, 5, 4};
    int k1 = 2;
    std::cout << "Example 1 Output: " << solution.findKthLargest(nums1, k1) << std::endl; // Expected: 4
    
    // Example 2
    std::vector<int> nums2 = {2, 3, 1, 1, 5, 5, 4};
    int k2 = 3;
    std::cout << "Example 2 Output: " << solution.findKthLargest(nums2, k2) << std::endl; // Expected: 4

    return 0;
}


// Driver Program
int main() {
    Solution solution;
    
    // Example 1
    std::vector<int> nums1 = {2, 3, 1, 5, 4};
    int k1 = 2;
    std::cout << "Example 1 Output: " << solution.findKthLargest(nums1, k1) << std::endl; // Expected: 4
    
    // Example 2
    std::vector<int> nums2 = {2, 3, 1, 1, 5, 5, 4};
    int k2 = 3;
    std::cout << "Example 2 Output: " << solution.findKthLargest(nums2, k2) << std::endl; // Expected: 4

    return 0;
}
