#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    PROBLEM: Longest Valid Obstacle Course at Each Position
    =======================================================
    For each position i, find the longest valid obstacle course that ends at i.
    A valid course means: indices i1 < i2 < ... < ik = i
                          obstacles[i1] <= obstacles[i2] <= ... <= obstacles[ik]
    (Non-decreasing heights as we move forward)

    INTUITION: Patience Sorting / LIS Technique
    =============================================
    This problem is similar to finding Longest Non-Decreasing Subsequence (LNDS)
    ending at each position.

    KEY INSIGHT:
    We maintain an array `lcs` where lcs[k] stores the SMALLEST ending element
    of all valid obstacle courses of length (k+1).

    Why smallest? Because a smaller ending element is more "flexible" - it can
    accommodate more future obstacles (since we need non-decreasing order).

    EXAMPLE:
    obstacles = [5, 3, 4, 6]
    
    i=0: lcs=[], find where 5 fits -> idx=0, lcs=[5], result[0]=1
    i=1: lcs=[5], find where 3 fits -> idx=0 (3 < 5), lcs=[3], result[1]=1
    i=2: lcs=[3], find where 4 fits -> idx=1 (4 > 3), lcs=[3,4], result[2]=2
    i=3: lcs=[3,4], find where 6 fits -> idx=2 (6 > 4), lcs=[3,4,6], result[3]=3

    WHY upper_bound?
    ================
    We use upper_bound (first element > obstacle[i]) because:
    - We allow EQUAL heights (non-decreasing, not strictly increasing)
    - If obstacle[i] == lcs[k], we can extend course of length k+1
    - upper_bound finds the position AFTER all equal elements
    
    Example: lcs = [2, 4, 6], obstacle = 4
    - lower_bound finds idx=1 (first element >= 4)
    - upper_bound finds idx=2 (first element > 4)
    - Using upper_bound allows us to extend the course since 4 == lcs[1]
    
    COMPLEXITY:
        Time:  O(n log n) - binary search for each element
        Space: O(n) - for lcs and result arrays
*/

class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n = obstacles.size();
        
        vector<int> lcs;    // Stores smallest ending element for each course length
                            // lcs[0] = smallest ending element of all courses of length 1
                            // lcs[1] = smallest ending element of all courses of length 2
                            // ... and so on
        
        vector<int> result(n); // result[i] = length of longest course ending at position i

        for(int i = 0; i < n; i++){
            
            // Use upper_bound to find first element in lcs that is > obstacles[i]
            // This tells us: what is the longest course we can extend with obstacles[i]?
            // idx = length of longest course that can end with obstacles[i]
            
            int idx = upper_bound(lcs.begin(), lcs.end(), obstacles[i]) - lcs.begin();

            if(idx == lcs.size()){
                // If idx equals lcs.size(), obstacles[i] is larger than ALL elements in lcs
                // We can extend the longest course by 1 (append to end)
                lcs.push_back(obstacles[i]);
            }else{
                // If idx < lcs.size(), we found a position where obstacles[i] can fit
                // Replace lcs[idx] with obstacles[i] to keep the smallest ending element
                // This "improves" future possibilities (smaller ending = more flexibility)
                lcs[idx] = obstacles[i];
            }

            // The length of longest course ending at position i is (idx + 1)
            // idx is 0-indexed, so +1 gives the actual length
            result[i] = idx + 1;
        }

        return result;
    }
};


int main(){
    return 0;
}