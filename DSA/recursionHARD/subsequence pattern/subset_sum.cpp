#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void generate( int indx , int n , int s , int sum , vector<int>&arr , vector<int>&subset){
    //base case
    if( indx == n){
        if(s == sum ){ //if the sum matches the target sum then print the subset
            cout<<"[ ";
            for( auto &it : subset){
                cout<<it<<" ";
            }
            cout<<"]";
            cout<<endl;
        }
        return;
    }

    //exclude the element which is at indx
    generate( indx + 1 , n , s , sum , arr , subset);
    //include after the recursion backtrack the changes
    subset.push_back(arr[indx]);
    s += arr[indx];

    //include call which adds the element at indx
    generate( indx + 1 , n , s , sum , arr , subset);
    //backtrack again and remove the element at index here 
    s -= arr[indx]; 
    subset.pop_back();
}

//now if i want to generate only one of the subset which matches the sum then i can use a boolean function here 

bool generate1( int indx , int n , int s , int sum , vector<int>&arr , vector<int>&subset){
    //base case
    if( indx == n){
        if(s == sum ){ //if the sum matches the target sum then print the subset
            cout<<"[ ";
            for( auto &it : subset){
                cout<<it<<" ";
            }
            cout<<"]";
            cout<<endl;
            return true; //return true if we found a valid subset
        }
        return false; //return false if no valid subset found
    }

    //exclude the element which is at indx
    if( generate1( indx + 1 , n , s , sum , arr , subset) == true ){
        return true; //if found in exclude call return true
    }
    //include after the recursion backtrack the changes
    subset.push_back(arr[indx]);
    s += arr[indx];

    //include call which adds the element at indx
    if( generate1( indx + 1 , n , s , sum , arr , subset) == true ){
        return true; //if found in include call return true
    }
    //backtrack again and remove the element at index here 
    s -= arr[indx]; 
    subset.pop_back();

    return false; //return false if no valid subset found in both calls
}

int main(){
    vector<int> arr = {1,2,1};  
    int n = 3; // Length of the string "abc"
    int sum  = 2;; // The target sum we want to achieve
    vector<int>subset;
    generate( 0 , n , 0, sum , arr , subset);
    cout<<endl;
    cout<<"Now printing only one subset which matches the sum "<<sum<<endl;
    generate1( 0 , n , 0, sum , arr , subset);

    return 0;
}


// 📊 Execution Flow Table
// Call	Index	Current State	    Action	                Result	    Early Term?
// 1	0	    s=0, subset=[]	    Exclude arr[0]=1	    Call 2	    ❌
// 2	1	    s=0, subset=[]	    Exclude arr[1]=2	    Call 3	    ❌
// 3	2	    s=0, subset=[]	    Exclude arr[2]=1	    Call 4	    ❌
// 4	3	    s=0, subset=[]	    Base: 0≠2	            false ↑	    ❌
// 3	2	    s=0, subset=[]	    Include arr[2]=1	    Call 5	    ❌
// 5	3	    s=1, subset=[1]	    Base: 1≠2	            false ↑	    ❌
// 3	2	    s=0, subset=[]	    Backtrack	            false ↑	    ❌
// 2	1	    s=0, subset=[]	    Include arr[1]=2	    Call 6	    ❌
// 6	2	    s=2, subset=[2]	    Exclude arr[2]=1	    Call 7	    ❌
// 7	3	    s=2, subset=[2]	    Base: 2==2	            true ↑	    ✅
// 6	2	    s=2, subset=[2]	    Skip include	        true ↑	    ✅
// 2	1	    s=2, subset=[2]	    Skip backtrack	        true ↑	    ✅
// 1	0	    s=0, subset=[]	    Skip include	        true ↑	    ✅