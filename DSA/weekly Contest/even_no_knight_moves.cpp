/*
QUESTION: Can the knight reach the target in an EVEN number of moves?

A knight on an infinite chessboard moves in L-shapes: (±2, ±1) or (±1, ±2).
Given a start and target coordinate, determine if the knight can reach the
target in an EVEN number of moves.

Key observation:
  A knight ALWAYS moves from a black square to a white square (or vice versa)
  because every move covers an odd total distance (2+1=3). On a chessboard,
  the color is determined by the parity of (x + y):
    (x + y) % 2 == 0 →  black
    (x + y) % 2 == 1 →  white

  Since the color flips EVERY move:
    - After an ODD  number of moves → opposite color
    - After an EVEN number of moves → same color

  Therefore, reaching the target in even moves is POSSIBLE iff
  start and target have the SAME (x+y) parity.

Example:
  start = (0,0) → 0+0=0 (even/black)
  target = (1,2) → 1+2=3 (odd/white)
  Different parity → reachable only in odd moves, NOT in even moves
  Output: false

  start = (0,0) → 0+0=0 (even)
  target = (2,1) → 2+1=3 (odd)   → same as above
  target = (3,3) → 3+3=6 (even)  → same parity → reachable in even moves

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// ╔══════════════════════════════════════════════════════════════╗
// ║  APPROACH 1: Parity Check (Mathematical — O(1))            ║
// ╚══════════════════════════════════════════════════════════════╝
//
// INTUITION:
//   A knight always moves to a square of the opposite color on the
//   chessboard (defined by (x+y)%2). Every knight move changes the
//   parity of (x+y) because it adds (±2±1) which is always an odd
//   number (2+1=3, 2-1=1, -2+1=-1, -2-1=-3 — all odd).
//
//   After an even number of parity flips, we return to the original
//   parity. So:
//     same parity  → reachable in an EVEN  number of moves
//     diff parity  → reachable only in an ODD number of moves
//
//   On an infinite board, every square of the correct parity IS
//   reachable (the knight's graph is connected and bipartite).
//
// ALGORITHM:
//   return (start[0] + start[1]) % 2 == (target[0] + target[1]) % 2
//
// TIME  : O(1)
// SPACE : O(1)

class Solution {
public:
    bool canReach(vector<int>& start, vector<int>& target) {
        // Same (x+y) parity ↔ reachable in even number of moves
        return ((start[0] + start[1]) % 2) == ((target[0] + target[1]) % 2);
    }
};

/*
DRY RUN:

  start=(0,0), target=(2,1)
    0+0=0 (even), 2+1=3 (odd)  → diff → false

  start=(0,0), target=(3,3)
    0+0=0 (even), 3+3=6 (even) → same → true

  start=(1,0), target=(0,2)
    1+0=1 (odd),  0+2=2 (even) → diff → false

  start=(1,1), target=(2,2)
    1+1=2 (even), 2+2=4 (even) → same → true
*/


// ╔══════════════════════════════════════════════════════════════╗
// ║  APPROACH 2: BFS (Breadth-First Search)                    ║
// ╚══════════════════════════════════════════════════════════════╝
//
// INTUITION:
//   Simulate the knight's moves level by level.
//   Track visited positions and distance (moves taken).
//   If we reach target with an even distance → return true.
//
//   This is O(N²) and only practical for small coordinate ranges
//   or limited move counts. It serves as a verification for the
//   parity approach on small search spaces.
//
// ALGORITHM:
//   1. If start == target → return true (0 moves, which is even).
//   2. Queue = {start}, visited[start] = true, distance = 0.
//   3. While queue is not empty (limit depth to avoid infinite loop):
//        Process current level:
//          For each of the 8 knight moves:
//            If new position == target and distance is odd → return true
//            (because distance counts moves taken so far; when we reach
//             target, total moves = distance + 1)
//            If not visited → mark visited, push to next level.
//        Increment distance.
//   4. Return false.
//
// Knight move offsets:
//   {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}
//
// TIME  : O(8^d) where d = number of moves to target (exponential)
// SPACE : O(8^d)

