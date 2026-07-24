#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Bad Boy - Codeforces 1537B):
We have an n x m grid. Anton is standing at cell (i, j).
Riley throws TWO yo-yos into two cells (can be the same cell).

Anton must:
  Start at (i,j) → Pick up yo-yo 1 → Pick up yo-yo 2 → Return to (i,j)

He can only move up/down/left/right (Manhattan distance).
We need to choose positions for the two yo-yos to MAXIMIZE
the total distance Anton travels.

Output the coordinates of the two yo-yos.

=========================================================
INTUITION & APPROACH:
=========================================================

KEY INSIGHT:
The total distance = dist(start, y1) + dist(y1, y2) + dist(y2, start).
To maximize this, place the yo-yos at OPPOSITE CORNERS of the grid.

Why opposite corners?
- The farthest cells from ANY starting point in a grid are the four corners.
- The farthest pair of cells in a grid is always a pair of OPPOSITE corners:
    Corner A = (1, 1)  ←→  Corner B = (n, m)    [diagonal 1]
    Corner C = (1, m)  ←→  Corner D = (n, 1)    [diagonal 2]
- By placing yo-yos at opposite corners, we maximize both the
  start→yoyo segments AND the yoyo1→yoyo2 segment simultaneously.

We only have two candidate pairs:
  Path 1: (i,j) → (1,1) → (n,m) → (i,j)
  Path 2: (i,j) → (1,m) → (n,1) → (i,j)

Compute total Manhattan distance for both, pick the longer one.

LOGIC:
- There are only 4 corners in a grid: (1,1), (1,m), (n,1), (n,m).
- The two diagonally opposite pairs are the farthest apart.
- Whichever pair gives the longer total path from Anton's position
  is the optimal answer.
- This is O(1) per test case — no need for complex search.

EXAMPLE:
n=2, m=3, Anton at (2,1)

Path 1: (2,1)→(1,1)→(2,3)→(2,1)
  dist = |2-1|+|1-1| + |1-2|+|1-3| + |2-2|+|3-1|
       = 1 + 0 + 1 + 2 + 0 + 2 = 6

Path 2: (2,1)→(1,3)→(2,1)→(2,1)
  dist = |2-1|+|1-3| + |1-2|+|3-1| + |2-2|+|1-1|
       = 1 + 2 + 1 + 2 + 0 + 0 = 6

Both equal, so either is valid. Output: 1 1 2 3 (for Path 1).
*/

typedef long long ll;

// Manhattan distance between two cells
ll dist(ll x1 , ll y1 , ll x2 , ll y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

void solve(){
    int n , m , i , j;
    cin >> n >> m >> i >> j;

    // Path 1: through opposite corners (1,1) and (n,m)
    ll distance1 = dist(i , j , 1 , 1) + dist(1 , 1 , n , m) + dist(n , m , i , j);

    // Path 2: through opposite corners (1,m) and (n,1)
    ll distance2 = dist(i , j , 1 , m) + dist(1, m , n , 1) + dist(n , 1 , i , j);

    if(distance1 > distance2){
        cout << 1 << " " << 1 << " " << n << " " << m << endl;
    }
    else{
        cout << 1 << " " << m << " " << n << " " << 1 << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}