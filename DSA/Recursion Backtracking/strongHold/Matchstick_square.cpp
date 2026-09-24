#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// PROBLEM: Matchsticks to Square
//
// Given an integer array matchsticks where matchsticks[i] is the length of
// the i-th matchstick, return true if you can make exactly one square using
// ALL matchsticks, and false otherwise. Each matchstick must be used exactly once.
//
// A square has 4 equal sides. So we need to partition the matchsticks into
// 4 groups where each group sums to the same value (the side length).
//
// EXAMPLE:
//   matchsticks = [1,1,1,1,2,2,2,2]
//   total sum = 12, target = 12/4 = 3 per side
//   Side 1: [1,1,1] = 3
//   Side 2: [1,1,1] = 3
//   Side 3: [2,1]   = 3
//   Side 4: [2,1]   = 3
//   Return true.
//
// APPROACH: Backtracking (Recursive Trial-and-Error)
//   We have 4 sides (buckets). We try to place each matchstick into one of
//   the 4 sides. If placing a stick on a side doesn't exceed the target,
//   we place it there and recurse to the next stick. If the recursion fails,
//   we remove the stick (backtrack) and try the next side.
//
// WHY SORT IN DESCENDING ORDER?
//   Placing larger sticks first prunes the search tree faster.
//   Large sticks are harder to fit, so it's better to commit them early.
//   If a large stick can't fit anywhere, we fail fast instead of exploring
//   many small-stick combinations first.
//
// WHY target = sum / 4?
//   A square has 4 equal sides. All matchsticks must be used.
//   So total sum must be divisible by 4, and each side must equal sum/4.
//   If sum % 4 != 0, it's impossible to form equal sides -> return false.
//
// ============================================================================

class Solution {
public:

    // sides[0..3] = current sum of matchsticks placed on each of the 4 sides
    // sticks      = the matchstick lengths (sorted descending for optimization)
    // target      = the required sum for each side = total_sum / 4
    vector<int> sides;
    vector<int> sticks;
    int target;

    // --------------------------------------------------------------------------
    // RECURSIVE BACKTRACKING FUNCTION
    //
    // Parameters:
    //   idx = index of the current matchstick we are trying to place
    //
    // We try to place sticks[idx] on each of the 4 sides.
    // If it fits (doesn't exceed target), we place it there and recurse.
    // If recursion returns false, we undo the placement (backtrack) and try next side.
    //
    // BASE CASE:
    //   If idx == sticks.size(), ALL matchsticks have been placed successfully.
    //   Return true (we found a valid square).
    //
    // WHY idx == sticks.size() works as base case:
    //   We are processing one stick at a time, from index 0 to n-1.
    //   When idx reaches n, we've tried to place all n sticks.
    //   If we reach this point without returning false earlier,
    //   it means all sticks fit perfectly into 4 sides of equal length.
    // --------------------------------------------------------------------------
    bool solve(int idx) {

        // BASE CASE: All matchsticks have been placed.
        // If we reach here, every stick was successfully assigned to a side.
        // All 4 sides must have reached 'target' (guaranteed by the <= check).
        if (idx == sticks.size()) {
            return true;
        }

        // TRY PLACING sticks[idx] ON EACH OF THE 4 SIDES
        //
        // Why 4 sides? A square has exactly 4 sides. We must distribute all
        // matchsticks into these 4 groups (buckets).
        //
        // This is like the "Partition into K Equal Sum Subsets" problem where K=4.
        for (int i = 0; i < 4; i++) {

            // PRUNING CHECK: Can this stick fit on side i?
            // If adding sticks[idx] to side[i] would exceed target, skip this side.
            //
            // Why <= target (not <)?
            //   Each side must equal exactly 'target'. If side[i] + sticks[idx]
            //   is exactly target, that's perfect - the side is complete.
            //   If it's less than target, the side still has room for more sticks.
            //   If it exceeds target, this placement is invalid.
            if (sides[i] + sticks[idx] <= target) {

                // CHOOSE: Place sticks[idx] on side i
                // Add the stick's length to the current side's sum.
                sides[i] += sticks[idx];

                // RECURSE: Try to place the NEXT stick (idx + 1).
                // If the next stick (and all remaining sticks) can be placed
                // successfully, the recursion will eventually return true all
                // the way back up.
                //
                // Short-circuit: as soon as one branch returns true,
                // we return true immediately (no need to try other placements).
                if (solve(idx + 1)) {
                    return true;
                }

                // BACKTRACK / UNDO: The placement of sticks[idx] on side i
                // did not lead to a valid solution.
                // Remove the stick from side i so we can try placing it
                // on a DIFFERENT side in the next iteration of the loop.
                //
                // This is the essence of backtracking:
                //   1. Make a choice (add stick to side)
                //   2. Recurse (explore consequences)
                //   3. Undo the choice (remove stick) if it didn't work
                //   4. Try the next option (next side in the loop)
                sides[i] -= sticks[idx];
            }
        }

        // If we tried all 4 sides and none of them led to a valid solution,
        // return false. This triggers backtracking in the caller.
        return false;
    }

