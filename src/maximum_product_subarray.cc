/*
Maximum Product Subarray

Given an integer array nums, find a subarray that has the largest product, and
return the product.

A subarray is a contiguous non-empty sequence of elements within an array.

You can assume the output will fit into a 32-bit integer.

Note that the product of an array with a single element is the value of that
element.

Example 1:
Input: nums = [2,4,-3,5]
Output: 8
Explanation: [2,4] has the largest product 8.

Example 2:
Input: nums = [-3,0,-2]
Output: 0
Explanation: The result cannot be 6, because [-3,-2] is not a subarray.

Constraints:
    1 <= nums.length <= 20,000
    -10 <= nums[i] <= 10
    The product of any subarray of nums is guaranteed to fit in a 32-bit integer.
*/

/*
Solution 1: Bottom-up BP
    dp_max(k)  -- maximum product of a subarray ending at position k, k=0...num.size()-1
    dp_min(k)  -- minimum product of a subarray ending at position k, k=0...num.size()-1

    dp_max(0) = nums[0]
    dp_min(0) = nums[0]

    dp_max(k) = max( nums[k], nums[k] * dp_max(k-1), nums[k] * dp_min(k-1))
    dp_max(k) = min( nums[k], nums[k] * dp_max(k-1), nums[k] * dp_min(k-1))

    Final answer = max dp_max(k)   k=0...nums.size()-1

Solution 2: Prefix/Suffix method
  Case 1: there's no zero
    (a) if there are even number of negative number, the product 
        of the whole array is the result
    (b) if there are odd number of negative number, we need to remove
        one negative number x. Now the array is divided as 3 parts:
          prefix x suffix
        The products of prefix and suffix will be non-negative.
        the maximum product of all prefixes and suffixes is the result
    (c) When there's a zero, it acts as a wall to reset the product chain.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution1 {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;

        // Base case initialization at index 0
        int currentMax = nums[0];
        int currentMin = nums[0];
        int globalMax = nums[0];

        // Iterate through the array starting from index 1
        for (size_t i = 1; i < nums.size(); ++i) {
            int num = nums[i];

            // If the current number is negative, multiplying swaps the boundaries:
            // (a large positive becomes a small negative, and a small negative becomes a large positive).
            // Swapping them ahead of time keeps the max/min math clean and concise.
            if (num < 0) {
                swap(currentMax, currentMin);
            }

            // State transitions matching the mathematical formulation
            currentMax = max(num, num * currentMax);
            currentMin = min(num, num * currentMin);

            // Record the highest product sequence seen up to this point
            globalMax = max(globalMax, currentMax);
        }

        return globalMax;
    }
};

class Solution2 {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;

        int n = nums.size();
        int maxProd = nums[0];
        
        // Initializing strictly to 1
        int prefix = 1;
        int suffix = 1;

        for (int i = 0; i < n; ++i) {
            // Multiply first
            prefix *= nums[i];
            suffix *= nums[n - 1 - i];

            // Capture the maximum product
            maxProd = max({maxProd, prefix, suffix});

            // If we hit a zero, reset back to 1 for the NEXT element
            if (prefix == 0) prefix = 1;
            if (suffix == 0) suffix = 1;
        }

        return maxProd;
    }
};


// Driver program to test the space-optimized DP solution
template<class Solution>
int test() {
    Solution solver;

    // Struct to organize test inputs and expectations
    struct TestCase {
        vector<int> nums;
        int expected;
        string description;
    };

    vector<TestCase> testCases = {
        {{2, 4, -3, 5}, 8, "Standard combination with a single negative ([2, 4])"},
        {{-3, 0, -2}, 0, "Array containing a zero value boundary"},
        {{2, -5, -2, -4, 3}, 24, "Multiple negative values ([2, -5, -2])"},
        {{-2}, -2, "Single negative element array"},
        {{-2, 3, -4}, 24, "Negatives around a positive element (全 elements array product)"},
        {{0, 2}, 2, "Leading zero followed by valid integer"}
    };

    cout << "--- Running Maximum Product Subarray Tests ---" << endl << endl;

    int passed = 0;
    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto& tc = testCases[i];
        int result = solver.maxProduct(const_cast<vector<int>&>(tc.nums));

        cout << "Test Case " << i + 1 << ": " << tc.description << endl;
        cout << "Input Array:    [";
        for (size_t j = 0; j < tc.nums.size(); ++j) {
            cout << tc.nums[j] << (j == tc.nums.size() - 1 ? "" : ", ");
        }
        cout << "]" << endl;
        cout << "Expected Max:   " << tc.expected << endl;
        cout << "Result Max:     " << result << endl;

        if (result == tc.expected) {
            cout << "Status:         [SUCCESS]" << endl;
            passed++;
        } else {
            cout << "Status:         [FAILED]" << endl;
        }
        cout << "-----------------------------------------------" << endl;
    }

    cout << endl << "Summary: Passed " << passed << " / " << testCases.size() << " tests." << endl;

    return 0;
}


int main()
{
    test<Solution1>();
    test<Solution2>();
    return 0;
}
