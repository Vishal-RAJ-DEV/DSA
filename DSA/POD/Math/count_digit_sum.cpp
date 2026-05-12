#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countEven(int num) {
        int sum = 0 ;
        int count = 0;

        for( int i = 1;i <= num;i++){
            int dup = i;
            int sum = 0 ;

            //calculate the digit sum first 
            //means if dup is 23 then the sum = 2 + 3
            //then check this is even or not
            while( dup >0){
                sum += dup % 10;
                dup /= 10;
            }

            if(sum % 2 == 0){
                count++;
            }

        }
        return count;
    }
};

int main(){
    Solution sol;
    cout << sol.countEven(4) << endl;  // Output: 2
    cout << sol.countEven(30) << endl; // Output: 14
    return 0;
}


