/*
 * Approach 1: Standard index skipping
 *
 * Apporach 2: Group based 
 */
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

class Solution2 {
private:
    void backtrack(int i, int remainingTarget, const std::vector<int>& candidates,
                   std::vector<int>& current, std::vector<std::vector<int>>& result) {
        // Base Case 1: Target achieved
        if (remainingTarget == 0) {
            result.push_back(current);
            return;
        }

        // Base Case 2: Out of bounds
        if (i >= candidates.size()) {
            return;
        }

        // Pruning Step, since the array is sorted in assending order
        if (candidates[i] > remainingTarget) {
            return;
        }

        // 1. Count how many times this specific number duplicates sequentially
        int nextUniqueIndex = i + 1;
        while (nextUniqueIndex < candidates.size() && candidates[i] == candidates[nextUniqueIndex]) {
            nextUniqueIndex++;
        }   
        int duplicateCount = nextUniqueIndex - i;

        // 2. Branch 1: Choose to use 0 copies of this element group
        backtrack(nextUniqueIndex, remainingTarget, candidates, current, result);

        // 3. Branch 2: Try using 1 copy, 2 copies, ... up to duplicateCount copies
        int itemsPushed = 0;
        for (int count = 1; count <= duplicateCount; count++) {
            if (count * candidates[i] > remainingTarget) {
                break; // Prune early if adding more copies exceeds target
            }

            current.push_back(candidates[i]);
            itemsPushed++;

            // Recurse directly to the next unique index group
            backtrack(nextUniqueIndex, remainingTarget - (count * candidates[i]), candidates, current, result);
        }

        // 4. Backtrack/Clean up all copies added in this specific frame
        for (int count = 0; count < itemsPushed; count++) {
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;

        // Sorting is required to keep identical items contiguous
        std::sort(candidates.begin(), candidates.end());

        // Start recursion cleanly at index 0
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
    Solution2 solution;

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

