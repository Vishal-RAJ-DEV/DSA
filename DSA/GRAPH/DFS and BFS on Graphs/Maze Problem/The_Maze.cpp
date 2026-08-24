/*
================================================================================
                        THE MAZE PROBLEM
================================================================================

PROBLEM:
--------
There is a ball in a maze. The maze has:
  - Empty cells (represented by 0) where the ball can roll
  - Walls (represented by 1) that block the ball

The ball can roll in 4 directions: Up, Down, Left, Right

KEY RULE: The ball does NOT stop at each cell. It keeps rolling in ONE
          direction until it hits a WALL or the BOUNDARY of the maze.

We need to find: Can the ball reach the destination?

MAZE EXAMPLE:
-------------
    +---+---+---+---+---+
    | 0 | 0 | 1 | 0 | 0 |   Row 0
    +---+---+---+---+---+
    | 0 | 0 | 0 | 0 | 0 |   Row 1
    +---+---+---+---+---+
    | 1 | 1 | 1 | 0 | 1 |   Row 2
    +---+---+---+---+---+
    | 0 | 0 | 0 | 0 | 0 |   Row 3
    +---+---+---+---+---+
    | 0 | 1 | 1 | 1 | 0 |   Row 4
    +---+---+---+---+---+
      C0  C1  C2  C3  C4

    Start = (0,0)        -- top-left
    Destination = (4,4)  -- bottom-right

HOW BALL ROLLS:
---------------
Example: Ball at (0,0), moving RIGHT

    (0,0) = 0 --> ball moves right
    (0,1) = 0 --> ball keeps rolling
    (0,2) = 1 --> WALL! Ball STOPS at (0,1)

    Ball does NOT stop at (0,0) and then move to (0,1) step by step.
    It ROLLS through (0,0) to (0,1) in ONE motion.

    +---+---+---+---+---+
    | S |->| 1 |   |   |   S = Start, -> = Rolls through
    +---+---+---+---+---+
              ^
              Ball stops HERE (before the wall)


================================================================================
                    APPROACH 1: DFS (Depth-First Search)
================================================================================

DFS IDEA:
---------
Go as DEEP as possible along one direction, then backtrack and try another.

DFS WORKS LIKE THIS:
--------------------
1. Start at position (row, col)
2. Try rolling in direction 1 (e.g., UP)
   - Roll until wall/boundary, reach new position
   - From NEW position, try rolling in ALL directions again (recursive call)
   - If destination found, return TRUE
3. If direction 1 doesn't work, try direction 2 (e.g., DOWN)
4. Continue for all 4 directions
5. If none work, return FALSE

DFS RECURSION TREE:
-------------------
                        Start (0,0)
                            |
            +-------+-------+-------+
            |       |       |       |
           UP     DOWN    LEFT    RIGHT
            |       |       |       |
         (0,0)   (1,0)   (0,0)   (0,1)
         (wall)   |      (wall)    |
                  |               +-------+-------+
                  |               |       |       |
                 ...           ...     ...     ...
                              (keep exploring deep)

DFS VISUAL WALKTHROUGH:
-----------------------
Step 1: Start at (0,0), mark visited
        Try DOWN: Roll to (1,0)
        
Step 2: At (1,0), mark visited
        Try RIGHT: Roll to (1,3)  [rolls through (1,1), (1,2)]

Step 3: At (1,3), mark visited
        Try DOWN: Roll to (3,3)  [rolls through (2,3)]

Step 4: At (3,3), mark visited
        Try RIGHT: Roll to (3,4)

Step 5: At (3,4), mark visited
        Try DOWN: Roll to (4,4) = DESTINATION! Return TRUE


================================================================================
                    APPROACH 2: BFS (Breadth-First Search)
================================================================================

BFS IDEA:
---------
Explore ALL positions reachable in 1 roll, then ALL positions reachable
in 2 rolls, then 3 rolls, and so on. Level by level.

BFS WORKS LIKE THIS:
--------------------
1. Create a QUEUE, add starting position
2. While queue is NOT empty:
   a. Remove front position from queue
   b. If this IS the destination, return TRUE
   c. Try rolling in all 4 directions
   d. For each direction:
      - Roll until wall/boundary to reach new position
      - If new position NOT visited, add to queue
3. If queue becomes empty, return FALSE

BFS QUEUE OPERATIONS:
---------------------
    Queue State          Action
    -----------          ------
    [(0,0)]              Pop (0,0), not destination
                         Roll in 4 directions -> (1,0), (0,1)
    [(1,0), (0,1)]       Pop (1,0), not destination
                         Roll in 4 directions -> (3,0), (1,3)
    [(0,1), (3,0), (1,3)]  Pop (0,1), not destination
                         Roll in 4 directions -> ...
                         ...continues until destination found

BFS LEVEL-BY-LEVEL:
-------------------
    Level 0: (0,0)                    -- starting point
    Level 1: (1,0), (0,1)            -- 1 roll away
    Level 2: (3,0), (1,3), (0,3)     -- 2 rolls away
    Level 3: (3,3), (3,4), ...       -- 3 rolls away
    Level 4: (4,4) = DESTINATION!     -- 4 rolls away

BFS GUARANTEES SHORTEST PATH (minimum number of rolls)


================================================================================
                    KEY CONCEPT: ROLLING MECHANISM
================================================================================

The ball ROLLS continuously. It does NOT stop at each cell.

Example: Ball at (1,3), moving DOWN

    Row 1: . . . [B] .    B = Ball starts here
    Row 2: 1 1 1  .  1    . = Rolling through (empty cells)
    Row 3: . . .  S  .    S = Stops here (before wall at row 4)
    Row 4: . 1 1  1  .

    Step 1: Check (2,3) = 0 (empty) -> keep rolling
    Step 2: Check (3,3) = 0 (empty) -> keep rolling
    Step 3: Check (4,3) = 1 (WALL!) -> STOP at (3,3)

    Ball stops at the LAST empty cell before hitting the wall.


================================================================================
                    DFS vs BFS COMPARISON
================================================================================

    Feature         DFS                     BFS
    -------         ---                     ---
    Data Structure  Stack (Recursion)       Queue
    Exploration     Goes DEEP first         Goes WIDE first
    Path Found      May not be shortest     Always shortest
    Memory          O(M*N) recursion        O(M*N) queue
    
    Time Complexity:  O(M * N * max(M, N))
                      M*N cells, max(M,N) max roll distance
    
    Space Complexity: O(M * N)
                      For visited array + stack/queue


================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Helper function to check if position is within maze bounds
bool isValid(int row, int col, int m, int n) {
    return row >= 0 && row < m && col >= 0 && col < n;
}


// ============================================================================
//                          DFS APPROACH
// ============================================================================
//
// RECURSIVE DFS LOGIC:
// -------------------
//   dfs(row, col)
//       |
//       +---> Is (row, col) the destination?
//       |       YES -> Return TRUE (destination reached!)
//       |       NO  -> Continue
//       |
//       +---> Mark (row, col) as visited
//       |
//       +---> For each direction (Up, Down, Left, Right):
//       |       |
//       |       +---> Roll ball until wall/boundary
//       |       |       (while loop moves newRow, newCol)
//       |       |
//       |       +---> Stopping position found at (newRow, newCol)
//       |       |
//       |       +---> If (newRow, newCol) NOT visited:
//       |               |
//       |               +---> Call dfs(newRow, newCol)
//       |               |       If returns TRUE -> return TRUE
//       |               |
//       |               +---> If returns FALSE -> try next direction
//       |
//       +---> All directions failed -> Return FALSE
//
// ============================================================================
bool dfs(int row, int col,
         vector<vector<int>>& maze,
         vector<vector<bool>>& visited,
         vector<int>& destination) {

    int m = maze.size();
    int n = maze[0].size();

    // BASE CASE: If we reached destination, return true
    if (row == destination[0] && col == destination[1]) {
        return true;
    }

    // Mark current position as visited to avoid revisiting
    visited[row][col] = true;

    // 4 possible directions: Up, Down, Left, Right
    // Each pair is (row_offset, col_offset)
    vector<pair<int, int>> directions = {
        {-1, 0}, // Up    -> row decreases
        {1, 0},  // Down  -> row increases
        {0, -1}, // Left  -> col decreases
        {0, 1}   // Right -> col increases
    };

    // Try rolling in each of the 4 directions
    for (auto it: directions) {
        int dr = it.first;   // row direction offset
        int dc = it.second;  // col direction offset
        int newRow = row;
        int newCol = col;

        // ROLLING MECHANISM:
        // Keep moving the ball in one direction until it hits:
        //   1. A wall (maze cell == 1)
        //   2. The boundary (out of maze bounds)
        //
        // The ball stops at the LAST valid empty cell.
        //
        // Example rolling RIGHT from (0,0):
        //   (0,0) -> (0,1) is empty -> keep going
        //   (0,1) -> (0,2) is WALL -> STOP at (0,1)
        //
        while (isValid(newRow + dr, newCol + dc, m, n) &&
               maze[newRow + dr][newCol + dc] == 0) {

            newRow += dr;  // move in row direction
            newCol += dc;  // move in col direction
        }
        // After loop: (newRow, newCol) = stopping position

        // Only explore if this stopping position hasn't been visited
        // This prevents infinite loops and redundant exploration
        if (!visited[newRow][newCol]) {

            // Recursively explore from the new stopping position
            // If any recursive call finds destination, propagate TRUE
            if (dfs(newRow, newCol,
                    maze, visited, destination)) {
                return true;
            }
        }
    }

    // All 4 directions explored, destination not reachable from here
    return false;
}

// Wrapper function that initializes DFS
bool canReachDestination(vector<vector<int>>& maze,
                         vector<int>& start,
                         vector<int>& destination) {

    int m = maze.size();
    int n = maze[0].size();

    // Create visited array to track explored positions
    // Initialized to all false (unvisited)
    vector<vector<bool>> visited(
        m, vector<bool>(n, false)
    );

    // Start DFS from the starting position
    return dfs(start[0], start[1],
               maze, visited, destination);
}


// ============================================================================
//                          BFS APPROACH
// ============================================================================
//
// ITERATIVE BFS LOGIC:
// -------------------
//   Create queue, push start position
//   Mark start as visited
//
//   While queue is NOT empty:
//       |
//       +---> Pop front position (row, col)
//       |
//       +---> Is (row, col) the destination?
//       |       YES -> Return TRUE
//       |       NO  -> Continue
//       |
//       +---> For each direction (Up, Down, Left, Right):
//               |
//               +---> Roll ball until wall/boundary
//               |       (while loop moves newRow, newCol)
//               |
//               +---> Stopping position found at (newRow, newCol)
//               |
//               +---> If (newRow, newCol) NOT visited:
//                       Mark as visited
//                       Push to queue
//
//   Queue empty -> Return FALSE (destination unreachable)
//
// ============================================================================
bool canReachDestination(
    vector<vector<int>>& maze,
    vector<int>& start,
    vector<int>& destination
) {
    int m = maze.size();
    int n = maze[0].size();

    // Visited array to track which positions we've explored
    vector<vector<bool>> visited(
        m, vector<bool>(n, false)
    );

    // Queue for BFS - stores positions yet to explore
    queue<pair<int, int>> q;

    // Push starting position and mark as visited
    q.push({start[0], start[1]});
    visited[start[0]][start[1]] = true;

    // 4 directions: Up, Down, Left, Right
    int directions[4][2] = {
        {-1, 0}, // Up
        {1, 0},  // Down
        {0, -1}, // Left
        {0, 1}   // Right
    };

    // Process queue until empty or destination found
    while (!q.empty()) {

        // Get the front element (FIFO - First In First Out)
        auto it = q.front();
        q.pop();
        int row = it.first;
        int col = it.second;

        // Check if we reached destination
        if (row == destination[0] &&
            col == destination[1]) {
            return true;
        }

        // Try rolling in all 4 directions from current position
        for (auto &dir : directions) {

            int dr = dir[0];
            int dc = dir[1];

            int newRow = row;
            int newCol = col;

            // ROLLING MECHANISM (same as DFS):
            // Keep moving until hitting wall or boundary
            //
            // Example: Ball at (1,3) moving DOWN
            //
            //   Row 1: . . . [B] .    B = Ball starts here
            //   Row 2: 1 1 1  .  1    . = Rolling through
            //   Row 3: . . .  S  .    S = Stops here
            //   Row 4: . 1 1  1  .
            //
            while (
                newRow + dr >= 0 &&
                newRow + dr < m &&
                newCol + dc >= 0 &&
                newCol + dc < n &&
                maze[newRow + dr][newCol + dc] == 0
            ) {
                newRow += dr;
                newCol += dc;
            }
            // (newRow, newCol) is the stopping position

            // Add to queue only if not visited before
            if (!visited[newRow][newCol]) {

                visited[newRow][newCol] = true;

                q.push({newRow, newCol});
            }
        }
    }

    // Queue empty, destination not reachable
    return false;
}


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
// Possible Path:
//   (0,0) --roll down--> (1,0)
//   (1,0) --roll right--> (1,3)  [rolls through (1,1), (1,2)]
//   (1,3) --roll down--> (3,3)   [rolls through (2,3)]
//   (3,3) --roll right--> (3,4)
//   (3,4) --roll down--> (4,4)   = DESTINATION!
//
// Output: true (path exists)
//
// ============================================================================
int main(){
    return 0;
}
