#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
        // code here
        
        int n = val.size();
        //first store the val and weight in the pair
        vector<pair<int, int>> vec(n);
        for( int i = 0 ; i< n ; i++){
            vec[i] = { val[i] , wt[i] } ;
        }
        
        //now sort it according to profit per weight ( profit / weight)
        //from high to low 
        
        auto lambda = [](pair<int ,int > &p1 , pair< int , int> &p2){
            return (1.0 * p1.first)/ p1.second > (1.0 * p2.first ) / p2.second;
        };
        
        sort( vec.begin() , vec.end() , lambda); //lambda is the condition when profit/weight is max to min 
        
        //calcualte the max profit 
        double res = 0.0;
        for( int i = 0 ; i < n ; i++){
            //when the current wt is less than the capacity 
            if( vec[i].second <= capacity){
                res += vec[i].first;
                capacity -= vec[i].second;
            }
            //current wt is greater then capacity , the capacity val from the wt 
            //if wt is 40 and capacity is 20 , then we take wt= 20 and profit get form wt= 20
            else{ 
                double reqProfit  = (1.0 * vec[i].first / vec[i].second) * capacity ;
                res += reqProfit ;
                
                break;//capacity becomes 0 
            }
        }
        
        return res;
        
        
        
    }
};


int main(){
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;
    vector<int> val(n), wt(n);
    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) {
        cin >> wt[i];
    }
    cout << "Enter capacity of knapsack: ";
    cin >> capacity;
    Solution sol;
    double maxProfit = sol.fractionalKnapsack(val, wt, capacity);
    cout << "Maximum profit in Knapsack = " << maxProfit << endl;
    
    return 0;
}