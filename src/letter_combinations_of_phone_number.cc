/*
Solution 1: Backtracking with recursion

Solution 2: Iteratvie BFS
   res = {""};
   for each dig in the input digits
      map the digit to a list of characters
      for each string s in res
          replace s with a list of string s + 'c'  
         
Example :  res = {""}   input=34
  1. 3->def
     s = res.pop()="";
     res.push(""+"d")
     res.push(""+"e")
     res.push(""+"f")
  2. 4->ghi
     s1=res.pop()="d"
        res.push(s1+"g")
        res.push(s1+"h")
        res.push(s1+"i")
     s2=res.pop()="e"
        res.push(s2+"g")
        res.push(s2+"h")
        res.push(s2+"i")
     s3=res.pop()="f"
        res.push(s3+"g")
        res.push(s3+"h")
        res.push(s3+"i")
     res = ("dg", "dh", "di", "eg", "eh", "ei", "fg", "fh", "fi") 

Solution 3: Iterative BFS using vector instead of queue

Similar problem: The Letter Case Permutation problem (LeetCode 784):
change the case of characters in a given string to find all possible variations
  Input: s = "a1b2"
  Output: ["a1b2", "a1B2", "A1b2", "A1B2"]
*/


#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    // Mapping of digits to corresponding letters as on a phone keypad
    const vector<string> keypad = {
        "",     "",     "abc",  "def",  // 0, 1, 2, 3
        "ghi",  "jkl",  "mno",         // 4, 5, 6
        "pqrs", "tuv",  "wxyz"         // 7, 8, 9
    };

    void backtrack(const string& digits, int index, string& current, vector<string>& result) {
        // Base case: if the current combination is of the same length as digits
        if (index == digits.length()) {
            result.push_back(current);
            return;
        }

        // Get the letters that the current digit maps to
        string letters = keypad[digits[index] - '0'];
        
        // Loop through all letters for this digit
        for (char letter : letters) {
            current.push_back(letter);             // Choose
            backtrack(digits, index + 1, current, result); // Explore
            current.pop_back();                    // Unchoose (Backtrack)
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        
        // Edge case: if the input string is empty
        if (digits.empty()) {
            return result;
        }
        
        string current = "";
        backtrack(digits, 0, current, result);
        return result;
    }
};


class Solution2 {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        
        // Edge case: empty input
        if (digits.empty()) {
            return result;
        }

        // Keypad mapping
        const vector<string> keypad = {
            "",     "",     "abc",  "def",
            "ghi",  "jkl",  "mno",
            "pqrs", "tuv",  "wxyz"
        };

        // Queue to hold intermediate combinations
        queue<string> q;
        q.push("");

        // Process each digit in the input string
        for (char digit : digits) {
            string letters = keypad[digit - '0'];
            
            // Get the number of elements at the current level of the tree
            int count = q.size();
            
            // Expand all current paths with the new letters
            for (int i = 0; i < count; ++i) {
                string current = q.front();
                q.pop();
                
                for (char letter : letters) {
                    q.push(current + letter);
                }
            }
        }

        // Transfer all completed combinations from the queue to the results vector
        while (!q.empty()) {
            result.push_back(q.front());
            q.pop();
        }

        return result;
    }
};

class Solution3 {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return {};
        }

        const vector<string> keypad = {
            "",     "",     "abc",  "def",
            "ghi",  "jkl",  "mno",
            "pqrs", "tuv",  "wxyz"
        };

        // Calculate exact total combinations to pre-allocate memory
        size_t total_combinations = 1;
        for (char digit : digits) {
            total_combinations *= keypad[digit - '0'].length();
        }

        // Initialize result vector with an empty string and reserve full capacity
        vector<string> result = {""};
        result.reserve(total_combinations);

        // Iterative vector-based BFS
        for (char digit : digits) {
            string letters = keypad[digit - '0'];
            vector<string> next_level;
            next_level.reserve(result.size() * letters.length());

            // Expand each combination from the previous level
            for (const string& current : result) {
                for (char letter : letters) {
                    next_level.push_back(current + letter);
                }
            }
            // Move ownership of the memory instead of copying
            result = move(next_level);
        }

        return result;
    }
};

int main() {
    Solution solver;

    string digits = "23";
    vector<string> result = solver.header? solver.letterCombinations(digits) : solver.letterCombinations(digits);
    
    cout << "Input: \"" << digits << "\"\nOutput: [";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "\"" << result[i] << "\"";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]\n";

    return 0;
}

// Driver Program
int main() {
    Solution solver;

    // Test Case 1
    string digits1 = "34";
    vector<string> result1 = solver.letterCombinations(digits1);
    cout << "Input: \"" << digits1 << "\"\nOutput: [";
    for (size_t i = 0; i < result1.size(); ++i) {
        cout << "\"" << result1[i] << "\"";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]\n\n";

    // Test Case 2
    string digits2 = "";
    vector<string> result2 = solver.letterCombinations(digits2);
    cout << "Input: \"" << digits2 << "\"\nOutput: [";
    for (size_t i = 0; i < result2.size(); ++i) {
        cout << "\"" << result2[i] << "\"";
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]\n";

    return 0;
}

