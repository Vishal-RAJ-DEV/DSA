#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*Given an integer array arr[], the task is to find the maximum sum of two elements such that sum is closest to zero.

Note: In case if we have two of more ways to form sum of two elements closest to zero return the maximum sum.

Examples:

Input: arr[] = [-8, 5, 2, -6]
Output: -1
Explanation: The min absolute sum pair is (5, -6)

Input:  arr[] = [0, -8, -6, 3]
Output: 3
Explanation: We have a tie between (0, 3) and (-6, 3). We pick the max sum in this case which is 0+3

Input: arr[] = [-7, 4, 1, -2]
Output: -1
Explanation: The min absolute sum pair is (1, -2).*/


int findpairClosetTo0(vector<int> &arr){
    int n = arr.size();
    sort(arr.begin(),arr.end());
    int min = INT_MAX;
    for(int i = 0 ;i<n;i++){
        int x = arr[i];
        int left = i+1;  //leave the current element and start from the next element
        int right = n-1;

        while(left <= right){
            int mid = (left + right) / 2;  //binary search to find the element which is closest to -x
            int sum = x + arr[mid];  //sum of the two elements

            if(abs(sum) == 0){  //if the sum is 0 then return 0
                return 0;
                
            }
            else if(abs(sum) < abs(min)){  //if the absolute value of the sum is less than the absolute value of the minimum then update the minimum
                min = sum;
            }
            else if(abs(sum) == abs(min)){
                min = max(min,sum);  //if the absolute value of the sum is equal to the absolute value of the minimum then update the minimum to the maximum of the two
            }
            if(sum < 0){
                left = mid + 1;  //if the sum is less than 0 then move the left pointer to mid + 1
            }
            else{
                right = mid - 1;  //if the sum is greater than 0 then move the right pointer to mid - 1
            }
        }
    }

    return min;  //return the minimum value found

}
int main(){
    vector<int>arr = { 0, -8, -6, 3 };
    cout<<findpairClosetTo0(arr);
    return 0;
}


/*
| i | x  | left | right | mid | arr\[mid] | sum | Condition Checked                      | min Update | Final min |
| - | -- | ---- | ----- | --- | --------- | --- | -------------------------------------- | ---------- | --------- |
| 0 | -8 | 1    | 3     | 2   | 0         | -8  | abs(-8) < abs(INT\_MAX)                | min = -8   | -8        |
| 0 | -8 | 3    | 3     | 3   | 3         | -5  | abs(-5) < abs(-8)                      | min = -5   | -5        |
| 1 | -6 | 2    | 3     | 2   | 0         | -6  | abs(-6) > abs(-5) → no update          | —          | -5        |
| 1 | -6 | 3    | 3     | 3   | 3         | -3  | abs(-3) < abs(-5)                      | min = -3   | -3        |
| 2 | 0  | 3    | 3     | 3   | 3         | 3   | abs(3) == abs(-3) → take max(-3,3) = 3 | min = 3    | 3         |
| 3 | 3  | 4    | 3     | —   | —         | —   | loop doesn’t run                       | —          | 3         |

*/