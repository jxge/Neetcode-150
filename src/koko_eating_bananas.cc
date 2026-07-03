#include <iostream>
#include <vector>
#include <algorithm>
#include <span>

// Time: O(n * log(m)), where n is the number of piles, and m is the maximal number of bananas in each pile
// The minimum possible eating rate is 1 banana/hour, and the maximum possible eating rate is m.
//
class Solution {
private:
    // Helper function to check if rate 'k' is sufficient to eat all bananas within 'h' hours
    [[nodiscard]] bool canEatAll(std::span<const int> piles, int h, int k) const noexcept {
        long long hours_needed = 0; // Use long long to prevent integer overflow
        
        for (const int pile : piles) {
            // Equivalent to ceil(static_cast<double>(pile) / k) without using floating point math
            hours_needed += (pile + k - 1) / k;
            
            // Early exit optimization if hours exceed h
            if (hours_needed > h) {
                return false;
            }
        }
        return hours_needed <= h;
    }

public:
    [[nodiscard]] int minEatingSpeed(const std::vector<int>& piles, int h) const noexcept {
        // Range boundaries for binary search
        int left = 1;
        int right = *std::max_element(piles.begin(), piles.end());
        int result = right;

        while (left <= right) {
            int mid = left + ((right - left) >> 1);

            if (canEatAll(piles, h, mid)) {
                result = mid;       // 'mid' works, record it as a potential minimum answer
                right = mid - 1;    // Try to find a smaller valid rate in the left half
            } else {
                left = mid + 1;     // 'mid' is too slow, increase rate by searching the right half
            }
        }

        return result;
    }
};

int main() {
    // Fast I/O optimization
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solver;

    // --- Example 1 ---
    std::vector<int> piles1 = {1, 4, 3, 2};
    int h1 = 9;
    int result1 = solver.minEatingSpeed(piles1, h1);
    std::cout << "Example 1 Output: " << result1 << " (Expected: 2)\n";

    // --- Example 2 ---
    std::vector<int> piles2 = {25, 10, 23, 4};
    int h2 = 4;
    int result2 = solver.minEatingSpeed(piles2, h2);
    std::cout << "Example 2 Output: " << result2 << " (Expected: 25)\n";

    return 0;
}
