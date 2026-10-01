#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// QUESTION: Last Stone Weight (LeetCode 1046)
// ----------------------------------------------------------------------------
// You are given an array of integers `stones` where stones[i] is the weight
// of the ith stone.
//
// Process:
// 1. Take the two HEAVIEST stones, let them be x <= y.
// 2. If x == y, both stones are destroyed.
// 3. If x != y, x is destroyed and y becomes (y - x) [new stone put back].
// 4. Repeat until at most 1 stone is left.
//
// Return the weight of the last remaining stone (or 0 if none left).
//
// Example: stones = [2,7,4,1,8,1]
//   Step1: pick 7,8 -> push 1  => [2,4,1,1,1]
//   Step2: pick 4,2 -> push 2  => [1,1,1,2]
//   Step3: pick 2,1 -> push 1  => [1,1,1]
//   Step4: pick 1,1 -> both gone => [1]
//   Answer = 1
//
// WHAT IS ASKING HERE?
// -> Simulate this "smash two largest" process efficiently and return final weight.
//
// CORE IDEA / APPROACH IN THIS FILE:
// -> We always need the MAXIMUM two elements quickly.
// -> File shows 2 ways to do the same simulation:
//      Approach-1: Sort again and again (simple but slow).
//      Approach-2: Use Max-Heap / priority_queue (optimal).
// ============================================================================

// ----------------------------------------------------------------------------
// Approach-1: Simulation using Sorting
// Time  : O(n^2 * log n) -> sort of size n, done n times.
// Space : O(1) extra (sorting in-place, vector modified).
// Logic : Loop while >1 stone -> sort -> pop 2 largest -> push back diff.
// ----------------------------------------------------------------------------
class Solution_Sort {
public:
    int lastStoneWeight(vector<int>& stones) {
        // Keep smashing until 0 or 1 stone remains.
        while (stones.size() > 1) {
            // Sort ascending, so largest 2 stones are at the end.
            sort(stones.begin(), stones.end());

            // y = heaviest stone. Remove it from vector.
            int y = stones.back();
            stones.pop_back();

            // x = second heaviest stone. Remove it from vector.
            int x = stones.back();
            stones.pop_back();

            // If weights differ, new stone of weight (y - x) is formed.
            // If equal, both are destroyed, so push nothing.
            if (x != y) {
                stones.push_back(y - x);
            }
        }

        // If vector empty -> all destroyed -> return 0, else last stone.
        return stones.empty() ? 0 : stones[0];
    }
};



// ----------------------------------------------------------------------------
// Approach-2: Simulation using Max-Heap (priority_queue) - OPTIMAL
// Time  : O(n log n) -> each push/pop on heap is log n, done O(n) times.
// Space : O(n) for heap.
// Logic : Same as above, but heap always gives max in O(1) top + O(log n) pop.
//         No need to sort full array every time.
// WHY BETTER?
// -> Sorting each iteration re-orders all n elements.
// -> Heap only fixes the top part, so much faster for large n.
// ----------------------------------------------------------------------------
class Solution_Heap {
public:
    int lastStoneWeight(vector<int>& stones) {
        // Max-heap: largest element always on top.
        priority_queue<int> pq;

        // Push all stones into heap - O(n log n).
        for (int stone : stones) {
            pq.push(stone);
        }

        // Smash until 0 or 1 stone left in heap.
        while (pq.size() > 1) {
            // Get heaviest stone y and remove it.
            int y = pq.top();
            pq.pop();

            // Get second heaviest stone x and remove it.
            int x = pq.top();
            pq.pop();

            // If different, push back remaining weight (y - x).
            // Note: y >= x always because max-heap, so (y - x) >= 0.
            // If equal, both destroyed -> push nothing.
            if (x != y) {
                pq.push(y - x);
            }
        }

        // Heap empty -> answer 0, else top is last stone weight.
        return pq.empty() ? 0 : pq.top();
    }
};



// NOTE: Original file had two `class Solution` with same name,
// which causes compilation error (redefinition). Renamed above to
// `Solution_Sort` and `Solution_Heap` so both approaches can stay
// in same file for learning. For LeetCode submit, rename any one
// back to `Solution`.

int main(){
    return 0;
}
