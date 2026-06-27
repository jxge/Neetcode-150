#include <vector>
#include <unordered_set>

class Solution1 {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        std::unordered_set<int> seen;
        seen.reserve(nums.size());  // worse case (all number are different) you need nums.size
        
        for (int num : nums) {
            if (seen.count(num)) {
                return true;
            }
            seen.insert(num);
        }
        
        return false;
    }
};

class Solution2 {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        std::unordered_set<int> seen;
        seen.reserve(nums.size());  // worse case (all number are different) you need nums.size
        
        for (int num : nums) {
            auto [_, created] = seen.insert(num);
            if (!created) {
                return true;
            }
        }
        
        return false;
    }
};
