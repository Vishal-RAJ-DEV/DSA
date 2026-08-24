/*
================================================================================
                    THE MAZE II - SHORTEST DISTANCE PROBLEM
================================================================================

THIS IS DIFFERENT FROM MAZE I:
------------------------------
  Maze I:   Check IF destination is reachable (return true/false)
  Maze II:  Find SHORTEST distance to reach destination (return minimum steps)

KEY DIFFERENCE: Instead of visited[] array, we use distance[] array

WHY DISTANCE ARRAY INSTEAD OF VISITED ARRAY?
---------------------------------------------
  visited[] array:  Only tells if a cell was visited (true/false)
  distance[] array: Tells IF visited AND the minimum steps to reach it

  distance[row][col] = minimum steps (rolls) to reach (row, col)
  
  If distance[row][col] == INF (infinity), cell is unvisited
  If distance[row][col] != INF, cell was visited with that many steps

EXAMPLE:
--------
  visited array:          distance array:
  +---+---+---+           +---+---+---+
  | F | T | F |           |INF| 0 |INF|
  +---+---+---+           +---+---+---+
  | T | T | F |    vs     | 2 | 5 |INF|
  +---+---+---+           +---+---+---+
  | F | F | T |           |INF|INF| 8 |
  +---+---+---+           +---+---+---+

  visited only says "visited or not"
  distance says "visited AND how many steps it took"


================================================================================
                    WHY WE NEED DISTANCE (NOT JUST VISITED)
================================================================================

PROBLEM: Find MINIMUM number of rolls to reach destination

If we only use visited[], we can't track which path is shorter.

Example:
--------
  Path 1: (0,0) -> (1,0) -> (1,3) -> (3,3)  = 3 rolls
  Path 2: (0,0) -> (0,1) -> (0,3) -> (3,3)  = 3 rolls
  Path 3: (0,0) -> (1,0) -> (3,0) -> (3,3)  = 3 rolls

  All paths reach destination, but which is SHORTEST?

With distance[] array:
  distance[3][3] = 3  (minimum of all path lengths)

We update distance only if we find a SHORTER path:
  if (newSteps < distance[newRow][newCol]) {
      distance[newRow][newCol] = newSteps;
  }


================================================================================
                    ROLLING MECHANISM (SAME AS MAZE I)
================================================================================

Ball rolls continuously until hitting wall or boundary:

  Example: Ball at (0,0) moving RIGHT
  
  Step 1: (0,0) -> check (0,1) = 0 (empty) -> move to (0,1), steps++
  Step 2: (0,1) -> check (0,2) = 1 (WALL!) -> STOP at (0,1)
  
  Ball stops at (0,1) with steps = 1
  
  +---+---+---+
  | S |->| W |    S = Start, -> = Rolling, W = Wall
  +---+---+---+
         ^
         Ball stops here

The distance to (0,1) = 1 (took 1 roll to get there)


================================================================================
                    DIRECTION TRICK: directions[5]
================================================================================

Instead of separate direction arrays, we use ONE array:
  int directions[5] = {-1, 0, 1, 0, -1};

How it works:
  directions[0] = -1, directions[1] = 0  -->  UP    (-1, 0)
  directions[1] =  0, directions[2] = 1  -->  RIGHT ( 0, 1)
  directions[2] =  1, directions[3] = 0  -->  DOWN  ( 1, 0)
  directions[3] =  0, directions[4] = -1 -->  LEFT  ( 0,-1)

  For direction index i:
    deltaRow = directions[i]
    deltaCol = directions[i+1]

This is a compact way to store 4 direction pairs.


================================================================================
                    DFS APPROACH (First Solution Class)
================================================================================

DFS LOGIC:
----------
  1. Start at position, distance = 0
  2. For each direction (Up, Right, Down, Left):
     a. Roll ball until wall/boundary
     b. Count steps while rolling
     c. If new distance < current distance at stopping position:
        - Update distance
        - Recursively DFS from new position
  3. Return distance to destination (or -1 if INF)

DFS RECURSION WITH DISTANCE:
-----------------------------
  dfs(maze, row, col):
      |
      +---> For each direction:
      |       |
      |       +---> Roll ball, count steps
      |       |
      |       +---> steps = dist[row][col] + rolled_steps
      |       |
      |       +---> if (steps < dist[newRow][newCol]):
      |               dist[newRow][newCol] = steps
      |               dfs(maze, newRow, newCol)  // recurse
      |
      +---> All directions explored

DFS VISUAL WALKTHROUGH:
-----------------------
  Maze:
    0 0 1 0 0
    0 0 0 0 0
    1 1 1 0 1
    0 0 0 0 0
    0 1 1 1 0

  Start: (0,0), Destination: (4,4)

  Step 1: dfs(0,0), dist[0][0] = 0
          Try DOWN: Roll to (1,0), steps = 1
          dist[1][0] = INF, 1 < INF -> Update dist[1][0] = 1
          Recurse: dfs(1,0)

  Step 2: dfs(1,0), dist[1][0] = 1
          Try RIGHT: Roll to (1,3), steps = 1+3 = 4
          dist[1][3] = INF, 4 < INF -> Update dist[1][3] = 4
          Recurse: dfs(1,3)

  Step 3: dfs(1,3), dist[1][3] = 4
          Try DOWN: Roll to (3,3), steps = 4+2 = 6
          dist[3][3] = INF, 6 < INF -> Update dist[3][3] = 6
          Recurse: dfs(3,3)

  ...continues until all paths explored...

  Final dist[4][4] = shortest distance found


================================================================================
                    BFS APPROACH (Second Solution Class)
================================================================================

BFS LOGIC:
----------
  1. Create queue, push start position
  2. Set dist[start] = 0
  3. While queue not empty:
     a. Pop front position (row, col)
     b. For each direction:
        - Roll ball, count steps
        - steps = dist[row][col] + rolled_steps
        - If steps < dist[newRow][newCol]:
          * Update dist[newRow][newCol] = steps
          * Push (newRow, newCol) to queue
  4. Return dist[destination] or -1

BFS QUEUE OPERATIONS WITH DISTANCE:
------------------------------------
  Queue State          Distances Updated
  -----------          -----------------
  [(0,0)]              dist[0][0] = 0
  Pop (0,0)
  Roll RIGHT -> (0,1)  dist[0][1] = 1
  Roll DOWN -> (1,0)   dist[1][0] = 1
  [(0,1), (1,0)]
  
  Pop (0,1)
  Roll RIGHT -> (0,3)  dist[0][3] = 3
  Roll DOWN -> (1,3)   dist[1][3] = 4
  [(1,0), (0,3), (1,3)]
  
  ...continues until destination reached...

BFS GUARANTEES SHORTEST PATH:
------------------------------
  BFS explores level by level:
    Level 0: (0,0) with dist = 0
    Level 1: (0,1), (1,0) with dist = 1
    Level 2: (0,3), (1,3) with dist = 3-4
    Level 3: ...
  
  First time we reach destination = shortest distance


================================================================================
                    DISTANCE UPDATE COMPARISON
================================================================================

  When do we update distance[row][col]?
  
  ONLY when: newSteps < distance[row][col]
  
  This ensures we keep the MINIMUM distance found so far.
  
  Example:
  --------
    Path A reaches (3,3) with steps = 6
      -> dist[3][3] = 6 (updated, was INF)
    
    Path B reaches (3,3) with steps = 5
      -> 5 < 6, so dist[3][3] = 5 (updated to shorter)
    
    Path C reaches (3,3) with steps = 7
      -> 7 > 5, so dist[3][3] stays 5 (NOT updated)


================================================================================
                    FINAL DISTANCE ARRAY VISUALIZATION
================================================================================

  After running algorithm on example maze:
  
    0  0  1  0  0
    0  0  0  0  0        0 = distance 0
    1  1  1  0  1        1 = distance 1
    0  0  0  0  0        3 = distance 3
    0  1  1  1  0        5 = distance 5
                         INF = unreachable
  
  Final dist array might look like:
    +---+---+---+---+---+
    | 0 | 1 |INF| 3 | 4 |   Row 0
    +---+---+---+---+---+
    | 1 | 2 | 3 | 4 | 5 |   Row 1
    +---+---+---+---+---+
    |INF|INF|INF| 5 |INF|   Row 2
    +---+---+---+---+---+
    | 3 | 4 | 5 | 6 | 7 |   Row 3
    +---+---+---+---+---+
    | 4 |INF|INF|INF| 8 |   Row 4
    +---+---+---+---+---+
  
  dist[4][4] = 8 = shortest distance


================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// ============================================================================
//                          DFS APPROACH
// ============================================================================
//
// DFS WITH DISTANCE TRACKING:
// ---------------------------
//   Instead of visited[] boolean array, we use dist[] integer array
//
//   dist[row][col] = minimum steps to reach (row, col)
//   Initial value: INF (infinity = unreachable)
//   Start position: dist[start] = 0
//
//   When we find a shorter path to a cell, we UPDATE dist[] and recurse
//
// ============================================================================
class Solution {
public:

    int rows, cols;
    vector<vector<int>> dist;  // Distance array (replaces visited[])

    // Direction trick: {-1,0}, {0,1}, {1,0}, {0,-1} for Up,Right,Down,Left
    int directions[5] = {-1, 0, 1, 0, -1};

    void dfs(vector<vector<int>>& maze, int row, int col) {

        // Try all 4 directions
        for (int dir = 0; dir < 4; dir++) {

            int newRow = row;
            int newCol = col;

            // Start with current distance, add steps while rolling
            int steps = dist[row][col];

            // Get direction deltas
            int deltaRow = directions[dir];
            int deltaCol = directions[dir + 1];

            // ROLL THE BALL:
            // Keep moving until hitting wall or boundary
            // Count each step while rolling
            //
            // Example: From (0,0) rolling RIGHT
            //   (0,0) -> (0,1): steps = 0 + 1 = 1
            //   (0,1) -> (0,2): WALL! Stop at (0,1)
            //
            while (
                newRow + deltaRow >= 0 &&
                newRow + deltaRow < rows &&
                newCol + deltaCol >= 0 &&
                newCol + deltaCol < cols &&
                maze[newRow + deltaRow][newCol + deltaCol] == 0
            ) {
                newRow += deltaRow;
                newCol += deltaCol;
                steps++;  // Count each roll as one step
            }
            // After loop: (newRow, newCol) = stopping position
            //             steps = total distance to reach here

            // KEY LOGIC: Only update if we found a SHORTER path
            // This is why we use distance[] instead of visited[]
            //
            // If dist[newRow][newCol] is INF, it's unvisited (update it)
            // If dist[newRow][newCol] is not INF, only update if shorter
            //
            if (steps < dist[newRow][newCol]) {

                dist[newRow][newCol] = steps;  // Update to shorter distance

                // Continue DFS from new position
                // This explores all paths from this new stopping point
                dfs(maze, newRow, newCol);
            }
        }
    }


    int shortestDistance(
        vector<vector<int>>& maze,
        vector<int>& start,
        vector<int>& destination
    ) {

        rows = maze.size();
        cols = maze[0].size();

        // Initialize distance array with infinity (INF)
        // INF means "unreachable" or "not visited yet"
        const int INF = 1e9;

        dist.assign(
            rows,
            vector<int>(cols, INF)
        );

        // Distance to start is 0 (starting point)
        dist[start[0]][start[1]] = 0;

        // Start DFS exploration
        dfs(maze, start[0], start[1]);

        // Return result:
        // - If dist[destination] is still INF -> unreachable, return -1
        // - Otherwise -> return the shortest distance
        return dist[destination[0]][destination[1]] == INF
                   ? -1
                   : dist[destination[0]][destination[1]];
    }
};


// ============================================================================
//                          BFS APPROACH
// ============================================================================
//
// BFS WITH DISTANCE TRACKING:
// ---------------------------
//   Same concept: use dist[] instead of visited[]
//
//   BFS explores level by level (all positions at distance 1, then 2, etc.)
//   This GUARANTEES first time we reach destination = shortest distance
//
//   Queue stores positions to explore
//   dist[] tracks minimum distance to each position
//
// ============================================================================
class Solution2 {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {

        int rows = maze.size();
        int cols = maze[0].size();

        // Initialize distance array with infinity
        // 0x3f3f3f3f is a common infinity value in competitive programming
        // It's large enough to not overflow when added to, but small enough to fit in int
        const int INF = 0x3f3f3f3f;
        vector<vector<int>> distance(rows, vector<int>(cols, INF));

        // Extract start and destination coordinates
        int startRow = start[0], startCol = start[1];
        int destRow = destination[0], destCol = destination[1];

        // Distance to start position is 0
        distance[startRow][startCol] = 0;

        // BFS queue - stores positions to explore
        queue<pair<int, int>> bfsQueue;
        bfsQueue.emplace(startRow, startCol);

        // Direction trick array
        int directions[5] = {-1, 0, 1, 0, -1};

        // BFS LOOP: Process all reachable positions
        while (!bfsQueue.empty()) {

            // Get front position (FIFO order)
            auto it = bfsQueue.front();
            bfsQueue.pop();
            int currentRow = it.first;
            int currentCol = it.second;

            // Try rolling in all 4 directions
            for (int dir = 0; dir < 4; ++dir) {

                // Initialize position and steps
                int newRow = currentRow;
                int newCol = currentCol;
                int steps = distance[currentRow][currentCol];  // Start with current distance

                // Get direction deltas
                int deltaRow = directions[dir];
                int deltaCol = directions[dir + 1];

                // ROLL THE BALL:
                // Keep moving until hitting wall or boundary
                // Increment steps for each roll
                while (
                    newRow + deltaRow >= 0 &&
                    newRow + deltaRow < rows &&
                    newCol + deltaCol >= 0 &&
                    newCol + deltaCol < cols &&
                    maze[newRow + deltaRow][newCol + deltaCol] == 0
                ) {
                    newRow += deltaRow;
                    newCol += deltaCol;
                    ++steps;  // Each roll counts as one step
                }
                // (newRow, newCol) = stopping position
                // steps = total distance to reach here

                // KEY LOGIC: Update if shorter path found
                // This is why we use distance[] instead of visited[]
                //
                // If distance[newRow][newCol] is INF -> unvisited (update)
                // If distance[newRow][newCol] is not INF -> only update if shorter
                //
                if (steps < distance[newRow][newCol]) {

                    distance[newRow][newCol] = steps;  // Update to shorter

                    // Add to queue to explore from this new position
                    bfsQueue.emplace(newRow, newCol);
                }
            }
        }

        // Return shortest distance, or -1 if unreachable
        return distance[destRow][destCol] == INF ? -1 : distance[destRow][destCol];
    }
};


// ============================================================================
//                           MAIN FUNCTION
// ============================================================================
//
// TEST CASE:
// ----------
// Maze:
//   0 0 1 0 0
//   0 0 0 0 0
//   1 1 1 0 1
//   0 0 0 0 0
//   0 1 1 1 0
//
// Start: (0,0)
// Destination: (4,4)
//
// Expected Output: 8 (shortest distance)
//
// ============================================================================
int main(){
    return 0;
}
