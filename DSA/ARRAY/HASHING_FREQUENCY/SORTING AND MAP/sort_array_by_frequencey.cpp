/*
QUESTION:
Given an array of integers "nums", sort the array in increasing order based
on the frequency of the values. If multiple values have the same frequency,
sort them in decreasing order (larger value first).

Example 1:
Input:  nums = [1,1,2,2,2,3]
Output: [3,1,1,2,2,2]
Explanation: 3 appears once, 1 appears twice, 2 appears thrice.
             Increasing frequency → 3(1), 1(2), 2(3).

Example 2:
Input:  nums = [2,3,1,3,2]
Output: [1,3,3,2,2]
Explanation: 1 appears once, 2 & 3 appear twice.
             Same frequency → larger value first: 3 before 2.
             So: 1(once), 3(twice), 2(twice).

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// ============================================================
// APPROACH 1: Custom Sort (using lambda + frequency map)
// Intuition:
//   Count frequencies, then sort the original array in-place using
//   a custom comparator that references the frequency map.
//   - Lower frequency first
//   - Same frequency → larger value first (descending)
// Time : O(N log N)   Space : O(N)
// ============================================================
class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {

        unordered_map<int,int> freq;

        for (int x : nums)
            freq[x]++;

        sort(nums.begin(), nums.end(),
             [&](int a, int b){
                if(freq[a] == freq[b])
                    return a > b;            // same freq → larger value first
                return freq[a] < freq[b];    // otherwise → increasing frequency
             });

        return nums;
    }
};


// ============================================================
// APPROACH 2: Max Heap with custom comparator
// Intuition:
//   Build a heap that gives smallest frequency first (and for ties,
//   largest value first). Pop sequentially while appending the value
//   'count' times to build the result.
//   Custom comparator makes it act as a min-heap on frequency and
//   a max-heap on value for tie-breaking.
// Time : O(N log N)   Space : O(N)
// ============================================================
class Compare {
public:
    // Returns true if 'a' has lower priority than 'b'
    // (i.e., 'a' should be placed below 'b' in the heap).
    // - Higher frequency → lower priority (so smallest freq stays on top)
    // - Same frequency  → smaller value → lower priority (so larger value stays on top)
    bool operator()(pair<int,int> &a, pair<int,int> &b) {
        if (a.second == b.second)
            return a.first < b.first;        // smaller value has lower priority
        return a.second > b.second;          // higher freq has lower priority
    }
};

class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {

        unordered_map<int,int> freq;

        for (int x : nums)
            freq[x]++;

        // Min-heap on frequency; for ties, max-heap on value
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       Compare> pq;

        for (auto &it : freq)
            pq.push({it.first, it.second});

        vector<int> ans;

        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();

            int value = cur.first;
            int count = cur.second;

            while (count--)
                ans.push_back(value);
        }

        return ans;
    }
};


// ============================================================
// APPROACH 3: Max Heap with negation trick (Simplest)
// Intuition:
//   Same as Approach 2 but avoids writing a custom comparator.
//   Store (-freq, value) pairs in a default max-heap.
//   The smallest frequency has the largest negative value, so it
//   sits at the top. For equal frequencies, the larger value's
//   negative is "larger" (e.g., -3 > -5), so larger value gets
//   priority — exactly the tie-break we need.
// Time : O(N log N)   Space : O(N)
// ============================================================
class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {

        unordered_map<int, int> freq;

        for (int x : nums)
            freq[x]++;

        // Default max-heap stores (-freq, value).
        // Top will be: smallest frequency (most negative), and for
        // ties, larger value (e.g. freq=2, value=5 → (-2,5) > (-2,3)).
        priority_queue<pair<int, int>> pq;

        for (auto &it : freq)
            pq.push({-it.second, it.first});

        vector<int> ans;

        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();

            int cnt = -it.first;      // restore positive count
            int value = it.second;

            while (cnt--)
                ans.push_back(value);
        }

        return ans;
    }
};


int main(){
    return 0;
}
