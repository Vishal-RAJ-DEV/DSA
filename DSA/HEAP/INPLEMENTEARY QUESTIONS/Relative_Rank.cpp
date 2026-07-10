#include <bits/stdc++.h>
using namespace std;

/*
============================================================
  PROBLEM: Relative Ranks
  - Given an integer array 'score' of size n, where score[i]
    is the score of the i-th athlete.
  - Athletes are ranked by score (highest → 1st place).
  - Return a vector<string> where:
      - 1st place → "Gold Medal"
      - 2nd place → "Silver Medal"
      - 3rd place → "Bronze Medal"
      - 4th place onward → the rank as a string (e.g. "4", "5")
  - All scores are unique.

============================================================
  APPROACH 1: Max-Heap (Priority Queue)
============================================================
  - Push all (score, index) pairs into a max-heap (priority_queue).
  - The largest score automatically comes to the top.
  - Pop one by one, assigning ranks 1, 2, 3, ... to the
    corresponding original index.
  - Time: O(n log n)  Space: O(n)
*/

class RelativeRankHeap {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        // Max-heap of {score, originalIndex}
        priority_queue<pair<int, int>> pq;

        for (int i = 0; i < n; i++) {
            pq.push({score[i], i});
        }

        vector<string> ans(n);
        int place = 1;

        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            int idx = it.second;

            if (place == 1)      ans[idx] = "Gold Medal";
            else if (place == 2) ans[idx] = "Silver Medal";
            else if (place == 3) ans[idx] = "Bronze Medal";
            else                 ans[idx] = to_string(place);

            place++;
        }

        return ans;
    }
};

/*
============================================================
  APPROACH 2: Sort by Score (Pairs + Custom Comparator)
============================================================
  - Create a vector of pairs: (score, originalIndex).
  - Sort in descending order of score.
  - After sorting, the i-th element in sorted order has
    rank = i+1. Assign the corresponding rank string to
    the stored originalIndex.
  - Time: O(n log n)  Space: O(n)
*/

class RelativeRankSort {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();

        // pair = {score, originalIndex}
        vector<pair<int, int>> sortedPairs(n);
        for (int i = 0; i < n; i++) {
            sortedPairs[i] = {score[i], i};
        }

        // Sort descending by score
        sort(sortedPairs.begin(), sortedPairs.end(),
             [](auto& a, auto& b) { return a.first > b.first; });

        vector<string> ans(n);

        for (int i = 0; i < n; i++) {
            int idx = sortedPairs[i].second;

            if (i == 0)      ans[idx] = "Gold Medal";
            else if (i == 1) ans[idx] = "Silver Medal";
            else if (i == 2) ans[idx] = "Bronze Medal";
            else             ans[idx] = to_string(i + 1);
        }

        return ans;
    }
};

/*
============================================================
  APPROACH 3: Counting Sort (Score-to-Index Map)
============================================================
  - Since all scores are unique, we can use the score value
    itself as an array index (counting sort technique).
  - Step 1: Find maxScore.
  - Step 2: Create a vector score2Index of size maxScore+1.
            For each athlete i, set score2Index[score[i]] = i+1
            (store original index + 1 to distinguish from 0).
  - Step 3: Iterate from maxScore down to 0. For each score
            that has a valid index, assign the next rank.
  - This avoids sorting entirely.
  - Time: O(n + maxScore)  Space: O(maxScore)
    (Useful when maxScore is not too large relative to n.)
*/

class RelativeRankCount {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();

        // Find the maximum score
        int maxScore = *max_element(score.begin(), score.end());

        // score2Index[s] = original index + 1 (0 means unused)
        vector<int> score2Index(maxScore + 1, 0);

        for (int i = 0; i < n; i++) {
            score2Index[score[i]] = i + 1; // +1 so 0 can mean "empty"
        }

        vector<string> ans(n);
        int place = 1;

        // Walk scores from highest to lowest
        for (int s = maxScore; s >= 0; s--) {
            if (score2Index[s] == 0) continue; // no athlete has this score

            int idx = score2Index[s] - 1; // back to 0-based index

            if (place == 1)      ans[idx] = "Gold Medal";
            else if (place == 2) ans[idx] = "Silver Medal";
            else if (place == 3) ans[idx] = "Bronze Medal";
            else                 ans[idx] = to_string(place);

            place++;
        }

        return ans;
    }
};

/*
============================================================
  MAIN
============================================================
  Input:  score = {10, 3, 8, 9, 4}
  Sorted: 10 → Gold (index 0)
           9  → Silver (index 3)
           8  → Bronze (index 2)
           4  → "4" (index 4)
           3  → "5" (index 1)
  Output: {"Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"}
*/

int main() {
    vector<int> scores = {10, 3, 8, 9, 4};

    RelativeRankHeap sol1;
    RelativeRankSort sol2;
    RelativeRankCount sol3;

    auto print = [](vector<string>& v) {
        for (auto& s : v) cout << s << "  ";
        cout << endl;
    };

    auto r1 = sol1.findRelativeRanks(scores); print(r1);
    auto r2 = sol2.findRelativeRanks(scores); print(r2);
    auto r3 = sol3.findRelativeRanks(scores); print(r3);

    return 0;
}
