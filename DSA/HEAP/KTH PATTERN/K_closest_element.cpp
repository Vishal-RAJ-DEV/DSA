/*
QUESTION:
Given a sorted integer array "arr", two integers "k" and "x", return the k
closest integers to x in the array. The result must be sorted in ascending order.

Closeness rule:
  An integer a is closer to x than b if:
    |a - x| < |b - x|   OR
    |a - x| == |b - x| and a < b

Example 1:
Input:  arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]

Example 2:
Input:  arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]

Example 3:
Input:  arr = [1,1,1,10,10,10], k = 1, x = 9
Output: [10]

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// ============================================================
// APPROACH 1: Binary Search on Window Start (Most Optimal)
//
// Intuition:
//   Since the array is sorted, the k closest elements must form a
//   contiguous subarray (window) of size k. We binary search for the
//   leftmost index of this window.
//
//   For a candidate mid (potential window start), compare:
//     arr[mid]            and      arr[mid + k]
//   Which one is farther from x?
//     - If arr[mid] is farther → the window should start to the right
//       (left = mid + 1)
//     - Otherwise → the window should start to the left (right = mid)
//
//   Why this works:
//     For a sorted array, if arr[mid] is farther from x than arr[mid+k],
//     then every element before mid is also farther → discard left half.
//
// Algorithm:
//   1. left = 0, right = n - k  (the window start can be at most n-k)
//   2. Binary search:
//        mid = left + (right - left) / 2
//        if (x - arr[mid] > arr[mid + k] - x)  → left = mid + 1
//        else                                   → right = mid
//   3. Return arr[left ... left + k - 1]
//
// Time  : O(log(N - k) + k) ≈ O(log N)
// Space : O(1)                (excluding output)
// ============================================================
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {

        int left = 0;
        int right = arr.size() - k;

        while (left < right) {

            int mid = left + (right - left) / 2;

            // arr[mid] is farther from x than arr[mid + k] ?
            // Window should shift right.
            if (x - arr[mid] > arr[mid + k] - x)
                left = mid + 1;
            else
                right = mid;
        }

        return vector<int>(arr.begin() + left,
                           arr.begin() + left + k);
    }
};


// ============================================================
// APPROACH 2: Two Pointers (Shrink from both ends, with tie-break)
//
// Intuition:
//   Start with the full array window [left=0, right=n-1].
//   While window size > k, discard the farther of the two ends.
//   Since the array is sorted, the farthest element from x will be
//   at one of the two ends. Shrink until exactly k remain.
//
// Algorithm:
//   1. left = 0, right = n - 1
//   2. While (right - left + 1 > k):
//        Compute distances of left and right from x.
//        If left is closer (or equal distance and left value < right),
//          discard right (right--)
//        Else discard left (left++)
//   3. Return arr[left ... right]
//
// Time  : O(N - k)
// Space : O(1)
// ============================================================
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
       int left = 0;
       int right = arr.size() - 1;

       while (right - left + 1 > k) {
        int leftval  = abs(arr[left]  - x);
        int rightval = abs(arr[right] - x);

        // Left is closer (or equal with smaller value) → discard right
        if ((leftval < rightval) ||
            (leftval == rightval && arr[left] < arr[right]))
            right--;
        else
            left++;
       }

       return vector<int>(arr.begin() + left,
                          arr.begin() + right + 1);
    }
};


// ============================================================
// APPROACH 3: Two Pointers (Simplified condition)
//
// Intuition:
//   Same shrink-from-ends approach as Approach 2, but uses a
//   simpler condition: since the array is sorted, when distances
//   are equal, the left element is always the smaller one.
//   So "abs(left) <= abs(right)" already implies we should keep
//   left (which is smaller/equal) and discard right.
//
// Algorithm:
//   1. left = 0, right = n - 1
//   2. While (right - left + 1 > k):
//        If left is closer or equally close → discard right
//        Else → discard left
//   3. Return arr[left ... right]
//
// Time  : O(N - k)
// Space : O(1)
// ============================================================
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {

        int left = 0;
        int right = arr.size() - 1;

        while (right - left + 1 > k) {

            // Left is closer or equally close → discard the right end
            if (abs(arr[left] - x) <= abs(arr[right] - x))
                right--;
            else
                left++;
        }

        return vector<int>(arr.begin() + left,
                           arr.begin() + right + 1);
    }
};


// ============================================================
// APPROACH 4: Max Heap of size k
//
// Intuition:
//   Maintain a max-heap of size k ordered by (distance from x, value).
//   The top of the heap is the "farthest" among the current candidates.
//   For each element, push it; if size exceeds k, pop the farthest.
//   After processing all elements, the heap holds the k closest.
//   Finally sort the result (the problem requires ascending order).
//
// Comparator (max-heap):
//   - Larger distance → higher priority (sits at top → gets popped)
//   - Same distance → larger value → higher priority (gets popped)
//
// Algorithm:
//   1. Count frequencies (not needed here, just iterate arr)
//   2. For each num, push {abs(num - x), num} into max-heap
//   3. If heap size > k, pop (removes farthest element)
//   4. Transfer remaining k elements to ans vector
//   5. Sort ans in ascending order before returning
//
// Time  : O(N log k + k log k) ≈ O(N log k)
// Space : O(k)
// ============================================================
class Solution {
public:

    typedef pair<int,int> P;

    class Compare {
    public:
        // Max-heap: larger distance = higher priority at top
        // Same distance: larger value = higher priority at top
        bool operator()(P &a, P &b) {
            if (a.first == b.first)
                return a.second < b.second;   // larger value → higher priority
            return a.first < b.first;          // larger distance → higher priority
        }
    };

    vector<int> findClosestElements(vector<int>& arr, int k, int x) {

        priority_queue<P, vector<P>, Compare> pq;

        for (int num : arr) {

            pq.push({abs(num - x), num});

            if (pq.size() > k)
                pq.pop();                  // remove the farthest among current
        }

        vector<int> ans;

        while (!pq.empty()) {
            ans.push_back(pq.top().second);
            pq.pop();
        }

        sort(ans.begin(), ans.end());       // result must be sorted ascending

        return ans;
    }
};


// ============================================================
// APPROACH 5: Custom Sort (Brute Force)
//
// Intuition:
//   Sort the entire array by the closeness rule (distance from x,
//   then value for ties). Take the first k elements, then sort
//   the result ascending (since the closeness order differs from
//   the required ascending output order).
//
// Algorithm:
//   1. Sort arr by: (abs(a - x), a) ascending
//   2. Take first k elements into ans
//   3. Sort ans ascending
//
// Time  : O(N log N + k log k) ≈ O(N log N)
// Space : O(1) (sorting may use O(log N) stack space)
// ============================================================
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {

        sort(arr.begin(), arr.end(), [&](int a, int b) {

            if (abs(a - x) == abs(b - x))
                return a < b;               // same distance → smaller value first

            return abs(a - x) < abs(b - x);  // smaller distance first
        });

        vector<int> ans(arr.begin(), arr.begin() + k);

        sort(ans.begin(), ans.end());        // result must be sorted ascending

        return ans;
    }
};


// ============================================================
// APPROACH 6: Two Pointers (Expand from closest element)
//
// Intuition:
//   Use binary search to find the first element >= x (call it 'right').
//   Set 'left' just before it. Now we have two pointers expanding
//   outwards. In each of k steps, pick the closer element between
//   arr[left] and arr[right], and move that pointer outward.
//   The window (left+1 ... right-1) will contain the k closest.
//
// Algorithm:
//   1. right = lower_bound(arr, x)  (first element >= x)
//   2. left  = right - 1
//   3. For k iterations:
//        If left  < 0        → take from right (right++)
//        If right >= n       → take from left  (left--)
//        If left  is closer  → left--
//        If right is closer  → right++
//   4. Return arr[left + 1 ... right - 1]
//
// Time  : O(log N + k)
// Space : O(1)
// ============================================================
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {

        int n = arr.size();

        int right = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int left  = right - 1;

        while (k--) {

            if (left < 0)
                right++;                 // exhausted left side → take from right

            else if (right >= n)
                left--;                  // exhausted right side → take from left

            else if (abs(arr[left] - x) <= abs(arr[right] - x))
                left--;                  // left is closer (or equal & smaller) → take left

            else
                right++;                 // right is closer → take right
        }

        return vector<int>(arr.begin() + left + 1,
                           arr.begin() + right);
    }
};


int main(){
    return 0;
}
