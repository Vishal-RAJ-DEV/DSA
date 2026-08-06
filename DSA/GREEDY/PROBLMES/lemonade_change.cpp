#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int n = bills.size();

        //pointer that count the no of 5's and 10's 
        //we can only return the 5 or 10 as the change for the 5 dollar
        //so no need to point to 20's
        int five = 0 ;
        int ten = 0 ;
        for( int i = 0 ; i < n ; i++){
            if( bills[i] == 5){
                five++;
            }
            else if( bills[i] == 10){
                if( five > 0) {
                    five--;
                    ten++;
                }else return false;
            }else{ //when the numbers is 20 
                if( ten > 0 && five > 0){ //when we can give 15 as 10 and 5
                    ten--;
                    five--;
                }
                else if( five >= 3){//when can don't have the 10 , give the 15 as the 3's five
                    five -= 3;
                }
                else return false;
            }
        }
        return true;
    }
};

int main(){
    Solution sol;
    vector<int> bills = {5, 5, 5, 10, 20};
    bool ans = sol.lemonadeChange(bills);
    if(ans) cout<<"We can give the change to all customers "<<endl;
    else cout<<"We cannot give the change to all customers "<<endl;
    
    return 0;
}
