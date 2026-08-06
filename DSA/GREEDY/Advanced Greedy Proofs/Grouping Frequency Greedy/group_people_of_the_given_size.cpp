/*
 * ============================================================
 *  PROBLEM: Group the People Given the Group Size They Belong To
 *           (Leetcode 1282)
 * ============================================================
 *
 *  QUESTION:
 *  ---------
 *  There are n people with IDs from 0 to n-1.
 *  You are given an array groupSizes where groupSizes[i] is the size
 *  of the group that person i should be in.
 *
 *  Each person must appear in exactly one group, and every person in
 *  a group must have the same groupSizes value. You may form groups
 *  in any order.
 *
 *  Return a list of groups such that each group satisfies the size
 *  requirement.
 *
 *  Example:
 *    groupSizes = [3, 3, 3, 3, 3, 1, 3]
 *    Output: [[0, 1, 2], [3, 4, 6], [5]]
 *    Explanation:
 *      - Persons 0,1,2 have groupSize 3 → they fill one group of size 3
 *      - Persons 3,4,6 have groupSize 3 → they fill another group of size 3
 *      - Person 5 has groupSize 1 → forms a group of size 1
 *
 *  INTUITION:
 *  ----------
 *  Think of it as a "packing" problem. People with the same group size
 *  need to be packed into buckets of that exact capacity.
 *
 *  Key insight → When you encounter a person, you know:
 *     1. What size group they belong to (groupSizes[i]).
 *     2. That they need to be grouped with other people of the SAME size.
 *
 *  This naturally suggests a greedy approach using a hash table:
 *    - Use the group size as a KEY in a hash map.
 *    - The VALUE is a list of person IDs waiting to form a group of
 *      that size.
 *    - As soon as the list for a size reaches the required capacity,
 *      we "seal" that group: move it to the answer and reset the list.
 *
 *  Why does this work?
 *    - We don't care WHICH specific people end up in which group,
 *      as long as each group has the right count.
 *    - The total number of people of each size is guaranteed to be
 *      divisible by that size (by the problem constraints), so we
 *      won't be left with incomplete groups.
 *
 *  ALGORITHM:
 *  ----------
 *  1. Create a hash map: key = group size, value = list of person IDs
 *     who belong to that size.
 *  2. Create an empty result vector.
 *  3. For each person i (0 to n-1):
 *       a. Get the required group size: g = groupSizes[i].
 *       b. Add person i to the list for size g.
 *       c. If the list for size g now has exactly g members:
 *            → Move this complete list to the result.
 *            → Clear the list for size g.
 *  4. Return the result.
 *
 *  COMPLEXITY:
 *  -----------
 *  Time  → O(n) — single linear pass over the array.
 *  Space → O(n) — hash map stores at most n person IDs across all keys.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        int n = groupSizes.size();                  // number of people

        /*
         * mpp maps a group size → list of person IDs waiting to form
         * a group of that size.
         * e.g., if groupSizes[0] = 3 and groupSizes[2] = 3,
         * then mpp[3] = [0, 2]
         */
        unordered_map<int, vector<int>> mpp;
        vector<vector<int>> res;                    // final list of groups

        for (int i = 0; i < n; i++) {
            int g = groupSizes[i];                  // required group size for person i
            mpp[g].push_back(i);                    // assign person i to this size bucket

            /*
             * If this bucket has exactly 'g' people, they form a complete group.
             * Move the entire group to the answer and clear the bucket so
             * the next set of people of size g can start fresh.
             */
            if (mpp[g].size() == g) {
                res.push_back(mpp[g]);              // seal the group
                mpp[g].clear();                     // reset bucket for more people of same size
            }
        }

        return res;
    }
};

int main() {
    return 0;
}
