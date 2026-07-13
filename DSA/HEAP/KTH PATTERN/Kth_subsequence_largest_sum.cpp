#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 2099. Find Subsequence of Length K With the Largest Sum

    Given an integer array nums and an integer k, return any subsequence of
    length k that has the largest possible sum.

    A subsequence is an array derived from another array by deleting some or
    no elements without changing the order of the remaining elements.

    In other words: pick k elements from nums that give the maximum sum,
    and return them in their original relative order.

    Example:
        Input: nums = [2,1,3,3], k = 2
        Output: [3,3]
        Explanation: The largest 2 values are 3 and 3 (indices 2 and 3).
                     Their original order is [3,3].

        Input: nums = [-1,-2,3,4], k = 3
        Output: [-1,3,4]
        Explanation: The largest 3 values are 4, 3, -1 (sum = 6).
                     Original order: -1 (idx 0), 3 (idx 2), 4 (idx 3).

        Input: nums = [3,4,3,3], k = 2
        Output: [3,4]
        Explanation: Largest 2 values are 4 and one of the 3's.
                     Original order gives [3,4] (indices 0 and 1).
*/


// =========================================================
// APPROACH 1: Min-Heap of Size k — O(n log k + k log k)
// =========================================================
/*
    LOGIC:
        1. Use a min-heap (priority_queue with greater<pair<int,int>>)
           of size at most k. The heap stores {value, originalIndex}.
        2. Iterate through nums. Push each {value, index} into the heap.
        3. If heap size exceeds k, pop the smallest element (min-heap pops
           the minimum). This ensures the heap always holds the k largest
           elements seen so far.
        4. After processing all elements, the heap contains the k largest
           values from nums (along with their original indices).
        5. Pop all elements from heap into a temporary vector.
        6. Sort this vector by original index (ascending) to restore the
           original subsequence order.
        7. Extract the values into ans vector and return.

        Intuition:
        - The k largest values give the maximum possible sum.
        - We only need to find which k values are largest, then reorder them
          by their original position to maintain subsequence property.
        - Min-heap of size k efficiently tracks the top k largest elements
          in O(n log k) instead of O(n log n).

    TIME COMPLEXITY:
        - Iterating nums and heap operations (push/pop): O(n log k)
          Each push is O(log k), and at most n-k pops, each O(log k).
        - Popping k elements from heap into temp: O(k log k)
        - Sorting temp by index: O(k log k)
        - Overall: O(n log k + k log k)
        - If k is small relative to n, this is essentially O(n log k).

    SPACE COMPLEXITY:
        - Min-heap stores at most k pairs: O(k)
        - temp vector: O(k)
        - ans vector: O(k)
        - Overall: O(k)
*/
class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {

        // Min-heap: smallest element is at top
        // Stores {value, originalIndex}
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        for (int i = 0; i < nums.size(); i++) {
            pq.push({nums[i], i});

            if (pq.size() > k)
                pq.pop();  // removes the smallest among top-k candidates
        }

        // Extract top k from heap
        vector<pair<int,int>> temp;

        while (!pq.empty()) {
            temp.push_back(pq.top());
            pq.pop();
        }

        // Sort by original index to restore subsequence order
        sort(temp.begin(), temp.end(),
             [](auto &a, auto &b) {
                 return a.second < b.second;
             });

        // Extract values
        vector<int> ans;

        for (auto &x : temp)
            ans.push_back(x.first);

        return ans;
    }
};


// =========================================================
// APPROACH 2: Full Sort by Value — O(n log n + k log k)
// =========================================================
/*
    LOGIC:
        1. Pair each element with its original index: {value, index}.
        2. Sort ALL elements by value in descending order (largest first).
        3. Take the first k elements (these are the k largest values).
        4. Sort these k elements by original index (ascending) to restore
           the subsequence order.
        5. Extract values into result and return.

        This is a simpler, more direct approach: find top k by sorting,
        then reorder by index.

    TIME COMPLEXITY:
        - Pairing elements with indices: O(n)
        - Sorting all n elements by value: O(n log n)
        - Sorting top k elements by index: O(k log k)
        - Overall: O(n log n + k log k)
        - This is worse than Approach 1 when n is large and k is small,
          because we sort ALL n elements instead of maintaining a heap of
          size k.

    SPACE COMPLEXITY:
        - numsWithIndices vector of size n: O(n)
        - topK vector: O(k)
        - result vector: O(k)
        - Overall: O(n)
*/
class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<pair<int, int>> numsWithIndices;
        for (int i = 0; i < nums.size(); i++) {
            numsWithIndices.push_back({nums[i], i});
        }

        // Sort by value descending
        sort(numsWithIndices.begin(), numsWithIndices.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.first > b.first;
             });

        // Take top k and sort by original index
        vector<pair<int, int>> topK(numsWithIndices.begin(), numsWithIndices.begin() + k);
        sort(topK.begin(), topK.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second < b.second;
             });

        // Extract values
        vector<int> result;
        for (auto& p : topK) {
            result.push_back(p.first);
        }

        return result;
    }
};  


int main(){
    return 0;
}
