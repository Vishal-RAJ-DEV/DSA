#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void solve( int start , vector<int>& comb ,  vector<vector<int>>& result  , int n , int k){

        //base  case when the combination size is k 
        if( comb.size() == k){
            result.push_back(comb);
            return;
        }
        for(int i = start ; i <= n ; i++){
            comb.push_back(i);
            solve ( i + 1 ,comb,  result , n , k);
            comb.pop_back(); //while backtracking the remove the current number i;
        }

    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>>result;
        vector<int>comb;

        solve ( 1 ,comb ,  result , n , k);

        return result;
    }
};

int main(){
    int n = 4; //total numbers from 1 to n
    int k = 2; //number of elements in the combination
    Solution sol;
    vector<vector<int>> result = sol.combine(n, k);
    cout<<"Combinations of "<<k<<" numbers from 1 to "<<n<<" are: "<<endl;
    for( auto &comb : result){
        cout<<"[ ";
        for( auto &num : comb){
            cout<<num<<" ";
        }
        cout<<"]"<<endl;
    }
    
    return 0;
}