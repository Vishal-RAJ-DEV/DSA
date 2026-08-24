/*
================================================================================
PROBLEM: Longest Increasing Path in a Matrix
================================================================================

Given an m x n matrix, find the length of the longest strictly increasing
path. You can move up, down, left, or right.

Example: matrix = [[3,4,5],[3,2,6],[2,2,1]]
  Path: 3 -> 4 -> 5 -> 6 (length 4)
  Answer: 4

================================================================================
APPROACH 2: TOPOLOGICAL SORT (KAHN'S BFS) (THIS FILE)
================================================================================

IDEA:
  Model the matrix as a DAG:
    - Nodes = cells
    - Edge from cell A to cell B if A and B are adjacent AND B > A
  Then find the LONGEST PATH in this DAG using Kahn's topological sort.

  WHY IS IT A DAG?
    Edges only go from SMALLER to LARGER values. You can never have
    a cycle because values must strictly increase along any path.

  HOW TOPOLOGICAL SORT GIVES LONGEST PATH:
    Process nodes level-by-level using BFS:
      - Level 0: all nodes with indegree 0 (no incoming edges = local minimums)
      - Level 1: neighbors of level 0 nodes (after removing their edges)
      - Level 2: neighbors of level 1 nodes
      - ...continue until all nodes processed
    The number of levels = length of longest path.

INDEGREE:
  indegree[i][j] = number of adjacent cells that are SMALLER than matrix[i][j]
  If indegree[i][j] == 0, no cell can move INTO (i,j) -> it's a path START point.

  For matrix = [[9,9,4],[6,6,8],[2,1,1]]:
    ┌───┬───┬───┐        ┌───┬───┬───┐
    │ 9 │ 9 │ 4 │        │ 0 │ 0 │ 1 │  indegree: 4 has neighbor 1<4 (NO!)
    ├───┼───┼───┤  ->    ├───┼───┼───┤  9 has no smaller neighbor -> 0
    │ 6 │ 6 │ 8 │        │ 1 │ 1 │ 0 │  6 has neighbor 1<6 (NO), 2<6? NO
    ├───┼───┼───┤        ├───┼───┼───┤  8 has neighbor 6<8 -> indegree=1
    │ 1 │ 2 │ 1 │        │ 0 │ 0 │ 0 │  1 has no smaller neighbor -> 0
    └───┴───┴───┘        └───┴───┴───┘  2 has neighbor 1<2 -> NO, 1<2 -> NO

CROSS-REFERENCE:
  This problem can ALSO be solved using DFS + Memoization.
  See: D:\\Data Structure and Algrothim\\DSA\\GRAPH\\DFS and BFS on Graphs\\
       Lonest_increasing_path_in_matrix.cpp

  Both approaches are O(m*n) time and space, but work differently:
    - DFS: Recursion from each cell, memoize results (top-down)
    - Topological: Process cells level-by-level using BFS (bottom-up)

TIME:  O(m * n) - each node and edge processed once
SPACE: O(m * n) for indegree array + queue
================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class TopologicalSort {
public:
    // -----------------------------------------------------------------------
    // TOPOLOGICAL SORT (KAHN'S ALGORITHM) APPROACH
    // -----------------------------------------------------------------------
    // STEPS:
    //   1. Build indegree for each cell:
    //      For each cell (i,j), check all 4 neighbors.
    //      If neighbor > (i,j), that neighbor has an incoming edge -> indegree++
    //
    //   2. Push all cells with indegree 0 into queue (path start points)
    //
    //   3. BFS level-by-level:
    //      - Process ALL current nodes (one level)
    //      - For each processed node, check its 4 neighbors
    //      - If neighbor > current (edge exists), decrement neighbor's indegree
    //      - If indegree becomes 0, push neighbor to queue (next level)
    //      - Each level = one more step in the path
    //
    //   4. Return the number of levels (longest path length)
    //
    // WHY THIS WORKS:
    //   - Level 0: cells that are local minimums (no smaller neighbor can reach them)
    //   - Level 1: cells reachable in 1 step from level 0
    //   - Level k: cells reachable in k steps from some level 0 cell
    //   - The LAST level processed = longest path
    //
    // VISUAL for [[9,9,4],[6,6,8],[2,1,1]]:
    //
    //   Level 0 (indegree=0): (0,0)=9, (0,1)=9, (2,0)=1, (2,1)=2, (2,2)=1
    //     After processing, remove edges from these nodes.
    //
    //   Level 1: (0,2)=4 (its edge from 1 was removed), (1,0)=6, (1,1)=6
    //     After processing, remove edges from these nodes.
    //
    //   Level 2: (1,2)=8 (its edge from 6 was removed)
    //     After processing, remove edges from this node.
    //
    //   Level 3: nothing new (8 has no outgoing edges to unprocessed nodes)
    //
    //   Answer = 4 (levels 0,1,2,3 -> but we count length as number of levels
    //            = 4 because level 0 = 1 node, each level adds 1 to path length)
    // -----------------------------------------------------------------------
    int longestIncreasingPath(vector<vector<int>>& matrix) {

        int m = matrix.size();
        int n = matrix[0].size();

        // -------------------------------------------------------------------
        // STEP 1: COMPUTE INDEGREE FOR EACH CELL
        // -------------------------------------------------------------------
        // indegree[i][j] = number of adjacent cells SMALLER than matrix[i][j]
        //
        // If indegree[i][j] == 0, no cell can move INTO (i,j).
        // This means (i,j) is a local minimum -> path starts here.
        // -------------------------------------------------------------------
        vector<vector<int>> indegree(
            m,
            vector<int>(n, 0)
        );

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                for (int k = 0; k < 4; k++) {

                    int ni = i + dr[k];
                    int nj = j + dc[k];

                    // If neighbor is LARGER, it has an incoming edge from (i,j)
                    if (ni >= 0 && ni < m &&
                        nj >= 0 && nj < n &&
                        matrix[ni][nj] > matrix[i][j]) {

                        indegree[ni][nj]++;
                    }
                }
            }
        }

        // -------------------------------------------------------------------
        // STEP 2: PUSH ALL INDEGREE-0 NODES INTO QUEUE
        // -------------------------------------------------------------------
        // These are cells where NO smaller neighbor can reach them.
        // They are the START of every increasing path.
        // -------------------------------------------------------------------
        queue<pair<int, int>> q;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (indegree[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }

        // -------------------------------------------------------------------
        // STEP 3: BFS LEVEL-BY-LEVEL (KAHN'S ALGORITHM)
        // -------------------------------------------------------------------
        // Each "level" of BFS = one more step in the longest path.
        //
        // Process all nodes at current level:
        //   - Pop node (row, col)
        //   - For each neighbor that is LARGER (outgoing edge):
        //     - Decrement its indegree (remove this edge)
        //     - If indegree becomes 0, push to queue (next level)
        //
        // WHY length++ INSIDE the outer while?
        //   Each iteration of the outer while processes ONE entire level.
        //   Level count = longest path length.
        //
        // VISUAL for [[9,9,4],[6,6,8],[2,1,1]]:
        //
        //   Initial queue: (0,0)=9, (0,1)=9, (2,0)=1, (2,1)=2, (2,2)=1
        //   length = 0
        //
        //   OUTER LOOP iteration 1 (length becomes 1):
        //     Process: (0,0)=9 -> neighbors > 9: NONE
        //     Process: (0,1)=9 -> neighbors > 9: NONE
        //     Process: (2,0)=1 -> neighbors > 1: (1,0)=6 indegree 2->1
        //                                 (2,1)=2 indegree 0 (already in queue)
        //     Process: (2,1)=2 -> neighbors > 2: (1,1)=6 indegree 2->1
        //                                 (2,0)=1 NOT > 2, (2,2)=1 NOT > 2
        //     Process: (2,2)=1 -> neighbors > 1: (1,2)=8 indegree 1->0 -> PUSH
        //                                 (2,1)=2 indegree 0 (already in queue)
        //     Queue now: (0,2)=4, (1,0)=6, (1,1)=6
        //
        //   OUTER LOOP iteration 2 (length becomes 2):
        //     Process: (0,2)=4 -> neighbors > 4: (1,2)=8 indegree 0 (already queued)
        //     Process: (1,0)=6 -> neighbors > 6: (0,0)=9 indegree 0 (done)
        //                                 (0,1)=9 indegree 0 (done)
        //     Process: (1,1)=6 -> neighbors > 6: (0,0)=9, (0,1)=9 (done)
        //     Queue now: (1,2)=8
        //
        //   OUTER LOOP iteration 3 (length becomes 3):
        //     Process: (1,2)=8 -> neighbors > 8: NONE
        //     Queue now: empty
        //
        //   Wait - we need to reconsider. Let me retrace carefully...
        //
        //   Actually, the issue is that 9s have indegree 0 but 4->8
        //   creates an edge. Let me redo:
        //
        //   Correct indegree:
        //     (0,0)=9: neighbors >9? NO -> indegree=0
        //     (0,1)=9: neighbors >9? NO -> indegree=0
        //     (0,2)=4: neighbors >4? (0,1)=9>4 YES, (1,2)=8>4 YES -> indegree=2
        //     (1,0)=6: neighbors >6? (0,0)=9>6 YES -> indegree=1
        //     (1,1)=6: neighbors >6? (0,1)=9>6 YES -> indegree=1
        //     (1,2)=8: neighbors >8? NO -> indegree=0
        //     (2,0)=1: neighbors >1? (1,0)=6>1 YES, (2,1)=2>1 YES -> indegree=2
        //     (2,1)=2: neighbors >2? (1,1)=6>2 YES -> indegree=1
        //     (2,2)=1: neighbors >1? (1,2)=8>1 YES, (2,1)=2>1 YES -> indegree=2
        //
        //   Initial queue (indegree=0): (0,0)=9, (0,1)=9, (1,2)=8
        //   length=0
        //
        //   Level 0 (length=1): process (0,0),(0,1),(1,2)
        //     (0,0)=9: no outgoing edges (nothing > 9)
        //     (0,1)=9: no outgoing edges
        //     (1,2)=8: no outgoing edges (nothing > 8)
        //     No new nodes pushed. Queue empty.
        //
        //   Answer = 1? That can't be right...
        //
        //   AH - the issue is my indegree calculation is for INCOMING edges
        //   to each node. But in the loop, we check if matrix[ni][nj] > matrix[i][j]
        //   which means (i,j) -> (ni,nj) is an edge, so indegree of (ni,nj)++.
        //   This is CORRECT.
        //
        //   Let me recheck: for (2,0)=1, we look at neighbors:
        //     (1,0)=6 > 1 -> edge (2,0)->(1,0), so indegree(1,0)++
        //     (2,1)=2 > 1 -> edge (2,0)->(2,1), so indegree(2,1)++
        //   This means indegree counts INCOMING edges correctly.
        //
        //   The answer of 1 means only the 9s and 8 are processed at level 0.
        //   But 9 can be reached from 6, and 6 from 1. So the longest path
        //   should be 1->2->6->9 = 4.
        //
        //   The problem: 9 has indegree 0, meaning nothing points TO it.
        //   But 6->9 IS an edge (6<9). So indegree(9) should be at least 1.
        //
        //   OH - I see the issue. In the indegree calculation loop:
        //   We check if matrix[ni][nj] > matrix[i][j], and if so, indegree[ni][nj]++.
        //   For (i,j)=(1,0)=6, neighbor (0,0)=9 > 6, so indegree[0][0]++.
        //   So indegree(0,0) should NOT be 0.
        //
        //   Let me recalculate properly:
        //     (0,0)=9: check neighbors (1,0)=6 NOT > 9, (-1,0) OOB, (0,-1) OOB, (0,1)=9 NOT > 9
        //       indegree = 0
        //     Wait - we need to check ALL 4 neighbors from EACH cell's perspective.
        //
        //   Actually, the loop goes through EACH cell (i,j) and for each neighbor (ni,nj):
        //     if matrix[ni][nj] > matrix[i][j], then there's an edge (i,j)->(ni,nj)
        //     so indegree[ni][nj]++.
        //
        //   For (1,0)=6: neighbors (0,0)=9>6 YES -> indegree[0][0]++
        //                 (2,0)=1 NOT >6, (1,-1) OOB, (1,1)=6 NOT >6
        //   So indegree[0][0] gets +1 from this.
        //
        //   For (1,1)=6: neighbors (0,1)=9>6 YES -> indegree[0][1]++
        //   So indegree[0][1] gets +1.
        //
        //   CORRECT indegree:
        //     (0,0)=9: from (1,0)=6 -> indegree=1
        //     (0,1)=9: from (1,1)=6 -> indegree=1
        //     (0,2)=4: nothing > 4 points to it? (0,1)=9>4 but 9 is at (0,1)
        //       Actually: from (0,1)=9, neighbor (0,2)=4 NOT > 9. So no edge.
        //       From (1,2)=8, neighbor (0,2)=4 NOT > 8. So no edge.
        //       indegree(0,2) = 0
        //     (1,0)=6: from (2,0)=1 NOT >6. No edge. indegree=0
        //     (1,1)=6: from (2,1)=2 NOT >6. No edge. indegree=0
        //     (1,2)=8: from (0,2)=4 NOT >8. No edge. From (2,2)=1 NOT >8.
        //       indegree=0
        //     (2,0)=1: from (1,0)=6>1 YES. indegree=1
        //     (2,1)=2: from (1,1)=6>2 YES. indegree=1. From (2,0)=1 NOT>2. From (2,2)=1 NOT>2.
        //     (2,2)=1: from (1,2)=8>1 YES. indegree=1. From (2,1)=2>1 YES. indegree=2.
        //
        //   So: (0,2)=0, (1,0)=0, (1,1)=0, (1,2)=0 have indegree 0.
        //   These are the START nodes.
        //
        //   Level 0 (length=1): process (0,2)=4, (1,0)=6, (1,1)=6, (1,2)=8
        //     (0,2)=4: neighbors >4 -> (0,1)=9 indegree 1->0 PUSH, (1,2)=8 indegree 0 (already in queue)
        //     (1,0)=6: neighbors >6 -> (0,0)=9 indegree 1->0 PUSH
        //     (1,1)=6: neighbors >6 -> (0,1)=9 indegree 0 (already pushed)
        //     (1,2)=8: no neighbors >8
        //     Queue: (0,1)=9, (0,0)=9
        //
        //   Level 1 (length=2): process (0,1)=9, (0,0)=9
        //     (0,1)=9: no neighbors >9
        //     (0,0)=9: no neighbors >9
        //     Queue empty
        //
        //   Hmm, answer = 2? Still wrong. The issue is that 1->2->6->9 = 4.
        //
        //   AH I SEE - the edges should go from SMALLER to LARGER.
        //   So edge (2,0)=1 -> (1,0)=6 -> (0,0)=9 means indegree(1,0) should have
        //   an incoming edge from (2,0). Let me check: from (2,0)=1, neighbor (1,0)=6>1
        //   -> indegree[1][0]++. YES! So indegree(1,0) should be 1, not 0.
        //
        //   I was wrong earlier. Let me redo properly:
        //
        //   For each cell (i,j), check 4 neighbors (ni,nj):
        //     if matrix[ni][nj] > matrix[i][j], then edge (i,j)->(ni,nj), indegree[ni][nj]++
        //
        //   (0,0)=9: neighbors: (1,0)=6 NOT>9, (-1,0)OOB, (0,-1)OOB, (0,1)=9 NOT>9
        //     indegree(0,0) = 0
        //   (0,1)=9: neighbors: (1,1)=6 NOT>9, (-1,1)OOB, (0,0)=9 NOT>9, (0,2)=4 NOT>9
        //     indegree(0,1) = 0
        //   (0,2)=4: neighbors: (1,2)=8>4 YES -> indegree(1,2)++
        //             (-1,2)OOB, (0,1)=9>4 YES -> indegree(0,1)++
        //     indegree(0,2) = 0 (nothing points to it)
        //   (1,0)=6: neighbors: (0,0)=9>6 YES -> indegree(0,0)++
        //             (2,0)=1 NOT>6, (1,-1)OOB, (1,1)=6 NOT>6
        //     indegree(1,0) = 0 (nothing points to it from our check)
        //   WAIT - from (2,0)=1, neighbor (1,0)=6>1 -> indegree[1][0]++
        //   So indegree(1,0) = 1 from (2,0).
        //
        //   Let me be very careful. For EVERY cell (i,j), we check 4 neighbors:
        //
        //   Cell (0,0)=9: check (1,0)=6, (0,1)=9, (-1,0), (0,-1)
        //     6>9? NO, 9>9? NO -> no edges FROM (0,0)
        //   Cell (0,1)=9: check (1,1)=6, (0,2)=4, (-1,1), (0,0)=9
        //     6>9? NO, 4>9? NO, 9>9? NO -> no edges FROM (0,1)
        //   Cell (0,2)=4: check (1,2)=8, (0,1)=9, (-1,2), (0,3)
        //     8>4? YES -> indegree[1][2]++
        //     9>4? YES -> indegree[0][1]++
        //   Cell (1,0)=6: check (0,0)=9, (2,0)=1, (1,1)=6, (1,-1)
        //     9>6? YES -> indegree[0][0]++
        //     1>6? NO, 6>6? NO
        //   Cell (1,1)=6: check (0,1)=9, (2,1)=2, (1,2)=8, (1,0)=6
        //     9>6? YES -> indegree[0][1]++
        //     2>6? NO, 8>6? YES -> indegree[1][2]++
        //     6>6? NO
        //   Cell (1,2)=8: check (0,2)=4, (2,2)=1, (1,3), (1,1)=6
        //     4>8? NO, 1>8? NO, 6>8? NO -> no edges FROM (1,2)
        //   Cell (2,0)=1: check (1,0)=6, (2,1)=2, (3,0), (2,-1)
        //     6>1? YES -> indegree[1][0]++
        //     2>1? YES -> indegree[2][1]++
        //   Cell (2,1)=2: check (1,1)=6, (2,2)=1, (2,0)=1, (2,2)=1
        //     6>2? YES -> indegree[1][1]++
        //     1>2? NO, 1>2? NO
        //   Cell (2,2)=1: check (1,2)=8, (2,1)=2, (3,2), (2,3)
        //     8>1? YES -> indegree[1][2]++
        //     2>1? YES -> indegree[2][1]++
        //
        //   FINAL INDEGREE:
        //     (0,0): from (1,0) -> 1
        //     (0,1): from (0,2), (1,1) -> 2
        //     (0,2): 0
        //     (1,0): from (2,0) -> 1
        //     (1,1): from (2,1) -> 1
        //     (1,2): from (0,2), (1,1), (2,2) -> 3
        //     (2,0): 0
        //     (2,1): from (2,0), (2,2) -> 2
        //     (2,2): 0
        //
        //   INITIAL QUEUE (indegree=0): (0,2)=4, (2,0)=1, (2,2)=1
        //
        //   Level 0 (length=1): process (0,2),(2,0),(2,2)
        //     (0,2)=4: edges to (1,2)=8 indegree 3->2, (0,1)=9 indegree 2->1
        //     (2,0)=1: edges to (1,0)=6 indegree 1->0 PUSH, (2,1)=2 indegree 2->1
        //     (2,2)=1: edges to (1,2)=8 indegree 2->1, (2,1)=2 indegree 1->0 PUSH
        //     Queue: (1,0)=6, (2,1)=2
        //
        //   Level 1 (length=2): process (1,0),(2,1)
        //     (1,0)=6: edges to (0,0)=9 indegree 1->0 PUSH
        //     (2,1)=2: edges to (1,1)=6 indegree 1->0 PUSH
        //     Queue: (0,0)=9, (1,1)=6
        //
        //   Level 2 (length=3): process (0,0),(1,1)
        //     (0,0)=9: no outgoing edges (nothing >9)
        //     (1,1)=6: edges to (0,1)=9 indegree 1->0 PUSH, (1,2)=8 indegree 1->0 PUSH
        //     Queue: (0,1)=9, (1,2)=8
        //
        //   Level 3 (length=4): process (0,1),(1,2)
        //     (0,1)=9: no outgoing edges
        //     (1,2)=8: no outgoing edges
        //     Queue empty
        //
        //   ANSWER = 4 ✓ (path: 1->2->6->9)
        // -------------------------------------------------------------------
        int length = 0;

        while (!q.empty()) {

            int size = q.size();

            length++;  // this level adds 1 to path length

            // Process all nodes at current level
            while (size--) {

                auto it = q.front();
                int row = it.first;
                int col = it.second;

                q.pop();

                // For each neighbor that is LARGER (outgoing edge exists)
                for (int k = 0; k < 4; k++) {

                    int nr = row + dr[k];
                    int nc = col + dc[k];

                    if (nr >= 0 && nr < m &&
                        nc >= 0 && nc < n &&
                        matrix[nr][nc] > matrix[row][col]) {

                        // Remove this edge
                        indegree[nr][nc]--;

                        // If no more incoming edges, push to next level
                        if (indegree[nr][nc] == 0) {
                            q.push({nr, nc});
                        }
                    }
                }
            }
        }

        // -------------------------------------------------------------------
        // STEP 4: RETURN RESULT
        // -------------------------------------------------------------------
        // 'length' = number of BFS levels = longest increasing path
        // -------------------------------------------------------------------
        return length;
    }
};


int main(){
    return 0;
}