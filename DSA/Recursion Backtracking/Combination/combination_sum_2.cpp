#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
=============================================================================
COMBINATION SUM II — PROBLEM
=============================================================================
Given a collection of candidate numbers (candidates) and a target number,
find all unique combinations where the chosen numbers sum to target.

Each number in candidates may only be used ONCE in the combination.
The solution set must not contain duplicate combinations.
The array may contain duplicates, but output must have unique combinations only.

Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: [[1,1,6], [1,2,5], [1,7], [2,6]]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output: [[1,2,2],[5]]

=============================================================================
KEY DIFFERENCES BETWEEN THE TWO APPROACHES
=============================================================================

| Feature               | Approach 1 (Loop-based)      | Approach 2 (Include/Exclude)  |
|------------------------|-------------------------------|-------------------------------|
| Recursion Style        | For-loop backtracking         | Binary include/exclude        |
| Duplicate Handling     | Skip at same level            | Skip via while loop           |
|                        | (i > start && arr[i]==arr[i-1]) | (while arr[indx]==arr[indx+1]) |
| Termination            | Loop ends naturally           | Explicit base cases           |
| Sum Tracking           | Remaining target (decreasing) | Current sum (increasing)      |
| Pruning                | arr[i] > target → break       | s > sum → return              |
| Each element used      | Only once (i+1 not i)         | Only once (indx+1 not indx)   |

Both approaches:
- Sort array first to handle duplicates and enable pruning
- Time: O(2^n) in worst case
- Space: O(n) recursion depth
=============================================================================
*/

/*
=============================================================================
APPROACH 1: LOOP-BASED BACKTRACKING
=============================================================================
HOW IT WORKS:
1. At each recursion level, iterate through candidates from `start` to `n`.
2. For each candidate:
   a. Skip if it's a duplicate at the same recursion level (i > start && arr[i] == arr[i-1])
   b. Skip if it exceeds remaining target (pruning — array is sorted)
   c. Choose: add to subset, reduce target
   d. Explore: recurse with i+1 (each element used only once)
   e. Backtrack: remove from subset

DUPLICATE HANDLING:
- Array is sorted BEFORE calling generate, so duplicates are adjacent.
- `if (i > start && arr[i] == arr[i-1])` skips duplicate values at the
  SAME recursion level. This prevents generating the same combination
  from duplicate elements.
- Example: [1,1,2,5,6,7] with target 8
  - First level picks arr[0]=1 (i=0, start=0, i==start so NOT skipped)
  - First level skips arr[1]=1 (i=1, start=0, i>start && arr[1]==arr[0])
  - This prevents duplicate [1,...] combinations

PRUNING:
- Since array is sorted, if arr[i] > target, all subsequent elements
  will also be > target, so we can break early.

Example trace for arr=[1,1,2,5,6,7], target=8:
  Level 0: i=0, pick 1, remaining=7
    Level 1: i=1, skip (duplicate 1)
    Level 1: i=2, pick 2, remaining=5
      Level 2: i=3, pick 5, remaining=0 → FOUND [1,2,5]
      Level 2: i=4, pick 6, remaining=-1 > 0? No, but 6>5 so break
    Level 1: i=3, pick 5, remaining=2
      Level 2: i=4, pick 6, remaining=-4 → 6>2 so break
    Level 1: i=4, pick 6, remaining=1 → 6>1 so break
  ...and so on

Time Complexity:  O(2^n) — each element is included or excluded.
                  With sorting + pruning,实际比 2^n 小很多。
Space Complexity: O(n) recursion stack depth.
                  O(2^n * k) for storing results (k = average combination length).
=============================================================================
*/
void generate(int start, int n, int target,
              vector<int>& arr, vector<int>& subset) {

    // Target reached — valid combination found
    if (target == 0) {
        cout << "[";
        for (int x : subset) {
            cout << x << " ";
        }
        cout << "]" << endl;
        return;
    }

    for (int i = start; i < n; i++) {

        // Skip duplicate choices at the same recursion level
        // This prevents duplicate combinations like [1,1,6] appearing twice
        if (i > start && arr[i] == arr[i - 1])
            continue;

        // If current element is greater than remaining target,
        // no further element can work because array is sorted
        if (arr[i] > target)
            break;

        // Choose: add current element to subset
        subset.push_back(arr[i]);

        // Explore: recurse with i+1 (each element used only ONCE)
        // target - arr[i] tracks remaining sum needed
        generate(i + 1, n, target - arr[i], arr, subset);

        // Backtrack: remove last added element
        subset.pop_back();
    }
}

