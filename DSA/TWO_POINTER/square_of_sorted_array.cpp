#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.
Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].
Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
*/

/*
algorithm flow :
1. taking two pointers left and right at the start and end of the array respectively and a position pointer at the end of the result array.
2. comparing the absolute values of the elements and placing the larger square at the position pointer in the result array.
3. left will decrease if the left element is larger otherwise right will decrease.
*/
vector<int> sortedSquares(vector<int> &nums)
{
    int n = nums.size();
    int left = 0;
    int right = n - 1;
    int pos = n - 1;
    vector<int> res(n); //this will store the result form last index to first index
    while (left <= right)
    {
        int ele1 = nums[left];
        int ele2 = nums[right];
        if (abs(ele1 * ele1) < abs(ele2 * ele2)) //compare the left and right element square
        //here the right element square is greater than left element square so we will put the right element square at the last position of the result array then decrease the right pointer
        {
            res[pos] = ele2 * ele2;
            right--;
        }
        else //here the left element square is greater than right element square so we will put the left element square at the last position of the result array then increase the left pointer
        {
            res[pos] = ele1 * ele1;
            left++;
        }
        pos--; //ones the element is placed at the last position decrease the position pointer
    }
    return res;
}
int main()
{
    vector<int> nums = {-7, -3, 2, 3, 11};
    vector<int> result = sortedSquares(nums);
    for (auto &it : result)
    {
        cout << it << " ";
    }
    cout << endl;
    return 0;
}