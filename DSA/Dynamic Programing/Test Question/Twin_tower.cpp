#include <bits/stdc++.h>
using namespace std;

// floor = current floor we are processing
// tower = 0 means tower1, tower = 1 means tower2
//
// tower1[i] = processing time on tower1 at floor i
// tower2[i] = processing time on tower2 at floor i
// leftright[i] = switching cost from tower1 to tower2
// rightleft[i] = switching cost from tower2 to tower1
//
// dp[floor][tower] stores the minimum remaining time
// when we are at 'floor' and currently on 'tower'.
int solve(int floor, int tower, vector<int>& tower1, vector<int>& tower2,
          vector<int>& leftright, vector<int>& rightleft,
          vector<vector<int>>& dp) {

    // BASE CASE:
    // If we have processed all floors, no time remains.
    if (floor == tower1.size()) return 0;

    // MEMOIZATION:
    // If this state was already calculated, reuse its result.
    // This avoids solving the same subproblem repeatedly.
    if (dp[floor][tower] != -1) return dp[floor][tower];

    // Store the minimum time among the possible choices.
    int time;

    // CASE 1: We are currently on tower1.
    if (tower == 0) {

        // OPTION 1: Stay on tower1.
        // Pay tower1's processing time at this floor,
        // then process the next floor while staying on tower1.
        time = tower1[floor] +
               solve(floor + 1, 0, tower1, tower2,
                     leftright, rightleft, dp);

        // We can switch only if there is a next floor.
        // leftright has only n-1 elements, so this check
        // prevents accessing an invalid index.
        if (floor < tower1.size() - 1) {

            // OPTION 2: Switch from tower1 to tower2.
            // Pay the current floor's processing time on tower1,
            // pay the switching cost, then continue on tower2.
            //
            // min() chooses the cheaper of staying and switching.
            time = min(time,
                       tower1[floor] + leftright[floor] +
                       solve(floor + 1, 1, tower1, tower2,
                             leftright, rightleft, dp));
        }
    }

    // CASE 2: We are currently on tower2.
    else {

        // OPTION 1: Stay on tower2.
        // Pay tower2's processing time at this floor,
        // then process the next floor on tower2.
        time = tower2[floor] +
               solve(floor + 1, 1, tower1, tower2,
                     leftright, rightleft, dp);

        // Switching is possible only if another floor exists.
        if (floor < tower1.size() - 1) {

            // OPTION 2: Switch from tower2 to tower1.
            // Pay tower2's processing time,
            // pay the switching cost, then continue on tower1.
            time = min(time,
                       tower2[floor] + rightleft[floor] +
                       solve(floor + 1, 0, tower1, tower2,
                             leftright, rightleft, dp));
        }
    }

    // Save the answer for this state before returning it.
    // Future calls with the same floor and tower can reuse it.
    return dp[floor][tower] = time;
}

// Handles one test case.
void solve() {
    int n;
    cin >> n;  // Number of floors.

    // Processing times for both towers.
    vector<int> tower1(n), tower2(n);

    // There are n-1 gaps between n floors,
    // so each switching-cost array has n-1 elements.
    vector<int> leftright(n - 1), rightleft(n - 1);

    // Read processing times for tower1.
    for (int i = 0; i < n; i++) {
        cin >> tower1[i];
    }

    // Read processing times for tower2.
    for (int i = 0; i < n; i++) {
        cin >> tower2[i];
    }

    // Read switching costs from tower1 to tower2.
    for (int i = 0; i < n - 1; i++) {
        cin >> leftright[i];
    }

    // Read switching costs from tower2 to tower1.
    for (int i = 0; i < n - 1; i++) {
        cin >> rightleft[i];
    }

    // Initially, no state has been calculated.
    // -1 indicates an uncomputed state.
    vector<vector<int>> dp(n, vector<int>(2, -1));

    // Find the minimum total time if we start on tower1.
    int ans1 = solve(0, 0, tower1, tower2,
                     leftright, rightleft, dp);

    // Find the minimum total time if we start on tower2.
    // The same dp table can be reused because each state
    // depends only on the current floor and tower.
    int ans2 = solve(0, 1, tower1, tower2,
                     leftright, rightleft, dp);

    // Choose the smaller result from the two starting towers.
    cout << min(ans1, ans2) << '\n';
}

int main() {
    // Faster input and output.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;  // Number of test cases.

    // Process every test case.
    while (t--) {
        solve();
    }

    return 0;
}