#include <iostream>
#include <vector>


// Time: O(log (m*n))

// Flatten the 2D matrix into 1D array:
//    (i,j) <-> k = i * n + j      or   i = k / n, j = k % n
//
class Solution {
public:
    [[nodiscard]] bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) const noexcept {
        if (matrix.empty() || matrix[0].empty()) return false;
        
        if (target < matrix.front().front() || target > matrix.back().back()) return false;

        const int m = static_cast<int>(matrix.size());
        const int n = static_cast<int>(matrix[0].size());

        int left = 0;
        int right = (m * n) - 1;

        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            
            // Map the 1D index back to 2D matrix coordinates
            int row = mid / n;
            int col = mid % n;
            int mid_val = matrix[row][col];

            if (mid_val == target) {
                return true;
            }

            left = (mid_val < target) ? mid + 1 : left;
            right = (mid_val > target) ? mid - 1 : right;
        }

        return false;
    }
};

int main() {
    // Fast I/O configuration
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solver;

    // Test Case Matrix
    std::vector<std::vector<int>> matrix = {
        {1,  2,  4,  8},
        {10, 11, 12, 13},
        {14, 20, 30, 40}
    };

    // --- Example 1 ---
    int target1 = 10;
    // Compiling with a boolean result to satisfy [[nodiscard]]
    bool result1 = solver.searchMatrix(matrix, target1);
    std::cout << "Example 1 (Target " << target1 << "):\n";
    std::cout << "Output: " << (result1 ? "true" : "false") << " (Expected: true)\n\n";

    // --- Example 2 ---
    int target2 = 15;
    bool result2 = solver.searchMatrix(matrix, target2);
    std::cout << "Example 2 (Target " << target2 << "):\n";
    std::cout << "Output: " << (result2 ? "true" : "false") << " (Expected: false)\n\n";

    // --- Edge Case: Out of absolute bounds ---
    int target3 = 50;
    bool result3 = solver.searchMatrix(matrix, target3);
    std::cout << "Edge Case (Target " << target3 << "):\n";
    std::cout << "Output: " << (result3 ? "true" : "false") << " (Expected: false)\n";

    return 0;
}
