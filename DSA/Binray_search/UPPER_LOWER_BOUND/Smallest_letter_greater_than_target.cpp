#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 744. Find Smallest Letter Greater Than Target

    You are given a sorted array of characters 'letters' in non-decreasing
    order, and a target character 'target'. Find the smallest character in
    the array that is STRICTLY GREATER than target.

    If no such character exists, return the FIRST character in the array
    (i.e., the array wraps around).

    Example:
        letters = ['c', 'f', 'j']
        target = 'a'  -> 'c'    (c > a, smallest greater)
        target = 'c'  -> 'f'    (f > c, smallest greater)
        target = 'd'  -> 'f'    (f > d, smallest greater)
        target = 'j'  -> 'c'    (j is not > j, so wrap to first)
        target = 'k'  -> 'c'    (no letter > k, so wrap to first)

    NOTE: The array is sorted and guaranteed to have at least 1 element.
*/


// =========================================================
// APPROACH 1: Binary Search with Explicit Answer Variable
// =========================================================
/*
    LOGIC:
        1. Perform standard binary search on the sorted letters array.
        2. Maintain an 'ans' variable to store the candidate answer.
        3. When letters[mid] > target, this mid is a valid candidate
           (strictly greater than target). Save it in ans and continue
           searching LEFT (high = mid - 1) to find an even smaller
           character that is still > target.
        4. When letters[mid] <= target, search RIGHT (low = mid + 1)
           for a larger character.
        5. After the loop, return ans.

    BUG: The variable 'ans' is uninitialized. If no character in the
    array is greater than target, ans contains garbage/undefined value.
    This approach does NOT handle the wrap-around requirement.

    TIME COMPLEXITY: O(log n) — standard binary search
    SPACE COMPLEXITY: O(1)
*/
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int low = 0;
        int high = letters.size() - 1;
        char ans;  // BUG: uninitialized — undefined behavior when no match

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (letters[mid] > target) {
                ans = letters[mid];    // valid candidate found
                high = mid - 1;        // search left for smaller candidate
            } else {
                low = mid + 1;         // search right
            }
        }

        return ans;  // BUG: garbage if all letters <= target
    }
};


// =========================================================
// APPROACH 2: Binary Search with Modulo Wrap — O(log n)
// =========================================================
/*
    LOGIC:
        1. Perform binary search on the sorted letters array.
        2. Condition: if letters[mid] <= target, move low to mid + 1.
           Otherwise (letters[mid] > target), move high to mid - 1.
        3. After the loop, 'low' will be at one of two positions:
            a. The index of the first character > target (if it exists).
            b. letters.size() if ALL characters are <= target.
        4. Return letters[low % letters.size()] — the modulo handles
           the wrap-around: when low == letters.size(), low % n = 0,
           giving us the first character.

        KEY INSIGHT:
        - After binary search terminates (low > high), 'low' is the
          insertion point of target in the sorted array (first position
          where the element is > target).
        - This is exactly std::upper_bound() behavior.
        - No need for a separate ans variable.

    DRY RUN:
        letters = ['c', 'f', 'j'], target = 'f'

        low=0, high=2, mid=1 -> letters[1]='f', 'f' <= 'f' -> low=2
        low=2, high=2, mid=2 -> letters[2]='j', 'j' > 'f'  -> high=1
        low=2, high=1 -> loop exits
        low=2, letters[2 % 3] = letters[2] = 'j'
        Answer: 'j'

        letters = ['c', 'f', 'j'], target = 'j'

        low=0, high=2, mid=1 -> letters[1]='f', 'f' <= 'j' -> low=2
        low=2, high=2, mid=2 -> letters[2]='j', 'j' <= 'j' -> low=3
        low=3, high=2 -> loop exits
        low=3, letters[3 % 3] = letters[0] = 'c'
        Answer: 'c' (wrap-around)

    TIME COMPLEXITY:
        - Standard binary search: O(log n), where n = letters.size().
        - Single modulo operation: O(1).
        - Overall: O(log n).

    SPACE COMPLEXITY:
        - Only a few integer variables: O(1).
*/


class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {

        int low = 0;
        int high = letters.size() - 1;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (letters[mid] <= target)
                low = mid + 1;   // move right — need a larger character
            else
                high = mid - 1;  // move left — current mid is a candidate
        }

        // low = first index where letters[index] > target
        // If all <= target, low = letters.size() -> wrap to index 0
        return letters[low % letters.size()];
    }
};


/*  NOTE ON STANDARD LIBRARY:
    This problem can also be solved using STL's upper_bound():
        auto it = upper_bound(letters.begin(), letters.end(), target);
        return (it == letters.end()) ? letters[0] : *it;

    This is equivalent to Approach 2 and runs in O(log n) as well.
*/


int main(){
    return 0;
}
