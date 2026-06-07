#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//question is : 1769. Minimum Number of Operations to Move All Balls to Each Box
// You have n boxes. You are given a binary string boxes of length n, where boxes[i] is '0' if the ith box is empty, and '1' if it contains one ball.
// In one operation, you can move one ball from a box to an adjacent box. Adjacent boxes are those with an index differing by one.
// The operation is performed on a box containing a ball, and it moves to an adjacent box. This can be interpreted as moving a ball from index i to index i + 1 or from index i to index i - 1.
// Return an array answer of size n, where answer[i] is the minimum number of operations needed to move all the balls to the ith box.
// Note that there may be more than one ball in some boxes. The answer is the total number of operations to move all balls from their current positions to the ith box.

//brute force approach : time complexity : O(n^2) and space complexity : O(n)
class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.length();
        vector<int> ans ( n , 0);

        //her put all ball in the box i and calculate the distance from all the other boxes to this box and add it to the answer
        for( int i = 0 ; i < n ; i++){
            for( int j = 0 ; j < n ; j++){
                if( boxes[j] == '1') ans[i] += abs(i-j); //if the box is not empty then add the distance to the answer 
            }
        }

        return ans;
    }
};
//approch 2 : 
class Solution {
    vector<int> minoperations( string boxes){
        int n = boxes.length();
        vector<int> ans ( n , 0);

        for( int i = 0 ; i< n ; i++){
            //here we find the ball and add the distance from this ball to all the other boxes to the answer
            if( boxes[i] == '1'){
                for( int j = 0 ; j < n ; j++){
                    ans[j] += abs(i-j); //if the box is not empty then add the distance to the answer 
                }
            }
        }
        return ans;
    }
};
/* 1769. Minimum Number of Operations to Move All Balls to Each Box */
class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.length();
        vector<int> ans ( n , 0);
        int currValue = 0;
        int currSum = 0;
        
        //find all the moves from the left sides
        for( int i = 0 ; i < n ; i++){
            ans[i] = currSum;
            currValue += boxes[i] == '0'? 0 : 1; //update the current Value to the current number

            //add this value for the further sum 
            currSum += currValue;

        }

        currValue = 0 ;
        currSum = 0;
        //find all the moves form the right sides 
        for ( int i = n - 1 ; i >= 0 ; i--){
            ans[i] += currSum;

            currValue += boxes[i] == '0' ? 0 : 1;

            currSum += currValue;
        }

        return ans;
    }
};
int main(){
    string boxes = "110";
    Solution sol;
    vector<int> ans = sol.minOperations(boxes);
    cout << "The minimum number of operations to move all balls to each box is: ";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    return 0;
}