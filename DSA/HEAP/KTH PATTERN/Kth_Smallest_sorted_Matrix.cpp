/*
 * Problem: Given an m x n matrix where each row and each column is sorted
 * in ascending order, find the k-th smallest element.
 *
 * Approach 1: Binary Search on Value + Staircase Count (Optimal)
 * Class: KthSmallestBinarySearch
 * Intuition:
 *   - The value range is [matrix[0][0], matrix[m-1][n-1]].
 *   - Binary search on value. For a candidate mid, count elements ≤ mid.
 *   - If count >= k, answer ≤ mid → search left, else search right.
 *   - Counting uses the staircase property: start at top-right, move left
 *     when matrix[r][c] > mid, else add (c+1) and move down.
 *   - This counting is O(m + n) per check.
 * TC: O((m + n) * log(range))  |  SC: O(1)
 *
 * Approach 2: Min-Heap (Merge k sorted rows)
 * Class: KthSmallestMinHeap
 * Intuition:
 *   - Each row is sorted. Treat the problem as merging k sorted lists.
 *   - Push (matrix[r][0], r, 0) for first min(m,k) rows into a min-heap.
 *   - Pop k times. On each pop of (val, r, c), if c+1 < n, push (matrix[r][c+1], r, c+1).
 *   - The k-th popped value is the answer.
 * TC: O(k log m)  |  SC: O(m)
 * Note: Slower than binary search when k is large.
 *
 * Approach 3: Binary Search on Value + Staircase Count (Identical to A1)
 * Class: KthSmallestBinarySearchV2
 * Same as Approach 1. Included as a duplicate for reference.
 */
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class KthSmallestBinarySearch {
public:
    int m, n;
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        m = matrix.size(), n = matrix[0].size();
        int left = matrix[0][0], right = matrix[m-1][n-1], ans = -1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (countLessOrEqual(matrix, mid) >= k) {
                ans = mid;
                right = mid - 1;
            } else left = mid + 1;
        }
        return ans;
    }
    int countLessOrEqual(vector<vector<int>>& matrix, int x) {
        int cnt = 0, c = n - 1;
        for (int r = 0; r < m; ++r) {
            while (c >= 0 && matrix[r][c] > x) --c;
            cnt += (c + 1);
        }
        return cnt;
    }
};


class KthSmallestMinHeap {
public:
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        int m = matrix.size(), n = matrix[0].size(), ans;
        priority_queue<vector<int>, vector<vector<int>>, greater<>> minHeap;
        for (int r = 0; r < min(m, k); ++r)
            minHeap.push({matrix[r][0], r, 0});

        for (int i = 1; i <= k; ++i) {
            auto top = minHeap.top(); minHeap.pop();
            int r = top[1], c = top[2];
            ans = top[0];
            if (c + 1 < n) minHeap.push({matrix[r][c + 1], r, c + 1});
        }
        return ans;
    }
};


class KthSmallestBinarySearchV2 {
public:
    int m, n;
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        m = matrix.size(), n = matrix[0].size();
        int left = matrix[0][0], right = matrix[m-1][n-1], ans = -1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (countLessOrEqual(matrix, mid) >= k) {
                ans = mid;
                right = mid - 1;
            } else left = mid + 1;
        }
        return ans;
    }
    int countLessOrEqual(vector<vector<int>>& matrix, int x) {
        int cnt = 0, c = n - 1;
        for (int r = 0; r < m; ++r) {
            while (c >= 0 && matrix[r][c] > x) --c;
            cnt += (c + 1);
        }
        return cnt;
    }
};


int main(){
    return 0;
}
