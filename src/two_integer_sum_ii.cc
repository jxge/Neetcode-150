#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        
        while (left < right) {
            int currentSum = numbers[left] + numbers[right];
            
            if (currentSum == target) {
                // Return 1-based indices
                return {left + 1, right + 1};
            } else if (currentSum < target) {
                left++; // Need a larger sum
            } else {
                right--; // Need a smaller sum
            }
        }
        
        return {}; // Fallback
    }
};

// Helper function to print vectors
void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Driver Code
int main() {
    Solution solver;
    
    // Test Case 1: Standard case from problem description
    vector<int> numbers1 = {1, 2, 3, 4};
    int target1 = 3;
    vector<int> result1 = solver.twoSum(numbers1, target1);
    
    cout << "Test Case 1:\nInput: numbers = ";
    printVector(numbers1);
    cout << ", target = " << target1 << "\nOutput: ";
    printVector(result1);
    cout << "\n\n";

    // Test Case 2: Array containing negative numbers
    vector<int> numbers2 = {-5, -2, 1, 4, 9};
    int target2 = -1;
    vector<int> result2 = solver.twoSum(numbers2, target2);
    
    cout << "Test Case 2:\nInput: numbers = ";
    printVector(numbers2);
    cout << ", target = " << target2 << "\nOutput: ";
    printVector(result2);
    cout << "\n\n";

    // Test Case 3: Target is made from the extreme ends
    vector<int> numbers3 = {2, 7, 11, 15};
    int target3 = 17;
    vector<int> result3 = solver.twoSum(numbers3, target3);
    
    cout << "Test Case 3:\nInput: numbers = ";
    printVector(numbers3);
    cout << ", target = " << target3 << "\nOutput: ";
    printVector(result3);
    cout << "\n";

    return 0;
}
