#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        //here push all the element in the priority queue
        //get the top value and remove the from it 

        priority_queue<int>pq(piles.begin() , piles.end());
        int res = accumulate(piles.begin() , piles.end(), 0);

        while(k--){
            int x  = pq.top();
            pq.pop(); //remove the top value 
            res -= x / 2; // remove top value's half floor value from the total sum 
            pq.push(x - ( x /2)); //push again the remaining value
        }

        return res;

        
    }
};


int main(){
    return 0;
}