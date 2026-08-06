#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
? PROBLEM: Gas Station (LeetCode 134)
? 
? There are n gas stations arranged in a circle. You are given:
?   - gas[i]  = amount of gas available at station i
?   - cost[i] = amount of gas required to travel from station i to i+1
?
? You start with an empty tank at some station, and can travel clockwise.
? Your car can hold unlimited gas.
?
? Return the starting station index if you can complete one full circuit,
? otherwise return -1. The solution is guaranteed to be unique if it exists.
?
?
? INTUITION:
? The brute force way: try every station as start, simulate, O(n²).
?
? Greedy insight:
?   1. If total_gas < total_cost, completing the circuit is IMPOSSIBLE.
?      Reason: you can't travel a route that costs more fuel than you
?      have across the entire trip, regardless of starting point.
?
?   2. If total_gas >= total_cost, a valid start MUST exist (by problem
?      guarantee it's unique). The question is: which station?
?
?   3. KEY OBSERVATION — "The discard range" trick:
?      Traverse stations in order. Keep a running tank. If at station i
?      the tank goes negative, then NO station between [start ... i] can
?      be a valid starting station. Why?
?
?      Proof: Suppose we start at station `start`. When we reach station
?      i, tank goes negative. This means the net gas from start to i
?      is < 0. Now consider any station j in (start, i]. Starting at j
?      means you skip stations start through j-1, which had POSITIVE or
?      ZERO net contribution (otherwise we would have failed earlier).
?      Skipping positive fuel only leaves you with LESS fuel at station i,
?      so you'd fail even earlier. Therefore none of them can work.
?
?      So we discard the entire prefix [start ... i], set start = i+1,
?      and reset tank to 0.
?
?   4. After one O(n) pass, `start` holds the unique valid answer.
?
? This is greedy because at each failure point we make a locally optimal
? decision (discard all prior candidates) that is provably globally correct.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        // ——— PASS 1: Feasibility check ———
        int total_gas = 0;
        int total_cost = 0;
        for (int i = 0; i < n; i++) {
            total_gas  += gas[i];
            total_cost += cost[i];
        }
        // If overall fuel is insufficient, no starting point can work
        if (total_gas < total_cost) return -1;

        // ——— PASS 2: Find the starting station ———
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



int main() {
    
    return 0;
}
