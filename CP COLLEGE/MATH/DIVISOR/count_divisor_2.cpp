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
const int MAX = 1000000;

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

// -------------------- Global Precomputation --------------------
vi divisorCount(MAX + 1, 0);

void precompute() {
    for (int i = 1; i <= MAX; i++) {
        for (int j = i; j <= MAX; j += i) {
            divisorCount[j]++;
        }
    }
}

// -------------------- Solve --------------------
void solve() {
    int n;
    cin >> n;

    while (n--) {
        int x;
        cin >> x;
        cout << divisorCount[x] << '\n';
    }
}

// -------------------- Main --------------------
int main() {

    fastIO();

    precompute();   // Build divisor counts ONCE

    solve();        // Only one test case in this problem

    return 0;
}

/*
================================================================
QUESTION:
Given an integer n (number of queries), followed by n integers x
(1 <= x <= 1e6), output the count of divisors for each x.

================================================================
INTUITION:
The number of divisors of a number can be found by prime factorization:
if x = p1^e1 * p2^e2 * ... * pk^ek, then divisor count = (e1+1)*(e2+1)*...*(ek+1).
Doing this per query (O(sqrt(x))) is fine for one number, but when
there are many queries, it's better to precompute divisor counts for
ALL numbers up to MAX using a sieve-like approach, then answer each
query in O(1).

================================================================
ALGORITHM (Precomputation – Sieve of divisors):
1. Create an array divisorCount[] of size MAX+1 initialized to 0.
2. For i = 1 to MAX:
     For every multiple j of i (j = i, 2i, 3i, ... <= MAX):
        divisorCount[j]++
   Explanation: i is a divisor of j, so we count it.
3. After the loops, divisorCount[x] holds the total number of divisors of x.
4. For each query x, output divisorCount[x] directly.

Time Complexity: O(MAX log MAX) for precomputation (harmonic series sum),
                 O(1) per query.
Space Complexity: O(MAX)

================================================================
EXAMPLE:
MAX = 10
i=1: increments all positions 1..10
i=2: increments positions 2,4,6,8,10
i=3: increments positions 3,6,9
...
Result: divisorCount[6] = 4 (divisors: 1,2,3,6)
*/