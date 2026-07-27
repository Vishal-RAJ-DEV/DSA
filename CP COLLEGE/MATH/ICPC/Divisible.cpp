// ============================================================
// PROBLEM: Check if a huge integer N (up to 10,000 digits)
//          is divisible by X.
//
// WHY WE CAN'T USE STANDARD INTEGER TYPES:
//   N can have up to 10,000 digits. The largest standard type
//   (unsigned long long) holds about 20 digits (~10^19). So N
//   must be read as a STRING.
//
// LOGIC — Modulo arithmetic digit-by-digit:
//   We process the string N one digit at a time, maintaining the
//   current remainder using the distributive property of modulo:
//
//       Let N = d₁d₂d₃...dₖ   (each dᵢ is a single digit)
//
//       N mod X = ((...((d₁ × 10 + d₂) × 10 + d₃) × 10 + ...) × 10 + dₖ) mod X
//
//   Since (a + b) mod X = ((a mod X) + (b mod X)) mod X and
//         (a × b) mod X = ((a mod X) × (b mod X)) mod X,
//
//   we can iteratively compute:
//       remainder = 0
//       for each digit d:
//           remainder = (remainder × 10 + d) % X
//
//   After all digits, if remainder == 0, N is divisible by X.
//
// WHY THIS WORKS:
//   The formula comes from Horner's method for evaluating a
//   polynomial. The number N is a polynomial:
//       N = d₁·10^{k-1} + d₂·10^{k-2} + ... + dₖ·10⁰
//   Horner's method rewrites this as:
//       N = (...((d₁·10 + d₂)·10 + d₃)·10 + ... + dₖ)
//   Taking mod X at each step keeps numbers small (bounded by X).
//
// EDGE CASE:
//   N could be "0" → remainder stays 0 → "YES" (0 is divisible
//   by any X, and the problem expects this).
//
// COMPLEXITY: O(len(N)) time, O(1) extra space
// ============================================================

#include <iostream>
#include <string>

using namespace std;

int main() {
    // Fast I/O for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string N;                   // N can be up to 10,000 digits → read as string
    long long X;
    
    // Read N as a string and X as an integer
    if (cin >> N >> X) {
        long long remainder = 0;   // Running remainder, initially 0
        
        // Process each digit from left (most significant) to right
        for (char c : N) {
            int digit = c - '0';                            // Convert char to integer
            remainder = (remainder * 10 + digit) % X;       // Update remainder: shift left by one digit, add new digit, mod X
        }
        
        // If the final remainder is 0, N is perfectly divisible by X
        if (remainder == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
