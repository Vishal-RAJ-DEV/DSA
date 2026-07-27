#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;


ll sumOfDivisors(ll n)
{
    ll ans = 1;                   // start with multiplicative identity

    // Trial division up to sqrt(current n)
    // n shrinks as we divide out factors → loop may end early
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)           // i is a prime factor of current n
        {
            int cnt = 0;          // count exponent of prime i

            // Divide out ALL occurrences of i from n
            while (n % i == 0)
            {
                cnt++;
                n /= i;
            }

            // Compute GP sum: 1 + i + i^2 + ... + i^cnt
            ll sum = 1;           // start with i^0 = 1
            ll power = 1;         // tracks i^j as j increments

            for (int j = 1; j <= cnt; j++)
            {
                power *= i;       // power = i^j
                sum += power;     // accumulate: 1 + i + ... + i^j
            }

            ans *= sum;           // multiply contribution of this prime
        }
    }

    // If n > 1, the remaining n is a prime factor with exponent 1.
    // Its GP sum = 1 + n^1 = 1 + n.
    // This is the same as the formula: ans *= (n^(1+1) - 1) / (n - 1)
    //                                = (n^2 - 1) / (n - 1)
    //                                = n + 1
    if (n > 1)
    {
        ans *= (1 + n);
    }

    return ans;
}


int main(){
    ll n;
    cin>>n;
    
    ll res = sumOfDivisors(n);
    cout<<res<<endl;
    
    return 0;
}