#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//
// 1. Compute the time to reach the desination for each car: time[i] = (target - pos[i])/speed[i]
// 2. Sort (pos[i], time[i]) in the descending order by position (closest to target first)   
//    We can allocate a fixed array with a size equal to target to make the sorting O(N).
// 3. Iterate (pos[i], time[i]) array from 0 to n-1
//      if (time[i] > current_fleet_time) {
//          fleets++;
//          current_fleet_time = time[i]
//      }
// Time complexity: O(N*logN)
// Space complexity: O(N)
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        if (n == 0) return 0;

        // Pair each car's position with its calculated arrival time
        vector<pair<int, double>> cars(n);
        for (int i = 0; i < n; ++i) {
            double time = static_cast<double>(target - position[i]) / speed[i];
            cars[i] = {position[i], time};
        }

        // Sort cars by position in descending order (closest to target first)
        sort(cars.begin(), cars.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
            return a.first > b.first;
        });

        int fleets = 0;
        double current_fleet_time = 0.0;

        // Iterate through the sorted cars
        for (int i = 0; i < n; ++i) {
            // If this car takes more time than the current fleet ahead,
            // it cannot catch up. It starts a new fleet.
            if (cars[i].second > current_fleet_time) {
                fleets++;
                current_fleet_time = cars[i].second; // Update the bottleneck time
            }
        }

        return fleets;
    }
};

// Driver program to test the solution
int main() {
    Solution solver;

    // Test Case 1
    int target1 = 10;
    vector<int> position1 = {1, 4};
    vector<int> speed1 = {3, 2};
    cout << "Test Case 1 Output: " << solver.carFleet(target1, position1, speed1) << " (Expected: 1)" << endl;

    // Test Case 2
    int target2 = 10;
    vector<int> position2 = {4, 1, 0, 7};
    vector<int> speed2 = {2, 2, 1, 1};
    cout << "Test Case 2 Output: " << solver.carFleet(target2, position2, speed2) << " (Expected: 3)" << endl;

    return 0;
}