class Solution2 {
public:
    bool canReach(vector<int>& start, vector<int>& target) {

        if (start == target)
            return true;            // 0 moves (even)

        // All 8 possible knight moves
        vector<pair<int,int>> dirs = {
            {2,1}, {1,2}, {-1,2}, {-2,1},
            {-2,-1}, {-1,-2}, {1,-2}, {2,-1}
        };

        // BFS
        queue<pair<int,int>> q;
        set<pair<int,int>> vis;

        q.push({start[0], start[1]});
        vis.insert({start[0], start[1]});

        int moves = 0;

        while (!q.empty() && moves < 10) {   // limit depth
            int size = q.size();
            moves++;

            while (size--) {
                auto it = q.front();
                int x = it.first;
                int y = it.second;
                q.pop();

                for (auto &dir : dirs) {
                    int dx = dir.first;
                    int dy = dir.second;
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx == target[0] && ny == target[1]) {
                        // Reached target in `moves` steps
                        return moves % 2 == 0;
                    }

                    if (vis.find({nx, ny}) == vis.end()) {
                        vis.insert({nx, ny});
                        q.push({nx, ny});
                    }
                }
            }
        }

        return false;
    }
};


// ╔══════════════════════════════════════════════════════════════╗
// ║  APPROACH 3: Mathematical Distance Formula                 ║
// ╚══════════════════════════════════════════════════════════════╝
//
// INTUITION:
//   For a knight on an infinite board, the minimum number of moves
//   can be computed using a formula. Once we know the minimum moves
//   needed, any larger number with the same parity is also possible
//   (the knight can always waste 2 moves by making a loop).
//
//   So reachable in even moves iff:
//     minMoves % 2 == 0   OR   we can add 2 to make it even
//
//   But this is essentially the same as the parity check, since
//   the parity of minMoves is determined by (x+y) parity.
//
// ALGORITHM:
//   1. dx = |target[0] - start[0]|, dy = |target[1] - start[1]|
//   2. Apply the O(1) knight distance formula, then check parity.
//
//   Note: This approach is overkill here; the simple parity check
//         is sufficient and O(1). This is listed for completeness.
//
// TIME  : O(1)
// SPACE : O(1)

class Solution3 {
public:
    // Returns the MINIMUM knight moves from (0,0) to (x,y)
    int minKnightMoves(int x, int y) {
        x = abs(x);
        y = abs(y);

        if (x < y) swap(x, y);      // x ≥ y

        if (x == 1 && y == 0) return 3;
        if (x == 2 && y == 2) return 4;

        int d = max((x + 1) / 2, (x + y + 2) / 3);
        d += (d % 2) != ((x + y) % 2);    // adjust parity

        return d;
    }

    bool canReach(vector<int>& start, vector<int>& target) {
        int dx = abs(target[0] - start[0]);
        int dy = abs(target[1] - start[1]);

        int minMoves = minKnightMoves(dx, dy);

        // Reachable in even number of moves if we can make minMoves even
        // (either minMoves is already even, or we add 2 to make it even)
        return minMoves % 2 == 0;
    }
};


int main() {
    Solution sol;

    vector<pair<vector<int>, vector<int>>> tests = {
        {{0, 0}, {1, 2}},     // diff parity → false
        {{0, 0}, {2, 1}},     // diff parity → false
        {{0, 0}, {3, 3}},     // same parity → true
        {{0, 0}, {0, 0}},     // trivially true (0 moves, even)
        {{1, 1}, {2, 2}},     // same parity → true
        {{0, 0}, {10, 10}},   // same parity → true
        {{0, 0}, {0, 1}},     // diff parity → false (1 move not possible for knight)
    };

    for (auto &test : tests) {
        auto &s = test.first;
        auto &t = test.second;
        cout << "(" << s[0] << "," << s[1] << ") → ("
             << t[0] << "," << t[1] << ") : "
             << (sol.canReach(s, t) ? "true" : "false")
             << "  [parity: s=" << (s[0]+s[1])%2
             << " t=" << (t[0]+t[1])%2 << "]\n";
    }

    return 0;
}
