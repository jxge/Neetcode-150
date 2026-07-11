/*******************************************************************************
The minimum number of CPU cycles required to complete all tasks can be calculated
efficiently using a greedy approach based on the maximum frequency of any task.

  offset = 0;
  Sort the tasks based on the frequency from high to low.
  for each (freq, task) in the sorted list {
     for (i = 0; i < freq; i++)
       result[i * n + offset] = task;
     offset++;
  }

Time Complexity: O(M), where M is the total number of tasks in the array. 
Space Complexity: O(1)
*******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
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
        return max(min_cycles, static_cast<int>(tasks.length()));
    }
};

// Driver Program
int main() {
    Solution solution;

    // Test Case 1
    vector<char> tasks1 = {'X', 'X', 'Y', 'Y'};
    int n1 = 2;
    cout << "Test Case 1 - Expected: 5, Result: " << solution.leastInterval(tasks1, n1) << endl;

    // Test Case 2
    vector<char> tasks2 = {'A', 'A', 'A', 'B', 'C'};
    int n2 = 3;
    cout << "Test Case 2 - Expected: 9, Result: " << solution.leastInterval(tasks2, n2) << endl;

    // Test Case 3 (Edge case where tasks length is greater than formula layout)
    vector<char> tasks3 = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n3 = 0;
    cout << "Test Case 3 - Expected: 6, Result: " << solution.leastInterval(tasks3, n3) << endl;

    return 0;
}

