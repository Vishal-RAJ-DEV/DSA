#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Memoization  {
public:
    int solve( int i , vector<int>& cost , vector<int>&dp){
        if( i < 0 ) return 0;//at the top , cross the 0th index

        if( i==0 || i == 1 ) return cost[i];
        if( dp[i] != -1) return dp[i];

        return dp[i] = cost[i] + min(solve(i-1 , cost , dp) , solve( i -2 , cost,  dp));
    }
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n , -1);
        return  min(solve ( n - 1, cost , dp) , solve(n -2 ,cost , dp));
    }
};



class Tabulation {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int>dp(n + 1);
        dp[0] = 0;
        dp[1] = cost[0];
        dp[2] = cost[1];

        for( int i = 3 ; i < n + 1 ;  i++){

            int cost1 = cost[i-1];
            int cost2 = min( dp[i-1] , dp[i-2]);

            dp[i] = cost1 + cost2;
        }

        return min( dp[n] , dp[n-1]);
    }
};

class SpaceOptimized {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int prev = cost[0] ;
        int sec = cost[1];

        if( n <= 2) return min(prev , sec);
        for( int i = 2 ; i < n ;  i++){

            int curr = cost[i] + min( prev , sec);

            prev = sec;
            sec = curr;
        }

        return min( prev , sec);
    }
};

int main(){
    SpaceOptimized obj;
     vector<int> cost{10, 15, 20};
        cout << obj.minCostClimbingStairs(cost) << endl;
        
    return 0;
}
