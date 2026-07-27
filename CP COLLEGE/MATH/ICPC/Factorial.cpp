// ============================================================
// PROBLEM: P. Factorial Digits — Find the number of digits in N!
//
// WHY WE CAN'T COMPUTE N! DIRECTLY:
//   N can be up to 100,000. 100000! has ~456,574 digits —
//   far more than any 64-bit integer (≤ 10^18) or even
//   standard big integers can handle. Computing the actual
//   factorial is impossible.
//
// MATHEMATICAL INSIGHT — Logarithms:
//   The number of digits of any positive integer X is:
//       digits = floor(log10(X)) + 1
//
//   Why? Because if X has d digits, then:
//       10^(d-1) ≤ X < 10^d
//       → d-1 ≤ log10(X) < d
//       → d = floor(log10(X)) + 1
//
//   Logarithms turn MULTIPLICATION into ADDITION:
//       log10(N!) = log10(1 × 2 × 3 × ... × N)
//       log10(N!) = log10(1) + log10(2) + ... + log10(N)
//
//   So instead of computing N! (impossible), we sum logs (easy).
//
// ALGORITHM:
//   1. Loop i = 1 to N, accumulate sum_of_logs += log10(i)
//   2. digits = floor(sum_of_logs) + 1
//   3. Print the result
//
// COMPLEXITY: O(N) time, O(1) space
// ============================================================

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    
    // Read the input number
    if (cin >> n) {
        double sum_of_logs = 0;                // Will store Σ log10(i) for i = 1..n
        
        // Sum the base-10 logarithms of all numbers from 1 to N
        // Since log10(1) = 0, the loop effectively starts adding from i=2
        for (int i = 1; i <= n; ++i) {
            sum_of_logs += log10(i);           // Add log10 of each multiplier
        }
        
        // Calculate the number of digits using the logarithm formula
        // floor(sum) gives the integer part; +1 converts to digit count
        long long digits = floor(sum_of_logs) + 1;
        
        // Print the output strictly matching the required format
        cout << "Number of digits of " << n << "! is " << digits << "\n";
    }
    
    return 0;
}
