// =============================================================================
// LONGEST TURBULENT SUBARRAY
// =============================================================================
// Problem: Find the longest turbulent subarray in an array.
//
// WHAT IS TURBULENT?
//   A subarray is turbulent if comparisons alternate between > and <:
//   - arr[0] > arr[1] < arr[2] > arr[3] < ...  OR
//   - arr[0] < arr[1] > arr[2] < arr[3] > ...
//
// EXAMPLES:
//   arr = [9,4,2,10,7,8,8,1,9]
//   Turbulent subarray: [4,2,10,7,8] (>, <, >, <) → length 5
//
//   arr = [4,8,12,16]
//   Not turbulent (all increasing) → length 2 (any pair)
//
//   arr = [100]
//   Single element → length 1
//
// TWO APPROACHES:
//   1. Two Counters (up/down) - O(n) time, O(1) space
//   2. Sign Comparison        - O(n) time, O(1) space
// =============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// APPROACH 1: TWO COUNTERS (up/down)
// =============================================================================
// TIME: O(n)  |  SPACE: O(1)
//
// KEY INSIGHT:
//   - `up` = length of turbulent subarray ENDING with an increase (arr[i-1] < arr[i])
//   - `down` = length of turbulent subarray ENDING with a decrease (arr[i-1] > arr[i])
//
// HOW IT WORKS:
//   When arr[i] > arr[i-1] (increase):
//     - Can EXTEND a previous decreasing sequence
//     - up = down + 1
//     - Reset down = 1 (current increase can't extend decrease)
//
//   When arr[i] < arr[i-1] (decrease):
//     - Can EXTEND a previous increasing sequence
//     - down = up + 1
//     - Reset up = 1 (current decrease can't extend increase)
//
//   When arr[i] == arr[i-1] (equal):
//     - Turbulence broken, reset both to 1
//
// VISUAL (arr = [9,4,2,10,7,8,8,1,9]):
//
//   Index:   0    1    2    3    4    5    6    7    8
//   Value:  [9]  [4]  [2]  [10] [7]  [8]  [8]  [1]  [9]
//            ↓    ↓    ↓    ↓    ↓    ↓    ↓    ↓    ↓
//   Comp:    -    <    <    >    <    >    =    <    >
//                  ↑    ↑    ↑    ↑    ↑    ↑    ↑    ↑
//              4<9  2<4  10>2  7<10  8>7  8=8  1<8  9>1
//
//   Step-by-step:
//   ┌───────┬─────────┬─────────┬─────────┬─────────┐
//   │  i    │  comp   │   up    │  down   │   ans   │
//   ├───────┼─────────┼─────────┼─────────┼─────────┤
//   │  0    │   -     │    1    │    1    │    1    │
//   │  1    │   <     │    1    │   2     │    2    │  down = up+1 = 2
//   │  2    │   <     │    1    │   2     │    2    │  same sign, down stays
//   │  3    │   >     │   3     │    1    │    3    │  up = down+1 = 3
//   │  4    │   <     │    1    │   4     │    4    │  down = up+1 = 4
//   │  5    │   >     │   5     │    1    │    5    │  up = down+1 = 5 ← MAX
//   │  6    │   =     │    1    │    1    │    5    │  reset
//   │  7    │   <     │    1    │   2     │    5    │
//   │  8    │   >     │   3     │    1    │    5    │
//   └───────┴─────────┴─────────┴─────────┴─────────┘
//
//   Answer = 5
// =============================================================================
class Solution1 {
public:
    int maxTurbulenceSize(vector<int>& arr) {

        int up = 1;    // Length ending with increase
        int down = 1;  // Length ending with decrease
        int ans = 1;   // Maximum length found

        for (int i = 1; i < arr.size(); i++) {

            if (arr[i] > arr[i - 1]) {
                // Increase: extend previous decreasing sequence
                up = down + 1;
                down = 1;  // Reset decrease counter
            }
            else if (arr[i] < arr[i - 1]) {
                // Decrease: extend previous increasing sequence
                down = up + 1;
                up = 1;    // Reset increase counter
            }
            else {
                // Equal: turbulence broken, reset both
                up = 1;
                down = 1;
            }

            ans = max(ans, max(up, down));
        }

        return ans;
    }
};

