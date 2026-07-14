#include <bits/stdc++.h>
using namespace std;

//==================== Typedefs ====================//
using ll = long long;
using ull = unsigned long long;
using ld = long double;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vi = vector<int>;
using vll = vector<ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;

//==================== Constants ====================//
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

//==================== Macros ====================//
#define pb push_back
#define eb emplace_back

#define ff first
#define ss second

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#define sz(x) (int)(x).size()

#define yes cout << "YES\n"
#define no cout << "NO\n"

#define endl '\n'

#define rep(i,a,b) for(int i=a;i<b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)

//==================== Fast IO ====================//
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

//==================== Input ====================//
template<typename T>
void input(vector<T>& v) {
    for(auto &x : v)
        cin >> x;
}

//==================== Output ====================//
template<typename T>
void print(const vector<T>& v) {
    for(auto x : v)
        cout << x << " ";
    cout << endl;
}

//==================== Math ====================//
ll gcd(ll a, ll b) {
    return __gcd(a, b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll power(ll a, ll b) {
    ll ans = 1;
    while(b) {
        if(b & 1)
            ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

ll modpow(ll a, ll b, ll mod = MOD) {
    ll ans = 1;
    a %= mod;

    while(b) {
        if(b & 1)
            ans = (ans * a) % mod;

        a = (a * a) % mod;
        b >>= 1;
    }

    return ans;
}

bool isPrime(ll n) {
    if(n < 2)
        return false;

    for(ll i = 2; i * i <= n; i++)
        if(n % i == 0)
            return false;

    return true;
}

//==================== Prefix Sum ====================//
vector<ll> prefixSum(const vi &a) {
    int n = a.size();

    vector<ll> pre(n + 1);

    for(int i = 0; i < n; i++)
        pre[i + 1] = pre[i] + a[i];

    return pre;
}

//==================== Min/Max Update ====================//
template<typename T>
bool ckmin(T &a, T b) {
    if(b < a) {
        a = b;
        return true;
    }
    return false;
}

template<typename T>
bool ckmax(T &a, T b) {
    if(b > a) {
        a = b;
        return true;
    }
    return false;
}

//==================== Debug ====================//
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x << endl;
#else
#define debug(x)
#endif

//==================== Solve ====================//
void solve() {
    
}

//==================== Main ====================//
int main() {

    fastIO();

    int t = 1;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}