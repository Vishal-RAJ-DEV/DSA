#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 287. Find the Duplicate Number

    Given an array of integers nums containing n + 1 integers where each
    integer is in the range [1, n] inclusive. There is only one repeated
    number in nums. Find and return this duplicate number.

    Constraints:
        - Must NOT modify the array (read-only).
        - Must use only constant extra space O(1).

    Example:
        Input: nums = [1,3,4,2,2]
        Output: 2

        Input: nums = [3,1,3,4,2]
        Output: 3

    NOTE: Not all approaches below satisfy the constraints (read-only + O(1)).
    The optimal solutions that DO are:
        - Approach 6: Binary Search     — O(n log n), O(1)
        - Approach 7: Floyd's Algorithm — O(n), O(1)
    Others are included for learning purposes.
*/


// =========================================================
// APPROACH 1: Brute Force (Two Loops) — O(n²)
// =========================================================
/*
    LOGIC:
        Compare every pair of elements (i, j) where i < j.
        If any pair matches, that element is the duplicate.

    TIME: O(n²) — nested loops
    SPACE: O(1)
    MODIFIES ARRAY: No
    SATISFIES CONSTRAINTS: No (time exceeds limit)
*/
int findDuplicate_2loops(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] == nums[j])
                return nums[i];
        }
    }
    return n;
}


// =========================================================
// APPROACH 2: Counting Array (Frequency) — O(n)
// =========================================================
/*
    LOGIC:
        Use an auxiliary counting array cnt of size n+1.
        For each num, increment cnt[num]. If cnt[num] > 1,
        num is the duplicate.

    TIME: O(n)
    SPACE: O(n) — counting array
    MODIFIES ARRAY: No
    SATISFIES CONSTRAINTS: No (uses O(n) space)
*/
int findDuplicate_count(vector<int>& nums) {
    int n = nums.size();
    vector<int> cnt(n + 1, 0);

    for (int i = 0; i < n; i++) {
        cnt[nums[i]]++;
        if (cnt[nums[i]] > 1)
            return nums[i];
    }
    return n;
}


// =========================================================
// APPROACH 3: HashSet — O(n)
// =========================================================
/*
    LOGIC:
        Insert each element into an unordered_set.
        If insertion fails (element already exists), it's the duplicate.

    TIME: O(n) average, O(n²) worst case (hash collisions)
    SPACE: O(n)
    MODIFIES ARRAY: No
    SATISFIES CONSTRAINTS: No (uses O(n) space)
*/
int findDuplicate_set(vector<int>& nums) {
    unordered_set<int> seen;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        if (seen.find(nums[i]) != seen.end())
            return nums[i];
        seen.insert(nums[i]);
    }
    return n;
}


// =========================================================
// APPROACH 4: Mark Visited (Negation) — O(n)
// =========================================================
/*
    LOGIC:
        Use the array itself as a marker. For each num, go to
        index = abs(num) and negate the value at that index.
        If the value is already negative, idx is the duplicate.

    TIME: O(n)
    SPACE: O(1)
    MODIFIES ARRAY: YES (violates read-only constraint)
    SATISFIES CONSTRAINTS: No (modifies array)

    NOTE: Works because all values are in [1, n], so they are valid indices.
    Assumes values are positive initially.
*/
int findDuplicate_mark(vector<int>& nums) {
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        int idx = abs(nums[i]);
        if (nums[idx] < 0)
            return idx;
        nums[idx] = -nums[idx];
    }
    return n;
}


// =========================================================
// APPROACH 5: Sorting — O(n log n)
// =========================================================
/*
    LOGIC:
        Sort the array. Then scan — if nums[i] == nums[i-1],
        that element is the duplicate.

    TIME: O(n log n) — sorting dominates
    SPACE: O(1) if in-place sort; O(n) otherwise
    MODIFIES ARRAY: YES (sorts it)
    SATISFIES CONSTRAINTS: No (modifies array, sort may use extra space)
*/
int findDuplicate_sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();

    for (int i = 1; i < n; i++) {
        if (nums[i] == nums[i - 1])
            return nums[i];
    }
    return n;
}


