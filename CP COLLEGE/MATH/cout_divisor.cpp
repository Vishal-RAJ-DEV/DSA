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
    int n;
    cin >> n;
    vi divisor;
    int ans = 1;
    for( int i = 1 ; i * i <= n ; i++){
        if( n % i == 0){
            int cnt = 0;
            while( n % i == 0){
                cnt++;
                n /= i;
            }
            ans *= (cnt + 1);
        }

    }
    if( n > 1) ans *= 2;
    cout << ans << endl;
}

// -------------------- Main --------------------
int main() {

    fastIO();

    int t = 1;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

/*
================================================================
QUESTION:
Given a single integer n (or t test cases, each with an integer n),
find the total number of positive divisors of n.

================================================================
INTUITION:
The fundamental theorem of arithmetic states any number n > 1 can be
expressed as a product of prime powers: n = p1^e1 * p2^e2 * ... * pk^ek.
Any divisor of n must be of the form p1^f1 * p2^f2 * ... * pk^fk
where 0 <= fi <= ei. Since each fi can be chosen independently in
(ei+1) ways, the total number of divisors = (e1+1)*(e2+1)*...*(ek+1).

================================================================
ALGORITHM (Prime Factorization by Trial Division):
1. Initialize ans = 1.
2. For i = 2 to sqrt(n):
     If i divides n:
        cnt = 0
        While i divides n:
            n /= i
            cnt++
        ans *= (cnt + 1)   // contribution of prime i
3. After the loop, if n > 1, it means the remaining n is a prime
   factor with exponent 1. So ans *= 2.
4. Output ans.

Time Complexity: O(sqrt(n)) per test case.
Space Complexity: O(1)

================================================================
EXAMPLE:
n = 84
i=2: cnt=2 (84->42->21), ans *= 3 -> ans=3, n=21
i=3: cnt=1 (21->7), ans *= 2 -> ans=6, n=7
Loop ends (i=4 > sqrt(7))
n=7 > 1 => ans *= 2 -> ans=12
84 = 2^2 * 3 * 7 => divisors = (2+1)*(1+1)*(1+1) = 12
*/