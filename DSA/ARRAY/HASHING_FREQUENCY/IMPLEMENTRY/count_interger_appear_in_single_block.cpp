/*
 * Problem: Count Integers That Appear in a Single Block
 *
 * Given an array of integers, count how many distinct integers appear
 * in exactly ONE contiguous block (group of same consecutive elements).
 *
 * What is a "block"?
 *   A block is a maximal group of consecutive equal elements.
 *   Example: [1, 2, 2, 1, 3, 3, 3]
 *            Block 1: [1]        (index 0)
 *            Block 2: [2, 2]     (indices 1-2)
 *            Block 3: [1]        (index 3)
 *            Block 4: [3, 3, 3]  (indices 4-6)
 *
 *   Element 1 appears in 2 blocks (Block 1 and Block 3) -> NOT counted
 *   Element 2 appears in 1 block  (Block 2)             -> counted
 *   Element 3 appears in 1 block  (Block 4)             -> counted
 *   Answer: 2
 *
 * Approach & Intuition:
 * ---------------------
 * Key Insight: An element appears in exactly one block if and only if
 * it is NEVER seen again after its block ends (i.e., after we encounter
 * a different element).
 *
 * Algorithm:
 *   1. Use two hash sets:
 *      - `seen`: stores all distinct elements encountered so far
 *      - `bad`:  stores elements that appear in MULTIPLE blocks
 *
 *   2. Traverse the array. When we encounter a NEW block (curr != prev):
 *      - If the current element was already in `seen`, it means this
 *        element appeared in an earlier block AND is now appearing again.
 *        So it spans multiple blocks -> mark it as `bad`.
 *      - Insert the current element into `seen`.
 *
 *   3. Final answer = (total unique elements) - (elements in multiple blocks)
 *      = seen.size() - bad.size()
 *
 * Why this works:
 *   - We only check at block boundaries (when curr != prev)
 *   - If an element is seen at a block boundary, it must have appeared
 *     in a previous block, so it now appears in at least 2 blocks
 *   - Elements that never trigger this condition appear in exactly 1 block
 *
 * Time Complexity:  O(n) - single pass through the array
 * Space Complexity: O(n) - for the hash sets
 *
 * Example Walkthrough:
 *   Input: nums = [1, 2, 2, 1, 3]
 *
 *   i=0: prev=1, seen={1}
 *   i=1: curr=2, curr!=prev(1), 2 not in seen -> seen={1,2}
 *   i=2: curr=2, curr==prev(2) -> skip
 *   i=3: curr=1, curr!=prev(2), 1 IN seen -> bad={1}, seen={1,2}
 *   i=4: curr=3, curr!=prev(1), 3 not in seen -> seen={1,2,3}
 *
 *   Result = seen.size() - bad.size() = 3 - 1 = 2
 *   (Elements 2 and 3 appear in exactly one block)
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSpecialIntegers(vector<int>& nums) {
        // `seen` stores all distinct elements encountered during traversal.
        // It tracks every unique value we've come across.
        unordered_set<int> seen;

        // `bad` stores elements that appear in MORE THAN ONE block.
        // These are the elements that fail the "single block" condition.
        unordered_set<int> bad;

        // Initialize prev with the first element of the array.
        // This marks the start of the first block.
        int prev = nums[0];

        // Insert the first element into seen set
        seen.insert(prev);

        // Traverse from the second element to the end
        for (int i = 1; i < nums.size(); i++) {
            int curr = nums[i];

            // Check if we've entered a NEW block (current element differs from previous)
            if (curr != prev) {
                // At a block boundary: check if this element was seen BEFORE.
                // If yes, it means this element appeared in an earlier block
                // and is now appearing again -> it spans multiple blocks.
                if (seen.count(curr)) {
                    bad.insert(curr);
                }

                // Mark this element as seen (whether new or already seen)
                seen.insert(curr);
            }

            // Update prev to track block transitions
            prev = curr;
        }

        // Answer = total unique elements - elements appearing in multiple blocks
        // = elements that appear in exactly one contiguous block
        return seen.size() - bad.size();
    }
};


int main(){
    return 0;
}