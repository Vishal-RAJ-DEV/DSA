#include <iostream>
#include <bits/stdc++.h>
using namespace std;



int generate1( int indx , int n , int s , int sum , vector<int>&arr , vector<int>&subset){
    if( s > sum ) return 0;
    //base case
    if( indx == n){
        if(s  == sum ) return 1;
        else return 0;
    }

    //exclude the element which is at indx
    int exclude = generate1( indx + 1 , n , s , sum , arr , subset);
    //include after the recursion backtrack the changes
    subset.push_back(arr[indx]);
    s += arr[indx];

    //include call which adds the element at indx
    int include = generate1( indx + 1 , n , s , sum , arr , subset);
    //backtrack again and remove the element at index here 
    s -= arr[indx]; 
    subset.pop_back();

    return exclude + include;
}

int main(){
    vector<int> arr = {1,2,1};  
    int n = 3; // Length of the string "abc"
    int sum  = 2;; // The target sum we want to achieve
    vector<int>subset;
    cout << generate1( 0 , n , 0, sum , arr , subset) << endl;

    return 0;
}