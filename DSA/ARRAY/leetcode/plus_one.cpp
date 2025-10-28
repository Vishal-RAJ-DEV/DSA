#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
66. Plus One
You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.
Example 1:
Input: digits = [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Incrementing by one gives 123 + 1 = 124.
Thus, the result should be [1,2,4].

Example 2:
Input: digits = [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
Incrementing by one gives 4321 + 1 = 4322.
Thus, the result should be [4,3,2,2].

Example 3:
Input: digits = [9]
Output: [1,0]
Explanation: The array represents the integer 9.
Incrementing by one gives 9 + 1 = 10.
Thus, the result should be [1,0].*/
vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();

    for (int i = n - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;         // ← THIS LINE corresponds to the step “2 < 9 → add 1” here the 1 added then there is no and we also add 1 to the next digit so we can return early
            return digits;       // return early because no carry left
        }
        digits[i] = 0;           // if digit was 9, set it to 0 and continue and its carry is added to the next digit in the next iteration in the above loop
    }

    digits.insert(digits.begin(), 1); // handle case like 999 → 1000  // if we are here that means all the digits were 9 so we need to add 1 at the beginning of the array and rest all will be 0
    return digits;
}

int main(){
    vector<int> digits = {9,9,9};   //input array
    vector<int> result = plusOne(digits); //function call
    for (int i : result) {
        cout << i << " ";  // print each element of the result
    }
    vector<int> digits1 = {1,2,3};   //input array
    vector<int> result1 = plusOne(digits1); //function call
    cout << endl;
    for (int i : result1) { // print each element of the result
        cout << i << " ";
    }
    return 0;
}
