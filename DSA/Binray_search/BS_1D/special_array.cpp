#include <bits/stdc++.h>
using namespace std;

/*
======================================================================
PROBLEM: Special Array With X Elements Greater Than or Equal X
         (LeetCode 1608)
======================================================================

You are given an array nums of non-negative integers.

Find x such that:
  There are EXACTLY x numbers in nums that are >= x.

If no such x exists, return -1.
x must be between 0 and nums.size() (inclusive) and x > 0.

Examples:
  nums = [3, 5, 6, 7, 8]  →  5 elements, x = ?

  Check x=1: numbers >= 1 → 5  (5 != 1)
  Check x=2: numbers >= 2 → 5  (5 != 2)
  Check x=3: numbers >= 3 → 5  (5 != 3)
  Check x=4: numbers >= 4 → 5  (5 != 4)
  Check x=5: numbers >= 5 → 4  (4 != 5)
  ...
  Answer: -1 (no x satisfies the condition)

  nums = [0, 4, 3, 0, 4] → sorted: [0, 0, 3, 4, 4]
  Check x=3: numbers >= 3 are {3, 4, 4} = 3  →  x=3 works! Return 3.

======================================================================
KEY OBSERVATION
======================================================================

If we SORT the array ascending, then at index i:
  There are (n - i) elements from i to n-1 (inclusive).
  Each of those elements is >= nums[i] (because sorted).

So: "count of numbers >= x" = (n - i) where i is the first index
    where nums[i] >= x.

We need: (n - i) == x

Or equivalently: at index i, if (n - i) is our candidate x,
  we check: nums[i] >= (n - i)   AND   nums[i-1] < (n - i)
  (ensuring exactly (n-i) elements are >= (n-i))

======================================================================
APPROACH 1: Linear Scan (O(n log n))
======================================================================

Sort the array. For each index i from 0 to n-1:
  x = n - i   (number of elements from i onward)
  if nums[i] >= x AND (i == 0 || nums[i-1] < x):
    return x  (found exactly x elements >= x)

Why the second condition?
  If nums[i-1] >= x, then elements from i-1 onward also have >= x
  elements, so the count would be (n - (i-1)) = x+1, not x.

Complexity: O(n log n) due to sort
======================================================================
APPROACH 2: Binary Search (O(n log n) with O(log n) search)
======================================================================

Same sorting, but find the first index where nums[mid] >= (n-mid)
using binary search. Then verify the exact condition.

Complexity: Sort O(n log n) + Binary Search O(log n)
======================================================================
APPROACH 3: Counting Sort / Frequency Array (O(n))
======================================================================

We don't need to check every x from 0 to n. Use frequency array:
  freq[min(num, n)]++   (cap at n, because x cannot exceed n)

Then iterate x from n down to 0, accumulate count.
If count == x at any point, return x.

No sorting needed → O(n) time, O(n) space.
*/

// ============================================================
// Approach 1: Linear Scan after Sorting
// ============================================================
class LinearScan {
    /*
    ALGORITHM:
    1. Sort nums in ascending order.
    2. For i = 0 to n-1:
         x = n - i   // number of elements from i to end
         Check: nums[i] >= x  (first element in the group >= x)
         AND:   (i == 0 || nums[i-1] < x)  (element before is < x,
                 so exactly n-i elements are >= x)
         If both true → return x
    3. Return -1

    WHY LINEAR SCAN WORKS:
    After sorting, at each index i:
      - nums[i] is the smallest element among those from i to n-1
      - If nums[i] >= (n-i), then ALL (n-i) elements from i onward are >= (n-i)
      - We also verify that nums[i-1] < (n-i) so the count is EXACTLY (n-i),
        not more (i.e., elements from i-1 onward would give (n-(i-1)) = x+1)
    */
public:
    int specialArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int x = n - i;  // candidate: number of elements from i to end

            // Check: every element from i onward is >= x,
            // AND no element before i is >= x (so count is exactly x)
            if (nums[i] >= x && (i == 0 || nums[i - 1] < x))
                return x;
        }

        return -1;
    }
};

