#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    PROBLEM: Kth Smallest Number in Multiplication Table (LeetCode 668)

    Given three integers m, n, and k:
    - m = number of rows, n = number of columns
    - We have an m x n multiplication table:

           1   2   3  ...  n
        1  1   2   3  ...  n
        2  2   4   6  ...  2n
        3  3   6   9  ...  3n
       ... ... ... ... ... ...
        m  m  2m  3m  ...  mn

    Find the k-th smallest number in this table.

    Example: m=3, n=3, k=5
    Table: {1, 2, 2, 3, 3, 4, 6, 6, 9}
    Sorted: {1, 2, 2, 3, 3, 4, 6, 6, 9}
    5th smallest = 3

    APPROACH: Binary Search on the Answer
    - The smallest possible value is 1, largest is m*n.
    - We binary search on the value range [1, m*n].
    - For a candidate value "mid", we COUNT how many numbers in the table are <= mid.
    - If count >= k, the k-th smallest is <= mid, so search LEFT.
    - If count < k, the k-th smallest is > mid, so search RIGHT.
    - This works because: if many numbers are <= mid, the k-th smallest
      must be somewhere in the left half (or at mid itself).
*/

class Solution {
public:
    /*
        COUNT FUNCTION: Counts how many numbers in the multiplication table are <= mid.

        How it works:
        - Each row i (1 to m) contains: i*1, i*2, i*3, ..., i*n
        - For row i, we want to count how many of these values are <= mid.
        - The values in row i are: i, 2i, 3i, ..., ni  (all multiples of i)
        - The number of multiples of i that are <= mid = floor(mid / i)
          BUT we can't exceed n columns, so we take min(n, mid / i).

        Example: mid=5, m=3, n=3
        Row 1 (i=1): values = {1,2,3} -> all <= 5, count = min(3, 5/1) = min(3,5) = 3
        Row 2 (i=2): values = {2,4,6} -> {2,4} <= 5, count = min(3, 5/2) = min(3,2) = 2
        Row 3 (i=3): values = {3,6,9} -> {3} <= 5, count = min(3, 5/3) = min(3,1) = 1
        Total = 3 + 2 + 1 = 6 numbers <= 5

        Time complexity: O(m) per call (iterates over m rows)
    */
    long long helperFunction(long long mid, long long m, long long n)
    {
        long long cnt = 0;
        for(int i = 1; i <= m; i++)
        {
            // For row i, count how many multiples (i*1, i*2, ..., i*n) are <= mid
            // mid/i gives the count of multiples of i up to mid
            // min(n, mid/i) ensures we don't count more than n columns
            cnt += min(n, mid / i);
        }
        return cnt;
    }

    /*
        MAIN FUNCTION: Binary search to find k-th smallest number.

        Search space: low = 1, high = m*n (smallest to largest possible value)
        - mid = candidate answer (a value we test)
        - cnt = how many numbers in table are <= mid
        - If cnt >= k: too many numbers <= mid, so k-th smallest is <= mid -> go left (high = mid-1)
        - If cnt < k:  too few numbers <= mid, so k-th smallest is > mid  -> go right (low = mid+1)

        Why return low?
        - When the loop ends (low > high), low points to the smallest value
          for which count >= k, which is exactly the k-th smallest number.
        - This is the standard binary search pattern for finding the
          "first value that satisfies a condition."
    */
    int findKthNumber(int m, int n, int k) {
        long long low = 1;
        long long high = (long long)m * n;

        while(low <= high)
        {
            long long mid = low + (high - low) / 2;

            long long cnt = helperFunction(mid, m, n);

            if(cnt >= k)
            {
                // count >= k means the k-th smallest is <= mid
                // But there might be a smaller value that also has count >= k
                // So we try to find a smaller answer by going left
                high = mid - 1;
            }
            else
            {
                // count < k means there aren't enough numbers <= mid
                // The k-th smallest must be larger than mid
                // So we go right to look for a bigger value
                low = mid + 1;
            }
        }

        return low;
    }
};


int main(){
    return 0;
}