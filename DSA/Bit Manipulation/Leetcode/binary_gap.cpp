#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
868. Binary Gap

Given a positive integer n, find and return the longest distance between any two adjacent 1's in the binary representation of n. If there are no two adjacent 1's, return 0.
Two 1's are adjacent if there are only 0's separating them (possibly no 0's). The distance between two 1's is the absolute difference between their bit positions. For example, the two 1's in "1001" have a distance of 3.
Example 1:

Input: n = 22
Output: 2
Explanation: 22 in binary is "10110".
The first adjacent pair of 1's is "10110" with a distance of 2.
The second adjacent pair of 1's is "10110" with a distance of 1.
The answer is the largest of these two distances, which is 2.
Note that "10110" is not a valid pair since there is a 1 separating the two 1's underlined.
*/
class Solution {
public:
    int binaryGap(int n) {
        int maxL = 0 ;
        int currL = 0 ;
        bool found1 = false;
        while( n > 0){
            int bit = n % 2;//this give the bit either 1 or 0 

            if( bit == 1){
                if( found1) maxL = max( currL , maxL); //means new 1bit find , update the maxstep 

                //now start as new with distance 1 ifthis is first 1bit
                currL = 1;
                found1 = true;
            }else{
                if( found1)currL++;

            }
            //move to next bit decimal digit number where next bit can be obtained 
            n = n/2;
        }

        return maxL;
    }
};
int main(){
    return 0;
}