// ============================================================
// Approach 2: Binary Search
// ============================================================
class BinarySearch {
    /*
    ALGORITHM:
    1. Sort nums.
    2. Binary search on index to find the first position where
       nums[mid] >= (n - mid).

       The condition pattern (false→true) is monotonic:
         i increases  → nums[i] increases, (n-i) decreases
         At some point, nums[i] >= (n-i) becomes true and stays true.

       low tracks the first index where condition becomes true.
    3. After binary search, low is the first valid index.
       Check: x = n - low
       Verify: nums[low] >= x AND (low == 0 || nums[low-1] < x)
       If valid → return x, else -1.

    WHY BINARY SEARCH WORKS:
    - The condition "nums[i] >= (n-i)" is monotonic (FFF...TTT).
    - Binary search finds the boundary in O(log n).
    - Verification step ensures exact count (not just >=).

    COMPLEXITY:
    - Sort: O(n log n)
    - Binary Search: O(log n)
    - Total: O(n log n)
    */
public:
    int specialArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int low = 0, high = n - 1;

        // Binary search for first index where nums[mid] >= (n-mid)
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int x = n - mid;

            if (nums[mid] >= x) {
                // Condition true: try smaller index (more elements)
                high = mid - 1;
            } else {
                // Condition false: need larger nums[mid], go right
                low = mid + 1;
            }
        }

        // low is the first index where condition holds
        if (low < n) {
            int x = n - low;
            // Verify exact count: first element >= x AND previous < x
            if (nums[low] >= x && (low == 0 || nums[low - 1] < x))
                return x;
        }

        return -1;
    }
};

// ============================================================
// Approach 3: Frequency Array (Counting Sort)
// ============================================================
class FrequencyCounting {
    /*
    ALGORITHM:
    1. Create a frequency array freq of size n+1, initialized to 0.
    2. For each num in nums:
         - If num >= n, increment freq[n] (cap at n, because x cannot
           exceed n — if num >= n, it contributes to any x up to n)
         - Else increment freq[num]
    3. Iterate x from n down to 0:
         count += freq[x]     // accumulate count of elements >= x
         if count == x → return x
    4. Return -1

    WHY THIS WORKS:
    - For any candidate x, the number of elements >= x equals
      the sum of freq[x] + freq[x+1] + ... + freq[n].
    - By iterating from n down to 0, we accumulate this sum
      incrementally (no need to recompute each time).
    - When count == x, we've found the answer.

    WHY freq[n] collects all nums[i] >= n:
    - x is at most n (can't have more than n elements >= x when
      there are only n total elements).
    - So any num >= n is indistinguishable for our check — it
      contributes to all x ≤ n.

    COMPLEXITY:
    - Time: O(n)
    - Space: O(n)
    */
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> freq(n + 1, 0);

        // Build frequency distribution, capping at n
        for (int num : nums) {
            if (num >= n) {
                freq[n]++;  // all values >= n count toward x ≤ n
            } else {
                freq[num]++;
            }
        }

        int count = 0;  // running count of elements >= current x

        // Check x from n down to 0
        for (int x = n; x >= 0; x--) {
            count += freq[x];   // add elements with value == x
            if (count == x)     // exactly x elements >= x
                return x;
        }

        return -1;
    }
};

int main() {
    vector<int> nums = {3, 5, 6, 7, 8};

    LinearScan sol1;
    cout << "Linear Scan:        " << sol1.specialArray(nums) << endl;

    BinarySearch sol2;
    cout << "Binary Search:      " << sol2.specialArray(nums) << endl;

    FrequencyCounting sol3;
    cout << "Frequency Counting: " << sol3.specialArray(nums) << endl;

    vector<int> nums2 = {0, 4, 3, 0, 1};

    cout << "\nTest 2: [0,4,3,0,1]" << endl;
    cout << "Linear Scan:        " << sol1.specialArray(nums2) << endl;
    cout << "Binary Search:      " << sol2.specialArray(nums2) << endl;
    cout << "Frequency Counting: " << sol3.specialArray(nums2) << endl;

    return 0;
}