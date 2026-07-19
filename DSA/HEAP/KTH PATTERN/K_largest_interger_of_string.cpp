/*
QUESTION:
Given an array of strings "nums" that represent large integers (may exceed
64-bit range), and an integer k, return the kth largest number as a string.

The numbers are given as strings because they can be arbitrarily large.
Since there are no leading zeros, we compare them as:
  - Longer string → larger number
  - Same length  → lexicographic comparison works as numeric comparison

Example:
Input:  nums = ["3","6","7","10"], k = 2
Output: "7"
Explanation: Sorted descending: "10" > "7" > "6" > "3" → 2nd largest = "7"

Input:  nums = ["2","21","12","1"], k = 3
Output: "2"
Explanation: Sorted descending: "21" > "12" > "2" > "1" → 3rd largest = "2"

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// ============================================================
// APPROACH 1: Min Heap of size k (Most Optimal)
//
// Intuition:
//   Maintain a min-heap of size at most k using a custom comparator
//   that orders numbers numerically (by length, then lexicographically).
//   For each element, push it. If heap size exceeds k, pop the smallest
//   (top of min-heap).
//   After processing all elements, the heap holds the k largest numbers,
//   and its top is the kth largest (smallest among the k largest).
//
// Custom comparator (min-heap on numeric value):
//   Returns true if 'a' should have lower priority than 'b'.
//   Larger numbers → higher priority (stay at bottom).
//   Smaller numbers → lower priority (sit at top, get popped).
//
// Algorithm:
//   1. Create a min-heap (priority_queue with custom cmp).
//   2. For each num in nums:
//        Push num into heap.
//        If heap.size() > k → pop() the smallest.
//   3. Return heap.top()  (the kth largest).
//
// Dry Run:
//   nums = ["3","6","7","10"], k = 2
//
//   Push "3" : heap = ["3"]                    size=1 ≤ 2
//   Push "6" : heap = ["3","6"]                size=2 ≤ 2
//   Push "7" : heap = ["3","6","7"] → pop "3"  heap = ["6","7"]  size=2
//   Push "10": heap = ["6","7","10"] → pop "6" heap = ["7","10"] size=2
//   Return top = "7"  ✓
//
// Time  : O(N log k)
// Space : O(k)
// ============================================================
class Solution {
public:
    string kthLargestNumber(vector<string>& nums, int k) {

        // Min-heap on numeric value:
        // Shorter string (or lexicographically smaller for same length)
        // has lower priority → sits at top.
        auto cmp = [](string a, string b) {
            if(a.size() == b.size()) return a > b;     // lexicographically smaller → lower priority
            return a.size() > b.size();                 // shorter → lower priority
        };

        priority_queue<string, vector<string>, decltype(cmp)> minH(cmp);

        for(auto &num : nums) {
            minH.push(num);
            if(minH.size() > k)
                minH.pop();       // remove the smallest among the heap
        }

        return minH.top();         // kth largest = smallest among the k largest
    }
};


// ============================================================
// APPROACH 2: Custom Sort (Descending)
//
// Intuition:
//   Sort the entire array in descending numeric order using the
//   same custom comparator (longer = larger; same length → lexicographic).
//   Then directly pick the (k-1)th index.
//
// Algorithm:
//   1. Sort nums descending using custom comparator.
//   2. Return nums[k-1].
//
// Dry Run:
//   nums = ["3","6","7","10"], k = 2
//   Sorted descending: ["10","7","6","3"]
//   Return nums[1] = "7"  ✓
//
// Time  : O(N log N)
// Space : O(1)  (sorting in-place)
// ============================================================
class Solution {
public:
    string kthLargestNumber(vector<string>& nums, int k) {

        sort(nums.begin(), nums.end(),
             [](const string &a, const string &b){
                 if(a.size() == b.size())
                     return a > b;                 // desc lexicographic
                 return a.size() > b.size();       // longer is larger → comes first
             });

        return nums[k-1];
    }
};


// ============================================================
// APPROACH 3: Ordered Multiset with Custom Comparator
//
// Intuition:
//   Insert all elements into a multiset sorted in descending numeric
//   order. Then advance an iterator to the (k-1)th position (0-based)
//   to get the kth largest.
//
// Algorithm:
//   1. Define a functor Compare (same logic: longer = larger).
//   2. Insert all nums into a multiset<string, Compare>.
//   3. Advance iterator to index k-1.
//   4. Return *it.
//
// Dry Run:
//   nums = ["3","6","7","10"], k = 2
//   Multiset (desc): ["10","7","6","3"]
//   Advance to index 1 → "7"  ✓
//
// Time  : O(N log N)
// Space : O(N)
// ============================================================
class Solution {
public:

    class Compare {
    public:
        // Returns true if a should appear before b (descending order)
        bool operator()(const string &a, const string &b) const {
            if(a.size() == b.size())
                return a > b;                     // desc lexicographic
            return a.size() > b.size();           // longer is larger
        }
    };

    string kthLargestNumber(vector<string>& nums, int k) {

        multiset<string, Compare> st;

        for(auto &x : nums)
            st.insert(x);

        auto it = st.begin();
        advance(it, k - 1);       // move to (k-1)th index (0-based)

        return *it;
    }
};


int main(){
    return 0;
}
