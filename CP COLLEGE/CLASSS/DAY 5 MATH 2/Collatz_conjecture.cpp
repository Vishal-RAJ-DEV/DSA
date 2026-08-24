#include <bits/stdc++.h>
using namespace std;

void collatz(long long n) {
    
    // Print current number
    cout << n << '\n';

    // Base case
    if (n == 1) {
        return;
    }

    // Recursive case
    if (n % 2 == 0) {
        collatz(n / 2);
    } 
    else {
        collatz(3 * n + 1);
    }
}

int main() {
    long long n;
    cin >> n;

    collatz(n);

    return 0;
}