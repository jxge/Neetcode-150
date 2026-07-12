#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
private:
    void backtrack(int startIndex, int remainingTarget, const std::vector<int>& candidates,
                   std::vector<int>& current, std::vector<std::vector<int>>& result) {
        // Base Case: If the target is met, record the unique combination
        if (remainingTarget == 0) {
            result.push_back(current);
            return;
        }

        for (int i = startIndex; i < candidates.size(); ++i) {
            // Pruning Step: Since candidates are sorted, if the current element is 
            // larger than the remaining target, no future elements will fit either.
            if (candidates[i] > remainingTarget) {
                break;
            }

            // Duplicate skipping: Skip identical elements *within the same recursive layer*
            if (i > startIndex && candidates[i] == candidates[i - 1]) {
                continue;
            }

            // Action: Include the candidate
            current.push_back(candidates[i]);

            // Recurse: Move to 'i + 1' because each element can only be used once
            backtrack(i + 1, remainingTarget - candidates[i], candidates, current, result);

            // Backtrack: Remove the element to try other options
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;

        // 1. Sort the array to place duplicates next to each other and allow pruning
        std::sort(candidates.begin(), candidates.end());

        // 2. Start backtracking from index 0
        backtrack(0, target, candidates, current, result);
        return result;
    }
};

// Helper function to print combinations clearly
void printResult(const std::vector<std::vector<int>>& result) {
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j];
            if (j + 1 < result[i].size()) std::cout << ",";
        }
        std::cout << "]";
        if (i + 1 < result.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Driver Program
int main() {
    Solution solution;

    // Example 1
    std::vector<int> candidates1 = {9, 2, 2, 4, 6, 1, 5};
    int target1 = 8;
    std::cout << "Example 1 Output:" << std::endl;
    std::vector<std::vector<int>> res1 = solution.combinationSum2(candidates1, target1);
    printResult(res1);
    
    std::cout << std::endl;

    // Example 2
    std::vector<int> candidates2 = {1, 2, 3, 4, 5};
    int target2 = 7;
    std::cout << "Example 2 Output:" << std::endl;
    std::vector<std::vector<int>> res2 = solution.combinationSum2(candidates2, target2);
    printResult(res2);

    return 0;
}

