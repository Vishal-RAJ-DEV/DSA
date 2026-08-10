#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {

        // Store all deadend states
        unordered_set<string> dead;

        for (string s : deadends) {
            dead.insert(s);
        }

        // If starting position itself is blocked
        if (dead.count("0000")) {
            return -1;
        }

        // BFS queue: {current state, number of moves}
        queue<pair<string, int>> q;

        // To avoid visiting the same state again
        unordered_set<string> visited;

        q.push({"0000", 0});
        visited.insert("0000");

        while (!q.empty()) {

            string curr = q.front().first;
            int moves = q.front().second;
            q.pop();

            // We reached the target
            if (curr == target) {
                return moves;
            }

            // Try changing each of the 4 wheels
            for (int i = 0; i < 4; i++) {

                // Move wheel forward (+1)
                string next = curr;

                next[i] = (curr[i] - '0' + 1) % 10 + '0';

                if (!dead.count(next) && !visited.count(next)) {
                    visited.insert(next);
                    q.push({next, moves + 1});
                }

                // Move wheel backward (-1)
                next = curr;

                next[i] = (curr[i] - '0' + 9) % 10 + '0';

                if (!dead.count(next) && !visited.count(next)) {
                    visited.insert(next);
                    q.push({next, moves + 1});
                }
            }
        }

        // Target cannot be reached
        return -1;
    }
};

