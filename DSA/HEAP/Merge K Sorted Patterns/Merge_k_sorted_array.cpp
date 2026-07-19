/*
QUESTION:
Given a matrix where each row is sorted in ascending order, merge all rows
into a single sorted array.

Example:
Input:  mat = [[1,3,5],
               [2,4,6],
               [0,7,8]]
Output: [0,1,2,3,4,5,6,7,8]

INTUITION:
  Each row is sorted. The global minimum at any point is the smallest among
  the current "heads" of all rows. Once we take that minimum, we advance
  that row by one — its new head becomes the next element.

  This is exactly the k-way merge pattern: maintain a min-heap of the
  current frontier (one element per row). At each step:
    1. Pop the smallest frontier element → this is the next global min
    2. Push the next element from the same row into the heap

  The heap always holds at most one element per row (size ≤ k), ensuring
  O(log k) per push/pop.

ALGORITHM:
  1. Skip empty rows; push the first element of every non-empty row as
     (value, row, col) into a min-heap.
  2. While heap is not empty:
       a. Pop top (smallest value) → append to result
       b. If next column exists in that row → push (mat[row][col+1], row, col+1)
  3. Return result.

DRY RUN:
  mat = [[1,3,5],
         [2,4,6],
         [0,7,8]]

  Heap (value, row, col):     Pop → result                 Push
  ───────────────────────────────────────────────────────────────
  (1,0,0) (2,1,0) (0,2,0)  → (0,2,0) → [0]                (7,2,1)
  (1,0,0) (2,1,0) (7,2,1)  → (1,0,0) → [0,1]              (3,0,1)
  (2,1,0) (3,0,1) (7,2,1)  → (2,1,0) → [0,1,2]            (4,1,1)
  (3,0,1) (4,1,1) (7,2,1)  → (3,0,1) → [0,1,2,3]          (5,0,2)
  (4,1,1) (5,0,2) (7,2,1)  → (4,1,1) → [0,1,2,3,4]        (6,1,2)
  (5,0,2) (6,1,2) (7,2,1)  → (5,0,2) → [0,1,2,3,4,5]      row 0 exhausted
  (6,1,2) (7,2,1)          → (6,1,2) → [0,1,2,3,4,5,6]    row 1 exhausted
  (7,2,1)                  → (7,2,1) → [0,1,2,3,4,5,6,7]  (8,2,2)
  (8,2,2)                  → (8,2,2) → [0,1,2,3,4,5,6,7,8] exhausted
  → Result: [0,1,2,3,4,5,6,7,8] ✓

TIME  : O(N log k)  — N = total elements, k = number of non-empty rows
SPACE : O(k)        — heap holds at most one element per row
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Custom struct instead of tuple — avoids operator> lookup issues
    // and structured-binding fragility on some compilers.
    struct Element {
        int value, row, col;
    };

    struct MinHeap {
        // Returns true if 'a' has lower priority than 'b'
        // (a goes after b, so smaller value sits on top).
        bool operator()(const Element &a, const Element &b) const {
            return a.value > b.value;
        }
    };

public:
    vector<int> mergeArrays(vector<vector<int>> &mat) {

        int rows = (int)mat.size();

        vector<int> res;

        // Min-heap using explicit custom comparator
        priority_queue<Element, vector<Element>, MinHeap> pq;

        // Seed the heap with the first element of every non-empty row
        for (int r = 0; r < rows; r++) {
            if (!mat[r].empty())
                pq.push({mat[r][0], r, 0});
        }

        while (!pq.empty()) {

            Element cur = pq.top();
            pq.pop();

            res.push_back(cur.value);

            // Push the next element from the same row (if it exists)
            if (cur.col + 1 < (int)mat[cur.row].size())
                pq.push({mat[cur.row][cur.col + 1], cur.row, cur.col + 1});
        }

        return res;
    }
};

int main(){
    return 0;
}
