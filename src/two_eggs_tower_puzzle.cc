/*
You are given a building with 100 floors and two eggs. There exists a certain
floor, called the critical floor, such that an egg dropped from this floor or
any floor below it does not break, while an egg dropped from any floor above it
will break.

Consider the event of the first egg, there are 2 cases: break (B) or survives(S).

Dropping the first egg from a floor k.

    ------ (B) try k-1 times with the 2nd egg
      |____(S) _____ (B) try k-2 time with the 2nd egg
                 |___(S) ____ (B) try k-3 time with the 2nd egg
                                          |____ (S) .....     
1 + 2 + 3 + ... + k >= 100, k = 13.651


Approach 2: The DP Fomula
    Let D(e, f) be the minimum number of drops needed for e eggs and f floors.
        D(e, 0) = 0
        D(e, 1) = 1 (e > 0)
        D(1, f) = f
        D(e, f) = 1 + min (max(D(e-1, k-1), D(e, f-k))     1<=k<=f

Approach 3: The Flipped DP Formula
    let F(d,e) the maximum number of floors we can test using d drops and e egges
        F(0,e) = F(d,0) = 0
        F(d,e) = F(d-1, e-1)    // if the first egg breaks
               + F(d-1, e)      // if the first egg does not break
               + 1              // the current floor
    The frist egg must be drooped from the k'th floor:
        k = F(d-1, e-1) + 1

    F(d,e) = \sum _{i=1}^{e}{d \choose i}\)
    If the number of eggs is greater than or equal to the number of drops,
    the upper limit of the sum simply becomes d, making the formula equal to
    2^d - 1 (binary search).
*/

#include <iostream>
#include <vector>

void printFirstDropFloor(int targetFloors, int totalEggs) {
    if (targetFloors == 0) {
        std::cout << "0 floors means 0 drops required." << std::endl;
        return;
    }

    int maxDrops = targetFloors; 
    // dp[d][e] stores the maximum floors we can test with d drops and e eggs
    std::vector<std::vector<int>> dp(maxDrops + 1, std::vector<int>(totalEggs + 1, 0));
    
    int optimalDrops = 0;

    // Fill the DP matrix
    for (int drops = 1; drops <= maxDrops; ++drops) {
        for (int eggs = 1; eggs <= totalEggs; ++eggs) {
            dp[drops][eggs] = dp[drops - 1][eggs - 1] + dp[drops - 1][eggs] + 1;
        }
        
        // Stop as soon as we find the minimum drops needed to cover the building
        if (dp[drops][totalEggs] >= targetFloors) {
            optimalDrops = drops;
            break;
        }
    }

    // Calculate the first drop floor using the step transition math
    // If the egg breaks, we must be able to cover all floors below it using (optimalDrops - 1) and (totalEggs - 1)
    int firstDropFloor = dp[optimalDrops - 1][totalEggs - 1] + 1;

    std::cout << "Minimum drops needed: " << optimalDrops << std::endl;
    std::cout << "You should drop the first egg from floor: " << firstDropFloor << std::endl;
}

int main() {
    int floors = 100;
    int eggs = 2;
    
    printFirstDropFloor(floors, eggs);
              
    return 0;
}

