#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 1539. Kth Missing Positive Number

    Given an array arr of positive integers sorted in strictly increasing
    order, and an integer k, return the kth positive integer that is
    missing from the array.

    Example 1:
        Input: arr = [2,3,4,7,11], k = 5
        Output: 9
        Explanation:
            Present:     2,  3,  4,      7,          11
            All positive: 1,2,3,4,5,6,7,8,9,10,11,12,...
            Missing:      1,          5,6,  8,9,10,   ...
            The 5th missing number is 9.

    Example 2:
        Input: arr = [1,2,3,4], k = 2
        Output: 6
        Explanation:
            Present: 1,2,3,4
            Missing:         5,6,...
            The 2nd missing number is 6.

    Example 3:
        Input: arr = [5,6,7], k = 3
        Output: 3
        Explanation:
            Present:     5,6,7
            Missing: 1,2,3,4,...
            The 3rd missing number is 3.
*/


// =========================================================
// APPROACH: Binary Search on Missing Count — O(log n)
// =========================================================
/*
    KEY INSIGHT (Missing Numbers Formula):
        In a perfect sequence 1,2,3,..., the element at index i (0-based)
        would be (i + 1). Since arr is strictly increasing but may have
        missing numbers, the number of missing numbers up to index i is:
            missing[i] = arr[i] - (i + 1)

        Why? If no numbers were missing up to arr[i], there would be exactly
        arr[i] numbers in total from 1 to arr[i]. But since we only have
        (i + 1) of them (indices 0 to i), the rest are missing.

        Example: arr = [2,3,4,7,11]
            i=0: arr[0]=2, missing = 2 - 1 = 1  (number 1 is missing)
            i=1: arr[1]=3, missing = 3 - 2 = 1
            i=2: arr[2]=4, missing = 4 - 3 = 1
            i=3: arr[3]=7, missing = 7 - 4 = 3  (1,5,6 missing)
            i=4: arr[4]=11, missing = 11 - 5 = 6 (1,5,6,8,9,10 missing)

    LOGIC:
        1. Binary search to find the largest index 'high' where
           missing[mid] < k (i.e., the last index before we have
           accumulated k missing numbers).
        2. After the loop:
            - 'high' is the last index where missing < k.
            - 'low' is the first index where missing >= k.
        3. The kth missing number is located after arr[high]:
            - Up to arr[high], missing[high] numbers are missing.
            - We need (k - missing[high]) more missing numbers after arr[high].
            - The answer = arr[high] + (k - missing[high]).
            - Substituting missing[high] = arr[high] - (high + 1):
              answer = arr[high] + k - (arr[high] - (high + 1))
                     = arr[high] + k - arr[high] + high + 1
                     = high + 1 + k
        4. Edge case: if even at i=0, missing >= k, then high = -1.
           Answer = -1 + 1 + k = k (which is correct — kth missing
           is just k itself before the first array element).

    DRY RUN:
        arr = [2,3,4,7,11], k = 5

        low=0, high=4
        mid=2: missing = arr[2]-3 = 4-3 = 1 < 5 -> low=3
        mid=3: missing = arr[3]-4 = 7-4 = 3 < 5 -> low=4
        mid=4: missing = arr[4]-5 = 11-5 = 6 >= 5 -> high=3
        low=4, high=3 -> exit
        Answer = high + 1 + k = 3 + 1 + 5 = 9  ✓

    TIME COMPLEXITY:
        - Binary search on n elements: O(log n).
        - Each iteration does O(1) work.
        - Overall: O(log n).

    SPACE COMPLEXITY:
        - Only a few integer variables: O(1).
*/


class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int n = arr.size();
        int low = 0;
        int high = n - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            int missing = arr[mid] - (mid + 1);  // numbers missing before arr[mid]

            if (missing < k)
                low = mid + 1;    // need more missing numbers, move right
            else
                high = mid - 1;   // overshot, move left
        }

        // After loop: high = last index where missing < k
        // Answer = high + 1 + k (derived formula, see explanation above)
        return high + 1 + k;
    }
};


// =========================================================
// APPROACH 2: Linear Scan (O(n)) — Converted from Java
// =========================================================
/*
    LOGIC:
        1. Start with k representing the kth missing number.
        2. Iterate through the sorted array. For each element num:
            - If num <= k: this num "occupies" one of the positions
              we thought was missing. So the kth missing number
              shifts one step to the right: k++.
            - If num > k: all subsequent numbers are also > k
              (since array is sorted), so k is already the final
              answer. Break out of the loop.
        3. Return k.

        WHY THIS WORKS:
        - Think of the positive integers as 1,2,3,4,5,...
        - k starts as the position of the kth missing number in
          this ideal sequence (e.g., if k=5, we're looking for
          the 5th missing = number 5 initially).
        - But whenever we encounter an array element that is <= k,
          that number is PRESENT, so it can't be missing. This
          means the missing number we're looking for is actually
          one position further ahead.
        - By incrementing k each time we see num <= k, we effectively
          skip over the numbers that are present.

    DRY RUN:
        arr = [2,3,4,7,11], k = 5

        num=2: 2 <= 5 -> k=6
        num=3: 3 <= 6 -> k=7
        num=4: 4 <= 7 -> k=8
        num=7: 7 <= 8 -> k=9
        num=11: 11 > 9 -> break
        return 9  ✓

        arr = [5,6,7], k = 3

        num=5: 5 > 3 -> break (k is unchanged)
        return 3  ✓
        (Missing: 1,2,3 — 3rd missing = 3)

    TIME COMPLEXITY:
        - Worst case: iterate through all n elements: O(n).
        - Best case: break early at first element: O(1).
        - Overall: O(n).

    SPACE COMPLEXITY:
        - Only a single integer variable reused: O(1).

    COMPARISON:
        | Approach        | Time    | Space | When to Use              |
        |-----------------|---------|-------|--------------------------|
        | Binary Search   | O(log n)| O(1)  | Large n, k varies        |
        | Linear Scan     | O(n)    | O(1)  | Small n, or simplicity   |

        Both are valid. Binary search is optimal for large arrays,
        while linear scan is simpler and doesn't require the math
        formula derivation.
*/

class Solution2 {
public:
    int findKthPositive(vector<int>& arr, int k) {

        for (int num : arr) {
            if (num <= k) {
                k++;          // this number is present, so shift the kth missing
            } else {
                break;        // sorted array — remaining nums > k, answer is k
            }
        }

        return k;
    }
};


int main(){
    return 0;
}

