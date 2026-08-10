#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Core intuition

Suppose you are currently at square curr.

A dice can take you to:

curr + 1
curr + 2
curr + 3
curr + 4
curr + 5
curr + 6

For each possible destination:

Find its (row, col) in the matrix.
Check whether there is a snake/ladder.
If yes, jump to its destination.
Otherwise stay there.
Put that resulting square into the BFS queue.

For example:

current = 2

dice:
3 -> maybe snake -> 22
4 -> normal -> 4
5 -> ladder -> 15
6 -> normal -> 6
7 -> normal -> 7
8 -> snake -> 3

All these moves cost one dice roll.

Therefore:

BFS

is perfect.

2. Why BFS?

Imagine this graph:

             2
          ↙  ↓  ↘
        3    4    5
        ↓    ↓    ↓
       22    4    15

Every edge means:

"One dice roll"

So:

start = 1

1 roll    -> all squares reachable in 1 dice roll
2 rolls   -> all squares reachable in 2 dice rolls
3 rolls   -> all squares reachable in 3 dice rolls
...

BFS explores exactly in this order.

Therefore, the first time we reach n², we have found the minimum number of dice rolls.
*/
class Solution {
public:

    // Convert square number -> board[row][col]
    pair<int, int> getPosition(int square, int n) {

        // Convert square to 0-based
        int x = square - 1;

        // Which row from the bottom?
        int rowFromBottom = x / n;

        // Convert to matrix row
        int row = n - 1 - rowFromBottom;

        int col;

        // Even row from bottom -> left to right
        if (rowFromBottom % 2 == 0) {
            col = x % n;
        }
        // Odd row from bottom -> right to left
        else {
            col = n - 1 - (x % n);
        }

        return {row, col};
    }


    int snakesAndLadders(vector<vector<int>>& board) {

        int n = board.size();
        int target = n * n;

        queue<int> q;
        vector<bool> visited(target + 1, false);

        // Start from square 1
        q.push(1);
        visited[1] = true;

        int rolls = 0;

        while (!q.empty()) {

            int size = q.size();

            // Process all squares reachable
            // using exactly 'rolls' dice throws
            while (size--) {

                int curr = q.front();
                q.pop();

                // Try every possible dice result
                for (int dice = 1; dice <= 6; dice++) {

                    int next = curr + dice;

                    // Cannot go beyond n^2
                    if (next > target)
                        break;

                    // Find board position of 'next'
                    auto it = getPosition(next, n);
                    int r = it.first;
                    int c = it.second;

                    // Take snake or ladder if present
                    if (board[r][c] != -1) {
                        next = board[r][c];
                    }

                    // Reached the final square
                    if (next == target) {
                        return rolls + 1;
                    }

                    // Visit this square only once
                    if (!visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }

            // One BFS level = one dice roll
            rolls++;
        }

        return -1;
    }
};


int main(){
    return 0;
}