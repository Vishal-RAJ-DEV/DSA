#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PROBLEM: Gas Station (LeetCode 134)
================================================================================

There are n gas stations arranged in a circle. You are given:
  - gas[i]  = amount of gas available at station i
  - cost[i] = amount of gas required to travel from station i to i+1

You start with an empty tank at some station, and can travel clockwise.
Your car can hold unlimited gas.

Return the starting station index if you can complete one full circuit,
otherwise return -1. The solution is guaranteed to be unique if it exists.

Example:
  gas  = [1, 2, 3, 4, 5]
  cost = [3, 4, 5, 1, 2]
  Answer: 3 (start at station 3)

  Station 3: tank = 0 + 4 - 1 = 3  -> move to 4
  Station 4: tank = 3 + 5 - 2 = 6  -> move to 0
  Station 0: tank = 6 + 1 - 3 = 4  -> move to 1
  Station 1: tank = 4 + 2 - 4 = 2  -> move to 2
  Station 2: tank = 2 + 3 - 5 = 0  -> move to 3 (completed!)

================================================================================
APPROACH 1: BRUTE FORCE  --  O(n^2) time, O(1) space
================================================================================

IDEA:
  Try every station as the starting point. For each candidate, simulate the
  entire circuit. If we can complete it, return that station.

HOW IT WORKS:
  For each starting station i (from 0 to n-1):
    1. Set tank = 0
    2. For each station j in the circuit (starting from i, wrapping around):
       - tank += gas[j] - cost[j]
       - If tank < 0 at any point, this starting station FAILS -> break
    3. If we complete the full circle without tank going negative -> return i

WHY IT'S CORRECT:
  We exhaustively try every possible starting station. If a valid start exists,
  we will find it. No greedy optimization -- just pure simulation.

WHY IT'S SLOW:
  For each of n starting stations, we might traverse up to n stations.
  Total work = n x n = O(n^2).

VISUAL (gas = [1,2,3,4,5], cost = [3,4,5,1,2]):

  Try start = 0:
    tank: 0 + 1 - 3 = -2  -> FAIL (tank < 0)

  Try start = 1:
    tank: 0 + 2 - 4 = -2  -> FAIL

  Try start = 2:
    tank: 0 + 3 - 5 = -2  -> FAIL

  Try start = 3:
    tank: 0 + 4 - 1 = 3   -> OK
    tank: 3 + 5 - 2 = 6   -> OK
    tank: 6 + 1 - 3 = 4   -> OK
    tank: 4 + 2 - 4 = 2   -> OK
    tank: 2 + 3 - 5 = 0   -> OK (completed circuit!)
    Return 3

================================================================================
APPROACH 2: GREEDY  --  O(n) time, O(1) space
================================================================================

INSIGHT:
  1. If total_gas < total_cost, completing the circuit is IMPOSSIBLE.
     Reason: you can't travel a route that costs more fuel than you
     have across the entire trip, regardless of starting point.

  2. If total_gas >= total_cost, a valid start MUST exist (by problem
     guarantee it's unique). The question is: which station?

  3. KEY OBSERVATION -- "The discard range" trick:
     Traverse stations in order. Keep a running tank. If at station i
     the tank goes negative, then NO station between [start ... i] can
     be a valid starting station. Why?

     Proof: Suppose we start at station `start`. When we reach station
     i, tank goes negative. This means the net gas from start to i
     is < 0. Now consider any station j in (start, i]. Starting at j
     means you skip stations start through j-1, which had POSITIVE or
     ZERO net contribution (otherwise we would have failed earlier).
     Skipping positive fuel only leaves you with LESS fuel at station i,
     so you'd fail even earlier. Therefore none of them can work.

     So we discard the entire prefix [start ... i], set start = i+1,
     and reset tank to 0.

  4. After one O(n) pass, `start` holds the unique valid answer.

This is greedy because at each failure point we make a locally optimal
decision (discard all prior candidates) that is provably globally correct.

================================================================================
*/

// ============================================================================
// BRUTE FORCE SOLUTION -- O(n^2) time, O(1) space
// ============================================================================
class SolutionBrute {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        // Try every station as the starting point
        for (int start = 0; start < n; start++) {

            int tank = 0;        // fuel in tank
            bool success = true; // assume this start works until proven otherwise

            // Simulate traveling n stations (full circle)
            // j goes from start, wraps around using (start + j) % n
            for (int j = 0; j < n; j++) {
                int idx = (start + j) % n;  // current station index (circular)

                // Arrive at station idx: gain gas[idx], then spend cost[idx] to leave
                tank += gas[idx] - cost[idx];

                // If tank goes negative, we ran out of fuel -- this start fails
                if (tank < 0) {
                    success = false;
                    break;  // no need to continue, try next starting station
                }
            }

            // If we completed the full circle without running out of fuel
            if (success) {
                return start;  // found the valid starting station
            }
        }

        // No starting station works
        return -1;
    }
};

// ============================================================================
// GREEDY SOLUTION -- O(n) time, O(1) space
// ============================================================================
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        // --- PASS 1: Feasibility check ---
        int total_gas = 0;
        int total_cost = 0;
        for (int i = 0; i < n; i++) {
            total_gas  += gas[i];
            total_cost += cost[i];
        }
        // If overall fuel is insufficient, no starting point can work
        if (total_gas < total_cost) return -1;

        // --- PASS 2: Find the starting station ---
        int start = 0;   // current candidate starting station
        int tank  = 0;   // current fuel in the tank

        for (int i = 0; i < n; i++) {
            // Net change: fuel gained at i minus fuel spent to leave i
            tank += gas[i] - cost[i];

            // If tank goes negative, stations [start ... i] are all invalid
            if (tank < 0) {
                start = i + 1;   // try the next station as new candidate
                tank  = 0;       // reset tank for the new attempt
            }
        }

        // start now holds the unique valid starting index
        return start;
    }
};

// ============================================================================
// MAIN -- Test both approaches
// ============================================================================
int main() {
    // Example 1: gas = [1,2,3,4,5], cost = [3,4,5,1,2], answer = 3
    vector<int> gas1  = {1, 2, 3, 4, 5};
    vector<int> cost1 = {3, 4, 5, 1, 2};

    // Example 2: gas = [2,3,4], cost = [3,4,3], answer = -1 (impossible)
    vector<int> gas2  = {2, 3, 4};
    vector<int> cost2 = {3, 4, 3};

    SolutionBrute brute;
    Solution greedy;

    cout << "Example 1:" << endl;
    cout << "  Brute Force: " << brute.canCompleteCircuit(gas1, cost1) << endl;
    cout << "  Greedy:      " << greedy.canCompleteCircuit(gas1, cost1) << endl;

    cout << "Example 2:" << endl;
    cout << "  Brute Force: " << brute.canCompleteCircuit(gas2, cost2) << endl;
    cout << "  Greedy:      " << greedy.canCompleteCircuit(gas2, cost2) << endl;

    return 0;
}
