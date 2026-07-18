#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int m = matrix[0].size();

        priority_queue<int , vector<int>, greater<int>>minheap;
        vector<vector<int>>prefix( n , vector<int>(m , 0));

        for(int i= 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                prefix[i][j] = matrix[i][j] ;

                if(i > 0 ){
                    prefix[i][j] ^= prefix[i-1][j]; //xor from the top
                }
                if(j > 0 ){
                    prefix[i][j] ^= prefix[i][j-1]; //xor from the left
                }
                if( i > 0 && j > 0 ){
                    prefix[i][j] ^= prefix[i-1][j-1]; //xor from the diagonal 
                    //on the diagonal xor of of the duplicated are there which is removed 
                    //which we done the prefix of (i,j - 1) and (i-1,j)
                }


                minheap.push(prefix[i][j]);
                if( minheap.size() > k ) minheap.pop();
            }
        }

        return minheap.top();
    }
};


int main(){

    return 0;
}