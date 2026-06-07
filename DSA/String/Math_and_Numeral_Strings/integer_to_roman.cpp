#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        //creating the mapping here 
        //here we use the greedy approch 
        //roman symbol start with the largest value 
        //so we start iterating form the largest 
        //We go largest → smallest and keep subtracting.
        const vector<pair<int,string>>mpp{
            {1000 , "M"} , { 900 , "CM"} , { 500 , "D"} , {400 , "CD"} , { 100 , "C"} ,
            { 90 , "XC"} , {50 , "L"} , { 40 , "XL"} , { 10 , "X"} , { 9 , "IX"} , { 5 , "V"} , 
            { 4 , "IV"} , { 1  , "I"}
        };

        string res;
        for( const auto & pair : mpp){
            if( num == 0)break;

            while( num >= pair.first){//if num = 1982 which is >1000 , so add the 'M' here 
                res+=pair.second; //here we addded the "M"
                num-=pair.first; //remove the added's value , which is 1000

                //then it becomes 982 , then move to next value, sym which is 900 ,CM 
            }
        }

        return res;
    }
};


int main(){
    Solution sol;
    cout << sol.intToRoman(1982) << endl; // Output: MCMLXXXII
    return 0;
}