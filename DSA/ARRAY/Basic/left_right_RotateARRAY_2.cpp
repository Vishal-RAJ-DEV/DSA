#include <iostream>
#include <bits/stdc++.h>

// Problem Statement: Given an array of integers, rotating array of elements by k elements right.

// Approach:
// 1. We will first take the modulo of k with n, where n is the size of the array.
// 2. If k is greater than n, then we will return as it will be the same as rotating the array by k%n.
// 3. We will create a temporary array of size k and copy the last k elements of the array to the temporary array.
// 4. We will shift the elements of the array to the right by k places.
// 5. We will copy the elements of the temporary array to the first k places of the array.
// 6. We will return the array after rotation.
// 7. If k is negative, we will rotate the array to the left by -k
// 8. We will repeat the steps 3-6 until k becomes positive.
// 9. We will return the array after rotation.
using namespace std;
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    if(n==0) return ;

    k = k % n;
    if(k>n) return ;
    vector<int> temp(k);
    for (int i = n-k ;i<n;i++){
        temp[i-n+k] = nums[i];
    }
    for(int i = n-k-1;i>=0;i--){
        nums[i+k] = nums[i];
    }
    for(int i = 0; i<k;i++){
        nums[i] = temp[i];
    }
    
}
int main(){
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 3;
    rotate(nums,k);
    for(int i=0; i<nums.size(); i++){
        cout<<nums[i]<<" ";
    }

    return 0;
}

//optimised code
// #include <iostream>
// #include <vector>
// #include <algorithm> // For reverse function

// using namespace std;

// void rotate(vector<int>& nums, int k) {
//     int n = nums.size();
//     k = k % n;  // Handle cases where k >= n

//     // Reverse the entire array
//     reverse(nums.begin(), nums.end());
    
//     // Reverse the first k elements
//     reverse(nums.begin(), nums.begin() + k);
    
//     // Reverse the remaining n-k elements
//     reverse(nums.begin() + k, nums.end());
// }

// int main() {
//     vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
//     int k = 3;

//     rotate(nums, k);

//     // Print rotated array
//     for (int num : nums) {
//         cout << num << " ";
//     }

//     return 0;
// }



// Problem Statement: Given an array of integers, rotating array of elements by k elements left.

// #include <iostream>
// using namespace std;
// void Rotatetoleft(int arr[], int n, int k)
// {
//   if (n == 0)
//     return;
//   k = k % n;
//   if (k > n)
//     return;
//   int temp[k];
//   for (int i = 0; i < k; i++)
//   {
//     temp[i] = arr[i];
//   }
//   for (int i = 0; i < n - k; i++)
//   {
//     arr[i] = arr[i + k];
//   }
//   for (int i = n - k; i < n; i++)
//   {
//     arr[i] = temp[i - n + k];
//   }
// }
// int main()
// {
//   int n = 7;
//   int arr[] = {1, 2, 3, 4, 5, 6, 7};
//   int k = 2;
//   Rotatetoleft(arr, n, k);
//   cout << "After Rotating the elements to left " << endl;
//   for (int i = 0; i < n; i++)
//   {
//     cout << arr[i] << " ";
//   }
//   return 0;
// }
