#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// complexity: O(N)
// A={1, 2, 1, 0, 4, 2, 6}, k=3
// i = 0, dq={0}
// i = 1, dq={1}  since A[1] > A[0]
// i = 2, dq={1,2}  -> val={2}
// i = 3, dq={1,2,3} ->val = {2,2}
// i = 4, dq={4}, since A[4] > A[3], A[2], A[1] is out of bound -> val = {2, 2, 4}
// i = 5, dq={4,5} --> val = {2, 2, 4} -> val={2, 2, 4, 5}
// i = 6, dq={6}, since A[6] > A[5] -> val = {2, 2, 4, 4, 5}

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> dq; // stores indices of strictly decreasing elements

        for (int i = 0; i < nums.size(); ++i) {
            // 1. Remove indices that are out of the current window bounds
            if (!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }

            // 2. Remove elements smaller than the current element from the back
            // maintaining a decreasing order of values in the deque
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }

            // 3. Add the current element's index to the back of the deque
            dq.push_back(i);

            // 4. Append the maximum element to the result once the first window is filled
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }

        return result;
    }
};

// Driver program to test the solution
int main() {
    Solution solver;
    
    // Example test case
    vector<int> nums = {1, 2, 1, 0, 4, 2, 6};
    int k = 3;
    
    vector<int> result = solver.maxSlidingWindow(nums, k);
    
    // Print the output
    cout << "Output: [";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}
