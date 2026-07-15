#include <iostream>
#include <algorithm>
using namespace std;

// =========================================================================
// TOPIC: GCD (Greatest Common Divisor) & LCM (Least Common Multiple)
// =========================================================================
//
// GCD(a, b) = largest integer that divides BOTH a and b without remainder.
// LCM(a, b) = smallest positive integer that is a multiple of BOTH a and b.
// =========================================================================

// =========================================================================
// EUCLIDEAN ALGORITHM — Intuition & Derivation
// =========================================================================
//
// THE CORE IDEA:
//   The GCD of two numbers does NOT change if we replace the larger
//   number by the remainder when divided by the smaller number.
//
//   i.e.,  GCD(a, b) = GCD(b, a % b)   for b != 0
//
// WHY THIS WORKS — The Subtractive Insight:
//   If d divides both a and b (d | a and d | b), then d also divides
//   their difference: d | (a - b). Because:
//     a = d * m,  b = d * n  →  a - b = d * (m - n)
//
//   By repeatedly subtracting b from a, we get the remainder.
//   Example: GCD(12, 8)
//     12 - 8 = 4   →   GCD(12, 8) = GCD(8, 4)   (since d|12 & d|8 ⇒ d|4)
//     8 - 4 = 4    →   GCD(8, 4) = GCD(4, 4)
//     4 - 4 = 0    →   GCD(4, 0) = 4
//
//   Subtraction repeated many times = modulo operation! So instead:
//     GCD(a, b) = GCD(b, a % b)
//
//   Example: GCD(12, 8)
//     12 % 8 = 4  →  GCD(8, 4)
//     8 % 4 = 0   →  GCD(4, 0) = 4
//
//   This is MUCH faster than repeated subtraction (O(log min(a,b))).
//
// BASE CASE:
//   GCD(a, 0) = a   because everything divides 0, and a is the
//   greatest number that divides a.
//
// VISUAL PROOF:
//   Let g = GCD(a, b). Then:
//     a = g * x,  b = g * y   where x and y are coprime (GCD(x,y)=1)
//     a % b = a - floor(a/b) * b
//           = g*x - floor(g*x / g*y) * g*y
//           = g*x - floor(x/y) * g*y
//           = g * (x - floor(x/y) * y)
//     So a % b is also a multiple of g. And GCD(b, a%b) = g.
//
// TIME:  O(log min(a,b))  — each step reduces at least one operand by half
// SPACE: O(1) for iterative, O(log n) for recursive (call stack)
// =========================================================================

// Recursive Euclidean Algorithm
//   - Simple, elegant, follows the mathematical definition directly.
//   - RISK: stack overflow for very large recursion depth (unlikely
//     since depth is O(log n), but possible if compiler doesn't
//     optimize tail recursion).
int __gcd(int a, int b) {
    if (b == 0)               // base case: GCD(a, 0) = a
        return a;
    return __gcd(b, a % b);    // recursive: GCD(a,b) = GCD(b, a%b)
}

// Iterative Euclidean Algorithm
//   - Same logic as recursive, but uses a loop instead.
//   - No recursion overhead or stack concerns.
//   - Preferred in competitive programming.
int gcd(int a, int b) {
    while (b != 0) {           // repeat until remainder becomes 0
        int temp = b;          // save current b
        b = a % b;             // new b = remainder of a / b
        a = temp;              // new a = old b
    }
    return a;                  // when b=0, a holds the GCD
}

// =========================================================================
// LCM — Intuition & Formula
// =========================================================================
//
// FORMULA:
//   LCM(a, b) = (a * b) / GCD(a, b)
//
// WHY THIS WORKS — Prime Factorization View:
//   Let a = 2^2 * 3^1 = 12,  b = 2^1 * 3^2 = 18
//
//   GCD = product of MINIMUM exponents: 2^1 * 3^1 = 6
//   LCM = product of MAXIMUM exponents: 2^2 * 3^2 = 36
//
//   Notice: GCD * LCM = (2^1 * 3^1) * (2^2 * 3^2)
//                      = 2^3 * 3^3
//                      = 2^(1+2) * 3^(1+2)
//                      = 2^min + max  * 3^min + max
//                      = (2^2 * 3^1) * (2^1 * 3^2)
//                      = a * b
//
//   So GCD(a,b) * LCM(a,b) = a * b  ⇒  LCM = a * b / GCD
//
// OVERFLOW WARNING:
//   The product a * b can overflow even when the final LCM fits
//   in the data type. Safer order:
//     LCM = (a / GCD) * b    ← divide FIRST, then multiply
//
//   Example: a=1e9, b=1e9 (barely fits in 32-bit)
//     a * b = 1e18 (overflows 32-bit)
//     (a / gcd) * b = (1e9 / 1e9) * 1e9 = 1e9 ✓ (no overflow)
//
//   But for the purpose of this simple program, we stick with
//   the direct formula (x * y) / gcd.
// =========================================================================

int main() {
    int t;
    cin >> t;                   // number of test cases

    while (t--) {
        int x, y;
        cin >> x >> y;          // read two numbers

        int g = __gcd(x, y);    // GCD using Euclidean algorithm

        // LCM = product / GCD
        // SAFER ALTERNATIVE: int lcm = (x / g) * y;
        int lcm = (x * y) / g;

        cout << lcm << " " << g << endl;
    }
    return 0;
}
