#include <iostream>
#include <vector>
#include <string>

/*
    case N = 2 
      * generate "(" when traversing down through the left node;
      * generate ")" when traversing down through the right node;
             

                                P(0,0)
                               /
                           P(1,0)
                         /      \
                    P(2,0)       P(1,1)
                       \         /
                       P(2,1)  P(2,1)
                        \           \
                       P(2,2)       P(2,2)
                        (())        ()()

    case N = 3
                                       P(0,0)
                                       /
                                   P(1,0)
                               /              \
                          P(2,0)               P(1,1)
                         /      \                /
                    P(3,0)     P(2,1)          P(2,1)
                      \         /    \         /    \
                    P(3,1)  P(3,1)  P(2,2)   P(3,1) P(2,2)
                      \       \        \      \       /
                    P(3,2)  P(3,2)  P(3,2)   P(3,2)  P(3,2)
                      \       \        \       \          \
                    P(3,3)  P(3,3)  P(3,3)    P(3,3)     P(3,3)
                    ((()))  (()())  (())()    ()(())     ()()()


  This is a Catalan problem: if S is a valid, well-formed paranthesis string, then it can be written
    S = (A)B    where A and B are valid well-formed paranthesis strings
    C(n) = sum C(k)*(n-k-1)  k=0...n-1   
*/

class Solution {
private:
    void backtrack(int openCount, int closeCount, int maxPairs, std::string& currentString, std::vector<std::string>& result) {
        // Base Case: If the current string reaches the target length (2 * n), 
        // we have constructed a perfectly balanced, well-formed combination.
        if (currentString.length() == maxPairs * 2) {
            result.push_back(currentString);
            return;
        }

        // Choice 1: Rule for adding an open parenthesis
        if (openCount < maxPairs) {
            currentString.push_back('(');
            backtrack(openCount + 1, closeCount, maxPairs, currentString, result);
            currentString.pop_back(); // Backtrack
        }

        // Choice 2: Rule for adding a closed parenthesis
        if (closeCount < openCount) {
            currentString.push_back(')');
            backtrack(openCount, closeCount + 1, maxPairs, currentString, result);
            currentString.pop_back(); // Backtrack
        }
    }

public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        std::string currentString = "";
        
        // Start the recursive branching with 0 open and 0 closed brackets
        backtrack(0, 0, n, currentString, result);
        return result;
    }
};

// Helper function to print results cleanly
void printResult(const std::vector<std::string>& result) {
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "\"" << result[i] << "\"";
        if (i + 1 < result.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Driver Program
int main() {
    Solution solution;

    // Example 1
    int n1 = 1;
    std::cout << "Example 1 (n = 1) Output:\n";
    printResult(solution.generateParenthesis(n1));
    
    std::cout << "\n";

    // Example 2
    int n2 = 3;
    std::cout << "Example 2 (n = 3) Output:\n";
    printResult(solution.generateParenthesis(n2));

    return 0;
}

