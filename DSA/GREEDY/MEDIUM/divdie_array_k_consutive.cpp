/*
 * Problem: "Divide Array in Sets of K Consecutive Numbers"
 * Given an array of integers and an integer k, determine if the array
 * can be divided into groups of size k such that each group contains
 * k consecutive numbers. If possible, print the groups.
 *
 * Example:
 *   nums = [1,2,3,3,4,4,5,6], k = 4
 *   Groups: [1,2,3,4], [3,4,5,6]  → Possible
 *
 * Intuition (Greedy):
 *   - Sort or use a map to process numbers in increasing order.
 *   - The smallest remaining number must start a group.
 *   - Take the next k-1 consecutive numbers, decrement frequencies.
 *   - If any required number is missing, impossible.
 *
 * Below are 3 implementations:
 *   A1: CheckPossible  – Only checks if grouping is possible (returns bool).
 *   A2: PrintGroupsV1  – Prints groups using while(it->second > 0) loop.
 *   A3: PrintGroupsV2  – Prints groups using freq = it->second approach
 *                        (similar batch-consumption logic as A1 but prints).
 */
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------
// Approach 1: Check only (returns bool)
// ---------------------------------------------------------------
/*
 * Intuition:
 *   - If total elements aren't divisible by k, impossible.
 *   - A map stores frequencies of each number (sorted order by key).
 *   - Greedy core: The smallest available number must be the start
 *     of some group(s). If number 'x' appears 'freq' times, then
 *     x, x+1, ..., x+k-1 must ALL appear at least 'freq' times.
 *     Because 'freq' groups must start from x, and each needs one
 *     copy of every consecutive number from x to x+k-1.
 *
 * Algorithm:
 *   1. If n % k != 0 → return false.
 *   2. Build freq map from nums.
 *   3. Iterate map in sorted order:
 *      - If current number count is 0, skip.
 *      - Let freq = count[first].
 *      - For i = 0..k-1:
 *          - If count[first + i] < freq → return false (not enough copies).
 *          - Else count[first + i] -= freq (consume freq copies for groups).
 *   4. Return true.
 *
 * Why this works:
 *   - When we process the smallest remaining number, it MUST be the
 *     start of some groups. There's no other element smaller to pair with.
 *   - Consuming freq copies in one batch is equivalent to forming
 *     'freq' groups all starting from 'first'.
 *
 * Example:
 *   nums = [1,2,3,3,4,4,5,6], k = 4
 *   count: {1:1, 2:1, 3:2, 4:2, 5:1, 6:1}
 *
 *   it→first=1, freq=1:
 *     check 1,2,3,4 each ≥ 1 → yes. consume: {1:0, 2:0, 3:1, 4:1, 5:1, 6:1}
 *   it→first=2, freq=0 → skip
 *   it→first=3, freq=1:
 *     check 3,4,5,6 each ≥ 1 → yes. consume: {3:0, 4:0, 5:0, 6:0}
 *   → true (groups: [1,2,3,4], [3,4,5,6])
 *
 * TC: O(n log n) for map inserts, O(n) for traversal.  |  SC: O(n)
 */
class CheckPossible {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.size() % k != 0)
            return false;

        map<int, int> count;
        for (int num : nums)
            count[num]++;

        for (auto it = count.begin(); it != count.end(); it++) {
            if (it->second == 0)
                continue;

            int freq = it->second;
            for (int i = 0; i < k; i++) {
                if (count[it->first + i] < freq)
                    return false;
                count[it->first + i] -= freq;
            }
        }
        return true;
    }
};

// ---------------------------------------------------------------
// Approach 2: Print groups – one group at a time (while loop)
// ---------------------------------------------------------------
/*
 * Intuition:
 *   - Same greedy principle: smallest available number starts a group.
 *   - Instead of batch-consuming freq copies at once, build groups
 *     one-by-one using a while loop.
 *   - For each group, take the starting number and the next k-1
 *     consecutive numbers, decrement each by 1, and print.
 *
 * Algorithm:
 *   1. If n % k != 0 → print "Not Possible" and return.
 *   2. Build freq map from nums.
 *   3. Iterate map in sorted order:
 *      - While count[current_number] > 0:
 *          - Create a new group.
 *          - For i = 0..k-1:
 *              - If count[first + i] == 0 → impossible, return.
 *              - Push first+i to group, decrement count.
 *          - Print the group.
 *
 * Difference from A1:
 *   A1 consumes 'freq' copies from k consecutive numbers in one step.
 *   A2 processes one element (one copy) at a time from each of the
 *   k consecutive numbers → while(it->second > 0) loop.
 *
 * Example trace:
 *   nums = [1,2,3,3,4,4,5,6], k = 4
 *   count: {1:1, 2:1, 3:2, 4:2, 5:1, 6:1}
 *
 *   it→1, second=1 > 0:
 *     group: [1,2,3,4]  → count: {1:0, 2:0, 3:1, 4:1, 5:1, 6:1}
 *   it→1, second=0 → exit while, move to next it
 *   it→2, second=0 → skip
 *   it→3, second=1 > 0:
 *     group: [3,4,5,6]  → count: {3:0, 4:0, 5:0, 6:0}
 *   → prints: 1 2 3 4 \n 3 4 5 6
 *
 * TC: O(n log n)  |  SC: O(n)
 */
