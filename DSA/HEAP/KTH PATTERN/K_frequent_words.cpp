/*
QUESTION:
Given an array of strings "words" and an integer k, return the k most frequent words.
The answer must be sorted by frequency (highest to lowest).
If two words have the same frequency, they must appear in lexicographical (ascending) order.

Example:
Input:  words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" and "love" appear twice; "i" comes before "love" (lexicographically).

Input:  words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
Explanation: "the"(3), "is"(2), "sunny"(1), "day"(1); "day" < "sunny" lexicographically so "day" comes first.

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// APPROACH 1: Custom Sort (Brute Force)
// Intuition:
//   Count frequencies, then sort all (word, freq) pairs with a
//   custom comparator. Finally take the first k elements.
// Time : O(N log N)   Space : O(N)
// ============================================================
class Solution {
public:

    static bool cmp(pair<string,int> &a, pair<string,int> &b){
        // Same frequency ? sort lexicographically ascending
        if(a.second == b.second)
            return a.first < b.first;
        // Otherwise sort by frequency descending
        return a.second > b.second;
    }

    vector<string> topKFrequent(vector<string>& words, int k) {

        unordered_map<string,int> freq;         // word -> frequency

        for(auto &word : words)                 // count frequencies
            freq[word]++;

        vector<pair<string,int>> vec;           // transfer to vector

        for(auto &it : freq)
            vec.push_back(it);

        sort(vec.begin(), vec.end(), cmp);      // sort using custom comparator

        vector<string> ans;

        for(int i=0;i<k;i++)                    // pick top k
            ans.push_back(vec[i].first);

        return ans;
    }
};


// ============================================================
// APPROACH 2: Max Heap (All elements pushed, then pop k times)
// Intuition:
//   Use a max-heap based on frequency (lexicographically smaller
//   wins ties). Push all (word, freq) pairs, then pop the top k.
// Time : O(N log N)   Space : O(N)
// ============================================================
class Solution {
public:
    typedef pair<string,int> p;

    vector<string> topKFrequent(vector<string>& words, int k) {
        int n = words.size();
        unordered_map<string, int> mpp;

        for(auto& s : words)
            mpp[s]++;

        // Max-heap comparator:
        // For same freq → lexicographically smaller word stays on top
        // Otherwise     → higher frequency stays on top
        auto cmp = [](p &a, p &b){
            if(a.second == b.second)
                return a.first > b.first;       // 'a' > 'b' means lexicographically smaller gets higher priority
            return a.second < b.second;         // higher freq gets higher priority
        };

        priority_queue<p, vector<p>, decltype(cmp)> pq(cmp);

        for(auto &it : mpp)
            pq.push({it.first, it.second});

        vector<string> ans;
        while(k--){
            ans.push_back(pq.top().first);
            pq.pop();
        }

        return ans;
    }
};


// ============================================================
// APPROACH 3: Min Heap of size k (Most optimal)
// Intuition:
//   Maintain a min-heap of size at most k. The heap keeps the
//   "worst" among the top k at the top. For each (word,freq):
//     - push it
//     - if size > k, pop the top (removes weakest candidate)
//   At the end, the heap holds the k most frequent words.
//   Since it's a min-heap, we pop in increasing order and then
//   reverse to get the required descending order.
// Time : O(N log k)   Space : O(N)
// ============================================================
class Solution {
public:

    typedef pair<string,int> P;

    class Compare {
    public:
        // For a MIN-HEAP:
        // Returns true if 'a' has LOWER priority than 'b'
        // i.e., 'a' should be placed below 'b'.
        //
        // We want the heap top to be the "worst" among the best k,
        // so we pop it when a better candidate arrives.
        bool operator()(P &a, P &b){
            if(a.second == b.second)
                return a.first < b.first;       // lexicographically larger is "worse" → stays near top
            return a.second > b.second;         // lower frequency is "worse" → stays near top
        }
    };

    vector<string> topKFrequent(vector<string>& words, int k) {

        unordered_map<string,int> freq;

        for(auto &word : words)
            freq[word]++;

        priority_queue<P, vector<P>, Compare> pq;    // min-heap

        for(auto &it : freq){
            pq.push({it.first, it.second});

            if(pq.size() > k)                 // keep only k best elements
                pq.pop();                     // remove the worst among them
        }

        vector<string> ans;

        while(!pq.empty()){
            ans.push_back(pq.top().first);
            pq.pop();
        }

        // Why reverse?
        // The min-heap top is the worst among the best k.
        // As we pop, we get elements in increasing order of
        // desirability (worst first).
        // We need descending order → reverse.
        //
        // Example:
        //   apple -> 5
        //   cat   -> 4
        //   dog   -> 3
        //
        // Min-heap (top = worst):  dog (3) → cat (4) → apple (5)
        // Popping gives:           dog, cat, apple
        // Required answer:         apple, cat, dog
        // So we reverse:

        reverse(ans.begin(), ans.end());

        return ans;
    }
};


int main(){

    return 0;
}
