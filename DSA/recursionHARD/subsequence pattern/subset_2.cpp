#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void gen( int i , vector<int>&nums , vector<vector<int>>&result , vector<int>&current){
        if( i== nums.size()){
            result.push_back(current);
            return;
        }
        //include the element at index i
        current.push_back(nums[i]);
        gen(i + 1 , nums , result , current);
        current.pop_back(); //remove the last element to backtrack so it can explore other possibilities

        //now skip the duplicates 
        int idx = i + 1;
        //if the next element is same as the current element then skip all the duplicates 
        while( idx < nums.size() && nums[idx] == nums[idx - 1]) idx++;
        gen(idx , nums , result , current); //then call the function with the next different element
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        sort(nums.begin() , nums.end());
        gen( 0 , nums , result , current);
        return result;
    }
};
int main(){
    vector<int> arr = {1, 2, 1};
    Solution obj;  
    vector<vector<int>> res = obj.subsetsWithDup(arr);
    for( auto &it : res){
        cout<<"[ ";
        for( auto &el : it){
            cout<<el<<" ";
        }
        cout<<"]"<<endl;
    }

    return 0;
}
