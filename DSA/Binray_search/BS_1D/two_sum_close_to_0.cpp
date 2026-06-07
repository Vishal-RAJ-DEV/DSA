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
    /*
    Algorithm:
    1. Sort the array.
    2. Fix one element x = arr[i].
    3. We now need another element as close as possible to -x,
       because x + y will then be closest to 0.
    4. Search in the remaining right part using binary-search-style movement:
       - calculate mid
       - compute sum = x + arr[mid]
       - update the best answer if this sum is closer to 0
       - if sum < 0, move toward larger values
       - if sum > 0, move toward smaller values
    5. If two sums are equally close to 0, keep the larger sum.

    Time Complexity: O(n log n)
    Space Complexity: O(1) extra space apart from sorting
    */

    int n = arr.size();
    sort(arr.begin(), arr.end());

    int bestSum = INT_MAX;

    for(int i = 0; i < n; i++){
        int x = arr[i];
        int left = i + 1;  // do not reuse the same element
        int right = n - 1;

        while(left <= right){
            // mid is the current candidate partner for x.
            int mid = (left + right) / 2;
            int sum = x + arr[mid];

            // Exact zero is the best possible answer.
            if(abs(sum) == 0){
                return 0;
            }

            // Update answer if current sum is closer to 0.
            if(abs(sum) < abs(bestSum)){
                bestSum = sum;
            }
            // If both are equally close to 0, keep the larger sum.
            else if(abs(sum) == abs(bestSum)){
                bestSum = max(bestSum, sum);
            }

            /*
            Intuition:
            - If sum < 0, the pair is too small.
              To get closer to 0, we need a bigger value.
              So move toward the right side.

            - If sum > 0, the pair is too large.
              To get closer to 0, we need a smaller value.
              So move toward the left side.
            */
            if(sum < 0){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
        }
    }

    // bestSum stores the pair sum whose absolute value is minimum.
    return bestSum;
}

int main(){
    vector<int> arr = {0, -8, -6, 3};
    cout << findpairClosetTo0(arr);
    return 0;
}
