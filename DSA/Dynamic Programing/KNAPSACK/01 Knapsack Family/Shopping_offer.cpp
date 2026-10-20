#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int solve(vector<int>& price, vector<vector<int>>& special, vector<int> needs, int index){
        if(index==special.size()){
            //Buy everything at the normal price
            int res = 0;
            for(int i=0;i<needs.size();i++){
                res += needs[i] * price[i];
            }
            return res;
        }
        
        //Reject Offer
        int reject = solve(price, special, needs, index + 1);
        
        //Apply Offer 
        for(int i=0;i<needs.size();i++){
            needs[i] = needs[i] - special[index][i]; //Decrement the needs
            if(needs[i] < 0) return reject; //Can't use this offer
        }
        
        int accept = special[index][needs.size()] + solve(price, special, needs, index);
        
        return min(accept, reject);
    }
    
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        return solve(price, special, needs, 0);
    }
};

class Solution {
public:
    map<pair<vector<int>, int>, int> dp;

    int solve(vector<int>& price, vector<vector<int>>& special, vector<int> needs, int index) {
        if (index == special.size()) {
            int res = 0;
            for (int i = 0; i < needs.size(); i++) {
                res += needs[i] * price[i];
            }
            return res;
        }

        auto key = make_pair(needs, index);
        if (dp.count(key)) return dp[key];

        int reject = solve(price, special, needs, index + 1);

        bool valid = true;
        for (int i = 0; i < needs.size(); i++) {
            needs[i] -= special[index][i];
            if (needs[i] < 0) {
                valid = false;
                break;
            }
        }

        int ans = reject;

        if (valid) {
            int accept = special[index][needs.size()] + solve(price, special, needs, index);
            ans = min(ans, accept);
        }

        return dp[key] = ans;
    }

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        dp.clear();
        return solve(price, special, needs, 0);
    }
};


int main(){
    return 0;
}