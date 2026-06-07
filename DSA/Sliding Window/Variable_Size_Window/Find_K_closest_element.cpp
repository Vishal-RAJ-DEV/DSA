#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
       int left = 0;
       int right = arr.size() - 1;

       //loop will goes till the we have more than k element
       //and we need only k element
       //so while shriking when we get the k element then loop will stop 
       while( right - left + 1 >k){
        //distance of left element from x 
        int leftval = abs( arr[left] - x);
        //distance of right element from x
        int rightval = abs( arr[right] - x);

        //now shrink either left or right 
        //the far one will be excluded so that side will pointer will change 

        if((leftval < rightval) || ( leftval == rightval && arr[left] < arr[right]))right--;
        else left++;
       }

       return vector<int>(arr.begin() + left , arr.begin() + right + 1);
    }
};

int main(){
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 4;
    int x = 3;
    Solution sol;
    vector<int> result = sol.findClosestElements(arr, k, x);
    cout << "K closest elements to " << x << " are: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}