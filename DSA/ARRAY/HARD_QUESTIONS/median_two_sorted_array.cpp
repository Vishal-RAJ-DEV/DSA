#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).



Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
*/
// time complexity : O((n1 + n2) log(n1 + n2))
// space complexity : O(n1 + n2)

//algorithm
/*
1. Merge the two sorted arrays into a single sorted array.
2. Calculate the median of the merged array.
   - If the total number of elements is odd, the median is the middle element.
   - If the total number of elements is even, the median is the average of the two middle elements.
3 . Return the median.   
*/
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
    int n1 = nums1.size();
    int n2 = nums2.size();
    int k = n1 + n2;
    vector<int> merged(k);
    for (int i = 0; i < n1; i++)
        merged[i] = nums1[i];
    for (int i = 0; i < n2; i++)
        merged[i + n1] = nums2[i];

    sort(merged.begin(), merged.end());
    if (k % 2 == 0)
    {
        return (merged[k / 2] + merged[(k / 2) - 1]) / 2.0;
    }
    else
    {
        return merged[k / 2];
    }
}

// Optimized approach: Time Complexity: O(m + n), where m and n are the sizes of the two arrays.
// Space Complexity: O(1), as we are using only a constant amount of extra space
//algorithm
/*

*/
double medianOf2(vector<int> &a, vector<int> &b)
{
    int n = a.size(), m = b.size();
    int i = 0, j = 0;

    // m1 to store the middle element
    // m2 to store the second middle element
    int m1 = -1, m2 = -1;

    // loop till (m+n)/2
    for (int count = 0; count <= (m + n) / 2; count++)
    {
        m2 = m1;

        // if both the arrays have remaining elements
        if (i != n && j != m)
            m1 = (a[i] > b[j]) ? b[j++] : a[i++];

        // if only a[] has remaining elements
        else if (i < n)
            m1 = a[i++];

        // if only b[] has remaining elements
        else
            m1 = b[j++];
    }

    // return median based on odd/even size
    if ((m + n) % 2 == 1)
        return m1;
    else
        return (m1 + m2) / 2.0;
}


int main()
{
    vector<int> arr1 = {1, 3};
    vector<int> arr2 = {2};
    cout << findMedianSortedArrays(arr1, arr2) << endl;
    return 0;
}
