#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Given an array, arr[] of rope lengths, connect all ropes into a single rope with the minimum total cost. The cost to connect two ropes is the sum of their lengths. 

Examples:

Input: arr[] = [4, 3, 2, 6]
Output: 29
Explanation: First connect 2 and 3 to get [4, 5, 6] with a cost of 5, then connect 4 and 5 to get [9, 6] with a cost of 9, and finally connect 9 and 6 to get one rope with a cost of 15, giving a total minimum cost of 29. Any other order, such as connecting 4 and 6 first, results in a higher total cost of 38.*/

class Solution {
  public:
    int minCost(vector<int>& arr) {
        // code here
        int n = arr.size();
        priority_queue<int , vector<int> , greater<int>>pq;
        
        int cost = 0;
        
        for(int i =0 ; i < n ; i++){
            pq.push(arr[i]);
        }
        
        
        while(pq.size() > 1){
            int f = pq.top(); pq.pop();
            int s = pq.top(); pq.pop();
            
            cost += (f + s);
            
            pq.push((f + s));
        }
        
        
        return cost;
    }
};


int main(){
    return 0;
}