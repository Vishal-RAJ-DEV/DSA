#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /***********************************************************************
        ALGORITHM (Binary Search + DFS)

        Observation:
        -------------------------
        We need to find the minimum time T such that there exists
        a path from (0,0) to (n-1,n-1).

        Water rises with time.

        At time = T,
        we are allowed to visit ONLY those cells whose elevation <= T.

        Therefore,

            Can we reach destination at time = T ?

        is simply a YES / NO question.

        ----------------------------------------------------------

        Binary Search Logic

        Suppose

            T = 5   -> Impossible
            T = 6   -> Impossible
            T = 7   -> Possible
            T = 8   -> Possible
            T = 9   -> Possible

        Notice the pattern

                F F F T T T T

        Once it becomes possible,
        it will always remain possible for larger times because
        more cells become accessible.

        This is a monotonic property.

        Therefore Binary Search can be applied on answer.

        ----------------------------------------------------------

        DFS Logic

        For every guessed time (mid),

        Start DFS from (0,0)

        Only move into cells satisfying

                grid[r][c] <= mid

        If DFS reaches destination

                answer may be smaller

        Else

                we need larger time.

        ----------------------------------------------------------

        Time Complexity

        Binary Search :
                O(log(n²))

        DFS each iteration :
                O(n²)

        Total

                O(n² log n)

        ----------------------------------------------------------

        Space Complexity

                O(n²)

        due to visited array + recursion stack.
    ***********************************************************************/


    // Four possible directions
    vector<vector<int>> dir{
        {-1,0},
        {1,0},
        {0,-1},
        {0,1}
    };

    int n;

    //------------------------------------------------------------------
    // DFS
    //
    // Returns true if destination can be reached
    // at current water level = time.
    //------------------------------------------------------------------
    bool dfs(int row,
             int col,
             int time,
             vector<vector<int>>& grid,
             vector<vector<bool>>& visited)
    {

        // Outside grid
        if(row < 0 || row >= n || col < 0 || col >= n)
            return false;

        // Already visited
        if(visited[row][col])
            return false;

        // Cell elevation is higher than current water level.
        // We cannot enter this cell.
        if(grid[row][col] > time)
            return false;

        // Mark current cell visited
        visited[row][col] = true;

        // Destination reached
        if(row == n-1 && col == n-1)
            return true;

        // Explore all four neighbours
        for(auto &d : dir)
        {
            int newRow = row + d[0];
            int newCol = col + d[1];

            // If any neighbour reaches destination
            if(dfs(newRow, newCol, time, grid, visited))
                return true;
        }

        // No path exists
        return false;
    }

    //------------------------------------------------------------------
    // Main Function
    //------------------------------------------------------------------
    int swimInWater(vector<vector<int>>& grid) {

        n = grid.size();

        //--------------------------------------------------------------
        // Lowest possible answer
        //
        // We cannot even stand on start cell before
        // water reaches grid[0][0].
        //
        // Similarly destination cannot be entered before
        // water reaches grid[n-1][n-1].
        //
        // Hence answer cannot be smaller than both.
        //--------------------------------------------------------------
        int low = max(grid[0][0], grid[n-1][n-1]);

        //--------------------------------------------------------------
        // Highest possible answer
        //
        // Maximum elevation in grid is n*n-1.
        //--------------------------------------------------------------
        int high = n * n - 1;

        // Store minimum valid answer
        int answer = high;

        //--------------------------------------------------------------
        // Binary Search
        //--------------------------------------------------------------
        while(low <= high)
        {
            // Current guessed answer
            int mid = low + (high - low) / 2;

            //----------------------------------------------------------
            // Fresh visited array for this DFS
            //----------------------------------------------------------
            vector<vector<bool>> visited(
                n,
                vector<bool>(n,false)
            );

            //----------------------------------------------------------
            // Can we reach destination at time = mid ?
            //----------------------------------------------------------
            if(dfs(0,0,mid,grid,visited))
            {
                // mid works

                answer = mid;

                // Try finding an even smaller answer
                high = mid - 1;
            }
            else
            {
                // mid is too small

                // Need larger water level
                low = mid + 1;
            }
        }

        return answer;
    }
};


class Solution {
public:

