#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
------------------------------------------------------------
Approach 2 : DP + Set (Optimal)
------------------------------------------------------------

Intuition:
----------
Instead of generating every subarray from scratch, we only keep
track of the OR values of subarrays ending at the previous index.

Let:
previous = {All distinct OR values of subarrays ending at i-1}

For every new element arr[i], every subarray ending at i is formed
in only two ways:

1. Start a brand new subarray.
      [arr[i]]

2. Extend every previous subarray by appending arr[i].
      Previous Subarray + arr[i]

------------------------------------------------------------
Example:
------------------------------------------------------------

arr = [1, 2]

Subarrays ending at index 1:

    [2]      -> OR = 2
    [1,2]    -> OR = 3

So,

previous = {2,3}

------------------------------------------------------------
Now process the next element = 4
------------------------------------------------------------

New subarrays ending here are:

    [4]
    [2,4]
    [1,2,4]

How are they formed?

Start new:
    [4]

Extend previous subarrays:

    OR([2])     = 2
    OR([1,2])   = 3

Append 4:

    2 | 4 = 6   -> OR([2,4])
    3 | 4 = 7   -> OR([1,2,4])

Therefore,

current = {4,6,7}

Finally,

previous = current

and continue for the next index.

------------------------------------------------------------
Transition:
------------------------------------------------------------

current.insert(arr[i]);          // Start a new subarray

for(each value in previous)
    current.insert(value | arr[i]); // Extend previous subarrays

Store every value of 'current' into the global answer set.

------------------------------------------------------------
Why does this work?
------------------------------------------------------------

Every subarray ending at index i is either:

1. [arr[i]]
2. A subarray ending at i-1 extended by arr[i]

These are the only possibilities, so no subarray is missed.

------------------------------------------------------------
Key Observation
------------------------------------------------------------

Bitwise OR is monotonic.

Bits can only change:

    0 -> 1   ✅
    1 -> 0   ❌

Since integers have only 32 bits, the number of distinct OR values
ending at any index is at most about 32.

Hence the algorithm runs in approximately O(32 * N) ≈ O(N).

------------------------------------------------------------
*/
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {

        // Stores every distinct OR value over ALL subarrays.
        unordered_set<int> answer;

        // Stores OR values of ALL subarrays
        // that end at the previous index.
        unordered_set<int> previous;

        // Process every element.
        for (int num : arr) {

            // OR values of all subarrays
            // ending at the current index.
            unordered_set<int> current;

            //-------------------------------------------------
            // Case 1
            //
            // Start a brand new subarray.
            //
            // Example
            //
            // [num]
            //-------------------------------------------------
            current.insert(num);

            //-------------------------------------------------
            // Case 2
            //
            // Extend every previous subarray.
            //
            // Suppose previous contains
            //
            // {2,3}
            //
            // These represent
            //
            // OR([2]) =2
            // OR([1,2])=3
            //
            // Current element =4
            //
            // New OR values become
            //
            // 2|4=6
            //
            // 3|4=7
            //
            // Which correspond to
            //
            // [2,4]
            //
            // [1,2,4]
            //-------------------------------------------------
            for (int value : previous) {

                current.insert(value | num);
            }

            //-------------------------------------------------
            // Add every OR ending here
            // into the global answer.
            //-------------------------------------------------
            for (int value : current) {

                answer.insert(value);
            }

            //-------------------------------------------------
            // Current becomes previous
            // for the next iteration.
            //
            // move() transfers ownership
            // instead of copying every element.
            //-------------------------------------------------
            previous = move(current);
        }

        return answer.size();
    }
};


class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {

        // Stores all distinct OR values of every subarray.
        unordered_set<int> answer;

        int n = arr.size();

        // Choose every index as the starting point.
        for (int start = 0; start < n; start++) {

            // OR of the current subarray.
            // Initially empty, so OR = 0.
            int currentOR = 0;

            // Extend the subarray one element at a time.
            for (int end = start; end < n; end++) {

                // Instead of recomputing OR from scratch,
                // keep extending the previous OR.
                //
                // Example:
                // current subarray = [1]
                // currentOR = 1
                //
                // Extend to [1,2]
                // currentOR = 1 | 2 = 3
                //
                // Extend to [1,2,4]
                // currentOR = 3 | 4 = 7
                currentOR |= arr[end];

                // Store this OR value.
                // unordered_set automatically removes duplicates.
                answer.insert(currentOR);
            }
        }

        // Number of distinct OR values.
        return answer.size();
    }
};




int main(){
    return 0;
}