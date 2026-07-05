// Solution 1: Construct a list and find a loop in the list.
// Solution 2: Use sign marking

// The loop detection approach:
// Array nums[0:n], and nums[i] is in range [1,n] inclusive
// Consider a function f: V->S, V={0,1,2,...,n} and S={1,2,...,n}.
//  f(i)=nums(i).
// Construct the following the path: 
//     x_0, x_1, x_2, ..., x_(n+1), where x_0 = 0, x_k=f^k(0)
// Since x_1, x_2, ..., x_(n+1) are in range [1,n], 
// there must be k and m, so that x_k == x_m  (1 <= m < k <= n+1).
// This means that there exists a loop:
//      x_m, x_(m+1), ..., x(k)==x(m)
// Since x_i is in range of [1,n] where 1<=i<=n+1, x_0=0 cannot be
// in the loop. This proves taht index 0 is an entry path to the 
// lopp and not part of the loop.
//
// To find the entrance, when the fast pointer catches up the slow
// pointer, move the fast pointer back to start of the path and move
// these 2 pointers at the same pace.
// Let l be the distance from starting point to the entrance, and m
// the length of the loop. 
// 1. Meeting Point Location: In Phase 1, the slow pointer starts at 
//    the entrance (position 0) and moves forward by m - (l % m) steps 
//    to meet the fast pointer. Therefore, the meeting point location 
//    relative to the entrance is: m - (l (mod m))
// 2. In Phase 2 Traversal: In Phase 2, the slow pointer starts at this 
//    meeting point and moves forward by exactly l steps. Its new 
//    location relative to the entrance becomes: 
//        (m - (l (mod m)) + l) (mod m) = m (mod m) - l (mod m) + l (mod m) = 0
// 
// Sign marking method: 
// For each i change the sign of nums[nums[i]]. If the value is negative, report
// the duplicate.

#include <iostream>
#include <vector>

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        // Step 1: Detect the cycle using Floyd's Tortoise and Hare
        int tortoise = nums[0];
        int hare = nums[0];

        // Move tortoise by 1 step and hare by 2 steps until they meet
        do {
            tortoise = nums[tortoise];
            hare = nums[nums[hare]];
        } while (tortoise != hare);

        // Step 2: Find the entrance to the cycle (the duplicate number)
        int ptr1 = nums[0];
        int ptr2 = tortoise;

        // Move both pointers at the same speed of 1 step until they meet
        while (ptr1 != ptr2) {
            ptr1 = nums[ptr1];
            ptr2 = nums[ptr2];
        }

        return ptr1; // The meeting point is the duplicate number
    }
};

#include <iostream>
#include <vector>
#include <cmath>

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        for (size_t i = 0; i < nums.size(); ++i) {
            // Get the original value to use as our target index
            int target_idx = std::abs(nums[i]);
            
            // If the element at that index is already negative, 
            // we have seen this value before!
            if (nums[target_idx] < 0) {
                return target_idx;
            }
            
            // Standard marking: flip the sign to negative.
            // Safe because nums[target_idx] is guaranteed to be >= 1.
            nums[target_idx] = -nums[target_idx];
        }
        
        return -1; 
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solver;

    // --- Case 1: Standard layout containing 0 ---
    // Here, 2 is the duplicate.
    std::vector<int> nums1 = {0, 2, 1, 3, 2}; 
    std::cout << "Case 1 Output: " << solver.findDuplicate(nums1) << " (Expected: 2)\n";

    // --- Case 2: 0 itself is the duplicate number ---
    std::vector<int> nums2 = {0, 1, 2, 0, 3}; 
    std::cout << "Case 2 Output: " << solver.findDuplicate(nums2) << " (Expected: 0)\n";

    return 0;
}



