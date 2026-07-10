/*****************************************************************************************************************
Solution 1: Max-Heap of size k.
As we loop through the points, we add them to the heap. If the heap's size exceeds k, we pop the furthest point.
Time complexity: O(N log k)
Space complexity: O(k)

Solution 2: Quickselect from Scratch
Quickselect uses the same partitioning logic as Quicksort. Instead of sorting both halves of the array, it only 
recurses into the half that contains our target index k.
Time Complexity: Average Case: O(N)     Worst Case: O(N^2) 

// Returns the k-th smallest element of list within left..right inclusive
// (i.e. left <= k <= right).
function select(list, left, right, k) is
    if left = right then   // If the list contains only one element,
        return list[left]  // return that element
    pivotIndex  := ...     // select a pivotIndex between left and right,
                           // e.g., left + floor(rand() % (right − left + 1))
    pivotIndex  := partition(list, left, right, pivotIndex)
    // The pivot is in its final sorted position
    if k = pivotIndex then
        return list[k]
    else if k < pivotIndex then
        return select(list, left, pivotIndex - 1, k)
    else
        return select(list, pivotIndex + 1, right, k) 
Space Complexity: O(1)
****************************************************************************************************************/


#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        // Pair structure: {squared_distance, point_index}
        // Max-heap will keep the largest distance at the top
        std::priority_queue<std::pair<int, int>> maxHeap;
        
        for (int i = 0; i < points.size(); ++i) {
            int x = points[i][0];
            int y = points[i][1];
            int squaredDist = x * x + y * y; // Avoid using sqrt()
            
            maxHeap.push({squaredDist, i});
            
            // If the heap grows larger than k, evict the farthest point
            if (maxHeap.size() > k) {
                maxHeap.pop();
            }
        }
        
        // Extract the k closest points from the heap
        std::vector<std::vector<int>> result;
        while (!maxHeap.empty()) {
            int index = maxHeap.top().second;
            maxHeap.pop();
            result.push_back(points[index]);
        }
        
        return result;
    }
};

#include <iostream>
#include <vector>
#include <cstdlib> // For std::rand

class Solution {
private:
    // Helper function to calculate squared Euclidean distance
    int getDistance(const std::vector<int>& point) {
        return point[0] * point[0] + point[1] * point[1];
    }

    // Partition function similar to Quicksort (Lomuto variant)
    int partition(std::vector<std::vector<int>>& points, int left, int right) {
        // Optional: Choose a random pivot index to avoid O(N^2) worst case
        int pivotIdx = left + std::rand() % (right - left + 1);
        std::swap(points[pivotIdx], points[right]);

        int pivotDist = getDistance(points[right]);
        int i = left; // Tracks the boundary of elements smaller than the pivot

        for (int j = left; j < right; ++j) {
            if (getDistance(points[j]) <= pivotDist) {
                std::swap(points[i], points[j]);
                i++;
            }
        }
        // Place the pivot element in its final sorted position
        std::swap(points[i], points[right]);
        return i;
    }

    // Recursive or iterative Quickselect worker
    void quickSelect(std::vector<std::vector<int>>& points, int left, int right, int k) {
        if (left >= right) return;

        int pivotIdx = partition(points, left, right);

        // If the pivot lands exactly at index k, everything to the left is smaller
        if (pivotIdx == k) {
            return;
        } else if (pivotIdx < k) {
            // Target is in the right subarray
            quickSelect(points, pivotIdx + 1, right, k);
        } else {
            // Target is in the left subarray
            quickSelect(points, left, pivotIdx - 1, k);
        }
    }

public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        // Quickselect will rearrange the array so that the k closest are at indices 0 to k-1
        quickSelect(points, 0, points.size() - 1, k);
        
        // Return the first k elements
        return std::vector<std::vector<int>>(points.begin(), points.begin() + k);
    }
};



// Driver Program
int main() {
    Solution solver;
    
    // Test Case 1
    std::vector<std::vector<int>> points1 = {{0, 2}, {2, 2}};
    int k1 = 1;
    std::vector<std::vector<int>> result1 = solver.kClosest(points1, k1);
    
    std::cout << "Test Case 1 Output: \n";
    for (const auto& point : result1) {
        std::cout << "[" << point[0] << ", " << point[1] << "] ";
    }
    std::cout << "\n\n";

    // Test Case 2
    std::vector<std::vector<int>> points2 = {{3, 3}, {5, -1}, {-2, 4}};
    int k2 = 2;
    std::vector<std::vector<int>> result2 = solver.kClosest(points2, k2);
    
    std::cout << "Test Case 2 Output: \n";
    for (const auto& point : result2) {
        std::cout << "[" << point[0] << ", " << point[1] << "] ";
    }
    std::cout << "\n";
    
    return 0;
}
