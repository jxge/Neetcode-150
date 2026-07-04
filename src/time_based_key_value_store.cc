#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

class TimeMap {
private:
    // Structure to hold our data cleanly
    struct TimeValue {
        int timestamp;
        std::string value;
        
        // Custom operator for binary searching against an integer timestamp
        bool operator<(int ts) const noexcept {
            return timestamp < ts;
        }
    };

    // Hash map grouping data vectors by their string keys
    std::unordered_map<std::string, std::vector<TimeValue>> cache;

public:
    TimeMap() {
        // Optimization: Pre-reserve hash bucket capacity if needed
    }
    
    void set(std::string key, std::string value, int timestamp) {
        // Appends to the vector. Since input timestamps increase strictly,
        // the underlying vector remains perfectly sorted.
        cache[key].push_back({timestamp, std::move(value)});
    }
    
    [[nodiscard]] std::string get(const std::string& key, int timestamp) const {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return ""; // Key does not exist
        }

        const auto& history = it->second;

        // upper_bound finds the first element GREATER than the given timestamp.
        auto bound = std::upper_bound(history.begin(), history.end(), timestamp);

        // If upper_bound points to the beginning, it means all stored 
        // timestamps are strictly greater than the requested timestamp.
        if (bound == history.begin()) {
            return "";
        }

        // Step back by one element to get the largest timestamp_prev <= timestamp
        return std::prev(bound)->value;
    }
};

int main() {
    // Fast I/O optimization
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TimeMap timeMap;
    
    // Simulating Example 1
    timeMap.set("alice", "happy", 1);
    
    std::cout << "get(\"alice\", 1): " << timeMap.get("alice", 1) << " (Expected: happy)\n";
    std::cout << "get(\"alice\", 2): " << timeMap.get("alice", 2) << " (Expected: happy)\n";
    
    timeMap.set("alice", "sad", 3);
    
    std::cout << "get(\"alice\", 3): " << timeMap.get("alice", 3) << " (Expected: sad)\n";
    std::cout << "get(\"alice\", 0): \"" << timeMap.get("alice", 0) << "\" (Expected: \"\")\n";

    return 0;
}
