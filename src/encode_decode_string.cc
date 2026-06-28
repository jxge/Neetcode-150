#include <string>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

class Solution {
public:
    // Encodes a list of strings into a single binary string.
    string encode(vector<string>& strs) {
        string encoded = "";
        
        for (const string& s : strs) {
            uint32_t len = s.length();
            
            // SAFE: Appends exactly 4 bytes of the integer, even if it contains '\0'
            encoded.append(reinterpret_cast<const char*>(&len), sizeof(len));
            
            // SAFE: Appends the string using its explicit length, ignoring internal '\0'
            encoded.append(s.data(), len);
        }
        
        return encoded;
    }

    // Decodes a single binary string back to a list of strings.
    vector<string> decode(string s) {
        vector<string> decoded;
        size_t i = 0;
        size_t n = s.length(); // SAFE: s.length() returns total bytes, not stopping at '\0'
        
        while (i < n) {
            // Read 4 bytes safely
            uint32_t len;
            memcpy(&len, &s[i], sizeof(len));
            i += sizeof(len);
            
            // SAFE: Constructing the string with explicit data pointer and length
            decoded.push_back(string(&s[i], len));
            i += len;
        }
        
        return decoded;
    }
};

// Driver code to prove it works with internal '\0' characters
int main() {
    Solution solution;

    // Create strings containing actual null characters in the middle
    string s1 = string("hello") + '\0' + "world"; // Length 11
    string s2 = string("abc") + '\0' + '\0' + "def"; // Length 8
    
    vector<string> original = {s1, s2, ""};
    
    string encoded = solution.encode(original);
    vector<string> decoded = solution.decode(encoded);
    
    // Verification
    cout << "Original total strings: " << original.size() << endl;
    cout << "Decoded total strings: " << decoded.size() << endl;
    cout << "String 1 lengths match: " << (s1.length() == decoded[0].length() ? "YES" : "NO") << endl;
    cout << "String 2 lengths match: " << (s2.length() == decoded[1].length() ? "YES" : "NO") << endl;
    cout << "Data matches perfectly: " << (original == decoded ? "YES" : "NO") << endl;

    return 0;
}
