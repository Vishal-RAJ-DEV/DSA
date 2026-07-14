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
    int ifuel;
    int dist;
    cin>> ifuel >> dist;
    vi a(ifuel);
    input(a);

    int ans = a[0];
    for(int i = 1 ; i < ifuel ; i++){
        ans = max(ans , ( a[i] - a[i-1]));
    }

    ans = max( ans  , 2*( dist - a[ifuel-1] ) );
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