// =============================================================================
// ROW WITH MAXIMUM ONES
// =============================================================================
// Problem: Find the row index with maximum number of 1s in a binary matrix.
//          Return {row_index, count_of_ones}
//
// TWO APPROACHES:
//   1. Brute Force (for UNSORTED matrix) - O(M * N) time
//   2. Binary Search (for SORTED matrix) - O(M * log N) time
//
// KEY DIFFERENCE:
//   - Unsorted: 0s and 1s can be anywhere → must check every element
//   - Sorted: 0s come first, then 1s → can use binary search to find first 1
// =============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// APPROACH 1: BRUTE FORCE (Works for UNSORTED Matrix)
// =============================================================================
// TIME: O(M * N)  |  SPACE: O(1)
//
// WHEN TO USE:
//   - Matrix is NOT sorted (0s and 1s are scattered randomly)
//   - Example: {{1, 0, 1}, {0, 1, 1}, {1, 1, 0}}
//
// HOW IT WORKS:
//   - For each row, count all 1s by traversing every element
//   - Track the row with maximum 1s
//
// VISUAL:
//   Matrix (unsorted):
//       col0  col1  col2
//   row0  1     0     1     → count = 2
//   row1  0     1     1     → count = 2
//   row2  1     1     0     → count = 2
//
//   Must check ALL elements because 1s are scattered
// =============================================================================
class Solution1 {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
        
        int m = mat.size();      // Number of rows
        int n = mat[0].size();   // Number of columns

        int maxOnes = 0;     // Maximum 1s found so far
        int answerRow = 0;   // Row index with maximum 1s

        // Check each row
        for (int i = 0; i < m; i++) {
            
            int count = 0;  // Count of 1s in current row

            // Count 1s in current row (must check ALL elements)
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    count++;
                }
            }

            // Update only if strictly greater (to handle ties - pick first occurrence)
            if (count > maxOnes) {
                maxOnes = count;
                answerRow = i;
            }
        }

        return {answerRow, maxOnes};
    }
};

// =============================================================================
// APPROACH 2: BINARY SEARCH (Works for SORTED Matrix)
// =============================================================================
// TIME: O(M * log N) if already sorted, O(M * N log N) if needs sorting
// SPACE: O(1)
//
// WHEN TO USE:
//   - Matrix is SORTED (all 0s come first, then all 1s in each row)
//   - Example: {{0, 0, 1}, {0, 1, 1}, {0, 0, 0}}
//
// HOW IT WORKS:
//   - Since row is sorted: [0, 0, ..., 0, 1, 1, ..., 1]
//   - Use binary search to find the INDEX of first 1
//   - Number of 1s = total columns - first 1 index
//
// VISUAL:
//   Sorted Row: [0, 0, 0, 1, 1, 1]
//                 ↑  ↑  ↑  ↑  ↑  ↑
//   Index:       0  1  2  3  4  5
//
//   Binary search finds first 1 at index 3
//   Count of 1s = 6 - 3 = 3
//
// BINARY SEARCH LOGIC:
//   - If mid == 1: found a 1, but check left for earlier 1 → high = mid - 1
//   - If mid == 0: first 1 must be on right → low = mid + 1
//   - Return low (index of first 1)
//
// EDGE CASES:
//   - All 0s: low will be n (no 1s found) → count = n - n = 0
//   - All 1s: low will be 0 → count = n - 0 = n
// =============================================================================
class Solution2 {
public:

    // Returns the index of the first 1 in a sorted row
    // Row must be sorted: [0, 0, ..., 0, 1, 1, ..., 1]
    int firstOne(vector<int>& row) {

        int low = 0;
        int high = row.size() - 1;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (row[mid] == 1) {
                // Found 1, but there may be another 1 further left
                high = mid - 1;  // Search left half
            }
            else {
                // Found 0, so first 1 must be on the right
                low = mid + 1;   // Search right half
            }
        }

        // low = index of first 1 (or n if no 1s exist)
        return low;
    }

    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {

        int m = mat.size();
        int n = mat[0].size();

        int maxOnes = 0;
        int answerRow = 0;

        for (int i = 0; i < m; i++) {

            // NOTE: This sorts the row if not already sorted
            // If matrix is guaranteed sorted, remove this line
            sort(mat[i].begin(), mat[i].end());

            // Find first 1 using binary search
            int first = firstOne(mat[i]);

            // Number of 1s = total columns - index of first 1
            int ones = n - first;

            // Update answer
            if (ones > maxOnes) {
                maxOnes = ones;
                answerRow = i;
            }
        }

        return {answerRow, maxOnes};
    }
};

// =============================================================================
// MAIN - Compare both approaches
// =============================================================================
int main(){
    // Test Case 1: UNSORTED matrix (Approach 1 is better)
    vector<vector<int>> unsorted = {
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 1},
        {1, 1, 1, 0, 0}
    };

    // Test Case 2: SORTED matrix (Approach 2 is better)
    vector<vector<int>> sorted = {
        {0, 0, 1, 1, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1}
    };

    /*
    COMPARISON TABLE:
    
    ┌─────────────────┬──────────────────┬──────────────────┐
    │     Aspect      │   Approach 1     │   Approach 2     │
    │                 │  (Brute Force)   │ (Binary Search)  │
    ├─────────────────┼──────────────────┼──────────────────┤
    │ Time Complexity │   O(M * N)       │  O(M * log N)    │
    │ Space           │   O(1)           │  O(1)            │
    │ Matrix Type     │   Unsorted       │  Sorted          │
    │ Best For        │   Random 0s/1s   │  0s then 1s      │
    │ Modifies Matrix │   No             │  Yes (if sorted) │
    └─────────────────┴──────────────────┴──────────────────┘
    
    WHEN TO USE WHICH:
    
    Approach 1 (Brute Force):
    ✓ Use when matrix is unsorted (0s and 1s scattered)
    ✓ Simple, no extra logic needed
    ✓ Always O(M * N) - guaranteed
    
    Approach 2 (Binary Search):
    ✓ Use when each row is sorted (0s followed by 1s)
    ✓ Faster: O(M * log N) vs O(M * N)
    ✓ Binary search eliminates half the elements each step
    
    EXAMPLE: 3 rows, 5 columns each
    
    Unsorted Matrix:          Sorted Matrix:
    col0 col1 col2 col3 col4  col0 col1 col2 col3 col4
    [  1    0    1    0    1]  [  0    0    1    1    1]  ← row 0: 3 ones
    [  0    1    0    1    1]  [  0    1    1    1    1]  ← row 1: 4 ones
    [  1    1    1    0    0]  [  0    0    0    0    1]  ← row 2: 1 one
    
    Approach 1 checks:        Approach 2 checks:
    15 elements total         ~8 comparisons (log2(5) ≈ 2.3 per row)
    5 per row × 3 rows       2-3 per row × 3 rows
    */

    // Test Approach 1 on unsorted matrix
    Solution1 sol1;
    vector<int> result1 = sol1.rowAndMaximumOnes(unsorted);
    cout << "Approach 1 (Brute Force) on UNSORTED matrix:" << endl;
    cout << "  Row " << result1[0] << " has maximum " << result1[1] << " ones" << endl;
    cout << endl;

    // Test Approach 2 on sorted matrix
    Solution2 sol2;
    vector<int> result2 = sol2.rowAndMaximumOnes(sorted);
    cout << "Approach 2 (Binary Search) on SORTED matrix:" << endl;
    cout << "  Row " << result2[0] << " has maximum " << result2[1] << " ones" << endl;

    return 0;
}