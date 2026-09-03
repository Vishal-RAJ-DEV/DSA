#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Maximize Distance to Closest Person (LeetCode 849)

    Given a row of seats represented by a binary array where:
        1 = seat is occupied (person sitting)
        0 = seat is empty

    Find the maximum distance to the closest person if you sit in an empty seat.
    Distance = number of seats between you and the closest occupied seat.

    Example: [1, 0, 0, 0, 1, 0, 0, 1] → answer = 3
    (sitting at index 3, closest person is 2 seats away on either side → distance = 2)
    Actually sitting at index 2 or 3 gives distance 2, but sitting between two 1s at
    index 3 gives min(3,1) = 1. Best is edge: index 0 is 1, so edge empty seats
    from index 0 count as first distance.

    KEY INSIGHT:
    Three cases to consider:
    1. Edge seats before the first occupied seat → distance = index of first '1'
    2. Gap between two consecutive occupied seats → best seat is in the middle → distance = gap / 2
    3. Edge seats after the last occupied seat → distance = (n - 1) - index of last '1'
*/

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int n = seats.size();

        // Step 1: Find the index of the FIRST occupied seat (first person)
        // and the LAST occupied seat (last person).
        // This helps us handle edge cases (empty seats before first person
        // and after last person).
        int first = -1;  // index of first person (leftmost occupied seat)
        int last = -1;   // index of last person (rightmost occupied seat)

        for(int i = 0; i < n; i++){
            if(seats[i] == 1){
                if(first == -1){
                    first = i;   // first time we see a person → record index
                }
                last = i;   // keep updating last → final value is rightmost person
            }
        }

        // Step 2: Handle edge case — if ALL seats are empty (no person found)
        // But per problem constraints, at least one person is always present,
        // so this case won't occur. Still, 'first' and 'last' are valid here.

        // Step 3: Case 1 — Empty seats BEFORE the first person.
        // If you sit at index 0 and first person is at index 'first',
        // your distance to closest person = 'first' seats.
        // (There's no person to your left, only to the right.)
        // Initialize ans with this edge distance.
        int ans = first;

        // Step 4: Case 2 — Empty seats BETWEEN two consecutive people.
        // Find all gaps between consecutive '1's.
        // Best seat in a gap of size 'gap' is the middle → distance = gap / 2
        // (integer division automatically floors it, giving optimal seat)
        // 'prev' tracks the index of the previous occupied seat.
        int prev = first;

        for(int i = first + 1; i < n; i++){
            if(seats[i] == 1){
                // Gap between prev and i: (i - prev) seats in between
                // But distance to closest person from middle seat = (i - prev) / 2
                // Example: seats at index 1 and 4 → gap = 3 empty seats (2,3)
                //   Best seat = index 2 or 3 → distance to closest = 1
                //   (4-1)/2 = 1 ✓
                ans = max(ans, (i - prev) / 2);
                prev = i;  // move prev to current person
            }
        }

        // Step 5: Case 3 — Empty seats AFTER the last person.
        // If you sit at last index (n-1) and last person is at index 'last',
        // distance = (n - 1) - last
        ans = max(ans, n - 1 - last);

        return ans;
    }
};


int main(){
    // Test with example: [1, 0, 0, 0, 1, 0, 0, 1]
    // Expected output: 3 (sit at index 6, distance to index 7 = 1... actually
    // let's trace: first=0, last=7
    //   ans = 0 (edge before first person)
    //   gaps: (4-0)/2 = 2, (7-4)/2 = 1 → ans = max(0, 2, 1) = 2
    //   edge after last: (7-7) = 0 → ans = max(2, 0) = 2
    // Wait - let me recheck with [1,0,0,0,1,0,0,1]:
    //   first=0, prev=0
    //   i=4: seats[4]=1 → (4-0)/2 = 2, prev=4
    //   i=7: seats[7]=1 → (7-4)/2 = 1, prev=7
    //   edge: 7-7=0 → ans = max(2, 1, 0) = 2
    // But for [1,0,0,0,0,1] → first=0, gap (5-0)/2=2, edge=0 → ans=2
    // For [0,0,1] → first=2... wait, seats[0]=0, seats[1]=0, seats[2]=1
    //   first=2, last=2, ans=2 (edge before), gaps: none, edge after: 0 → ans=2

    Solution sol;
    vector<int> seats1 = {1, 0, 0, 0, 1, 0, 0, 1};
    cout << "Test 1: " << sol.maxDistToClosest(seats1) << endl;  // 2

    vector<int> seats2 = {1, 0, 0, 0};
    cout << "Test 2: " << sol.maxDistToClosest(seats2) << endl;  // 3

    vector<int> seats3 = {0, 0, 1};
    cout << "Test 3: " << sol.maxDistToClosest(seats3) << endl;  // 2

    return 0;
}