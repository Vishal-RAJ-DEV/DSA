#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string>res;
    vector<string> addOperators(string num, int target) {
        helper(num ,target , 0 ,  "" , 0 , 0);
        return res;
    }

    void helper(string num , int target , int idx , const string& path , long currsum , long lastdig){
        //base case 
        if( idx == num.size()){
            if(currsum == target){
                res.push_back(path);
            }
            return;
        }

        string currpath = "";
        long currnum = 0 ;
        for( int i = idx ; i < num.size(); i++){
            //edge case
            if( i > idx && num[idx] == '0') return;

            //extract the current digit 
            currpath += num[i];
            currnum = currnum*10 + num[i] - '0';

            if( idx == 0 ){
                helper(num , target , i+1 , path + currpath , currnum , currnum);
            }else{
                helper(num , target , i + 1, path + '+'+ currpath , currsum+currnum , currnum);
                helper(num , target , i + 1, path + '-'+ currpath , currsum-currnum , -currnum);
                helper(num , target , i + 1, path + '*'+ currpath , 
                        (currsum-lastdig) + (currnum * lastdig) 
                        , currnum*lastdig
                    );
            }
        }
    }
};

int main(){
    string num = "123";
    int target = 6;
    Solution s;
    vector<string> res = s.addOperators(num , target);

    for( auto &it : res){
        cout<<it<<" ";
    }

    
    return 0;
}
