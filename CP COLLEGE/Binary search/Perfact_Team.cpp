// ═══════════════════════════════════════════════════════════════
// PROBLEM: A. Perfect Team (Codeforces)
// ═══════════════════════════════════════════════════════════════
//
// You have n students in a college. Each student belongs to one
// of three categories:
//
//   - Coder    (can only code)
//   - Mathematician (can only do math)
//   - No specialization (can do nothing, just an ordinary student)
//
// You are given three numbers:
//   c = number of coders
//   m = number of mathematicians
//   x = number of students with no specialization
//
// So total students = c + m + x
//
// ─────────────────────────────────────────────────────────────
// TEAM FORMATION RULES:
// ─────────────────────────────────────────────────────────────
//
// You need to form teams where:
//
//   1. Each team has EXACTLY 3 members.
//
//   2. Each team MUST have at least 1 coder.
//
//   3. Each team MUST have at least 1 mathematician.
//
//   4. The 3rd member can be ANYONE — a coder,
//      a mathematician, or an unspecialized student.
//
// ─────────────────────────────────────────────────────────────
// WHAT IS BEING ASKED:
// ─────────────────────────────────────────────────────────────
//
// Find the MAXIMUM number of complete teams you can form
// following the above rules.
//
// ─────────────────────────────────────────────────────────────
// EXAMPLE 1:
//   c = 4, m = 4, x = 1  →  total = 9 students
//
//   Team 1: Coder + Mathematician + Coder
//   Team 2: Coder + Mathematician + Mathematician
//   Team 3: Coder + Mathematician + No-spec
//
//   All 9 students used, 3 complete teams.
//   Answer = 3
//
// ─────────────────────────────────────────────────────────────
// EXAMPLE 2:
//   c = 10, m = 1, x = 10  →  total = 21 students
//
//   We only have 1 mathematician, so we can form
//   at most 1 team (every team needs at least 1 math).
//   Answer = 1
//
// ─────────────────────────────────────────────────────────────
// EXAMPLE 3:
//   c = 100, m = 100, x = 0  →  total = 200 students
//
//   We have plenty of coders and mathematicians,
//   but 100 teams need 300 students — we only have 200.
//   Max teams = 200 / 3 = 66
//   Answer = 66
// ═══════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;

    while (q--) {
        long long c, m, x;
        cin >> c >> m >> x;

        // ─────────────────────────────────────────────────────
        // PROBLEM: Form maximum teams of 3 students each.
        //          Each team MUST contain at least 1 coder
        //          and at least 1 mathematician.
        //          The 3rd member can be anyone (coder,
        //          mathematician, or unspecialized).
        // ─────────────────────────────────────────────────────
        //
        // FOR k TEAMS we need to satisfy ALL THREE conditions:
        //
        // 1) Every team needs at least 1 coder → need k coders
        //        k <= c
        //
        // 2) Every team needs at least 1 mathematician → need k maths
        //        k <= m
        //
        // 3) Each team has 3 members → need 3k total students
        //        3k <= c + m + x
        //        k  <= (c + m + x) / 3
        //
        // The answer is the maximum k that satisfies all three,
        // which is simply the smallest of the three upper bounds.
        //
        // Example walkthrough:
        //   c = 4, m = 4, x = 1
        //   k <= 4  (enough coders)
        //   k <= 4  (enough mathematicians)
        //   k <= 9/3 = 3  (enough total people)
        //   → min(4, 4, 3) = 3 teams
        //
        //   c = 100, m = 100, x = 0
        //   k <= 100
        //   k <= 100
        //   k <= 200/3 = 66
        //   → min(100, 100, 66) = 66 teams
        //   (Can't make 100 teams because that needs 300
        //    students but only 200 exist)
        // ─────────────────────────────────────────────────────

        long long ans = min({c, m, (c + m + x) / 3});

        cout << ans << endl;
    }

    return 0;
}