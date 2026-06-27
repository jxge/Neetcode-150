class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Hash map to store the value and its index
        unordered_map<int, int> seen;
        
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            
            // Check if the complement already exists in the map
            if (seen.find(complement) != seen.end()) {
                // Return the smaller index first
                return {seen[complement], i};
            }
            
            // Store the current number and its index in the map
            seen[nums[i]] = i;
        }
        
        return {}; // Return empty vector if no solution is found (per constraints, this won't happen)
    }
};
