#include <bits/stdc++.h>
using namespace std;

/*
=============================================================
 PROBLEM: 1875A - Jellyfish and Undertale (Codeforces)
=============================================================

PROBLEM SUMMARY:

Bomb timer starts at 'b'. Every second:
  1. Optionally use any unused tools (adds x_i each, capped at 'a')
  2. Timer decreases by 1
  3. If timer = 0, bomb explodes

Goal: Maximize total seconds until explosion.

=============================================================
 KEY OBSERVATION:

The timer can never exceed 'a'. Since the timer decreases by 1
every second, each unit of timer = 1 extra second of life.

When we use a tool with value x:
  • Current timer increases by x, but capped at a
  • Then timer decreases by 1
  • Net gain = how much extra timer we have after this cycle

=============================================================
 OPTIMAL STRATEGY:

  Phase 1: Let timer fall from b down to 1 naturally.
            This takes (b - 1) seconds, but we count b as the
            initial total (b seconds to reach 0 without tools).

  Phase 2: Use tools ONE AT A TIME when timer = 1.

Why timer = 1? Because we want the timer to be as LOW as
possible before using a tool — this maximizes the gain since
the cap 'a' is the same regardless. Using a tool when timer
is higher wastes potential (the +x would overflow to a anyway).

=============================================================

 MATH BEHIND ONE TOOL USE:

  • Current timer: 1
  • Add tool x: timer = min(1 + x, a)
  • Decrease by 1: timer = min(1 + x, a) - 1
  • Timer now decreases naturally back to 1

  Extra seconds gained from this tool:
    = 1 (the second we used the tool)
    + (min(1 + x, a) - 2) (seconds to fall from min(1+x,a)-1 to 1)
    = min(1 + x, a) - 1
    = min(x, a - 1)

  So each tool adds exactly min(x, a-1) seconds.

=============================================================

 FINAL FORMULA:

  Answer = b + Σ min(x_i, a - 1)

  • b: initial timer value = seconds to explode without tools
  • Σ min(x_i, a-1): extra seconds from each tool

=============================================================

 WHY NOT USE MULTIPLE TOOLS AT ONCE?

If you use 2 tools at timer=1:
    timer = min(1 + x₁ + x₂, a)

The second tool's contribution might be wasted if we already
hit the cap 'a'. Using tools ONE AT A TIME (letting timer
fall back to 1 between uses) extracts full value from each.

Example: a=5, x=[7, 7]
  Using both at once: min(1+7+7,5)=5, gain=4. Only 4 extra sec.
  Using one by one:
    Tool1 at timer=1: min(1+7,5)=5 → gain=4
    Tool2 at timer=1: min(1+7,5)=5 → gain=4
    Total gain=8!

=============================================================

 EDGE CASE:

If a = 1: then a-1 = 0, so min(x, 0) = 0 for all tools.
Timer can never exceed 1, tools give no benefit.
Answer = b × 1 = b. ✓
=============================================================
*/

void solve(){
    long long a, b, n;
    cin >> a >> b >> n;

    long long ans = b;  // Initial time = starting timer value b

    for(int i = 0 ; i < n ; i++){
        long long x;
        cin >> x;

        // Each tool adds min(x, a-1) extra seconds
        // (cannot exceed a-1 because timer is capped at a and we use at timer=1)
        ans += min(x, a - 1);
    }

    cout << ans << "\n";
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
