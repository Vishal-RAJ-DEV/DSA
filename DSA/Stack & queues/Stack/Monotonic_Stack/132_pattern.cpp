#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// SOLUTION 1 : STACK (Monotonic Stack) — O(n) time, O(n) space
// ============================================================================
//
// PROBLEM : Find any triple (i, j, k) with  i < j < k  such that
//
//              nums[i] < nums[k] < nums[j]      (the "132" pattern)
//
// Example : nums = [3, 1, 4, 2]
//
//            1 < 2 < 4
//
//            nums[i]=1   nums[k]=2   nums[j]=4
//
// ============================================================================
//
// THE CORE IDEA — every variable has one job :
//
//      stack  ----------> possible "3"   (largest  / nums[j])
//      second ----------> possible "2"   (middle  / nums[k])
//      nums[i] ---------> possible "1"   (smallest / nums[i])
//
// Invariant we are always trying to build :
//
//      current       second        stack
//         ↓             ↓             ↓
//         1      <      2      <      3
//
// ============================================================================
//
// WHY SCAN FROM RIGHT → LEFT ?
//
// Everything already inside  stack / second  is located to the RIGHT
// of the current nums[i].
//
// So the moment we find  nums[i] < second,  the indices are
// automatically ordered :
//
//        i        j        k
//        ↓        ↓        ↓
//      [1] ...  [4] ...  [2]
//
// i.e.  i < j < k  is guaranteed for free.
// That is the ONLY reason the scan is right → left.
//
// ============================================================================
//
// WHY POP() ?
//
// Step-by-step on  nums = [3, 1, 4, 2] :
//
//   start : second = INT_MIN , stack = []
//
//   i=3 → 2 :
//     2 < second ?  no
//     stack empty → nothing to pop
//     push 2            →  stack = [2]
//
//   i=2 → 4 :
//     4 < second ?  no
//     4 > st.top()(2) ?  YES → POP :  second = 2 , stack = []
//     4 > top ?  no → stop
//     push 4            →  stack = [4]
//
//     state :
//                   4            second = 2
//                   ↑            stack  = [4]
//                  "3"
//                   ↓
//                   2
//                   ↑
//                  "2"
//
//   i=1 → 1 :
//     1 < second(2) ?  YES → 1 < 2 < 4  →  132 found ✓
//
// ============================================================================
//
// WHY DOES THE POP LOOP GIVE THE BEST "2" ?
//
//      while (!st.empty() && nums[i] > st.top()) {
//          second = st.top();
//          st.pop();
//      }
//
// "Every stack value smaller than my current value can become the 2,
//  because the current value can act as the 3."
//
// Example : stack = [10, 7, 4, 2]   (top = 2) , current = 8
//
//     8 > 2 → pop, second = 2
//     8 > 4 → pop, second = 4
//     8 > 7 → pop, second = 7
//     8 > 10 → stop
//
// The LAST / LARGEST popped value wins :  second = 7
// Now we know  7 < 8   (i.e. 2 < 3 exists).
// A bigger "2" is better — it gives the left side more chances :
//
//     5 < 7 < 8    ✓  found        (but 5 < 4 < 8 would be impossible)
//
// After the loop we push 8, so the stack always stays DECREASING
// (bottom → top) and each pushed value becomes a new candidate "3".
//
// ============================================================================
//
// MENTAL PICTURE TO REMEMBER :
//
//                RIGHT → LEFT  scan
//                     ←
//
//       current          second          stack
//          ↓               ↓               ↓
//       possible 1      possible 2      possible 3
//
//          1        <       2        <       3
//          │                │                │
//          └────────────────┴────────────────┘
//                         132
//
// stack finds the 3 → popping creates the 2 → nums[i] becomes the 1
//
// ============================================================================

class Solution {
public:
    bool find132pattern(vector<int>& nums) {

        int n = nums.size();

        if (n < 3)
            return false;

        // "second" represents the 2 in 132
        int second = INT_MIN;

        // Stack stores possible 3 values
        stack<int> st;

        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--) {

            // nums[i] can be the "1"
            //
            // If nums[i] < second,
            // then we have:
            //
            // nums[i] < second < some stack value
            //
            // which forms 132.
            if (nums[i] < second) {
                return true;
            }

            // Find a bigger value that can act as "3"
            //
            // Every popped value can become "2"
            while (!st.empty() && nums[i] > st.top()) {

                second = st.top();

                st.pop();
            }

            // Current value becomes a possible "3"
            st.push(nums[i]);
        }

        return false;
    }
};


class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();

        if (n < 3)
            return false;

        int leftMin = nums[0];

        set<int> right;

        // Initially all elements except nums[0]
        for (int i = 1; i < n; i++) {
            right.insert(nums[i]);
        }

        for (int j = 1; j < n - 1; j++) {

            // Remove nums[j]
            // because k must be AFTER j
            right.erase(right.find(nums[j]));

            // Find smallest number > leftMin
            auto it = right.upper_bound(leftMin);

            if (it != right.end() && *it < nums[j]) {
                return true;
            }

            leftMin = min(leftMin, nums[j]);
        }

        return false;
    }
};

class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {

                    if (nums[i] < nums[k] && nums[k] < nums[j]) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};



int main(){
    return 0;
}