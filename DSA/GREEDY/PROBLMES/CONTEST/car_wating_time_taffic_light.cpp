/*
================================================================================
Problem: Car Waiting Time at Traffic Lights (Minimum Penalty Assignment)
================================================================================

QUESTION UNDERSTANDING:
-----------------------
You are given:
  - period      : total duration of one full cycle (green + red) for all traffic lights.
  - lights[i]   : green phase duration of the ith traffic light.
                   Red phase of ith light = period - lights[i] seconds.
  - arrivalTime[j] : arrival time (in seconds) of the jth car.

Rules:
  1. All traffic lights are SYNCHRONIZED - they all start a new cycle at t = 0,
     t = period, t = 2*period, etc.
  2. Each car MUST be assigned to EXACTLY ONE traffic light.
  3. Multiple cars CAN be assigned to the SAME traffic light.
  4. Cars do NOT block each other - any number can cross simultaneously while green.

Waiting Time Calculation:
  For car j assigned to light i:
    r = arrivalTime[j] % period       // position within current cycle [0, period-1]
    if r < lights[i]  => wait = 0     // car arrives during GREEN phase
    if r >= lights[i] => wait = period - r  // car arrives during RED, must wait

  Penalty = MAXIMUM waiting time among ALL cars.

GOAL: Return the MINIMUM possible penalty by optimally assigning cars to lights.

--------------------------------------------------------------------------------

EXAMPLE WALKTHROUGH (Example 1):
  period = 8, lights = [2, 3], arrivalTime = [2, 5, 8, 11]

  max_green = 3 (best light has 3 seconds of green)

  Car at t=2:  r = 2%8 = 2  => 2 < 3 => wait = 0
  Car at t=5:  r = 5%8 = 5  => 5 >= 3 => wait = 8-5 = 3
  Car at t=8:  r = 8%8 = 0  => 0 < 3 => wait = 0
  Car at t=11: r = 11%8 = 3 => 3 >= 3 => wait = 8-3 = 5

  Penalty = max(0, 3, 0, 5) = 5

================================================================================

APPROACH (Greedy):
-------------------
KEY INSIGHT:
  If we assign a car to the light with the LONGEST green phase (maxgreen),
  the car has the BEST possible chance of arriving during green (wait = 0).

WHY maxgreen is always optimal:
  Case 1: r < maxgreen
    -> There EXISTS a light (the one with maxgreen green time) where the car
       arrives during green -> wait = 0. We can always achieve 0 wait.

  Case 2: r >= maxgreen
    -> NO light can help. Even the longest green phase (maxgreen) is not enough
       because r >= maxgreen. The car MUST wait period - r seconds regardless
       of which light it is assigned to.

THEREFORE:
  The answer is simply the MAXIMUM of (period - r) over all cars where r >= maxgreen.
  We don't need to track individual assignments - the greedy choice is always optimal.

TIME COMPLEXITY:  O(n + m) where n = len(arrivalTime), m = len(lights)
SPACE COMPLEXITY: O(1)

================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPenalty(int period, vector<int>& lights, vector<int>& arrivalTime) {
        // Step 1: Find the maximum green phase duration among all traffic lights.
        // This represents the "best" light - assigning cars here minimizes their wait.
        // If a car's r < maxgreen, we can always assign it to this light for 0 wait.
        int maxgreen = *max_element(lights.begin(), lights.end());

        // Step 2: Track the penalty (maximum waiting time across all cars).
        int ans = 0;

        // Step 3: For each car, compute its waiting time when assigned to the best light.
        for(int t : arrivalTime){
            // r = position within the current cycle [0, period-1]
            // This tells us WHERE in the cycle the car arrives.
            int r = t % period;

            int wait;

            // If r < maxgreen: car arrives during GREEN phase of the best light.
            // We can assign it to that light -> wait = 0.
            if(r < maxgreen){
                wait = 0;
            }
            // If r >= maxgreen: car arrives during RED phase of ALL lights.
            // No matter which light we choose, the car must wait for next cycle.
            // Waiting time = period - r (time until next cycle starts).
            else{
                wait = period - r;
            }

            // The penalty is the WORST (maximum) waiting time among all cars.
            ans = max(ans, wait);
        }

        return ans;
    }
};

// Driver code for testing with provided examples
int main(){
    Solution sol;

    // Example 1: period=8, lights=[2,3], arrivalTime=[2,5,8,11]
    // maxgreen=3, waits: [0, 3, 0, 5] -> penalty = 5
    vector<int> l1 = {2,3}, a1 = {2,5,8,11};
    cout << "Example 1 Output: " << sol.minPenalty(8, l1, a1) << endl;

    // Example 2: period=10, lights=[3,6,8], arrivalTime=[4,9,15]
    // maxgreen=8, waits: [0, 1, 0] -> penalty = 1
    vector<int> l2 = {3,6,8}, a2 = {4,9,15};
    cout << "Example 2 Output: " << sol.minPenalty(10, l2, a2) << endl;

    // Example 3: period=5, lights=[2], arrivalTime=[2,3,4,5,6]
    // maxgreen=2, waits: [3, 2, 1, 0, 0] -> penalty = 3
    vector<int> l3 = {2}, a3 = {2,3,4,5,6};
    cout << "Example 3 Output: " << sol.minPenalty(5, l3, a3) << endl;

    return 0;
}
