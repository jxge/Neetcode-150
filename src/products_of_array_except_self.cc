#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> output(n, 1);
        
        // Step 1: Calculate prefix products
        // output[i] will contain the product of all elements to the left of i
        int prefix = 1;
        for (int i = 0; i < n; ++i) {
            output[i] = prefix;   // output[i] = sums[0] * ... * nums[i-1]
            prefix *= nums[i];
        }
        
        // Step 2: Calculate suffix products on the fly
        // Multiply each output[i] by the product of all elements to the right of i
        int suffix = 1;
        for (int i = n - 1; i >= 0; --i) {
            output[i] *= suffix;  // suffix = sums[i+1] * ... * nums[n-1]
            suffix *= nums[i];
        }
        
        return output;
    }
};
