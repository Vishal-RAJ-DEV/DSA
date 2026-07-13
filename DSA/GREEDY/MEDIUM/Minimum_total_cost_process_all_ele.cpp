#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: Minimum Total Cost to Process All Elements

    You are given an array nums where each element represents a resource
    requirement that must be fulfilled in order. You start with 'k' units
    of resource.

    At each step:
        - If you have enough resource (available >= x), you simply consume x.
        - If not, you must perform "operations" to gain more resources.
          Each operation gives you exactly 'k' additional resources.
          The cost of the i-th operation overall is i (1-indexed).
          i.e., 1st operation costs 1, 2nd costs 2, 3rd costs 3, ...

    Goal: Find the minimum total cost to process all elements.

    Example:
        nums = [4, 7, 6], k = 5
        Start: available = 5, total_ops = 0, total_cost = 0
        Step 1: x=4, available=5 >= 4 -> consume: available = 1
        Step 2: x=7, available=1 < 7 -> need 6 more
                Need m = ceil(6/5) = 2 operations (costs: 1st=1, 2nd=2)
                Cost added = 1+2 = 3, total_ops=2, available=1+10=11
                Consume 7 -> available=4
        Step 3: x=6, available=4 < 6 -> need 2 more
                Need m = ceil(2/5) = 1 operation (costs: 3rd=3)
                Cost added = 3, total_ops=3, available=4+5=9
                Consume 6 -> available=3
        Total cost = 3 + 3 = 6

    This is a greedy + simulation problem: whenever we run short, we
    perform the minimum number of operations needed to cover the shortage.
*/


class Solution {
public:
    int minimumCost(vector<int>& nums, long long k) {

        const long long MOD = 1e9 + 7;

        // available: current resource we have. Start with k.
        long long available = k;

        // total_ops: total operations performed so far (across all steps).
        // Used to compute the cost of the next operation.
        long long total_ops = 0;

        // total_cost: accumulated answer (mod MOD).
        long long total_cost = 0;

        // Process each requirement in order
        for (int x : nums) {

            // CASE 1: Not enough resource -> need more operations
            if (available < x) {

                // diff: how much more resource we need
                long long diff = x - available;

                // m = ceil(diff / k): minimum operations needed to get >= diff resources.
                // Integer ceil division formula: (diff + k - 1) / k
                // Why? If diff is exactly divisible, result stays same.
                //      If there is a remainder, adding (k-1) pushes to next integer.
                // Example: diff=6, k=5 -> (6+4)/5 = 10/5 = 2 ✓
                //          diff=5, k=5 -> (5+4)/5 = 9/5 = 1 ✓
                long long m = (diff + k - 1) / k;

                /*
                    Cost formula for the next 'm' operations:

                    The operations performed so far are numbered 1..total_ops.
                    The next m operations will be numbered:
                        (total_ops+1), (total_ops+2), ..., (total_ops+m)

                    Sum of these costs =
                        (total_ops+1) + (total_ops+2) + ... + (total_ops+m)

                    = (total_ops repeated m times) + (1 + 2 + ... + m)

                    = m * total_ops  +  m * (m + 1) / 2
                      ^^^^^^^^^^^^^    ^^^^^^^^^^^^^^^^
                      m copies of       sum of first m
                      total_ops         natural numbers

                    The term 'm copies of total_ops' means total_ops appears
                    once in each of the m terms:

                        (total_ops + 1)
                        (total_ops + 2)
                        ...
                        (total_ops + m)

                    Adding vertically: m*total_ops + (1+2+...+m).
                */

                // Use __int128 to avoid overflow during multiplication
                // before applying modulo
                long long add =
                    ((__int128)m * total_ops +
                    (m * (m + 1)) / 2) % MOD;

                // Accumulate the cost
                total_cost = (total_cost + add) % MOD;

                // Update total operations count
                total_ops += m;

                // Gain m*k resources from these m operations
                available += m * k;
            }

            // CASE 2: Consume the resource 'x' (always happens)
            // If we entered the if-block above, available is now >= x.
            // If we didn't, available was already >= x.
            available -= x;
        }

        return (int)total_cost;
    }
};


/*
    COMPLEXITY ANALYSIS:

    Time: O(n)
        - Single pass through the array of size n.
        - Each iteration does O(1) arithmetic.
        - No nested loops.

    Space: O(1)
        - Only a few long long variables.
        - No auxiliary data structures.

    KEY TAKEAWAYS:
        1. Recognize greedy + simulation problems — process in order,
           take minimum action when needed.
        2. Ceiling division: (a + b - 1) / b
        3. Arithmetic progression sum: 1 + 2 + ... + m = m(m+1)/2
        4. When adding increasing-cost operations, derive formula
           instead of looping (avoids O(n²) worst case).
        5. Use __int128 for intermediate multiplication to prevent overflow
           before applying modulo.
*/


int main(){
    return 0;
}
