/*******************************************************************************
Solution 2: Count the minimal cycles needed (formula)
Time complexity: O(N) where N is the total number of tasks

1. For the first task with the most frequency, you need (max_freq-1)*(n+1) cycles.
   Consider AAA and n=2,   A**A**A, you need (3-1)*3+1=7 cycles
2. For other tasks with frequency max_freq, one extra cycle will be needed.
   Consider AAABBB and n=2, A**A**A needs 7 cycles, AB*AB*AB*AB needs 8 cycles
3. When the last idle cycle is filled, the min_cycles equals the number of 
   tasks processed. After that min_cycles <= total number of task processed
4. The final max(min_cycles, tasks.size()) should return the minimal cycles
   truely needed.

Solution 2: Count idle cycles
Time complexity: O(N) where N is the total number of tasks

  1. Find the bottleneck: identify the maximum frequency (max_freq).
     The task with this frequency dictates the structrual layout since
     it requres the most idle cycles.
  2. Placing the task with max_freq frequency will create max_freq-1 chunks.
     Each chunk contains n empty idle cycle. Total idle cycles = (max_freq-1)*n
     Consider AAA and n=2,   A**A**A, you will have (3-1)*2=4 idle cycle.
  3. For the remaining tasks[i], each can fill at most min(max_freq-1,freq[i])
     When the idle time is 0, then the minimum cycle will match the total
     number of tasks.

Solution 3: improvement of Solution2 by removing std::sort
*******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution1 {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // Step 1: Count the frequency of each task
        vector<int> frequencies(26, 0);
        for (char task : tasks) {
            frequencies[task - 'A']++;
        }

        // Step 2: Sort frequencies to easily find the maximum frequency
        sort(frequencies.begin(), frequencies.end());

        // Max frequency value
        int max_freq = frequencies[25];

        // Step 3: Calculate the minimum execution time required based on max_freq
        // The most frequent task creates chunks of size (n + 1)
        int min_cycles = (max_freq - 1) * (n + 1) + 1;

        // Step 4: Add the number of tasks that share this same maximum frequency
        for (int i = 24; i >= 0; i--) {
            if (frequencies[i] == max_freq) {
                min_cycles++;
            } else {
                break; // Since it's sorted, no more tasks will have max_freq
            }
        }

        // Step 5: The answer is at least the number of total tasks
        return max(min_cycles, static_cast<int>(tasks.size()));
    }
};

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n) {
        // Step 1: Count the frequency of each task
        std::vector<int> frequencies(26, 0);
        for (char task : tasks) {
            frequencies[task - 'A']++;
        }

        // Step 2: Sort frequencies to find the maximum frequency
        std::sort(frequencies.begin(), frequencies.end());
        int max_freq = frequencies[25]; // FIXED: Added missing [25] index

        // Step 3: Calculate the maximum possible idle slots
        int max_idle_slots = (max_freq - 1) * n;

        // Step 4: Reduce idle slots using the remaining tasks
        for (int i = 24; i >= 0 && frequencies[i] > 0; i--) {
            // Subtract first
            max_idle_slots -= std::min(max_freq - 1, frequencies[i]);

            // If the subtraction filled or over-allocated all slots, reset and exit
            if (max_idle_slots <= 0) {
                max_idle_slots = 0;
                break;
            }
        }

        // Step 5: Total execution time is total tasks + remaining idle slots
        return tasks.size() + max_idle_slots;
    }
};


class Solution3 {
public:
    int leastInterval(std::vector<char>& tasks, int n) {
        std::vector<int> frequencies(26, 0);
        int max_freq = 0;
        int max_freq_count = 0;

        // Combined Step 1 & 2: Process tasks, track frequencies, and find max stats on the fly
        for (char task : tasks) {
            int idx = task - 'A';
            frequencies[idx]++;
            
            // Check if this updated frequency matches or beats our current maximum
            if (frequencies[idx] > max_freq) {
                max_freq = frequencies[idx];
                max_freq_count = 1; // Reset count: we have a new lone king
            } else if (frequencies[idx] == max_freq) {
                max_freq_count++;   // Found another task that ties the current peak
            }
        }

        // Step 3: Compute total blocks using the direct formula
        int min_cycles = (max_freq - 1) * (n + 1) + max_freq_count;

        // Step 4: Safely clamp to total task size if tasks overflow the spaces
        return std::max(min_cycles, static_cast<int>(tasks.size()));
    }
};

// Driver Program
int main() {
    Solution1 sol1;
    Solution2 sol2;

    // Test Case 1
    vector<char> tasks1 = {'X', 'X', 'Y', 'Y'};
    int n1 = 2;
    cout << "Test Case 1 - Expected: 5, Result: " << sol1.leastInterval(tasks1, n1) << endl;
    cout << "Test Case 1 - Expected: 5, Result: " << sol2.leastInterval(tasks1, n1) << endl;

    // Test Case 2
    vector<char> tasks2 = {'A', 'A', 'A', 'B', 'C'};
    int n2 = 3;
    cout << "Test Case 2 - Expected: 9, Result: " << sol1.leastInterval(tasks2, n2) << endl;
    cout << "Test Case 2 - Expected: 9, Result: " << sol2.leastInterval(tasks2, n2) << endl;

    // Test Case 3 (Edge case where tasks length is greater than formula layout)
    vector<char> tasks3 = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n3 = 0;
    cout << "Test Case 3 - Expected: 6, Result: " << sol1.leastInterval(tasks3, n3) << endl;
    cout << "Test Case 3 - Expected: 6, Result: " << sol2.leastInterval(tasks3, n3) << endl;

    // Test Case 3 (Edge case where tasks length is greater than formula layout)
    vector<char> tasks4 = {'A', 'A', 'A', 'B', 'B', 'B', 'C', 'C', 'C', 'D', 'D', 'E', 'E'};
    int n4 = 2;
    cout << "Test Case 4 - Expected: 6, Result: " << sol1.leastInterval(tasks4, n4) << endl;
    cout << "Test Case 4 - Expected: 6, Result: " << sol2.leastInterval(tasks4, n4) << endl;
    return 0;
}

