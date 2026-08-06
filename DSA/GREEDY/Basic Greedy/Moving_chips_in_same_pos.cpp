#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
? PROBLEM: Minimum Cost to Move Chips to The Same Position (LeetCode 1217)
?
? You have n chips, where the i-th chip is at position[i].
? You need to bring ALL chips to the SAME position (any position).
?
? Moving rules:
?   - Move a chip by 2 positions (left or right) → cost = 0
?   - Move a chip by 1 position (left or right) → cost = 1
?
? You can move chips independently and in any order.
? Return the minimum total cost to bring all chips to one position.
?
? EXAMPLE:
?   position = [1, 2, 3]
?   Chip at 1 (odd), 2 (even), 3 (odd)
?   Target = 1 (odd): cost = chip at 2 moves by 1 (cost 1) + chip at 3 moves by 2 (cost 0) = 1
?   Target = 2 (even): cost = chip at 1 moves by 1 (cost 1) + chip at 3 moves by 1 (cost 1) = 2
?   Minimum = 1
?
?
? INTUITION:
?   Moving by 2 is FREE → a chip at an even index can reach ANY even index at zero cost.
?   Similarly, a chip at an odd index can reach ANY odd index at zero cost.
?   The only time you pay is when you need to change parity (even ↔ odd), which costs 1.
?
?   So the problem reduces to:
?     "Pick a target position (even or odd). All chips of the other parity must
?      move by 1 (cost 1 each). Chips of the same parity move for free."
?
?   To minimize cost, pick the parity with FEWER chips and move them to the
?   other parity. Hence → min(evenCount, oddCount).
?
?   This is greedy because the optimal choice at the parity level is locally
?   obvious (move the minority group), and it's globally optimal.
*/

class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        int evenCount = 0;  // chips on even positions
        int oddCount  = 0;  // chips on odd positions

        // Count chips by parity
        for (int pos : position) {
            if (pos % 2 == 0) {
                evenCount++;
            } else {
                oddCount++;
            }
        }

        // Move the smaller group to the larger group's parity
        // Each chip in the smaller group costs 1 (one odd↔even move)
        return std::min(oddCount, evenCount);
    }
};

int main() {
    return 0;
}

