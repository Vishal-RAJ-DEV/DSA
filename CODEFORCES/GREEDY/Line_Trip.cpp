/*
 * =============================================================
 *  PROBLEM: Line Trip (Codeforces Round 1901A)
 * =============================================================
 *
 *  QUESTION:
 *  ---------
 *  There is a road from point 0 to point X.
 *  Along the road there are N gas stations at given positions.
 *  A car starts at 0 with a full tank of fuel of capacity V (unknown).
 *  The car must:
 *     1. Drive from 0 to X, then
 *     2. Turn around and drive back from X to 0.
 *  The car can refuel to full capacity at any gas station (or at start).
 *  Find the MINIMUM fuel capacity V needed to complete the round trip.
 *
 *  NOTE: In the code, variables are named differently:
 *        - ifuel → number of gas stations (N)
 *        - dist  → the destination point (X)
 *        - a[]   → positions of gas stations (sorted ascending)
 *
 *  INTUITION:
 *  ----------
 *  The car consumes 1 unit of fuel per 1 unit of distance traveled.
 *  At any gas station (including start), the tank is refilled to full capacity V.
 *
 *  So between two consecutive refueling opportunities, the maximum distance
 *  the car must travel WITHOUT refueling determines the minimum V required.
 *
 *  Consider the segments of the journey:
 *
 *    FORWARD trip (0 → X):
 *    ----------------------
 *    Segment 1: 0 → a[0]
 *        Start with full tank at 0. Drive to first station.
 *        Distance = a[0]
 *        → Need V ≥ a[0]
 *
 *    Segment i (2 ≤ i ≤ N): a[i-2] → a[i-1]
 *        Refuel at a[i-2], then drive to a[i-1].
 *        Distance = a[i-1] - a[i-2]
 *        → Need V ≥ a[i-1] - a[i-2]
 *
 *    Segment N+1: a[N-1] → X
 *        Refuel at last station, then drive to X.
 *        Distance = X - a[N-1]
 *        → Need V ≥ X - a[N-1]  (but see RETURN trip below!)
 *
 *    RETURN trip (X → 0):
 *    ---------------------
 *    After reaching X, the car immediately turns back toward 0.
 *    The nearest gas station on the return is a[N-1] (the last station).
 *    From X, the car must go:
 *        X → a[N-1]  (distance = X - a[N-1])
 *        refuel at a[N-1]
 *        a[N-1] → a[N-2] → ... → a[0] → 0
 *
 *    CRITICAL INSIGHT:
 *    The segment from the last station (a[N-1]) to X and BACK to a[N-1]
 *    is the ONLY segment that is traversed TWICE without a refuel in between:
 *        - On the forward trip: a[N-1] → X  (distance = X - a[N-1])
 *        - On the return trip:  X → a[N-1]  (distance = X - a[N-1])
 *        - Total continuous distance without refuel = 2 × (X - a[N-1])
 *
 *    For all other interior segments (a[i-1] ↔ a[i]), the car passes them
 *    with a gas station at each end, so each direction is refueled separately.
 *
 *    → So for the last segment, we need V ≥ 2 × (X - a[N-1])
 *
 *  FINAL ANSWER:
 *  -------------
 *  V_min = max( a[0],                     // start → first station
 *               max_diff between stations, // station i-1 → station i
 *               2 × (X - a[N-1])          // last station → X → last station
 *             )
 *
 *  ALGORITHM:
 *  ----------
 *  1. Read N (number of stations) and X (destination).
 *  2. Read the station positions into array a[].
 *  3. Initialize ans = a[0].                     // segment 0 → a[0]
 *  4. For i = 1 to N-1:
 *         ans = max(ans, a[i] - a[i-1])          // segment a[i-1] → a[i]
 *  5. ans = max(ans, 2 * (X - a[N-1]))          // round trip from last station
 *  6. Print ans.
 *
 *  COMPLEXITY:
 *  -----------
 *  Time  → O(N) — single pass through the stations
 *  Space → O(1) aside from input storage (or O(N) if array is stored)
 */

#include <bits/stdc++.h>
using namespace std;

// -------------------- Typedefs --------------------
using ll = long long;
using ull = unsigned long long;
using ld = long double;

using pii = pair<int,int>;
using pll = pair<ll,ll>;

using vi = vector<int>;
using vll = vector<ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;

// -------------------- Constants --------------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

// -------------------- Macros --------------------
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

// -------------------- Fast IO --------------------
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

// -------------------- Input --------------------
template<typename T>
void input(vector<T> &v) {
    for (auto &x : v)
        cin >> x;
}

// -------------------- Output --------------------
template<typename T>
void print(vector<T> &v) {
    for (auto x : v)
        cout << x << " ";
    cout << '\n';
}

// -------------------- Solve --------------------
void solve() {
    int ifuel;          // N: number of gas stations
    int dist;           // X: destination coordinate
    cin >> ifuel >> dist;

    vi a(ifuel);         // positions of gas stations (sorted)
    input(a);

    /*
     * ans starts as the distance from start (0) to the first station.
     * The car must cover this without refueling.
     */
    int ans = a[0];

    /*
     * For each consecutive pair of stations, the maximum gap between them
     * is a candidate. The car must traverse this gap without refueling.
     */
    for (int i = 1; i < ifuel; i++) {
        ans = max(ans, (a[i] - a[i-1]));
    }

    /*
     * The last segment is special:
     * From the last station to X (forward) and back to the last station (return)
     * is a continuous distance of 2 * (X - last_station) without refueling.
     */
    ans = max(ans, 2 * (dist - a[ifuel - 1]));

    cout << ans << endl;
}

// -------------------- Main --------------------
int main() {
    fastIO();

    int t = 1;           // number of test cases (default 1)
    cin >> t;            // read test case count

    while (t--) {
        solve();         // solve each test case
    }

    return 0;
}
