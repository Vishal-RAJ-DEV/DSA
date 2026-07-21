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




// O(1) Prime Check
bool isPrime(int x)
{
    return x >= 2 && spf[x] == x;
}

// O(log N) Prime Factorization
vector<int> primeFactorization(int x)
{
    vector<int> factors;

    while (x > 1)
    {
        factors.push_back(spf[x]);
        x /= spf[x];
    }

    return factors;
}


int main()
{
    //THIS IS TO CHECK THE SMALLEST PRIME FACTOR OF A NUMBER
    linearSieve(20);
    for (int i = 2; i <= 20; i++)
    {
        cout << "SPF[" << i << "] = " << spf[i] << "\n";
    }



    //------------------------------------------------------------------------------------------------------------------------------------------------------



    //THIS IS TO CHECK THE PRIME FACTORIZATION OF A NUMBER
    //HERE FIRST WE CHECK WHETHER THE NUMBER IS PRIME OR NOT AND THEN IF IT IS NOT PRIME THEN WE FIND THE PRIME FACTORS OF THAT NUMBER
    //HERE WE USE SIZE MAXN = 1000000 BECAUSE WE WANT TO FIND THE PRIME FACTORS OF A NUMBER UPTO 10^6
    linearSieve(MAXN);

    int n;
    cin >> n;

    if (isPrime(n))
    {
        cout << n << " is Prime\n";
        cout << "Prime Factors : " << n << '\n';
    }
    else
    {
        cout << n << " is Not Prime\n";

        vector<int> factors = primeFactorization(n);

        cout << "Prime Factors : ";

        for (int x : factors)
            cout << x << " ";

        cout << '\n';
    }

    return 0;
}
