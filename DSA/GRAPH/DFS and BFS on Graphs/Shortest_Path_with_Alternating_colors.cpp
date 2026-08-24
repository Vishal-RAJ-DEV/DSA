/*
================================================================================
            SHORTEST PATH WITH ALTERNATING COLORS - EXPLANATION
================================================================================

PROBLEM:
--------
Given a directed graph with n nodes (0 to n-1).
Edges are colored RED or BLUE.
Find shortest path from node 0 to every other node such that:
  - Colors of edges in path ALTERNATE (red -> blue -> red -> blue...)

If no path exists to a node, return -1 for that node.

EXAMPLE:
--------
  Nodes: 0, 1, 2, 3
  
  Red Edges:   0 -> 1, 1 -> 2
  Blue Edges:  0 -> 2, 1 -> 3
  
  Graph Visualization:
  
       RED        RED
    0 -----> 1 -------> 2
    |        |
    | BLUE   | BLUE
    v        v
    2        3
  
  Shortest alternating paths from node 0:
    Node 0: distance 0 (starting point)
    Node 1: 0 ->(RED) 1           = distance 1
    Node 2: 0 ->(BLUE) 2          = distance 1
    Node 3: 0 ->(RED) 1 ->(BLUE) 3 = distance 2
            (alternating: RED then BLUE)
  
  Output: [0, 1, 1, 2]


================================================================================
                    INTUITION / KEY INSIGHT
================================================================================

WHY IS THIS PROBLEM TRICKY?
----------------------------
Normal shortest path: Just track which NODE we're at
This problem: Must track which NODE + what COLOR we last used

Because the NEXT edge color depends on the PREVIOUS edge color:
  - If we arrived via RED edge  -> next must be BLUE
  - If we arrived via BLUE edge -> next must be RED

SOLUTION: Track state as (node, lastColor)
  - node: which node we're at
  - lastColor: what color edge we used to get here (0=RED, 1=BLUE)

This is why we need visited[node][color] (2D visited array)


================================================================================
                    WHY TWO SEPARATE GRAPHS?
================================================================================

We build TWO adjacency lists:
  red[node]  = list of nodes reachable from 'node' via RED edges
  blue[node] = list of nodes reachable from 'node' via BLUE edges

Example:
  Red Edges:   0 -> 1, 1 -> 2
  Blue Edges:  0 -> 2, 1 -> 3

  red[0]  = {1}      (from 0, can go to 1 via RED)
  red[1]  = {2}      (from 1, can go to 2 via RED)
  red[2]  = {}       (no RED edges from 2)
  
  blue[0] = {2}      (from 0, can go to 2 via BLUE)
  blue[1] = {3}      (from 1, can go to 3 via BLUE)
  blue[2] = {}       (no BLUE edges from 2)

This separation makes it easy to pick the RIGHT color based on alternation


================================================================================
                    HOW STEPS ARE CALCULATED
================================================================================

BFS LEVEL-BY-LEVEL TRAVERSAL:
-----------------------------
  Each BFS level = one more edge traversal = one more step
  
  Level 0: Start at node 0 (steps = 0)
  Level 1: All nodes reachable in 1 edge (steps = 1)
  Level 2: All nodes reachable in 2 edges (steps = 2)
  ...

STEP COUNTER LOGIC:
-------------------
  int steps = 0;
  
  while (!q.empty()) {
      int size = q.size();   // Number of nodes at current level
      
      while (size--) {       // Process ALL nodes at this level
          // ... explore neighbors ...
      }
      
      steps++;               // Move to next level
  }

  When we FIRST reach a node, that's its shortest distance.
  We only set ans[node] once (when ans[node] == -1).


================================================================================
                    WHY WE START WITH BOTH COLORS
================================================================================

At node 0, we haven't used ANY edge yet.
So the FIRST edge can be EITHER red or blue.

We push TWO starting states:
  q.push({0, 0});  // "Starting at 0, pretend last edge was RED"
  q.push({0, 1});  // "Starting at 0, pretend last edge was BLUE"

Why pretend? Because from node 0:
  - If we "pretend" last was RED, we must use BLUE next
  - If we "pretend" last was BLUE, we must use RED next

This covers both possibilities for the first edge.


================================================================================
                    VISITED ARRAY: visited[node][color]
================================================================================

Standard BFS: visited[node] = true/false
This problem: visited[node][color] = true/false

Why 2D?
-------
  We can visit the SAME node with DIFFERENT last colors.
  
  Example: Node 2 can be reached via:
    - RED edge  (visited[2][0] = true)
    - BLUE edge (visited[2][1] = true)
  
  These are DIFFERENT states because they lead to different next moves:
    - Arrived via RED  -> must use BLUE next
    - Arrived via BLUE -> must use RED next

  So we need to track BOTH states separately.


================================================================================
                    ALTERNATION LOGIC VISUALIZATION
================================================================================

STATE TRANSITIONS:
------------------
  
  Current State: (node, lastColor)
  
  If lastColor == 0 (RED):
      ┌─────────────────────────────────────┐
      │  Next edge must be BLUE             │
      │  Explore: blue[node] (all BLUE      │
      │           neighbors)                │
      │  New state: (next, 1)               │
      └─────────────────────────────────────┘
  
  If lastColor == 1 (BLUE):
      ┌─────────────────────────────────────┐
      │  Next edge must be RED              │
      │  Explore: red[node] (all RED        │
      │           neighbors)                │
      │  New state: (next, 0)               │
      └─────────────────────────────────────┘

VISUAL EXAMPLE:
---------------
  Path: 0 --RED--> 1 --BLUE--> 2 --RED--> 3
  
  State transitions:
    (0, ?) --[start]--> (0, RED) or (0, BLUE)
    
    If we start with (0, BLUE):
      (0, BLUE) --[use RED]--> (1, RED)
      (1, RED)  --[use BLUE]--> (2, BLUE)
      (2, BLUE) --[use RED]--> (3, RED)
  
  Colors alternate: BLUE(start) -> RED -> BLUE -> RED


================================================================================
                    BFS PROCESSING DIAGRAM
================================================================================

  Initial Queue:
    Q = [(0, 0), (0, 1)]
         node  node
         color color
         (RED) (BLUE)
  
  Level 0 (steps = 0):
    Process (0, 0): lastColor = RED
      Must use BLUE next
      blue[0] = {2}
      Push (2, 1)
    
    Process (0, 1): lastColor = BLUE
      Must use RED next
      red[0] = {1}
      Push (1, 0)
    
    Q = [(2, 1), (1, 0)]
    steps++ -> steps = 1
  
  Level 1 (steps = 1):
    Process (2, 1): lastColor = BLUE
      Must use RED next
      red[2] = {} (empty)
      No neighbors
    
    Process (1, 0): lastColor = RED
      Must use BLUE next
      blue[1] = {3}
      Push (3, 1)
    
    Q = [(3, 1)]
    steps++ -> steps = 2
  
  Level 2 (steps = 2):
    Process (3, 1): lastColor = BLUE
      Must use RED next
      red[3] = {} (empty)
      No neighbors
    
    Q = []
    steps++ -> steps = 3
  
  Queue empty, BFS complete


================================================================================
                    ANSWER ARRAY UPDATE LOGIC
================================================================================

  ans[node] = shortest distance from node 0 to node
  Initial: ans = [-1, -1, -1, ...] (all unreachable)
  ans[0] = 0 (starting point)

  When do we update?
  ------------------
    if (ans[node] == -1) {
        ans[node] = steps;
    }
  
  This means:
    - Only update if node NOT YET REACHED
    - First time reaching = shortest distance (BFS guarantee)
    - Never update again (keep the minimum)

  Example:
  --------
    Node 3 first reached at steps = 2
      -> ans[3] = 2 (updated)
    
    Node 3 reached again at steps = 4 (longer path)
      -> ans[3] == -1? NO (already set to 2)
      -> Do NOT update (keep 2)


================================================================================
                    COMPLETE WORKED EXAMPLE
================================================================================

  Graph:
    Nodes: 0, 1, 2, 3, 4
    
    Red Edges:   0 -> 1, 0 -> 2, 2 -> 3, 3 -> 4
    Blue Edges:  1 -> 2, 2 -> 4, 1 -> 3
  
  Adjacency Lists:
    red[0]  = {1, 2}      blue[0]  = {}
    red[1]  = {}           blue[1]  = {2, 3}
    red[2]  = {3}          blue[2]  = {4}
    red[3]  = {4}          blue[3]  = {}
    red[4]  = {}           blue[4]  = {}
  
  BFS Execution:
  ==============
  
  Start: Q = [(0, RED), (0, BLUE)]
         ans = [0, -1, -1, -1, -1]
  
  Level 0 (steps=0):
    (0, RED): lastColor=RED -> use BLUE -> blue[0]={} -> nothing
    (0, BLUE): lastColor=BLUE -> use RED -> red[0]={1,2}
      Push (1, RED), (2, RED)
    
    Q = [(1, RED), (2, RED)]
    steps = 1
  
  Level 1 (steps=1):
    (1, RED): lastColor=RED -> use BLUE -> blue[1]={2,3}
      Push (2, BLUE), (3, BLUE)
    (2, RED): lastColor=RED -> use BLUE -> blue[2]={4}
      Push (4, BLUE)
    
    Q = [(2, BLUE), (3, BLUE), (4, BLUE)]
    ans = [0, 1, 1, -1, -1]  (node 1 and 2 reached)
    steps = 2
  
  Level 2 (steps=2):
    (2, BLUE): lastColor=BLUE -> use RED -> red[2]={3}
      Push (3, RED)
    (3, BLUE): lastColor=BLUE -> use RED -> red[3]={4}
      Push (4, RED)
    (4, BLUE): lastColor=BLUE -> use RED -> red[4]={} -> nothing
    
    Q = [(3, RED), (4, RED)]
    ans = [0, 1, 1, 2, 2]  (node 3 and 4 reached)
    steps = 3
  
  Level 3 (steps=3):
    (3, RED): lastColor=RED -> use BLUE -> blue[3]={} -> nothing
    (4, RED): lastColor=RED -> use BLUE -> blue[4]={} -> nothing
    
    Q = []
    steps = 4
  
  Final Answer: [0, 1, 1, 2, 2]


================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestAlternatingPaths(
        int n,
        vector<vector<int>>& redEdges,
        vector<vector<int>>& blueEdges
    ) {
        
        // Color constants for clarity
        // 0 = RED, 1 = BLUE
        // Used in visited[node][color] and queue state (node, lastColor)
        
        // BUILD TWO SEPARATE ADJACENCY LISTS
        // ------------------------------------
        // red[node]  = list of neighbors reachable via RED edges
        // blue[node] = list of neighbors reachable via BLUE edges
        //
        // Why separate? Because alternation depends on LAST color used.
        // If last was RED, we MUST use BLUE neighbors (blue[node])
        // If last was BLUE, we MUST use RED neighbors (red[node])
        //
        vector<vector<int>> red(n);
        vector<vector<int>> blue(n);
        
        // Build red graph
        for (auto &edge : redEdges) {
            red[edge[0]].push_back(edge[1]);
        }
        
        // Build blue graph
        for (auto &edge : blueEdges) {
            blue[edge[0]].push_back(edge[1]);
        }
        
        // ANSWER ARRAY
        // ------------
        // ans[node] = shortest alternating path distance from node 0
        // Initialize to -1 (unreachable)
        // ans[0] = 0 (starting point, distance 0)
        vector<int> ans(n, -1);
        ans[0] = 0;
        
        // VISITED ARRAY: visited[node][color]
        // ------------------------------------
        // visited[node][0] = visited via RED edge
        // visited[node][1] = visited via BLUE edge
        //
        // Why 2D? Same node can be visited with DIFFERENT last colors.
        // Each (node, color) pair is a UNIQUE state.
        //
        // Example: Node 2 reached via RED  -> state (2, RED)
        //          Node 2 reached via BLUE -> state (2, BLUE)
        //          These are DIFFERENT states!
        //
        vector<vector<bool>> visited(n, vector<bool>(2, false));
        
        // BFS QUEUE: stores {node, lastColor}
        // ------------------------------------
        // Each element represents a STATE: (which node, what color last edge was)
        // lastColor tells us which color to use NEXT (opposite)
        //
        queue<pair<int, int>> q;
        
        // START WITH BOTH COLOR Possibilities
        // ------------------------------------
        // At node 0, no edge has been used yet.
        // First edge can be EITHER red or blue.
        //
        // We "pretend" last edge was RED  -> next must be BLUE
        // We "pretend" last edge was BLUE -> next must be RED
        //
        // This covers both possibilities for the first edge.
        //
        q.push({0, 0}); // State: at node 0, pretend last was RED (color=0)
        q.push({0, 1}); // State: at node 0, pretend last was BLUE (color=1)
        
        visited[0][0] = true;  // Mark state (0, RED) as visited
        visited[0][1] = true;  // Mark state (0, BLUE) as visited
        
        // STEP COUNTER
        // ------------
        // Each BFS level = one more edge traversal = one more step
        // When we first reach a node, steps = shortest distance
        //
        int steps = 0;
        
        // BFS MAIN LOOP
        // ==============
        // Process level by level (all nodes at current distance)
        //
        while (!q.empty()) {
            
            // Get number of nodes at current level
            // Process ALL of them before incrementing steps
            //
            int size = q.size();
            
            // Process all nodes at this level
            while (size--) {
                
                // Get current state from queue front
                auto it = q.front();
                q.pop();
                int node = it.first;       // Current node
                int lastColor = it.second; // Color of edge used to reach here
                
                // UPDATE ANSWER (first time reaching this node = shortest)
                // -------------------------------------------------------
                // If ans[node] == -1, this is the FIRST time reaching 'node'
                // BFS guarantees this is the SHORTEST distance
                // Set ans[node] = steps and never update again
                //
                if (ans[node] == -1) {
                    ans[node] = steps;
                }
                
                // ALTERNATION LOGIC
                // =================
                // If last edge was RED (lastColor == 0):
                //     Next edge MUST be BLUE
                //     Explore: blue[node] (all BLUE neighbors)
                //
                // If last edge was BLUE (lastColor == 1):
                //     Next edge MUST be RED
                //     Explore: red[node] (all RED neighbors)
                //
                
                // Case 1: Last edge was RED -> use BLUE next
                if (lastColor == 0) {
                    
                    // Try all BLUE neighbors of current node
                    for (int next : blue[node]) {
                        
                        // Only visit if this (node, BLUE) state not visited
                        if (!visited[next][1]) {
                            visited[next][1] = true;
                            q.push({next, 1});  // State: at 'next', lastColor=BLUE
                        }
                    }
                }
                
                // Case 2: Last edge was BLUE -> use RED next
                else {
                    
                    // Try all RED neighbors of current node
                    for (int next : red[node]) {
                        
                        // Only visit if this (node, RED) state not visited
                        if (!visited[next][0]) {
                            visited[next][0] = true;
                            q.push({next, 0});  // State: at 'next', lastColor=RED
                        }
                    }
                }
            }
            
            // Move to next level (one more edge traversal)
            steps++;
        }
        
        // Return shortest alternating distances to all nodes
        // -1 means unreachable with alternating colors
        return ans;
    }
};


// ============================================================================
//                           MAIN FUNCTION
// ============================================================================
//
// TEST CASE:
// ----------
//   n = 5 nodes (0, 1, 2, 3, 4)
//   
//   Red Edges:   0->1, 0->2, 2->3, 3->4
//   Blue Edges:  1->2, 2->4, 1->3
//   
//   Expected Output: [0, 1, 1, 2, 2]
//   
//   Explanation:
//     Node 0: distance 0 (start)
//     Node 1: 0 --RED--> 1 (distance 1)
//     Node 2: 0 --RED--> 2 (distance 1)
//     Node 3: 0 --RED--> 1 --BLUE--> 3 (distance 2)
//     Node 4: 0 --RED--> 2 --BLUE--> 4 (distance 2)
//
// ============================================================================
int main(){
    return 0;
}
