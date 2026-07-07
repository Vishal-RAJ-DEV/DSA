#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();
        vector<int>closed( n + 1 , 0);
        vector<int>open( n +1  , 0);

        // Algorithm:
        // 1. Try every possible closing hour from 0 to n.
        // 2. For each hour, count the penalty caused by:
        //    - customers before that hour while the shop was closed
        //    - customers after that hour while the shop was open
        // 3. Choose the hour with the smallest total penalty.
        //
        // Intuition:
        // `customers[i]` describes the i-th hour in the original string.
        // `open[i]` stores the penalty if the shop is open for hours [0, i-1].
        // `closed[i]` stores the penalty if the shop is closed for hours [i, n-1].
        //
        // The extra index `i == n` is important:
        // it means "close after the last hour".
        // So the arrays have size `n + 1`, not `n`.
        //
        // Example for customers = "NYNN":
        // - open[2] counts penalty from hours 0 and 1
        // - closed[2] counts penalty from hours 2 and 3
        // - total penalty for closing at hour 2 is open[2] + closed[2]

        // Build the prefix penalty for the time when the shop is OPEN.
        // open[i] means: consider the first i characters of `customers`.
        // If any of those characters is 'N', that hour adds a penalty because
        // the shop was open but no customer came.
        for( int i = 1 ; i <= n; i++){
            open[i] = open[i-1];
            if(customers[i-1] == 'N') open[i]++;
        }

        // Build the suffix penalty for the time when the shop is CLOSED.
        // closed[i] means: consider the substring from hour i to hour n-1.
        // If any of those characters is 'Y', that hour adds a penalty because
        // the shop was closed but a customer came.
        //
        // We start from the end because closed[n] = 0:
        // after the last hour there are no customers left to punish.
        for( int i = n - 1 ; i >= 0; i--){
            closed[i] = closed[i+1];
            if(customers[i] =='Y')closed[i]++;

        }

        // Now combine both parts for every possible closing hour i.
        //
        // If we close at hour i:
        // - hours [0, i-1] are OPEN, so use open[i]
        // - hours [i, n-1] are CLOSED, so use closed[i]
        //
        // Therefore total penalty = open[i] + closed[i].
        int maxplenty = INT_MAX ; 
        int besthr = 0;
        for(int i=0 ; i<= n ; i++){
            int total = closed[i] + open[i];
            if( total < maxplenty ){
                maxplenty = total;
                besthr = i;
            }
        }

        return besthr;
        
    }
};


int main(){
    string customers = "YYNY";
    Solution obj;
    int ans = obj.bestClosingTime(customers);
    cout<<"The best closing time for the shop is: "<<ans<<endl;
    
    return 0;
}