#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 1337. The K Weakest Rows in a Matrix

    You are given an m x n binary matrix mat of 1's (soldiers) and 0's (civilians).
    The rows are sorted from left to right in non-increasing order of soldiers
    (i.e., all 1's come before any 0's).

    A row i is weaker than row j if:
        - The number of soldiers in row i is less than in row j, OR
        - They have the same number of soldiers but i < j (smaller index).

    Return the indices of the k weakest rows in the matrix ordered from
    weakest to strongest.

    Example:
        Input: mat =
        [[1,1,0,0,0],
         [1,1,1,1,0],
         [1,0,0,0,0],
         [1,1,0,0,0],
         [1,1,1,1,1]],
        k = 3
        Output: [2,0,3]
        Explanation:
            Row 2 has 1 soldier  -> weakest
            Row 0 has 2 soldiers
            Row 3 has 2 soldiers
            Row 1 has 4 soldiers
            Row 4 has 5 soldiers  -> strongest
            The 3 weakest are [2,0,3].
*/


// =========================================================
// APPROACH 1: Max-Heap + Linear Soldier Count — O(n*m + n log k)
// =========================================================
/*
    LOGIC:
        1. Iterate through each row of the matrix.
        2. For each row, count the number of soldiers (1's) by scanning all
           'm' columns linearly.
        3. Push a pair {soldierCount, rowIndex} into a max-heap (which keeps
           the largest count at the top by default for pairs).
        4. Maintain heap size ≤ k. Whenever size exceeds k, pop the top
           (which removes the strongest row among the k weakest so far).
        5. After processing all rows, the heap contains the k weakest rows,
           but in descending order of weakness (strongest weakest at top).
        6. Pop all elements into a vector and then reverse it to get the
           required ascending order (weakest to strongest).

        Why max-heap and not min-heap?
        - Min-heap would keep smallest at top, but we want to keep only the
          k smallest rows overall. With a max-heap of size k, the top holds
          the largest among the k smallest — so any new row smaller than top
          should push out the top. This is more efficient than storing all
          n rows in a min-heap (which would take O(n log n) vs O(n log k)).

    TIME COMPLEXITY:
        - Counting soldiers per row: O(m) per row, so O(n * m) total
        - Pushing into heap: O(log k) per row, so O(n log k) total
        - Popping excess (at most n - k pops): O((n - k) log k)
        - Popping final k elements into ans: O(k log k)
        - Reversing ans: O(k)
        - Overall: O(n * m + n log k)

    SPACE COMPLEXITY:
        - Max-heap stores at most k pairs: O(k)
        - ans vector: O(k)
        - Overall: O(k)
*/
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {

        int n = mat.size();
        int m = mat[0].size();

        priority_queue<pair<int,int>> pq;

        for(int i = 0; i < n; i++){

            int soldiers = 0;

            for(int j = 0; j < m; j++){

                if(mat[i][j] == 1)
                    soldiers++;
            }

            pq.push({soldiers, i});

            if(pq.size() > k)
                pq.pop();  // removes the strongest among the k weakest
        }

        vector<int> ans;

        while(!pq.empty()){

            ans.push_back(pq.top().second);
            pq.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};


// =========================================================
// APPROACH 2: Max-Heap + Binary Search Soldier Count — O(n log m + n log k)
// =========================================================
/*
    LOGIC:
        1. Since each row is sorted with all 1's first followed by all 0's,
           we can find the number of soldiers using binary search.
        2. countSoldiers(row):
           - Performs binary search on the row to find the first occurrence
             of 0. The index of the first 0 equals the number of 1's.
           - Standard lower-bound search on a descending-then-ascending seq:
             if row[mid] == 1, search right half (low = mid + 1);
             else search left half (high = mid - 1).
           - Returns low (which is the count of soldiers).
        3. Same max-heap logic as Approach 1 to maintain the k weakest rows.

        Binary search is faster than linear scan when m is large, because we
        reduce per-row cost from O(m) to O(log m).

        Edge case: If all elements are 1 (no 0), the while loop exits when
        low > high. low will be = row.size(), which correctly equals the
        number of soldiers.

    TIME COMPLEXITY:
        - Binary search per row: O(log m), so O(n log m) total
        - Heap operations: O(n log k)
        - Overall: O(n log m + n log k)
        - This is better than Approach 1 when m is large.

    SPACE COMPLEXITY:
        - Max-heap stores at most k pairs: O(k)
        - ans vector: O(k)
        - Overall: O(k)
*/
class Solution {
public:
    int countSoldiers(vector<int>& row) {
        int low = 0;
        int high = row.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (row[mid] == 1)
                low = mid + 1;   // 1 found, search right half
            else
                high = mid - 1;  // 0 found, search left half
        }

        return low;  // low = index of first 0 = number of 1's
    }

    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {

        int rows = mat.size();

        priority_queue<pair<int, int>> pq;

        for (int i = 0; i < rows; i++) {

            int soldiers = countSoldiers(mat[i]);

            pq.push({soldiers, i});

            if (pq.size() > k)
                pq.pop();
        }

        vector<int> ans;

        while (!pq.empty()) {
            ans.push_back(pq.top().second);
            pq.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};
int main(){
    return 0;
}
