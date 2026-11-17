/*
================================================================================
 PROBLEM: EQUAL ROW AND COLUMN PAIRS  (LeetCode 2352 - Medium)
 Topic : 2D Array + Hashing / Frequency Counting
================================================================================

 ---------------------------------------------------------------------------
 WHAT IS ASKED? (Problem Statement)
 ---------------------------------------------------------------------------
 We are given a 0-indexed square matrix `grid` of size n x n (n rows and
 n columns, n == grid.size() == grid[i].size()).

 We have to count the number of PAIRS (i, j) such that:

        the entire ROW number i   is EXACTLY EQUAL TO   the entire COLUMN number j

 "Exactly equal" means element-by-element equality in order:

        ROW i    = [ grid[i][0], grid[i][1], ... , grid[i][n-1] ]   (left -> right)
        COLUMN j = [ grid[0][j], grid[1][j], ... , grid[n-1][j] ]   (top  -> bottom)

 They form an equal pair only if ALL of these hold together:

        grid[i][0] == grid[0][j]
        grid[i][1] == grid[1][j]
        grid[i][2] == grid[2][j]
        ...
        grid[i][k] == grid[k][j]   for every k from 0 to n-1

 Important points / traps:
 - (i, j) and (j, i) are DIFFERENT pairs. Order matters: row i with column j.
 - The same row can match MULTIPLE columns (count every match),
   and the same column can be matched by MULTIPLE rows.
 - Rows are read left-to-right, columns are read top-to-bottom.
 - It is a COUNTING problem -> answer can be more than 1.

 ---------------------------------------------------------------------------
 EXAMPLES
 ---------------------------------------------------------------------------
 Example 1:
   grid = [ [3, 2, 1],
            [1, 7, 6],
            [2, 7, 7] ]

   rows:
     row0 = [3,2,1]
     row1 = [1,7,6]
     row2 = [2,7,7]
   columns:
     col0 = [3,1,2]
     col1 = [2,7,7]
     col2 = [1,6,7]

   Compare every row with every column:
     row0 vs col0/col1/col2 -> no match
     row1 vs col0/col1/col2 -> no match
     row2 = [2,7,7]  ==  col1 = [2,7,7]  -> MATCH  (pair i=2, j=1)
   Answer = 1

 Example 2 (all elements same):
   grid = [ [1,1],
            [1,1] ]
   Every row equals every column -> 2 rows x 2 columns = 4 pairs.

 ---------------------------------------------------------------------------
 APPROACH 1 : BRUTE FORCE (compare every row with every column)
 ---------------------------------------------------------------------------
 Idea:
   - Take each ROW i one by one                        (outer loop)
   - Take each COLUMN j one by one                     (middle loop)
   - Compare them element by element                   (inner loop)
   - If all n elements match -> it is a valid pair, increment answer

 Three nested loops each running n times  ->  O(n * n * n) = O(n^3) time
 Extra space: only a few variables      ->  O(1)

 Detailed walk-through of the code below:
   grid[i][k]  -> element of ROW i at position k   (k moves along the row)
   grid[k][j]  -> element of COLUMN j at position k (k moves down the column)
   If for ANY k the two values differ, the pair is invalid -> `match = false`
   and we `break` immediately (no need to check the remaining elements).
   If the inner loop finishes without breaking, all n elements matched
   and we count this pair.

 ---------------------------------------------------------------------------
 APPROACH 2 : HASHING / FREQUENCY MAP (optimised)
 ---------------------------------------------------------------------------
 Idea:
   Instead of comparing row vs column in O(n) time again and again,
   store all ROWS in a hash map first, then look up every COLUMN.

   Step 1: Insert every row of the matrix into `unordered_map`
           (key = the whole row vector, value = how many times it occurred).
           Because two rows can be identical, we count frequencies.

   Step 2: Build each column j as a vector (top -> bottom).

   Step 3: Look up that column vector in the map.
           If it exists, it means "there are mp[col] rows identical to this
           column", so we add mp[col] to the answer.
           (If not found -> mp.count(col) == 0 -> nothing is added.)

   Time  : O(n^2) to insert all rows + O(n^2) to build/lookup n columns
           -> O(n^2) total  (each lookup is O(1) average)
   Space : O(n^2) for storing all rows in the map

 NOTE: `unordered_map` cannot hash a `vector<int>` by default, so we provide
       a custom hasher `VectorHash` (explained inside the struct below).
================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// ===========================================================================
// APPROACH 1 : BRUTE FORCE  -  Time O(n^3), Space O(1)
// ===========================================================================
class SolutionBruteForce {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();   // matrix is n x n (rows = cols = n)
        int ans = 0;           // counter for the number of equal pairs

        // Loop 1: pick every ROW of the matrix (i = 0 .. n-1)
        for (int i = 0; i < n; i++) {

            // Loop 2: pick every COLUMN of the matrix (j = 0 .. n-1)
            // With Loop 1 + Loop 2 together we visit every (row i, col j) pair
            for (int j = 0; j < n; j++) {

                // Assume this pair matches until we find a mismatch
                bool match = true;

                // Loop 3: compare row i and column j element by element.
                //   grid[i][k] = k-th element of ROW i    (move right along row)
                //   grid[k][j] = k-th element of COLUMN j  (move down the column)
                // Both must be equal for EVERY k = 0 .. n-1
                for (int k = 0; k < n; k++) {
                    if (grid[i][k] != grid[k][j]) {
                        match = false;   // one mismatch -> pair is not equal
                        break;           // stop early, no need to check further
                    }
                }

                // If we never broke out, all n elements matched -> valid pair
                if (match) {
                    ans++;   // count this (i, j) pair
                }
            }
        }

        return ans;   // total number of equal row-column pairs
    }
};


// ===========================================================================
// APPROACH 2 : HASHING WITH FREQUENCY MAP  -  Time O(n^2), Space O(n^2)
// ===========================================================================
class SolutionHashing {
public:

    // -------------------------------------------------------------------------
    // CUSTOM HASH FUNCTION FOR vector<int>
    // -------------------------------------------------------------------------
    // unordered_map needs 3 things:
    //   1. key type            -> here `vector<int>` (a whole row/column)
    //   2. value type          -> `int` (its frequency)
    //   3. a HASH function      -> converts the vector into a size_t number
    // C++'s std::hash is NOT defined for vector<int>, so we must write our own.
    //
    // How our hash works (a rolling/mixing hash):
    //   seed starts from the size of the vector, then for every element x we
    //   combine x's hash into seed using a well-known bit-mixing formula:
    //
    //     seed ^= hash<int>(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    //
    //   - hash<int>(x)      : gives a numeric value for the element
    //   - 0x9e3779b9        : a magic golden-ratio constant that spreads bits
    //   - (seed << 6)/(seed>>2): shift old seed so order of elements matters
    //     (so [1,2] and [2,1] get different hashes)
    //   - ^=                : mixes everything together
    // After processing all elements, `seed` is the hash of the whole vector.
    // -------------------------------------------------------------------------
    struct VectorHash {
        size_t operator()(const vector<int>& v) const {
            size_t seed = v.size();   // start from the vector's length

            for (int x : v) {
                // fold each element into the running hash (order sensitive)
                seed ^= hash<int>{}(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }

            return seed;   // final hash value of the whole row/column
        }
    };

    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();
        int ans = 0;

        // Map:  key = a row (vector<int>),  value = how many rows equal it
        unordered_map<vector<int>, int, VectorHash> mp;

        // -----------------------------------------------------------------
        // STEP 1: Store ALL rows in the hash map and count their frequency.
        //   mp[grid[i]]++  -> if this row already exists, increase its count,
        //                     otherwise it is inserted with count 1.
        // Example: if row [2,7,7] appears twice -> mp[[2,7,7]] = 2
        // -----------------------------------------------------------------
        for (int i = 0; i < n; i++) {
            mp[grid[i]]++;
        }

        // -----------------------------------------------------------------
        // STEP 2: Build every COLUMN (from top to bottom) as a vector.
        // -----------------------------------------------------------------
        for (int j = 0; j < n; j++) {
            vector<int> col;               // this will hold column j

            // i moves DOWN the rows, grid[i][j] picks the j-th element of row i
            for (int i = 0; i < n; i++) {
                col.push_back(grid[i][j]);
            }

            // -----------------------------------------------------------------
            // STEP 3: Search this column in the map.
            //   mp.count(col) tells whether any ROW equals this column.
            //   If yes, then mp[col] = number of rows identical to this column,
            //   and EACH of those rows forms a valid pair with column j.
            //   So we add mp[col] (not just 1!) to the answer.
            //   If not present -> count is 0 -> nothing is added.
            // -----------------------------------------------------------------
            if (mp.count(col)) {
                ans += mp[col];
            }
        }

        return ans;   // total number of equal row-column pairs
    }
};


/*
 ---------------------------------------------------------------------------
 DRY RUN of Approach 2 on Example 1:
   grid = [[3,2,1],
           [1,7,6],
           [2,7,7]]

 STEP 1 (insert rows):
   mp = { [3,2,1] -> 1,
          [1,7,6] -> 1,
          [2,7,7] -> 1 }

 STEP 2 + 3 (check columns):
   j=0: col = [3,1,2] -> not in map -> ans += 0        (ans = 0)
   j=1: col = [2,7,7] -> FOUND!   count = 1 -> ans += 1 (ans = 1)
   j=2: col = [1,6,7] -> not in map -> ans += 0        (ans = 1)

 Final answer = 1
 ---------------------------------------------------------------------------
 COMPARISON
                    Brute Force            Hashing
   Time             O(n^3)                 O(n^2)
   Space            O(1)                   O(n^2)
   Reads            very easy              needs custom hash
   Best for         small n                large n (LeetCode constraints n<=200)
 ===========================================================================
*/


int main(){
    // Example usage:
    // SolutionBruteForce s1;
    // SolutionHashing   s2;
    // vector<vector<int>> grid = {{3,2,1},{1,7,6},{2,7,7}};
    // cout << s1.equalPairs(grid) << endl;   // prints 1
    // cout << s2.equalPairs(grid) << endl;   // prints 1
    return 0;
}
