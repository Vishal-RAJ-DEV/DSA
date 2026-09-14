/*
================================================================================
PROBLEM: Kth Smallest Sum from Row-Sorted Matrix
================================================================================

Given a matrix where each ROW is sorted in non-decreasing order, pick exactly
one element from each row to form a sum. Find the kth smallest possible sum.

Example: mat = [[1,3,11], [2,4,6], [5,8,9]], k = 3
  Possible sums (pick one from each row):
    1+2+5=8, 1+2+8=11, 1+2+9=12, 1+4+5=10, ...
  Sorted sums: [8, 10, 11, 12, 13, ...]
  Answer: 11 (3rd smallest)

================================================================================
APPROACH: Row-by-Row Merging with Max-Heap
================================================================================

SIMPLE INTUITION:
  Think of it like merging sorted lists, but instead of merging two at a time,
  we merge row by row. After processing some rows, we have a list of possible
  partial sums. When we add a new row, we combine each partial sum with every
  element in the new row, then keep ONLY the k smallest results.

WHY A MAX-HEAP?
  - We only care about the k smallest values at any point.
  - A max-heap of size k stores the k smallest seen so far.
  - If a new value is smaller than the heap's maximum (top), the max is no
    longer needed — pop it and push the new value.
  - The heap top always holds the LARGEST among the k smallest (our filter).

STEP BY STEP:
  1. Start: sums = first row (the only possible sums with 1 row).
  2. For each next row i:
     a. For every existing partial sum + every element in row i → newSum.
     b. Keep only k smallest newSum values using max-heap.
     c. Replace sums with these k values.
  3. After all rows processed, sums holds up to k smallest full-row sums.
  4. The kth smallest is the MAXIMUM in sums (since they are the k smallest,
     the last one is the kth smallest).

WHY does this work?
  - Each step considers ALL combinations with the next row but prunes aggressively.
  - We never discard a value that could be in the top k — the heap ensures that.
  - Rows being sorted helps because smaller elements in each row produce smaller
    sums, so the first combinations explored are naturally the smallest.

TIME: O(m * k * log k) where m = number of rows, n = columns per row.
SPACE: O(k) for the heap and sums array.

================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        // Start with the first row as possible partial sums
        // (only one row processed so far, so sums = elements of row 0)
        vector<int> sums = mat[0];

        // Process each subsequent row one by one
        for (int i = 1; i < mat.size(); i++) {
            // Max-heap to keep only the k smallest combinations
            priority_queue<int> pq;

            // Combine every existing partial sum with every element in current row
            for (int sum : sums) {
                for (int x : mat[i]) {
                    int newSum = sum + x;  // new partial sum including row i

                    if (pq.size() < k) {
                        // Heap not full yet, just add
                        pq.push(newSum);
                    }
                    else if (newSum < pq.top()) {
                        // New sum is smaller than the largest in our top-k → replace
                        pq.pop();       // remove the largest (it's no longer needed)
                        pq.push(newSum); // add the better (smaller) value
                    }
                    // else: newSum >= pq.top(), it's too big, skip it
                }
            }

            // Extract k smallest sums from heap into the sums vector for next iteration
            sums.clear();
            while (!pq.empty()) {
                sums.push_back(pq.top());
                pq.pop();
            }
        }

        // sums now holds the k smallest full-row sums.
        // The kth smallest is the largest among them (heap stored them in max order).
        return *max_element(sums.begin(), sums.end());
    }
};



int main(){
    return 0;
}