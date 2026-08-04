#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   PROBLEM : SPECIAL ARRAY WITH X ELEMENTS >= X (LeetCode 1608)
   Find a number x (0 <= x <= n, where n = nums.size()) such that
   EXACTLY x numbers in the array are GREATER THAN OR EQUAL to x.
   If no such x exists, return -1.

   Example: nums = [3, 5]  ->  x = 2 works, because 2 numbers
   (3 and 5) are >= 2.  Also x = 0 always counts 0 only if array
   is empty; for non-empty arrays x is usually > 0.

   ============================================================
   APPROACH 1 : FREQUENCY ARRAY (COUNTING)  -- O(n)
   ============================================================
   INTUITION :
   We need the answer "how many numbers are >= x" very fast for
   many possible x values. A frequency array lets us answer that
   in O(1) per x. The key trick: any number >= n can be lumped
   together into a single bucket, because for every candidate
   x <= n, any value >= n is certainly >= x. So we only need
   buckets 0..n.

   ALGORITHM :
   1. freq[i] = how many numbers are exactly equal to i
      (with all values >= n counted inside freq[n]).
   2. Walk x from n down to 0, accumulating cnt += freq[x].
      While going DOWNWARD, cnt = "count of numbers >= x"
      (because we keep adding the buckets of every value higher
       than x as we descend).
   3. The first x where cnt == x is the answer.

   DIAGRAM : nums = [0, 0, 3, 4, 4] , n = 5
     freq:  idx:  0   1   2   3   4   5
                [ 2,  0,  0,  1,  2,  0 ]

     x = 5: cnt += freq[5] = 0        -> cnt=0 != 5
     x = 4: cnt += freq[4] = 2        -> cnt=2 != 4
     x = 3: cnt += freq[3] = 1        -> cnt=3 == 3  -> return 3
     (3 numbers {3,4,4} are >= 3)  CORRECT.

   COMPLEXITY : Time O(n), Space O(n). Fastest.
   ============================================================ */

class Solution {
public:
    int specialArray(vector<int>& nums) {

        int n = nums.size();

        vector<int> freq(n + 1, 0);

        for (int num : nums) {
            if (num >= n)
                freq[n]++;
            else
                freq[num]++;
        }

        int cnt = 0;

        for (int x = n; x >= 0; x--) {

            cnt += freq[x];

            if (cnt == x)
                return x;
        }

        return -1;
    }
};

/* ============================================================
   APPROACH 2 : BINARY SEARCH ON THE ANSWER x  -- O(n log n)
   ============================================================
   INTUITION :
   Let f(x) = count of numbers >= x. As x INCREASES, f(x)
   DECREASES (monotonic). We search for a value x where f(x) == x.
   Because f(x) decreases and x increases, we can bisect the
   candidate range [0, n] like a classic binary search:
     - if f(mid) > mid  -> x is too small, look in the RIGHT half
       (bigger x gives smaller f, moving f down toward x).
     - if f(mid) < mid  -> x is too big, look in the LEFT half.
     - if f(mid) == mid -> found it.

   ALGORITHM :
   1. low = 0, high = n.
   2. While low <= high:
        mid = (low + high)/2
        cnt = count of nums[i] >= mid   (one O(n) scan)
        if cnt == mid return mid
        if cnt > mid  low  = mid + 1
        else          high = mid - 1
   3. Return -1.

   NOTE : Unlike classic "first position" binary search, this
   directly compares the monotonic function f(mid) with mid, so
   an exact equality check works because f(x) is integer-valued
   and changes by steps.

   COMPLEXITY : Time O(n log n), Space O(1). Log of iterations
   but each needs a full O(n) scan.
   ============================================================ */

class Solution {
public:
    int specialArray(vector<int>& nums) {

        int n = nums.size();

        int low = 0;
        int high = n;

        while (low <= high) {

            int mid = (low + high) / 2;

            int cnt = 0;

            for (int num : nums)
                if (num >= mid)
                    cnt++;

            if (cnt == mid)
                return mid;

            if (cnt > mid)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return -1;
    }
};

/* ============================================================
   APPROACH 3 : SORT + SINGLE PASS  -- O(n log n)
   ============================================================
   INTUITION :
   After sorting, the array is ascending. If there are exactly x
   numbers >= x, then those x numbers must be the LAST x elements
   of the sorted array. Consider index i (0-based):
       x = n - i     (number of elements from i..n-1)
   Element nums[i] is the SMALLEST of those x elements, so the
   condition "all last x elements are >= x" is equivalent to
   "nums[i] >= x". We also need the remaining n - x = i elements
   BEFORE index i to be STRICTLY < x, otherwise more than x
   numbers would be >= x. This is checked with nums[i-1] < x.

   ALGORITHM :
   1. Sort nums ascending.
   2. For i from 0 to n-1:
        x = n - i
        if nums[i] >= x  AND  (i == 0 OR nums[i-1] < x)
            return x
   3. Return -1.

   DIAGRAM : nums = [3, 5] -> sorted [3, 5], n = 2
     i=0: x=2 ; nums[0]=3 >= 2 ; i==0  -> return 2  CORRECT.
     (2 numbers {3,5} are >= 2.)

   DIAGRAM : nums = [0, 0, 3, 4, 4] -> sorted same, n = 5
     i=0: x=5 ; nums[0]=0 >= 5 ? NO
     i=1: x=4 ; nums[1]=0 >= 4 ? NO
     i=2: x=3 ; nums[2]=3 >= 3 YES ; nums[1]=0 < 3 YES -> return 3
     CORRECT.

   COMPLEXITY : Time O(n log n) [sorting], Space O(1) or O(n).
   ============================================================ */

class Solution {
public:
    int specialArray(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        int n = nums.size();

        for (int i = 0; i < n; i++) {

            int x = n - i;

            if (nums[i] >= x &&
                (i == 0 || nums[i - 1] < x))
                return x;
        }

        return -1;
    }
};

/* ============================================================
   APPROACH 4 : BRUTE FORCE  -- O(n^2)
   ============================================================
   INTUITION :
   x can only be an integer in [0, n] (if x > n then zero numbers
   can be >= x, and the count would never equal x). So we simply
   TRY every possible x from 0 to n, and for each x we count how
   many numbers are >= x with a fresh full-array scan. The first
   x whose count equals x is returned.

   ALGORITHM :
   1. For x = 0 .. n:
        cnt = 0
        for each num: if num >= x then cnt++
        if cnt == x return x
   2. Return -1.

   This is the most straightforward reading of the problem
   statement -- no clever counting, sorting or searching. It is
   only used to validate the other approaches, since it is too
   slow for large inputs.

   COMPLEXITY : Time O(n^2), Space O(1).
   ============================================================ */

class Solution {
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();

        for (int x = 0; x <= n; x++) {

            int cnt = 0;

            for (int num : nums) {
                if (num >= x)
                    cnt++;
            }

            if (cnt == x)
                return x;
        }

        return -1;
    }
};


int main(){
    return 0;
}