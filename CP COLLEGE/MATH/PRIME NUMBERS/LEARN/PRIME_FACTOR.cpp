#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;

vector<int> primes;     // Stores all prime numbers
vector<int> spf(MAXN + 1, 0); // spf[x] = smallest prime factor of x

void linearSieve(int n)
{
    // Traverse every number from 2 to n
    for (int i = 2; i <= n; i++)
    {
        // If spf is still 0, nobody marked it.
        // Therefore it is a prime.
        if (spf[i] == 0)
        {
            spf[i] = i;
            primes.push_back(i);
        }

        // Generate composite numbers using previously found primes.
        for (int p : primes)
        {
            // Don't go outside the limit.
            if (1LL * i * p > n)
                break;

            // Stop when p becomes larger than the smallest
            // prime factor of i.
            // This guarantees every composite is generated exactly once.
            if (p > spf[i])
                break;

            // First time this composite is generated,
            // so p is its smallest prime factor.
            spf[i * p] = p;
        }
    }
}

vector<pair<int,int>> factorize(int x)
{
    vector<pair<int,int>> ans;

    while (x > 1)
    {
        int p = spf[x];
        int cnt = 0;

        while (x % p == 0)
        {
            cnt++;
            x /= p;
        }

        ans.push_back({p, cnt});
    }

    return ans;
}


int main(){
    //first we find all the prime numbers upto MAXN using linear sieve and then we find the prime factorization of a number using the smallest prime factor array.
    linearSieve(MAXN);
    int n = 360;
    //then we find the prime factorization of the number n using the smallest prime factor array.
    auto factors = factorize(n);

    for (auto it: factors)
    {
        cout << it.first << "^" << it.second << " ";
    }

    return 0;
}