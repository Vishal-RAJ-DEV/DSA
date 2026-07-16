/*  Factorial under MOD 998244353
    If n >= MOD, answer = 0 (since MOD is prime and divides n!)
    Otherwise compute iteratively with modulo at each step.  */

#include <iostream>
using namespace std;
using ll = long long;
const ll MOD = 998244353;

ll factorial_mod(ll n) {
    if (n >= MOD) return 0;
    ll res = 1;
    for (ll i = 2; i <= n; i++)
        res = (res * i) % MOD;
    return res;
}

int main() {
    ll n;
    cin >> n;
    cout << factorial_mod(n) << '\n';
    return 0;
}
