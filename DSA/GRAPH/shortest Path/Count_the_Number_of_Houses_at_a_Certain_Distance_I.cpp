#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * PROBLEM: Count the Number of Houses at a Certain Distance I
 *
 * n houses are labeled 1 to n and arranged in a LINE:
 *
 *   1 --- 2 --- 3 --- 4 --- ... --- n
 *
 * There is ONE extra undirected road between house x and house y.
 * This may create a shortcut (or a cycle if x and y are neighbors).
 *
 * GOAL: For each k from 1 to n-1, count how many PAIRS of houses (i, j)
 *       have shortest distance exactly k.
 *
 * Return a vector res of size n where:
 *   res[0] = number of pairs at distance 1
 *   res[1] = number of pairs at distance 2
 *   ...
 *   res[n-2] = number of pairs at distance n-1
 *
 * APPROACH: Floyd-Warshall (All-Pairs Shortest Path)
 *
 * Why Floyd-Warshall?
 *   - n <= 100, so O(n^3) = 1,000,000 operations — fast enough.
 *   - It's simple to implement: just 3 nested loops.
 *   - We need shortest paths between EVERY pair, which is exactly
 *     what Floyd-Warshall gives us.
 *
 * INTUITION:
 *   1. Build an adjacency matrix with direct edge weights = 1.
 *   2. Run Floyd-Warshall to compute shortest paths between ALL pairs.
 *   3. Count how many pairs have each distance.
 *
 * EXAMPLE: n=5, x=2, y=5
 *   Line: 1-2-3-4-5, plus edge 2-5
 *
 *   Adjacency matrix (after init):
 *        1  2  3  4  5
 *   1:  0  1  -  -  -
 *   2:  1  0  1  -  1   (extra edge 2-5)
 *   3:  -  1  0  1  -
 *   4:  -  -  1  0  1
 *   5:  -  1  -  1  0   (extra edge 5-2)
 *
 *   After Floyd-Warshall:
 *        1  2  3  4  5
 *   1:  0  1  2  3  2
 *   2:  1  0  1  2  1
 *   3:  2  1  0  1  2
 *   4:  3  2  1  0  1
 *   5:  2  1  2  1  0
 *
 *   Distance 1: (1,2)(2,3)(3,4)(4,5)(2,5) → 5 pairs
 *   Distance 2: (1,3)(1,5)(2,4)(3,5)       → 4 pairs
 *   Distance 3: (1,4)                       → 1 pair
 *   res = [5, 4, 1, 0]
 */

class Solution {
public:
    vector<int> countOfPairs(int n, int x, int y) {

        // Create an (n+1) x (n+1) distance matrix (1-based indexing).
        // Initialize all distances to INT_MAX (unreachable).
        vector<vector<int>> grid(
            n + 1,
            vector<int>(n + 1, INT_MAX)
        );

        // Step 1: Add edges for the LINE: 1-2-3-...-n
        // Each edge has weight 1 (undirected).
        for (int i = 1; i < n; i++) {
            grid[i][i + 1] = 1;
            grid[i + 1][i] = 1;
        }

        // Step 2: Add the EXTRA road between x and y (weight 1, undirected).
        grid[x][y] = 1;
        grid[y][x] = 1;

        // Step 3: Distance from every node to itself is 0.
        for (int i = 1; i <= n; i++) {
            grid[i][i] = 0;
        }

        // Step 4: Floyd-Warshall — compute all-pairs shortest paths.
        //
        // For each intermediate node "via", check if the path
        //   i -> via -> j
        // is shorter than the current known path i -> j.
        //
        // Why this works: after processing all "via" nodes,
        // every possible path has been considered.
        for (int via = 1; via <= n; via++) {

            for (int i = 1; i <= n; i++) {

                for (int j = 1; j <= n; j++) {

                    // Guard: skip if either half of the path is unreachable
                    if (grid[i][via] != INT_MAX &&
                        grid[via][j] != INT_MAX) {

                        grid[i][j] = min(
                            grid[i][j],
                            grid[i][via] + grid[via][j]
                        );
                    }
                }
            }
        }

        // Step 5: Count pairs by distance.
        // res[d-1] = number of pairs with shortest distance d.
        vector<int> res(n, 0);

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= n; j++) {

                if (i == j) continue;  // skip self-pairs

                int distance = grid[i][j];

                // distance is 1-indexed, res is 0-indexed
                res[distance - 1]++;
            }
        }

        return res;
    }
};



int main(){
    return 0;
}