#include <iostream>
#include <vector>
#include <algorithm>
#include <span>

// Time: O(n * log(m)), where n is the number of piles, and m is the maximal number of bananas in each pile
// The minimum possible eating rate is 1 banana/hour, and the maximum possible eating rate is m.
// Possible improvements:
//   1. minimum possible rate = ceiling(total bananas / h)
//   2. Frequency compression: compress duplicates into {pile_size, frequency} pairs.
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


#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

class Solution2 {
public:
    [[nodiscard]] int minEatingSpeed(const std::vector<int>& piles, int h) const noexcept {
        long long total_bananas = 0;
        int max_pile = 0;

        // Step 1: Track frequencies of pile sizes using a bucket approach
        // Given constraints (piles.length <= 1,000), a frequency array reduces 
        // the check loop size from 'n' down to unique elements.
        for (const int pile : piles) {
            total_bananas += pile;
            if (pile > max_pile) {
                max_pile = pile;
            }
        }

        // Step 2: Establish a tight mathematical lower bound
        // Koko cannot eat faster than max_pile, and mathematically cannot eat 
        // slower than (total_bananas / h) rounded up.
        int left = static_cast<int>((total_bananas + h - 1) / h);
        if (left == 0) left = 1;
        
        int right = max_pile;
        int result = right;

        // Pre-count frequencies of each pile size to compress the search footprint
        // Using a sorted unique list allows us to treat duplicate piles instantly
        std::vector<int> unique_piles = piles;
        std::sort(unique_piles.begin(), unique_piles.end());

        // Create pairs of {pile_size, frequency}
        std::vector<std::pair<int, int>> compressed_piles;
        for (size_t i = 0; i < unique_piles.size();) {
            size_t j = i;
            while (j < unique_piles.size() && unique_piles[j] == unique_piles[i]) {
                j++;
            }
            compressed_piles.emplace_back(unique_piles[i], static_cast<int>(j - i));
            i = j;
        }

        // Step 3: Binary search over the narrowed search space
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            long long hours_needed = 0;
            bool valid = true;

            for (const auto& [pile_size, count] : compressed_piles) {
                hours_needed += static_cast<long long>((pile_size + mid - 1) / mid) * count;
                if (hours_needed > h) {
                    valid = false;
                    break; // Early exit optimization
                }
            }

            if (valid) {
                result = mid;
                right = mid - 1; // Try slower speed
            } else {
                left = mid + 1;  // Must go faster
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