// =========================================================
// APPROACH 6: Index Sort (Cyclic Sort) — O(n)
// =========================================================
/*
    LOGIC:
        Place each number at its correct position (value-1 is the index).
        For each i, while nums[i] != i+1:
            - Let correct = nums[i] - 1 (the index where nums[i] belongs).
            - If nums[i] == nums[correct], we found the duplicate.
            - Else swap nums[i] with nums[correct].
        If no duplicate found in the loop, return 0.

    TIME: O(n) — each number is placed at most once
    SPACE: O(1)
    MODIFIES ARRAY: YES
    SATISFIES CONSTRAINTS: No (modifies array)

    This is the standard "find missing/duplicate number" cyclic sort pattern.
*/
int findDuplicate_index_sort(vector<int>& nums) {
    int n = nums.size();

    for (int i = 0; i < n; ) {
        int correctIdx = nums[i] - 1;  // where this value should be

        if (nums[i] == i + 1) {
            i++;  // already in correct position
        } else if (nums[i] == nums[correctIdx]) {
            return nums[i];  // duplicate found
        } else {
            swap(nums[i], nums[correctIdx]);  // place at correct position
        }
    }
    return 0;
}


// =========================================================
// APPROACH 7: Binary Search on Value Range — O(n log n)
// =========================================================
/*
    LOGIC:
        Binary search on the VALUE range [1, n-1] (not indices).
        For a given mid, count how many numbers in nums are <= mid.
            - If count <= mid: duplicate is in the RIGHT half (mid+1..n-1)
            - If count > mid:  duplicate is in the LEFT half (1..mid)
        This works because in a valid set of [1..n-1] with no duplicates,
        exactly 'mid' numbers would be <= mid. More than 'mid' means
        a number <= mid is duplicated.

        PIGEONHOLE PRINCIPLE: n+1 numbers in range [1,n] — at least one repeat.

    TIME: O(n log n) — binary search O(log n) iterations, each O(n) count
    SPACE: O(1)
    MODIFIES ARRAY: No
    SATISFIES CONSTRAINTS: YES (read-only, O(1) space)

    DRY RUN:
        nums = [1,3,4,2,2], n = 5 (values 1..4)

        low=1, high=4, mid=2:
            count of <=2: [1,2,2] = 3
            3 > 2 -> high = 2
        low=1, high=2, mid=1:
            count of <=1: [1] = 1
            1 <= 1 -> low = 2
        low=2, high=2 -> exit
        return 2  ✓
*/
int findDuplicate_bs(vector<int>& nums) {
    int n = nums.size();        // n+1 elements, values in [1, n-1]
    int low = 1;
    int high = n - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;
        int cnt = 0;

        // Count numbers <= mid
        for (int i = 0; i < n; i++) {
            if (nums[i] <= mid)
                cnt++;
        }

        if (cnt <= mid)
            low = mid + 1;   // duplicate in right half
        else
            high = mid;      // duplicate in left half (mid is candidate)
    }

    return low;
}


