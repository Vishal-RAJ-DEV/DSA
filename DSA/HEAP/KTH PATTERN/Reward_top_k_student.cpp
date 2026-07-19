/*
QUESTION:
Given positive_feedback, negative_feedback (lists of words), report (a list of
strings — each is a student's report), student_id, and an integer k:

Score for each student:
  +3 points for EVERY occurrence of a positive word in their report
  -1 point  for EVERY occurrence of a negative word in their report

Return the top k student IDs sorted by:
  1. Higher score first
  2. If scores tie → smaller student ID first

Example:
  positive_feedback = ["smart","brilliant","studious"]
  negative_feedback = ["not"]
  report = ["this student is studious and brilliant",
            "this student is not smart"]
  student_id = [1, 2]
  k = 2

  Student 1: +3(studious) +3(brilliant) = 6
  Student 2: +3(smart) -1(not) = 2
  Output: [1, 2]

---
*/

#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
using namespace std;

// ============================================================
// APPROACH: Min Heap of size k
//
// Intuition:
//   For each student, compute score = 3*(pos_word_count) - neg_word_count.
//   Use a min-heap of size k where the heap top is the "worst" among the
//   current best k students (lowest score, and for tie → largest id).
//   After processing all students, the heap holds the k best.
//   Pop & reverse to get best-first order.
// ============================================================

class Solution {
public:

    // ----------------------------------------------------------
    // Compare functor for min-heap on (student_id, score)
    //
    // priority_queue: cmp(a,b) returns true if a has LOWER priority
    // than b (a goes after/under b). The TOP of the heap is the
    // element with HIGHEST priority.
    //
    // We want the top to be the "worst" among our kept candidates:
    //   - Lower score → higher priority (sits at top → gets popped)
    //   - Same score → larger id → higher priority (sits at top → gets popped)
    //
    // This way, when we pop (size > k), we remove the worst candidate,
    // and the heap always retains the k best ones.
    // ----------------------------------------------------------
    struct Compare {
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) {

            if (a.second != b.second)
                return a.second > b.second;     // higher score → lower priority (keep)

            return a.first < b.first;           // smaller id → lower priority (keep)
        }
    };

    // ----------------------------------------------------------
    // count_pos: Count occurrences of positive words in a report.
    //   Splits the report by spaces, checks each word against
    //   the positive set, and returns 3 * count.
    // ----------------------------------------------------------
    int count_pos(unordered_set<string>& pos_set, string& report) {
        istringstream stream(report);
        string word;
        int res = 0;

        while (getline(stream, word, ' ')) {
            if (pos_set.find(word) != pos_set.end())
                res++;
        }

        return 3 * res;               // each positive word = +3 points
    }

    // ----------------------------------------------------------
    // count_neg: Count occurrences of negative words in a report.
    //   Same as count_pos, but returns raw count (each = -1 point).
    // ----------------------------------------------------------
    int count_neg(unordered_set<string>& neg_set, string& report) {
        istringstream stream(report);
        string word;
        int res = 0;

        while (getline(stream, word, ' ')) {
            if (neg_set.find(word) != neg_set.end())
                res++;
        }

        return res;                   // each negative word = -1 point
    }

    // ----------------------------------------------------------
    // topStudents: Main driver.
    //
    // Algorithm:
    //   1. Build hash sets from positive_feedback and negative_feedback
    //      for O(1) word lookup.
    //   2. Create a min-heap (priority_queue with custom Compare).
    //   3. For each student i:
    //        a) Compute score = count_pos(...) - count_neg(...)
    //        b) Push {student_id[i], score} into heap
    //        c) If heap.size() > k → pop() the worst candidate
    //   4. Transfer remaining heap contents to ans vector.
    //      (Heap yields worst-to-best order.)
    //   5. Reverse ans to get best-to-worst order (required output).
    //   6. Return ans.
    //
    // Dry Run:
    //   positive_feedback = ["smart","brilliant","studious"]
    //   negative_feedback = ["not"]
    //   report  = ["this student is studious and brilliant",
    //               "this student is not smart"]
    //   student_id = [1, 2]
    //   k = 1
    //
    //   Student 1: pos=2 (studious,brilliant)→ +6, neg=0 → score=6
    //     Push (1,6) → heap = [(1,6)]
    //   Student 2: pos=1 (smart)→ +3, neg=1 (not)→ -1 → score=2
    //     Push (2,2) → heap = [(1,6), (2,2)]  size=2 > k=1
    //     Pop top → (2,2) is top (lower score) → pop (2,2)
    //     heap = [(1,6)]
    //
    //   Transfer: ans = [1]
    //   Reverse: ans = [1]
    //   Return [1]  ✓
    //
    // Time  : O(N log k) where N = number of students
    // Space : O(N + P + N) = O(N) where P = unique feedback words
    // ----------------------------------------------------------
    vector<int> topStudents(vector<string>& positive_feedback,
                            vector<string>& negative_feedback,
                            vector<string>& report,
                            vector<int>& student_id,
                            int k) {

        unordered_set<string> pos_set;          // for O(1) positive lookup
        unordered_set<string> neg_set;          // for O(1) negative lookup

        for (auto &val : positive_feedback)
            pos_set.insert(val);
        for (auto &val : negative_feedback)
            neg_set.insert(val);

        // Min-heap: top = worst candidate (lowest score, largest id for ties)
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       Compare> pq;

        for (int i = 0; i < student_id.size(); i++) {

            int pos = count_pos(pos_set, report[i]);
            int neg = count_neg(neg_set, report[i]);

            int score = pos - neg;

            pq.push({student_id[i], score});

            if (pq.size() > k)
                pq.pop();                   // discard the worst candidate
        }

        vector<int> ans;

        while (!pq.empty()) {
            ans.push_back(pq.top().first);   // student_id
            pq.pop();
        }

        // pq pops worst-first → ans is worst-to-best → reverse for best-to-worst
        reverse(ans.begin(), ans.end());

        return ans;
    }
};


int main(){
    return 0;
}
