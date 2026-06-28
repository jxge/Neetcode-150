/*
 * Solution 1: O(N*log(k))
 */

#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Step 1: Count the frequency of each element
        unordered_map<int, int> counts;
        for (int num : nums) {
            counts[num]++;
        }
        
        // Step 2: Use a min-heap to keep track of the top k frequent elements
        // The pair stores: {frequency, element}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        
        for (auto& [num, count] : counts) {
            minHeap.push({count, num});
            // If the heap exceeds size k, remove the element with the smallest frequency
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        // Step 3: Extract the elements from the min-heap into the result vector
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        return result;
    }
};

/*
 * Solution 2: O(N)
 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> counts;
        for (int num : nums) {
            counts[num]++;
        }
        
        // Buckets where index represents frequency
        // Max possible frequency is n, so we need n + 1 size
        vector<vector<int>> buckets(n + 1);
        for (auto& [num, count] : counts) {
            buckets[count].push_back(num);
        }
        
        // Gather the top k elements starting from the highest frequency bucket
        vector<int> result;
        for (int i = n; i >= 0 && result.size() < k; --i) {
            if (!buckets[i].empty()) {
                for (int num : buckets[i]) {
                    result.push_back(num);
                    if (result.size() == k) {
                        return result;
                    }
                }
            }
        }
        
        return result;
    }
};

// Driver code to test the implementation
int main() {
    Solution solution;

    // Test Case 1
    vector<int> nums1 = {1, 2, 2, 3, 3, 3};
    int k1 = 2;
    vector<int> result1 = solution.topKFrequent(nums1, k1);
    
    cout << "Test Case 1 Output: ";
    for (int num : result1) {
        cout << num << " ";
    }
    cout << "\n(Expected: 3 2 or 2 3)" << endl;

    // Test Case 2
    vector<int> nums2 = {7, 7};
    int k2 = 1;
    vector<int> result2 = solution.topKFrequent(nums2, k2);
    
    cout << "\nTest Case 2 Output: ";
    for (int num : result2) {
        cout << num << " ";
    }
    cout << "\n(Expected: 7)" << endl;

    return 0;
}
