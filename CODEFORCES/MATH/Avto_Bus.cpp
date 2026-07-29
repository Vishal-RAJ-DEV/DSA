#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
=============================================================
 PROBLEM: 1679A - AvtoBus (Codeforces)
=============================================================

🔹 PROBLEM (Simple words):

  We have n total wheels. Buses come in two types:
    - 4-wheel (2 axles)
    - 6-wheel (3 axles)

  We don't know how many of each type exist.
  Find MINIMUM and MAXIMUM possible number of buses.
  If impossible → print -1.

=============================================================

🔹 KEY INSIGHT #1: When is it IMPOSSIBLE?

  Equation: 4a + 6b = n   (a = 4-wheelers, b = 6-wheelers)

  Both 4 and 6 are EVEN numbers.
  Sum of even numbers is always EVEN.
  So if n is ODD → impossible.

  Also, smallest possible n is 4 (one 4-wheeler).
  n = 2 is even but too small → impossible.

=============================================================

🔹 KEY INSIGHT #2: MAXIMUM buses → use more 4-wheelers

  4-wheelers have FEWER wheels per bus.
  To MAXIMIZE the bus count, use as many 4s as possible.

  Example: n = 14
    Try all 4s: 14/4 = 3.5 → 3 fours = 12 wheels, 2 left
    Replace one 4 with a 6: 2 fours + 1 six = 3 buses

  Formula: max_buses = n / 4   (integer division)

  Why this always works?
    n is even, so n % 4 is either 0 or 2.
    - If n % 4 == 0: all 4s → max = n/4
    - If n % 4 == 2: use (n-6)/4 fours + 1 six → same count = n/4
    Both cases give n/4 (integer division handles it).

=============================================================

🔹 KEY INSIGHT #3: MINIMUM buses → use more 6-wheelers

  6-wheelers have MORE wheels per bus.
  To MINIMIZE the bus count, use as many 6s as possible.

  Try using only 6s: b = n / 6 (integer division)
  Remainder r = n % 6 (can be 0, 2, or 4 since n is even)

  Case 1: r == 0 → all 6s work. min = n/6
  Case 2: r == 2 or 4 → need extra wheels
    We replace ONE 6-wheeler (removing 6 wheels) and add
    the remainder + 6 = 8 or 10 wheels using 4-wheelers.
    - r=2: replace 1 six with 2 fours (2×4 = 8: covers 6+2)
    - r=4: replace 1 six with... actually, 6+4=10, need 2.5 fours? No.
           Simply keep 1 six and add 4-wheeler for remainder 4.
           Wait, n = 6k + 4 → 6(k) + 1×4 → buses = k + 1

    Either way, min = n/6 + 1 (one extra bus from the remainder).

  Formula:
    if n % 6 == 0 → min = n / 6
    else          → min = n / 6 + 1

=============================================================

🔹 VISUAL EXAMPLES:

  n=24:
    24 = all 4s → 6 buses (max)
    24 = all 6s → 4 buses (min)
    Output: 4 6  ✓

  n=10:
    10 = 4+6 → 2 buses (both min and max)
    10/4 = 2, 10/6=1 + (10%6=4 ≠ 0) → 1+1=2
    Output: 2 2  ✓

  n=14:
    14 = 4+4+6 → 3 buses (both min and max)
    14/4 = 3, 14/6=2 + (14%6=2 ≠ 0) → 2+1=3
    Output: 3 3  ✓

  n=7 (odd): -1 ✓
  n=2 (even but < 4): -1 ✓

=============================================================

🔹 TIME COMPLEXITY: O(1) per test case
=============================================================
*/

void solve(){
    ll n; 
    cin>>n;

    // If n is odd or too small, impossible
    if( n % 2 != 0 || n < 4){
        cout<<-1<<endl;
        return;
    }

    // Maximum buses: use as many 4-wheelers as possible
    ll max_buses = n / 4;

    // Minimum buses: use as many 6-wheelers as possible
    ll min_buses;
    if( n % 6 == 0){
        min_buses = n / 6;
    }else{
        min_buses = n / 6 + 1;
    }

    cout<< min_buses << " " << max_buses <<endl;
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