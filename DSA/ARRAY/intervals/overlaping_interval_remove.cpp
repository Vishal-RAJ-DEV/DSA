#include <iostream>
#include <bits/stdc++.h>
using namespace std;



class Solution {
public:
    //thsi cmp function is used to sort the intervals based on their end time
    //so that we can easily compare the end time of the previous interval with the start time of the current interval to check for overlapping intervals
    static bool cmp( vector<int>& a, vector<int>&b){
        return a[1] < b[1];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        ///first we sort the interval here 
        sort(intervals.begin() , intervals.end(), cmp);

        //we track of the previous end value which is in the interval
        //if a previous end val in  interval is lgreater than current than increse the result value 
        //means that in not in the current start in not in the interval
        int prevEnd = intervals[0][1];
        int res = 0 ;

        for( int i = 1 ; i < intervals.size() ; i++){
            if( prevEnd > intervals[i][0]){
                res++;
            }else{
                prevEnd = intervals[i][1];
            }
        }
        return res;
    }
};


int main(){
    return 0;
}
