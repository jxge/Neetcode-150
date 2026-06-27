class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // Hash map to store sorted string signature -> list of original strings
        unordered_map<string, vector<string>> anagramGroups;
        
        for (const string& s : strs) {
            string key = s;
            sort(key.begin(), key.end()); // Sorting creates a uniform signature
            anagramGroups[key].push_back(s);
        }
        
        // Collect all grouped sublists into the final result
        vector<vector<string>> result;
        result.reserve(anagramGroups.size());
        for (auto& pair : anagramGroups) {
            result.push_back(move(pair.second));
        }
        
        return result;
    }
};

// Input: strs = ["act","pots","tops","cat","stop","hat"]
// map:   { a#1c#1t1 -> act, a#1c#1#t#1 -> cat
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramGroups;
        
        for (const string& s : strs) {
            int count[26] = {0};
            for (char c : s) {
                count[c - 'a']++;
            }
            
            string key = "";
            for (int i = 0; i < 26; ++i) {
                if (count[i] == 1) {
                    // Just append the character
                    key += (char)('a' + i);
                } else if (count[i] > 1) {
                    // Append character, delimiter, and count for duplicates
                    key += (char)('a' + i);
                    key += '#';
                    key += to_string(count[i]);
                }
            }
            
            anagramGroups[key].push_back(s);
        }
        
        vector<vector<string>> result;
        result.reserve(anagramGroups.size());
        for (auto& pair : anagramGroups) {
            result.push_back(move(pair.second));
        }
        
        return result;
    }
};

