#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Stack based Algorithm:  Time: O(N), Space: O(N)
// The daily temperatures problem is solved optimally using a Monotonic Decreasing Stack to track 
// indices of days whose next warmer day has not yet been found.
//
// Suffix based Algorith:  Time: O(N), Space: O(N)   --> slightly more efficient
// Compute R[i] based on temperature[i] and R[j], where j=i+1, ... N-1
//     j=i+1
//     while (j < n) {
//         if (temperature[i] < temperature[j]) {
//             result[i] = j - i; break;    // found
//         }
//         else if (result[j] == 0) {
//             result[i] = 0; break;   // not found
//         }
//         else {
//             j += result[j]; // day j is cooler, jump to the day that is warmer than day j.
//         }
//    }
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        // Initialize the result vector with 0s as the default fallback
        vector<int> result(n, 0);
        stack<int> s; // Monotonic decreasing stack storing indices

        for (int i = 0; i < n; ++i) {
            // While the current day's temperature is warmer than the day on top of the stack
            while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
                int prev_day_index = s.top();
                s.pop();
                // Distance to the next warmer day
                result[prev_day_index] = i - prev_day_index;
            }
            // Push current day index onto the stack
            s.push(i);
        }

        return result;
    }
};

class Solution2 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0); // Serves as both our output and our jump table

        // Traverse backwards from the second-to-last element
        for (int i = n - 2; i >= 0; --i) {
            int j = i + 1;

            while (j < n) {
                if (temperatures[j] > temperatures[i]) {
                    result[i] = j - i;
                    break;
                } else if (result[j] == 0) {
                    // If day j has no warmer day in its future, day i won't either
                    result[i] = 0;
                    break;
                } else {
                    // Efficiently jump to day j's next warmer day
                    j += result[j];
                }
            }
        }

        return result;
    }
};

// Driver program to test the solution
int main() {
    Solution solver;

    // Test Case 1
    vector<int> temps1 = {30, 38, 30, 36, 35, 40, 28};
    vector<int> res1 = solver.dailyTemperatures(temps1);
    
    cout << "Test Case 1 Output: [";
    for (size_t i = 0; i < res1.size(); ++i) {
        cout << res1[i] << (i == res1.size() - 1 ? "" : ",");
    }
    cout << "] (Expected: [1,4,1,2,1,0,0])" << endl;

    // Test Case 2
    vector<int> temps2 = {22, 21, 20};
    vector<int> res2 = solver.dailyTemperatures(temps2);

    cout << "Test Case 2 Output: [";
    for (size_t i = 0; i < res2.size(); ++i) {
        cout << res2[i] << (i == res2.size() - 1 ? "" : ",");
    }
    cout << "] (Expected: [0,0,0])" << endl;

    return 0;
}
