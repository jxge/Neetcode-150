/*
Climbing Stairs

You are given an integer n representing the number of steps to reach the top of
a staircase. You can climb with either 1 or 2 steps at a time.

Return the number of distinct ways to climb to the top of the staircase.

Example 1:
Input: n = 2
Output: 2
Explanation:
    1 + 1 = 2
    2 = 2

Example 2:

Input: n = 3
Output: 3
Explanation:
    1 + 1 + 1 = 3
    1 + 2 = 3
    2 + 1 = 3

Constraints:
    1 <= n <= 45
*/

/*
Let DP(n) be the umber of distinct ways to climb up a N-step stair.
    DP(0) = 0
    DP(1) = 1
    DP(n) = DP(n-1) + DP(n-2)
*/

#include <iostream>

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        int first = 1;
        int second = 2;
        
        for (int i = 3; i <= n; ++i) {
            int current = first + second;
            first = second;
            second = current;
        }
        
        return second;
    }
};

int main() {
    Solution solver;
    
    // Test cases
    int testCases[] = {1, 2, 3, 5, 45};
    
    std::cout << "--- Climbing Stairs Results ---" << std::endl;
    for (int n : testCases) {
        std::cout << "Steps: " << n 
                  << " -> Distinct Ways: " << solver.climbStairs(n) 
                  << std::endl;
    }
    
    return 0;
}