    /***********************************************************************

        ALGORITHM (Dijkstra - Minimum Maximum Path)

        Observation
        ---------------------------------------------------------

        In a normal shortest path problem,

            Cost of Path = Sum of Edge Weights

        Dijkstra minimizes

                total distance

        ---------------------------------------------------------

        But in this problem,

        Water level must be at least equal to the
        HIGHEST elevation on our chosen path.

        Example

                0 -> 2 -> 5 -> 3 -> 8

        Required Time

                max(0,2,5,3,8) = 8

        Another Path

                0 -> 1 -> 2 -> 3 -> 4

        Required Time

                max(0,1,2,3,4)=4

        Obviously second path is better.

        Therefore,

        Instead of minimizing

                SUM

        we minimize

                MAXIMUM elevation on path.

        ---------------------------------------------------------

        Modified Dijkstra

        dist[r][c]

        means

        Minimum possible maximum elevation needed
        to reach cell (r,c).

        Transition

        Suppose

            Current Path Cost = 6

            Neighbour Elevation = 4

        New Cost

            max(6,4)=6

        Because water is already at level 6.

        Another Example

            Current Cost = 6

            Neighbour = 9

        New Cost

            max(6,9)=9

        Since water must rise to 9.

        Transition Formula

            newCost = max(currentCost,
                          grid[newRow][newCol])

        ---------------------------------------------------------

        Why Dijkstra Works ?

        Dijkstra works whenever

        extending a path can never decrease its cost.

        Here

            newCost = max(currentCost,elevation)

        Since

            max(a,b) >= a

        Cost never decreases.

        Therefore once a node is popped from the
        priority queue,

        we have already found its minimum possible cost.

        Same proof as standard Dijkstra.

        ---------------------------------------------------------

        Time Complexity

        Number of Vertices

                n²

        Number of Edges

                4*n²

        Dijkstra

                O(V log V)

        Therefore

                O(n² log n)

        ---------------------------------------------------------

        Space Complexity

                O(n²)

        due to

            distance array
            priority queue

    ***********************************************************************/


    // Four possible movement directions
    vector<vector<int>> dir{
        {-1,0},
        {1,0},
        {0,-1},
        {0,1}
    };

    int swimInWater(vector<vector<int>>& grid) {

        int n = grid.size();

        //----------------------------------------------------------
        // dist[r][c]
        //
        // Minimum possible maximum elevation required
        // to reach this cell.
        //----------------------------------------------------------
        vector<vector<int>> dist(
            n,
            vector<int>(n, INT_MAX)
        );

        //----------------------------------------------------------
        // Min Heap
        //
        // Stores
        //
        // {
        //      currentCost,
        //      row,
        //      column
        // }
        //
        // Smallest currentCost comes first.
        //----------------------------------------------------------
        priority_queue<
            vector<int>,
            vector<vector<int>>,
            greater<vector<int>>
        > pq;

        //----------------------------------------------------------
        // Starting point
        //
        // Initially we are standing at (0,0).
        //
        // Water level must at least reach
        // grid[0][0].
        //----------------------------------------------------------
        dist[0][0] = grid[0][0];

        pq.push({
            grid[0][0],
            0,
            0
        });

        //----------------------------------------------------------
        // Standard Dijkstra Loop
        //----------------------------------------------------------
        while(!pq.empty())
        {
            //------------------------------------------------------
            // Take node having minimum current cost.
            //------------------------------------------------------
            auto current = pq.top();
            pq.pop();

            int cost = current[0];
            int row  = current[1];
            int col  = current[2];

            //------------------------------------------------------
            // Ignore outdated entry.
            //
            // Better path already found earlier.
            //------------------------------------------------------
            if(cost > dist[row][col])
                continue;

            //------------------------------------------------------
            // Destination reached.
            //
            // Since Dijkstra pops nodes in increasing order
            // of cost,
            //
            // this is guaranteed to be the minimum answer.
            //------------------------------------------------------
            if(row == n-1 && col == n-1)
                return cost;

            //------------------------------------------------------
            // Explore all four neighbours.
            //------------------------------------------------------
            for(auto &d : dir)
            {
                int newRow = row + d[0];
                int newCol = col + d[1];

                //--------------------------------------------------
                // Outside grid
                //--------------------------------------------------
                if(newRow < 0 || newRow >= n ||
                   newCol < 0 || newCol >= n)
                    continue;

                //--------------------------------------------------
                // Cost of going to neighbour.
                //
                // Water level must be maximum of
                //
                // current path cost
                //
                // and
                //
                // neighbour elevation.
                //--------------------------------------------------
                int newCost = max(
                    cost,
                    grid[newRow][newCol]
                );

                //--------------------------------------------------
                // Found a better path.
                //--------------------------------------------------
                if(newCost < dist[newRow][newCol])
                {
                    dist[newRow][newCol] = newCost;

                    pq.push({
                        newCost,
                        newRow,
                        newCol
                    });
                }
            }
        }

        return -1;
    }
};


int main(){
    return 0;
}