/*Problem Statement: You are given an array of integers 'arr' and an integer i.e. a threshold value 'limit'. Your task is to find the smallest positive integer divisor, such that upon dividing all the elements of the given array by it, the sum of the division's result is less than or equal to the given threshold value.

Examples

Example 1:
Input Format: N = 5, arr[] = {1,2,3,4,5}, limit = 8
Result: 3
Explanation: We can get a sum of 15(1 + 2 + 3 + 4 + 5) if we choose 1 as a divisor. 
The sum is 9(1 + 1 + 2 + 2 + 3)  if we choose 2 as a divisor. Upon dividing all the elements of the array by 3, we get 1,1,1,2,2 respectively. Now, their sum is equal to 7 <= 8 i.e. the threshold value. So, 3 is the minimum possible answer.

Example 2:
Input Format: N = 4, arr[] = {8,4,2,3}, limit = 10
Result: 2
Explanation: If we choose 1, we get 17 as the sum. If we choose 2, we get 9(4+2+1+2) <= 10 as the answer. So, 2 is the answer.

Point to remember:
While dividing the array elements with a chosen number, we will always take the ceiling value. And then we will consider their summation. For example, 3 / 2 = 2.*/


#include <bits/stdc++.h>
using namespace std;

int smallestDivisor(vector<int>& arr, int limit) {   //time complexity O(n * m) where n is the size of the array and m is the maximum element in the array.
    int n = arr.size(); //size of array.
    //Find the maximum element:
    int maxi = *max_element(arr.begin(), arr.end());

    //Find the smallest divisor:
    for (int d = 1; d <= maxi; d++) {
        //Find the summation result:
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += ceil((double)(arr[i]) / (double)(d));
        }
        if (sum <= limit)
            return d;
    }
    return -1;
}


//Optimized approach using binary search:

int sumByD(vector<int> &arr, int div) {
    int n = arr.size(); //size of array
    //Find the summation of division values:
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += ceil((double)(arr[i]) / (double)(div));  //ceil is used to take the upper value after division like 3/2 = 1.5 ceil(1.5) = 2
    }
    return sum;
}

int smallestDivisor1(vector<int>& arr, int limit) {
    int n = arr.size();
    if (n > limit) return -1;
    int low = 1, high = *max_element(arr.begin(), arr.end());

    //Apply binary search:
    while (low <= high) {
        int mid = (low + high) / 2;
        if (sumByD(arr, mid) <= limit) {
            high = mid - 1;   //try to find a smaller divisor to get increase the sum for eg if we have 8,4,2,3 and limit is 10 if we take 2 as divisor we get 9 which is <=10 but if we take 1 as divisor we get 17 which is >10 so we will try to find a smaller divisor
        }
        else {
            low = mid + 1; //try to find a larger divisor to get decrease the sum for eg if we have 1,2,3,4,5 and limit is 8 if we take 3 as divisor we get 7 which is <=8 but if we take 2 as divisor we get 9 which is >8 so we will try to find a larger divisor
        }
    }
    return low;
}


int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    int limit = 8;
    int ans = smallestDivisor1(arr, limit);
    cout << "The minimum divisor is: " << ans << "\n";
    return 0;
}
