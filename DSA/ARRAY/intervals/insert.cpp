#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Problem: Insert Interval

Given a list of intervals where each interval is [start, end], insert one new
interval and return the resulting list after merging all overlapping intervals.

This implementation uses a simple approach:
1) Add newInterval into the list.
2) Sort all intervals by start time.
3) Merge overlapping intervals in one pass.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for the output list.
*/

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // Step 1: Add the new interval into the existing list.
        intervals.push_back(newInterval);

        // Step 2: Sort by start value so intervals are processed left-to-right.
        sort(intervals.begin() , intervals.end());

        // Step 3: Merge overlapping intervals and store final result.
        vector<vector<int>>ans;
        for( int i = 0 ; i < intervals.size() ; i++){
            //push to answer if the ans if empty 
            //or interval in correct , no overlapping 
            //correct interval is interval[i][0] first ele of pair 
            //is greater then than previous interval[][1] second ele of the pair
            //eg [1][3] , [4][7] -> here 4 > 3 so its correct 
            //eg [1][3] , [2][7] -> 2 < 3 so its not correct
            if( ans.empty() || ans.back()[1] < intervals[i][0]){
                ans.push_back(intervals[i]);
            }
            else{
                //overlapping the interval , so merged it 
                //eg [1][3] , [2][5] and 2 < 3 so max( 3 ,5) = 5
                //merged = [1] [5]
                ans.back()[1] = max( ans.back()[1] , intervals[i][1]);
            }
        }
        return ans;

    }
};


int main(){
    // Example:
    // intervals = [[1,3], [6,9]], newInterval = [2,5]
    // Result    = [[1,5], [6,9]]
    vector<vector<int>> intervals = {{1, 3}, {6, 9}};
    vector<int> newInterval = {2, 5};
    Solution s;
    vector<vector<int>> ans = s.insert(intervals, newInterval);
    cout << "Merged Intervals: ";
    for (const auto& interval : ans) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << endl;
    
    return 0;
}
