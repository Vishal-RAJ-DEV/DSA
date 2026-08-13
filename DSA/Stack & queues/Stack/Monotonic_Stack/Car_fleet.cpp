#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// SOLUTION 1 : SORT + COUNT  —  O(n log n) time, O(n) space
// ============================================================================
//
// PROBLEM : Cars drive toward a target. Each car has a position and speed.
//
//           A faster car BEHIND catches a slower car AHEAD →
//           they merge into ONE fleet (moving at the slower car's speed).
//
//           Count how many fleets reach the target.
//
// Example : target = 12
//
//           car A : pos 10 , speed 2
//           car B : pos  8 , speed 4
//           car C : pos  5 , speed 1
//
// ============================================================================
//
// THE CORE IDEA — compare TIME, not speed :
//
//              (target - position)
//     time  =  ───────────────────
//                   speed
//
//     A : (12-10)/2 = 1.0 h
//     B : (12- 8)/4 = 1.0 h
//     C : (12- 5)/1 = 7.0 h
//
// ============================================================================
//
// STEP 1 — WHY SORT BY POSITION (closest to target FIRST) ?
//
//     A car can only merge with cars AHEAD of it.
//     So we walk the road from the FRONT (closest) → BACK (farthest).
//
//     cars.rbegin() / cars.rend()  →  descending position order :
//
//           pos  10        8         5
//            ↓              ↓         ↓
//          [A]           [B]       [C]
//          front                      back
//         closest                  farthest
//        to target               from target
//
// ============================================================================
//
// STEP 2 — THE ONE RULE THAT DECIDES EVERYTHING :
//
//     car behind's time  <=  fleet-ahead's time  →  CATCHES UP → JOIN  (same fleet)
//     car behind's time  >   fleet-ahead's time  →  ARRIVES LATE → NEW FLEET
//
//     WHY ?  If the car behind arrives LATER than the fleet ahead,
//     it can never touch it — the fleet is already gone by the time
//     the slow car reaches the target.
//
// ============================================================================
//
// FULL WALKTHROUGH  (target = 12)
//
//     ROAD at t = 0 :
//
//     pos:  0   1   2   3   4   5   6   7   8   9  10  11  12
//          |---|---|---|---|---|---|---|---|---|---|---|---|
//                                 B(8,4)        A(10,2)
//                     C(5,1)
//
//     TRAVEL TIMES (time-lines start at t=0) :
//
//     t=0            t=1.0
//      ├───────────────┤
//     A┤               ├──────────────────→  A takes 1.0 h
//      └───────────────┘
//      ├───────────────┤
//     B┤               ├──────────────────→  B takes 1.0 h
//      └───────────────┘         same time → A and B MERGE → fleet 1
//
//     t=0                                        t=7.0
//      ├──────────────────────────────────────────┤
//     C┤                                          ├────→  C takes 7.0 h
//      └──────────────────────────────────────────┘      arrives later → fleet 2
//
//     ANSWER = 2 fleets
//
// ============================================================================
//
// LOOP LOGIC (walking sorted cars front → back) :
//
//     car A : first car → always a new fleet        fleets = 1 , lastTime = 1.0
//     car B : 1.0 <= lastTime(1.0) → joins fleet A  fleets = 1
//     car C : 7.0 >  lastTime(1.0) → new fleet      fleets = 2 , lastTime = 7.0
//
//     lastTime  =  arrival time of the fleet DIRECTLY AHEAD
//                (the only fleet the current car can possibly merge with)
//
// ============================================================================
//
// MENTAL PICTURE :
//
//     sorted cars (closest → farthest)
//
//        [A] → fleet 1 (lastTime = 1.0)
//         │
//        [B] → 1.0 <= 1.0  →  joins the fleet above (NO new fleet)
//         │
//        [C] → 7.0 > 1.0   →  can't catch it  →  NEW fleet (lastTime = 7.0)
//
//     the chain of "fleet boundaries" = the answer
//
// ============================================================================

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {

        int n = position.size();

        // Store {position, speed}
        vector<pair<int, int>> cars;

        for (int i = 0; i < n; i++) {
            cars.push_back({position[i], speed[i]});
        }

        // Closest to target first
        sort(cars.rbegin(), cars.rend());

        int fleets = 0;

        // Time of the fleet directly ahead
        double lastTime = 0;

        for (auto &it : cars) {

            // Time required to reach targetx
            double time = (double)(target - it.first) / it.second;

            // This car cannot catch the fleet ahead
            if (time > lastTime) {
                fleets++;

                // This becomes the new fleet ahead
                lastTime = time;
            }

            // If time <= lastTime:
            // this car catches the fleet ahead,
            // so no new fleet is created.
        }

        return fleets;
    }
};

// ============================================================================
// SOLUTION 2 : SORT + STACK  —  SAME idea as Solution 1, but with a stack
//
//     We process cars from CLOSEST to FARTHEST (sorted descending).
//     Instead of counting with lastTime, we PUSH the arrival time
//     onto the stack ONLY when it is bigger than everything above it.
//
//     STACK VISUALIZATION (target = 12, example above) :
//
//        sorted cars :   A(1.0)   B(1.0)   C(7.0)
//
//        A → stack empty → push 1.0       stack: [1.0]
//        B → 1.0 <= top(1.0) → skip      stack: [1.0]   ← joins fleet A
//        C → 7.0 >  top(1.0) → push 7.0  stack: [1.0, 7.0]  ← new fleet
//
//        ANSWER = st.size() = 2
//
//     The stack is monotonic — times only ever INCREASE going up:
//
//           ┌─────┐
//           │ 7.0 │  ← fleet 2  (slowest / newest)
//           ├─────┤
//           │ 1.0 │  ← fleet 1
//           └─────┘
//
//     Each level of the stack = one fleet boundary.
//
// ============================================================================
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {

        int n = position.size();

        // {position, speed}
        vector<pair<int, int>> cars;

        for (int i = 0; i < n; i++) {
            cars.push_back({position[i], speed[i]});
        }

        // Closest to target first
        sort(cars.rbegin(), cars.rend());

        stack<double> st;

        for (auto &it : cars) {

            // Time required to reach target
            double time = (double)(target - it.first) / it.second;

            // If current car cannot catch the fleet ahead,
            // it forms a new fleet.
            if (st.empty() || time > st.top()) {
                st.push(time);
            }

            // Otherwise:
            // time <= st.top()
            // current car joins the fleet ahead.
        }

        return st.size();
    }
};


int main(){
    return 0;
}