class PrintGroupsV1 {
public:
    void divideAndPrint(vector<int>& nums, int k) {
        if (nums.size() % k != 0) {
            cout << "Not Possible\n";
            return;
        }

        map<int, int> count;
        for (int x : nums)
            count[x]++;

        for (auto it = count.begin(); it != count.end(); it++) {
            while (it->second > 0) {
                vector<int> group;
                for (int i = 0; i < k; i++) {
                    if (count[it->first + i] == 0) {
                        cout << "Not Possible\n";
                        return;
                    }
                    group.push_back(it->first + i);
                    count[it->first + i]--;
                }
                for (int x : group)
                    cout << x << " ";
                cout << "\n";
            }
        }
    }
};

// ---------------------------------------------------------------
// Approach 3: Print groups – batch consumption (freq at a time)
// ---------------------------------------------------------------
/*
 * Intuition:
 *   - Hybrid of A1's batch-consumption idea and A2's printing.
 *   - Same freq logic as A1: if 'x' appears 'freq' times, then
 *     'freq' groups must start from x.
 *   - Instead of consuming all freq copies from all k numbers in
 *     one shot (like A1), we print 'freq' groups one by one,
 *     each time taking one copy from x, x+1, ..., x+k-1.
 *
 * Algorithm:
 *   1. If n % k != 0 → print "Not Possible" and return.
 *   2. Build freq map.
 *   3. Iterate map in sorted order:
 *      - If count[current] == 0, skip.
 *      - Let freq = count[first].
 *      - For t = 0..freq-1 (build 'freq' groups):
 *          - For i = 0..k-1:
 *              - If count[first + i] == 0 → impossible, return.
 *              - Else print first+i, decrement count[first+i].
 *          - Print newline (group complete).
 *
 * Key difference from A2:
 *   A2 uses while(it->second > 0) — which implicitly treats freq=1
 *   per iteration (one group per pass through the inner for loop).
 *   A3 explicitly loops t from 0 to freq-1, making it clear we
 *   are forming 'freq' groups starting from 'first'.
 *
 * Example trace:
 *   nums = [1,2,3,3,4,4,5,6], k = 4
 *   count: {1:1, 2:1, 3:2, 4:2, 5:1, 6:1}
 *
 *   it→1, freq=1:
 *     t=0: print 1 2 3 4 \n  → count: {1:0, 2:0, 3:1, 4:1, 5:1, 6:1}
 *   it→2, second=0 → skip
 *   it→3, freq=1:
 *     t=0: print 3 4 5 6 \n  → count: {3:0, 4:0, 5:0, 6:0}
 *   → prints: 1 2 3 4 \n 3 4 5 6
 *
 * TC: O(n log n)  |  SC: O(n)
 */
class PrintGroupsV2 {
public:
    void divideAndPrint(vector<int>& nums, int k) {
        if (nums.size() % k != 0) {
            cout << "Not Possible\n";
            return;
        }

        map<int, int> count;
        for (int num : nums)
            count[num]++;

        for (auto it = count.begin(); it != count.end(); it++) {
            if (it->second == 0)
                continue;

            int freq = it->second;
            for (int t = 0; t < freq; t++) {
                for (int i = 0; i < k; i++) {
                    if (count[it->first + i] == 0) {
                        cout << "Not Possible\n";
                        return;
                    }
                    cout << it->first + i << " ";
                    count[it->first + i]--;
                }
                cout << "\n";
            }
        }
    }
};

// ---------------------------------------------------------------
int main() {
    vector<int> nums = {1, 2, 3, 3, 4, 4, 5, 6};
    int k = 4;

    // Demo A1: Check
    CheckPossible checker;
    cout << "A1 - Possible? " << (checker.isPossibleDivide(nums, k) ? "Yes" : "No") << "\n\n";

    // Demo A2: Print (while loop)
    cout << "A2 - Groups (one-by-one):\n";
    PrintGroupsV1 printer1;
    printer1.divideAndPrint(nums, k);
    cout << "\n";

    // Demo A3: Print (batch consumption)
    cout << "A3 - Groups (batch):\n";
    PrintGroupsV2 printer2;
    printer2.divideAndPrint(nums, k);

    return 0;
}