    // --------------------------------------------------------------------------
    // MAIN FUNCTION: Entry point
    //
    // Steps:
    //   1. Calculate total sum of all matchsticks.
    //   2. Check if sum is divisible by 4 (required for 4 equal sides).
    //   3. Set target = sum / 4 (each side must equal this).
    //   4. Sort sticks in DESCENDING ORDER (optimization for pruning).
    //   5. Start backtracking from the first stick (index 0).
    // --------------------------------------------------------------------------
    bool makesquare(vector<int>& matchsticks) {

        // STEP 1: Calculate total sum of all matchsticks
        int sum = 0;
        for (int x : matchsticks) {
            sum += x;
        }

        // STEP 2: Divisibility check
        // If total sum is NOT divisible by 4, we cannot split into 4 equal parts.
        // Example: sum=10 -> 10/4 = 2.5 (not integer) -> impossible
        // Example: sum=12 -> 12/4 = 3 (integer) -> possible
        if (sum % 4 != 0)
            return false;

        // STEP 3: Each side of the square must have length = sum / 4
        // This is the target sum that each of the 4 sides must reach exactly.
        //
        // WHY sum / 4?
        //   Square = 4 equal sides. All matchsticks used.
        //   side1 + side2 + side3 + side4 = total_sum
        //   Since all sides are equal: 4 * side = total_sum -> side = total_sum / 4
        target = sum / 4;

        // Copy matchsticks to our member variable for manipulation
        sticks = matchsticks;

        // Initialize 4 sides, all starting at 0 (no matchsticks placed yet)
        sides = vector<int>(4, 0);

        // STEP 4: Sort in DESCENDING order (largest first)
        //
        // WHY sort descending?
        //   - Large sticks are hardest to place (they need more room).
        //   - By placing them first, we fail early if no valid arrangement exists.
        //   - Without sorting, we might waste time placing small sticks first,
        //     only to discover at the end that the large stick doesn't fit anywhere.
        //   - This is a CRITICAL optimization that can reduce runtime from exponential
        //     to practical for many test cases.
        //
        // rbegin/rend = reverse iterators (sorts largest to smallest)
        sort(sticks.rbegin(), sticks.rend());

        // STEP 5: Start recursive backtracking from stick index 0
        // Try to place all sticks into the 4 sides.
        return solve(0);
    }
};

// ============================================================================
// WHY THIS WORKS - THE BIG PICTURE:
//
// This is a classic "Partition into K Equal Sum Subsets" problem with K=4.
//
// We have 4 empty buckets (sides) and need to fill them so each reaches 'target'.
//
// The recursion tree looks like:
//
//                    Place stick 0
//                   /  |   |   \
//              Side0 Side1 Side2 Side3  (try all 4 sides)
//              /      |     |      \
//          stick1  stick1  stick1  stick1  (for each choice, try next stick)
//          /|\      /|\    /|\     /|\
//         ...     ...    ...    ...
//
// At each level, we try placing the current stick on each of the 4 sides.
// If it fits (doesn't exceed target), we go deeper.
// If we place all sticks, we found a valid square.
// If no side works for a stick, we backtrack (undo previous placements).
//
// TIME COMPLEXITY: O(4^n) in worst case (n = number of matchsticks)
//   Each stick can go on 4 sides, and we have n sticks.
//   But with sorting + pruning,实际 performance is much better.
//
// SPACE COMPLEXITY: O(n) for the recursion stack (depth = n)
// ============================================================================
