/*
    Problem: Codeforces "Forked!" (CF 1904A)

    A knight moves by (a, b) or (b, a) in all 8 sign combinations.
    Given positions of a king (xK, yK) and a queen (xQ, yQ),
    count how many squares a knight can stand on to ATTACK both
    the king AND the queen simultaneously (a "fork").

    Intuition:
        If a knight is at position P and attacks the king, then:
            P + (dx, dy) = (xK, yK)
        So P = (xK - dx, yK - dy) where (dx, dy) is one of the
        8 knight move vectors.

        Equivalently, P = (xK + dx', yK + dy') where dx' = -dx.
        Since our move list includes both + and - of each pair
        (the set is symmetric), adding is the same as subtracting.

        So we compute all possible knight positions that attack
        the king, and all that attack the queen, then find their
        intersection. The size of the intersection is the answer.

    Example:
        a=2, b=1
        King at (4,5), Queen at (7,5)
        Knight attack positions for king:
            (4+2,5+1)=(6,6), (4+2,5-1)=(6,4), (4-2,5+1)=(2,6), etc.
        Knight attack positions for queen:
            (7+2,5+1)=(9,6), (7+2,5-1)=(9,4), etc.
        Count positions common to both sets.

    Time: O(8) per test case (constant)
    Space: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        ll a, b;
        cin >> a >> b;

        ll xK, yK;
        cin >> xK >> yK;

        ll xQ, yQ;
        cin >> xQ >> yQ;

        // All 8 possible knight move offsets
        vector<pair<ll,ll>> moves = {
            { a,  b}, { a, -b}, {-a,  b}, {-a, -b},
            { b,  a}, { b, -a}, {-b,  a}, {-b, -a}
        };

        set<pair<ll,ll>> king, queen;

        // Compute all positions a knight can be at to attack each piece
        for (auto it : moves) {
            ll dx = it.first;
            ll dy = it.second;

            // (xK + dx, yK + dy) is a knight position that attacks king
            king.insert({xK + dx, yK + dy});
            // (xQ + dx, yQ + dy) is a knight position that attacks queen
            queen.insert({xQ + dx, yQ + dy});
        }

        // Count positions that attack BOTH (fork)
        int ans = 0;
        for (auto pos : king) {
            if (queen.count(pos))
                ans++;
        }

        cout << ans << '\n';
    }

    return 0;
}