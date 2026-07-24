#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Different Divisors - Codeforces 1474B):
Given an integer d, find the SMALLEST positive integer a such that:
1) a has AT LEAST 4 divisors.
2) The difference between ANY two divisors of a is at least d.

In other words, if you list all divisors of a, no two divisors
should be closer than d apart.

EXAMPLE:
d = 1  → smallest a = 6  (divisors: 1,2,3,6  → diffs: 1,1,3,2,3,4 all ≥1)
d = 2  → smallest a = 15 (divisors: 1,3,5,15 → diffs: 2,2,10,4,12,14 all ≥2)
d = 3  → smallest a = 55 (divisors: 1,5,11,55 → diffs: 4,6,44,10,50,54 all ≥3)

=========================================================
APPROACH & LOGIC:
=========================================================

KEY INSIGHT:
A number with exactly 4 divisors comes in only TWO forms:

  Form 1: a = p1 * p2    (product of two distinct primes)
          Divisors: 1, p1, p2, p1*p2  → exactly 4 divisors.

  Form 2: a = p1^3       (cube of a prime)
          Divisors: 1, p1, p1^2, p1^3  → exactly 4 divisors.

Any other form (like p^2 * q or p*q*r) would have MORE than 4
divisors and would be larger. So the answer must be one of these
two forms.

Now, apply the "difference >= d" constraint:

FORM 1: a = p1 * p2 (with p1 < p2, both primes)
  Divisors: 1, p1, p2, p1*p2
  Critical differences:
      p1 - 1 >= d   →  p1 >= d + 1
      p2 - p1 >= d  →  p2 >= p1 + d
  (Other diffs like p1*p2 - p2 = p2*(p1-1) are automatically larger)

FORM 2: a = p1^3
  Divisors: 1, p1, p1^2, p1^3
  Critical difference:
      p1 - 1 >= d   →  p1 >= d + 1
  (Other diffs like p1^2 - p1 = p1*(p1-1) are automatically larger)

So the constraints reduce to:
  p1 = smallest prime >= d + 1
  p2 = smallest prime >= p1 + d
  ans = min(p1 * p2, p1 * p1 * p1)

WHY THESE TWO FORMS?
- p1 * p2 gives 4 divisors with the second prime placed exactly d apart.
- p1^3 gives 4 divisors using only one prime but in a tighter package.
  Sometimes p1^3 is smaller than p1 * p2 (e.g., when p2 is very large).
- We take the MINIMUM of both possibilities.

ALGORITHM:
1. Precompute all primes up to 1,000,000 using Sieve of Eratosthenes.
2. For each test case with given d:
   a. Find p1 = first prime >= d + 1 (using binary search on prime list).
   b. Find p2 = first prime >= p1 + d.
   c. ans1 = p1 * p2
   d. ans2 = p1 * p1 * p1
   e. Print min(ans1, ans2).

EXAMPLE WALKTHROUGH:
d = 3
  Primes list: [2, 3, 5, 7, 11, 13, 17, 19, ...]
  p1 = first prime >= 3+1=4  → p1 = 5
  p2 = first prime >= 5+3=8  → p2 = 11
  ans1 = 5 * 11 = 55
  ans2 = 5 * 5 * 5 = 125
  ans = min(55, 125) = 55 ✓

d = 4
  p1 = first prime >= 5  → p1 = 5
  p2 = first prime >= 5+4=9 → p2 = 11
  ans1 = 55
  ans2 = 125
  ans = 55  (divisors: 1,5,11,55 → diffs: 4,6,44,10,50,54 all ≥4)

d = 10
  p1 = first prime >= 11 → p1 = 11
  p2 = first prime >= 11+10=21 → p2 = 23
  ans1 = 11 * 23 = 253
  ans2 = 11 * 11 * 11 = 1331
  ans = 253
*/

vector<int>prime;
typedef long long ll;

void solve(){
    ll d;
    cin>> d;

    // p1 = smallest prime >= d + 1
    ll p1 = *lower_bound(prime.begin() , prime.end() , d + 1);

    // p2 = smallest prime >= p1 + d
    ll p2 = *lower_bound(prime.begin() , prime.end() , p1 + d);

    ll ans1 = p1 * p2;    // form: product of two primes
    ll ans2 = p1 * p1 * p1;  // form: cube of a prime

    cout << min(ans1 , ans2) << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Sieve of Eratosthenes up to 1,000,000
    vector<bool> isPrime(1000001, true);
    isPrime[0] = isPrime[1] = false;

    for(int i = 2 ; i * i <= 1000000; i++){
        if(isPrime[i]){
            for(int j = i * i ; j <= 1000000; j += i){
                isPrime[j] = false;
            }
        }
    }

    // Collect all primes into a sorted list for binary search
    for(int i = 2; i <= 1000000; i++){
        if(isPrime[i]){
            prime.push_back(i);
        }
    }

    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}