/*
=============================================================================
APPROACH 2: INCLUDE/EXCLUDE BINARY RECURSION
=============================================================================
HOW IT WORKS:
1. At each index, make exactly 2 choices: INCLUDE or EXCLUDE current element.
2. Base cases:
   a. s == sum → valid combination found, print and return
   b. indx == n or s > sum → invalid path, return
3. Duplicate handling: BEFORE the exclude call, skip all duplicates using
   a while loop. This ensures we only process unique elements once.

DUPLICATE HANDLING (different from Approach 1):
- Uses `while (indx+1 < n && arr[indx] == arr[indx+1]) indx++;`
- This skips ALL consecutive duplicates of current element BEFORE making
  the exclude call.
- Example: [1,1,2,5,6,7]
  - At indx=0, include arr[0]=1, then exclude
  - Before exclude, while loop skips indx from 0 to 1 (both are 1)
  - So exclude call starts from indx=2 (element 2), skipping duplicate 1

SUM TRACKING:
- Tracks current sum `s` (increasing) instead of remaining target (decreasing).
- More intuitive: "have we reached the target sum?"
- Pruning: if s > sum, no need to continue.

Example trace for arr=[1,1,2,5,6,7], target=8:
  generate(0, 0, ...):
    Include 1: s=1
      Include 1: s=2
        Include 2: s=4
          Include 5: s=9 > 8, return
          (skip duplicates) → Exclude at indx=4 (element 6)
            s=4 < 8, include 6: s=10 > 8, return
            Exclude 6, s=4, include 7: s=11 > 8, return
        Exclude 2: s=2 (after while loop skips nothing)
          Include 5: s=7
            Include 6: s=13 > 8, return
            Exclude 6, include 7: s=14 > 8, return
          Exclude 5, include 6: s=8 → FOUND [1,1,6]

Time Complexity:  O(2^n) — binary tree with n levels.
Space Complexity: O(n) recursion stack depth.
=============================================================================
*/
void generate(int indx, int n, int s, int sum, vector<int> &arr, vector<int> &subset)
{
    // Base case: sum matches target — valid combination found
    if (s == sum)
    { 
        cout << "[ ";
        for (auto &it : subset)
        {
            cout << it << " ";
        }
        cout << "]";
        cout << endl;
        return;
    }

    // Base case: reached end of array or sum exceeds target
    if (indx == n || s > sum) return;

    // INCLUDE: add current element to subset
    subset.push_back(arr[indx]);
    s += arr[indx];

    // Recurse with next index (each element used only once)
    generate(indx + 1, n, s, sum, arr, subset);

    // BACKTRACK: undo the include
    s -= arr[indx];
    subset.pop_back();

    // Skip ALL duplicates of current element before EXCLUDE call
    // This ensures we don't process duplicate values again
    while (indx + 1 < n && arr[indx] == arr[indx + 1]) {
        indx++;
    }

    // EXCLUDE: move to next unique element without adding anything
    generate(indx + 1, n, s, sum, arr, subset);
}

int main()
{
    vector<int> arr = {10,1,2,7,6,1,5};
    int n = arr.size();
    int sum = 8;
    vector<int> subset;

    // Sort first — required for both duplicate handling and pruning
    sort(arr.begin(), arr.end());
    
    // Choose either approach (uncomment one):
    // Approach 1: Loop-based backtracking
    // generate(0, n, 0, sum, arr, subset);
    
    // Approach 2: Include/Exclude binary recursion
    generate(0, n, 0, sum, arr, subset);

    return 0;
}