// =========================================================
// APPROACH 8: Floyd's Tortoise and Hare (Cycle Detection) — O(n)
// =========================================================
/*
    LOGIC:
        Treat the array as a linked list where nums[i] is the "next"
        pointer for node i. Since values are in [1, n] and there are
        n+1 elements, at least one value repeats, creating a cycle.
        Use Floyd's cycle detection algorithm to find the entry point
        of the cycle, which is the duplicate number.

        WHY IT WORKS:
        - Each index 0..n points to another index via nums[i].
        - Since values are in [1,n], index 0 starts outside the cycle
          (no value 0 exists), so we must eventually enter a cycle.
        - The entry point of the cycle is the value that is pointed to
          by two different indices = the duplicate number.

        STEPS:
        1. Phase 1 (Detect cycle):
            slow = nums[slow] (moves 1 step)
            fast = nums[nums[fast]] (moves 2 steps)
            Stop when slow == fast (they meet inside the cycle).
        2. Phase 2 (Find cycle entry = duplicate):
            Reset slow = 0.
            Move both slow and fast one step at a time.
            When they meet again, that point is the cycle entry = duplicate.

    TIME: O(n)
    SPACE: O(1)
    MODIFIES ARRAY: No
    SATISFIES CONSTRAINTS: YES (optimal solution — read-only, O(1))

    DRY RUN:
        nums = [1,3,4,2,2]
        Indices: 0→1→3→2→4→2→4→2→... (cycle: 2→4→2)
        Phase 1:
            slow=0, fast=0
            slow=nums[0]=1, fast=nums[nums[0]]=nums[1]=3
            slow=nums[1]=3, fast=nums[nums[3]]=nums[2]=4
            slow=nums[3]=2, fast=nums[nums[4]]=nums[2]=4
            slow=nums[2]=4, fast=nums[nums[4]]=nums[2]=4 → meet at 4
        Phase 2:
            slow=0, fast=4
            slow=nums[0]=1, fast=nums[4]=2
            slow=nums[1]=3, fast=nums[2]=4
            slow=nums[3]=2, fast=nums[4]=2 → meet at 2
            return 2  ✓
*/
int findDuplicate_fastSlow(vector<int>& nums) {
    // Phase 1: Detect the cycle
    int slow = nums[0];
    int fast = nums[0];

    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    // Phase 2: Find the cycle entry point (duplicate)
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    return slow;
}


/*  SUMMARY TABLE:

    | Approach                | Time        | Space | Modifies? | Meets Constraints? |
    |-------------------------|-------------|-------|-----------|-------------------|
    | 1. Brute Force          | O(n²)       | O(1)  | No        | No (time)         |
    | 2. Counting Array       | O(n)        | O(n)  | No        | No (space)        |
    | 3. HashSet              | O(n)        | O(n)  | No        | No (space)        |
    | 4. Mark Visited         | O(n)        | O(1)  | YES       | No (modifies)     |
    | 5. Sorting              | O(n log n)  | O(1)  | YES       | No (modifies)     |
    | 6. Index Sort           | O(n)        | O(1)  | YES       | No (modifies)     |
    | 7. Binary Search        | O(n log n)  | O(1)  | No        | YES               |
    | 8. Floyd's Tortoise/Hare| O(n)        | O(1)  | No        | YES (BEST)        |

    The optimal solution that satisfies ALL constraints (read-only, O(1)
    space) is Floyd's Tortoise and Hare (Approach 8) — O(n) time.
*/


int main() {
    vector<int> nums = {1, 3, 4, 2, 2};

    cout << "Duplicate found via each approach:\n";
    cout << "1. Brute Force:        " << findDuplicate_2loops(nums) << "\n";

    // Reset nums (some approaches modify it)
    nums = {1, 3, 4, 2, 2};
    cout << "2. Counting Array:     " << findDuplicate_count(nums) << "\n";

    nums = {1, 3, 4, 2, 2};
    cout << "3. HashSet:            " << findDuplicate_set(nums) << "\n";

    nums = {1, 3, 4, 2, 2};
    cout << "4. Mark Visited:       " << findDuplicate_mark(nums) << "\n";

    nums = {1, 3, 4, 2, 2};
    cout << "5. Sorting:            " << findDuplicate_sort(nums) << "\n";

    nums = {1, 3, 4, 2, 2};
    cout << "6. Index Sort:         " << findDuplicate_index_sort(nums) << "\n";

    nums = {1, 3, 4, 2, 2};
    cout << "7. Binary Search:      " << findDuplicate_bs(nums) << "\n";

    nums = {1, 3, 4, 2, 2};
    cout << "8. Floyd's Algorithm:  " << findDuplicate_fastSlow(nums) << "\n";

    return 0;
}
