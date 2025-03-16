#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int maxprofit = 0;
    int mini = prices[0];
    for(int i =1; i<n;i++){
        int cost = prices[i]-mini;
        maxprofit = max(maxprofit,cost);
        mini = min(mini,prices[i]);
    }
    return maxprofit;
    
}

int main(){
    vector<int> prices = {7,1,5,3,6,4};
    int maxprofit = maxProfit(prices);
    cout<<"the maximun profit can obtian will : "<<maxprofit;
    return 0;
}