// =============================================================================
// APPROACH 2: SIGN COMPARISON
// =============================================================================
// TIME: O(n)  |  SPACE: O(1)
//
// KEY INSIGHT:
//   - Convert each comparison to a sign: +1 (increase), -1 (decrease), 0 (equal)
//   - Turbulence = alternating signs (+1, -1, +1, -1, ...)
//   - Track if current sign alternates with previous sign
//
// HOW IT WORKS:
//   curr = sign of (arr[i] - arr[i-1])
//   prev = sign of (arr[i-1] - arr[i-2])
//
//   If curr == 0:     → Equal, reset current = 1
//   If prev == 0:     → First comparison, extend current++
//   If curr != prev:  → Alternating! Extend current++
//   If curr == prev:  → Same sign twice, reset current = 2
//
// VISUAL (arr = [9,4,2,10,7,8,8,1,9]):
//
//   Index:   0    1    2    3    4    5    6    7    8
//   Value:  [9]  [4]  [2]  [10] [7]  [8]  [8]  [1]  [9]
//
//   Signs:      -1   -1   +1   -1   +1    0   -1   +1
//               ↓    ↓    ↓    ↓    ↓    ↓    ↓    ↓
//            4<9  2<4  10>2 7<10 8>7  8=8  1<8  9>1
//
//   Step-by-step:
//   ┌───────┬─────────┬─────────┬─────────┬─────────┬─────────┐
//   │  i    │  comp   │  curr   │  prev   │ current │   ans   │
//   ├───────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//   │  0    │    -    │    -    │    -    │    1    │    1    │
//   │  1    │    <    │   -1    │    0    │    2    │    2    │  prev=0, extend
//   │  2    │    <    │   -1    │   -1    │    2    │    2    │  same sign, reset to 2
//   │  3    │    >    │   +1    │   -1    │    3    │    3    │  alternate, extend
//   │  4    │    <    │   -1    │   +1    │    4    │    4    │  alternate, extend
//   │  5    │    >    │   +1    │   -1    │    5    │    5    │  alternate, extend ← MAX
//   │  6    │    =    │    0    │   +1    │    1    │    5    │  equal, reset
//   │  7    │    <    │   -1    │    0    │    2    │    5    │  prev=0, extend
//   │  8    │    >    │   +1    │   -1    │    3    │    5    │  alternate, extend
//   └───────┴─────────┴─────────┴─────────┴─────────┴─────────┘
//
//   Answer = 5
// =============================================================================
class Solution2 {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = arr.size();

        if (n == 1)
            return 1;

        int ans = 1;       // Maximum length found
        int current = 1;   // Current turbulent length
        int prev = 0;      // Previous comparison sign (0 = none)

        for (int i = 1; i < n; i++) {

            // Convert comparison to sign
            int curr;

            if (arr[i] > arr[i - 1])
                curr = 1;   // Increase
            else if (arr[i] < arr[i - 1])
                curr = -1;  // Decrease
            else
                curr = 0;   // Equal

            if (curr == 0) {
                // Equal elements break turbulence
                current = 1;
            }
            else if (prev == 0 || curr != prev) {
                // First comparison OR signs are alternating → extend
                current++;
            }
            else {
                // Same comparison sign appeared twice → reset to 2
                // (current pair forms a length-2 turbulent subarray)
                current = 2;
            }

            ans = max(ans, current);

            prev = curr;  // Update previous sign
        }

        return ans;
    }
};

// =============================================================================
// MAIN - Test both approaches
// =============================================================================
int main(){
    vector<int> arr = {9, 4, 2, 10, 7, 8, 8, 1, 9};

    /*
    EXAMPLE TRACE: arr = [9, 4, 2, 10, 7, 8, 8, 1, 9]
    
    Visual:
    Index:  0   1   2   3   4   5   6   7   8
    Value: [9] [4] [2] [10] [7] [8] [8] [1] [9]
            ↓   ↓   ↓   ↓   ↓   ↓   ↓   ↓   ↓
    
    Comparisons:
    9 > 4 → decrease
    4 > 2 → decrease (same sign, turbulence breaks)
    2 < 10 → increase
    10 > 7 → decrease
    7 < 8 → increase
    8 = 8 → equal (turbulence breaks)
    8 > 1 → decrease
    1 < 9 → increase
    
    Longest turbulent subarray: [4, 2, 10, 7, 8]
    Indices: 1 to 5
    Length: 5
    Pattern: > < > < (alternating)
    */

    Solution1 sol1;
    Solution2 sol2;

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl << endl;

    cout << "Approach 1 (Two Counters): " << sol1.maxTurbulenceSize(arr) << endl;
    cout << "Approach 2 (Sign Compare): " << sol2.maxTurbulenceSize(arr) << endl;

    return 0;
}