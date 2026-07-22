/*
Word Ladder

You are given two words, beginWord and endWord, and also a list of words
wordList. All of the given words are of the same length, consisting of
lowercase English letters, and are all distinct.

Your goal is to transform beginWord into endWord by following the rules:

You may transform beginWord to any word within wordList, provided that at
exactly one position the words have a different character, and the rest of the
positions have the same characters.  You may repeat the previous step with the
new word that you obtain, and you may do this as many times as needed.

Return the minimum number of words within the transformation sequence needed to
obtain the endWord, or 0 if no such sequence exists.

Example 1: Input: beginWord = "cat", endWord = "sag", wordList = ["bat","bag","sag","dag","dot"]
Output: 4
Explanation: The transformation sequence is "cat" -> "bat" -> "bag" -> "sag".

Example 2: Input: beginWord = "cat", endWord = "sag", wordList = ["bat","bag","sat","dag","dot"]
Output: 0
Explanation: There is no possible transformation sequence from "cat" to "sag" since the word "sag" is not in the wordList.

Constraints:
    1 <= beginWord.length <= 10
    1 <= wordList.length <= 100
*/

/*
Approach 1: Use BFS to find the shortest path from beginWord to endWord.
  (1) Store all the words in the word list in a hash table.
  (2) For the current word in BSF traversal, generate all possible neighboring
      word by muate one character each time. If the neighboring word 
      is in the word list (in hash table) then do DFS recursively.

Time Complexity: O(M * N) where M is the lenght of the word and N is the total
number of words. Note that for each word, we use 26*M operations to generate
the possible neighboring words, and each string copy/lookup takes O(M). 
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Transfer word list to a hash set for O(1) lookups
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        // If the endWord is not in the wordList, no valid transformation exists
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }
        
        // BFS Queue stores pairs of {current_word, current_path_length}
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        
        // Keep track of visited words to prevent infinite loops
        unordered_set<string> visited;
        visited.insert(beginWord);
        
        while (!q.empty()) {
            auto [word, level] = q.front();
            q.pop();
            
            // If we reached the target word, return the transformation count
            if (word == endWord) {
                return level;
            }
            
            // Try mutating every character of the current word
            for (int i = 0; i < word.length(); ++i) {
                char originalChar = word[i];
                
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == originalChar) continue;
                    
                    word[i] = c; // Mutate character
                    
                    // Check if this new word exists in our valid set and hasn't been visited
                    if (wordSet.find(word) != wordSet.end() && visited.find(word) == visited.end()) {
                        visited.insert(word);
                        q.push({word, level + 1});
                    }
                }
                
                word[i] = originalChar; // Revert mutation for the next index tracking
            }
        }
        
        return 0; // Return 0 if no transformation path connects to endWord
    }
};

// Driver program
int main() {
    Solution solver;

    // Test Example 1
    string beginWord1 = "hit";
    string endWord1 = "cog";
    vector<string> wordList1 = {"hot", "dot", "dog", "lot", "log", "cog"};
    cout << "Example 1 Output: " << solver.ladderLength(beginWord1, endWord1, wordList1) 
         << " (Expected: 5)" << endl;

    // Test Example 2
    string beginWord2 = "hit";
    string endWord2 = "cog";
    vector<string> wordList2 = {"hot", "dot", "dog", "lot", "log"};
    cout << "Example 2 Output: " << solver.ladderLength(beginWord2, endWord2, wordList2) 
         << " (Expected: 0)" << endl;

    return 0;
}

