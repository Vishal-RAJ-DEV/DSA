#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// LeetCode 1122: Relative Sort Array
//
// Problem:
//   Given arr1 and arr2, sort arr1 such that the relative order of
//   elements follows the order in arr2. Elements not in arr2 should
//   be placed at the end in ascending order.
//
//   Example:
//     arr1 = [2,3,1,3,2,4,6,7,9,2,19]
//     arr2 = [2,1,4,3,9,6]
//     Output: [2,2,2,1,4,3,3,9,6,7,19]
//
// Intuition:
//   Elements in arr2 define a custom order. Elements not in arr2 have
//   no relative constraint among themselves, so they just need to be
//   sorted ascending. The core challenge is efficiently grouping and
//   placing elements according to arr2.
//

// ============================================================
// Approach 1 — Brute Force (Mark & Collect)
// ============================================================
//
// How it works:
//   1. For each element x in arr2, scan the entire arr1.
//      Whenever x matches arr1[j], push it to result and mark
//      arr1[j] = -1 (visited) so it won't be picked again.
//   2. After processing all arr2 elements, sort arr1.
//   3. Append all non -1 values (elements not in arr2) to result.
//
// Intuition:
//   "Pick out" elements in the order specified by arr2 by repeatedly
//   scanning arr1. Marking as -1 avoids reusing elements. Since arr2
//   elements are extracted in order, result naturally follows arr2's
//   order. Leftover unmarked elements are just sorted ascending.
//
// Time: O(m * n + m log m)  — m = |arr1|, n = |arr2|
//   Outer loop: n iterations, inner scan: O(m) each → O(n*m)
//   Sorting leftovers: O(m log m)
// Space: O(1) extra (result excluded)
//
// Weakness: Repeated full scans of arr1 are expensive.

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int> result;

        for (int i = 0; i < arr2.size(); i++) {
            for (int j = 0; j < arr1.size(); j++) {
                if (arr1[j] == arr2[i]) {
                    result.push_back(arr1[j]);
                    arr1[j] = -1;
                }
            }
        }
        sort(arr1.begin(), arr1.end());

        for (int i = 0; i < arr1.size(); i++) {
            if (arr1[i] != -1) {
                result.push_back(arr1[i]);
            }
        }
        return result;
    }
};

// ============================================================
// Approach 2 — Hash Map (Frequency + Remainder)
// ============================================================
//
// How it works:
//   1. Initialize an unordered_map with keys from arr2 (value = 0).
//   2. Count occurrences of each arr1 element:
//        - If it's in the map (i.e., in arr2), increment count.
//        - Otherwise, push it to a 'remaining' vector.
//   3. Sort the 'remaining' vector.
//   4. For each element in arr2, push it count[element] times.
//   5. Append all remaining elements.
//
// Intuition:
//   Instead of scanning arr1 repeatedly, we do a single pass to
//   count how many times each arr2 element appears and separately
//   collect the "leftovers". Then we reconstruct the result by
//   dumping the counts in arr2's order, followed by the sorted
//   leftovers. This avoids the O(n*m) of Approach 1.
//
// Time: O(m log m)  — dominated by sorting remaining elements
//   One pass over arr1 to count: O(m)
//   Sorting remaining: O(m log m)
//   Two construction passes over arr2 and remaining: O(n + m)
//   Total: O(m log m)
// Space: O(n + m)  — map size n, remaining vector up to m

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> countMap;
        vector<int> remaining, result;

        for (int i = 0; i < arr2.size(); i++) {
            countMap[arr2[i]] = 0;
        }

        for (int i = 0; i < arr1.size(); i++) {
            if (countMap.find(arr1[i]) != countMap.end()) {
                countMap[arr1[i]]++;
            } else {
                remaining.push_back(arr1[i]);
            }
        }

        sort(remaining.begin(), remaining.end());

        for (int i = 0; i < arr2.size(); i++) {
            for (int j = 0; j < countMap[arr2[i]]; j++) {
                result.push_back(arr2[i]);
            }
        }

        for (int i = 0; i < remaining.size(); i++) {
            result.push_back(remaining[i]);
        }
        return result;
    }
};

// ============================================================
// Approach 3 — Counting Sort (Optimal)
// ============================================================
//
// Counting Sort Concept:
//   Counting sort is a non-comparison sorting algorithm that works
//   when the input range (0..k) is known and small. Instead of
//   comparing values, it counts occurrences of each value using a
//   frequency array indexed by the value itself. The sorted order
//   is recovered by iterating the index from 0 to k and emitting
//   each value count[value] times. Array indices provide natural
//   ascending order — no comparisons needed.
//
// How it works here:
//   1. Find maxElement in arr1 (largest possible value).
//   2. Build a frequency array count[0..maxElement].
//      count[x] = how many times x appears in arr1.
//   3. Iterate arr2 in order. For each element, drain all its
//      occurrences from count[] into result.
//   4. Iterate num from 0 to maxElement. For any remaining counts,
//      push num into result that many times. Since we go from
//      low to high, these are naturally ascending.
//
// Intuition:
//   The frequency array gives us two things for free:
//     a) The count of any element — O(1) lookup.
//     b) Natural ascending order via index traversal.
//   Step 3 handles arr2's custom order (we "pluck" elements in
//   the sequence arr2 dictates). Step 4 handles leftovers in
//   ascending order without any extra sort step — the index
//   traversal does it automatically. This is the cleanest and
//   fastest solution when the element range is manageable.
//
// Time: O(m + k)  where m = |arr1|, k = maxElement value
//   Finding maxElement: O(m)
//   Counting frequencies: O(m)
//   Draining arr2 elements: O(n) total (each element visited once)
//   Draining leftover counts: O(k) (up to k+1 array slots checked)
//   Total: O(m + k)
//
//   Note: O(m + k) is linear in both array size and value range.
//   When k <= m, this is ~O(m). When k >> m, sorting (O(m log m))
//   may be better.
//
// Space: O(k) for the count array (size maxElement + 1)

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        int maxElement = *max_element(arr1.begin(), arr1.end());
        vector<int> count(maxElement + 1);

        for (int element : arr1) {
            count[element]++;
        }

        vector<int> result;

        for (int element : arr2) {
            while (count[element] > 0) {
                result.push_back(element);
                count[element]--;
            }
        }

        for (int num = 0; num <= maxElement; num++) {
            while (count[num] > 0) {
                result.push_back(num);
                count[num]--;
            }
        }
        return result;
    }
};

int main() {
    return 0;
}
