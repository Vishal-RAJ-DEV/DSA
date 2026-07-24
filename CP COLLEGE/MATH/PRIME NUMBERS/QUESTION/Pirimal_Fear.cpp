#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;

vector<bool> isPrime(MAXN + 1, true);
vector<int> prefix(MAXN + 1, 0);

// Sieve of Eratosthenes
void sieve() {
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= MAXN; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAXN; j += i)
                isPrime[j] = false;
        }
    }
}

// Check whether x is a "fear prime"
bool isFearPrime(int x) {

    if (!isPrime[x]) return false;

    string s = to_string(x);

    // Must not contain digit 0
    for (char c : s)
        if (c == '0')
            return false;

    // Every suffix must also be prime
    for (int i = 1; i < (int)s.size(); i++) {
        int suffix = stoi(s.substr(i));
        if (!isPrime[suffix])
            return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    // Build prefix array
    for (int i = 1; i <= MAXN; i++) {
        prefix[i] = prefix[i - 1];
        if (isFearPrime(i))
            prefix[i]++;
    }

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        cout << prefix[N] << '\n';
    }

    return 0;
}