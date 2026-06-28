#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;


/*
 * Solution 1: O(N)
 */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {       
        // CRITICAL: Reserve space ahead of time to avoid rehashing overhead
        unordered_set<int> numSet;
        numSet.reserve(nums.size()); 
        numSet.insert(nums.begin(), nums.end());
        
        int longestStreak = 0;
        
        for (int num : numSet) {
            if (numSet.find(num - 1) == numSet.end()) {
                int currentNum = num;
                int currentStreak = 1;
                
                while (numSet.find(currentNum + 1) != numSet.end()) {
                    currentNum += 1;
                    currentStreak += 1;
                }
                
                longestStreak = max(longestStreak, currentStreak);
            }
        }
        
        return longestStreak;
    }
};

/*
 * Solution 2: O(N log(N))
 */
#include <vector>
#include <algorithm>

class Solution2 {
public:
    int longestConsecutive(vector<int>& nums) {
        // Boost C++ input/output operations for speed
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        if (nums.empty()) return 0;
        
        // Fast, cache-friendly sorting
        sort(nums.begin(), nums.end());
        
        int longestStreak = 1;
        int currentStreak = 1;
        
        for (size_t i = 1; i < nums.size(); ++i) {
            // If it's a duplicate, skip it (doesn't break the chain)
            if (nums[i] == nums[i - 1]) {
                continue;
            }
            // If it is consecutive, extend the streak
            if (nums[i] == nums[i - 1] + 1) {
                currentStreak++;
            } else {
                // Chain is broken; update max and reset
                longestStreak = max(longestStreak, currentStreak);
                currentStreak = 1;
            }
        }
        
        return max(longestStreak, currentStreak);
    }
};

