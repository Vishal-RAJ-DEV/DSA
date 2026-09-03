/*
 * Problem: Sum of Decoded Numbers
 *
 * Each number in the array is an ENCODED value. We need to decode each
 * number and return the sum of all decoded values (mod 10^9 + 7).
 *
 * Encoding Format:
 *   A number is encoded as: [d][w]
 *   where:
 *     - w = last digit (exponent info)    -> num % 10
 *     - d = remaining digits (base info)  -> num / 10
 *
 *   The value of d is further split into base (x) and exponent (y):
 *     - Count digits in d -> let that be `digit`
 *     - div = 10^(digit - w)  (determines where to split d)
 *     - x = d / div  (the BASE)
 *     - y = d % div  (the EXPONENT)
 *     - Decoded value = x^y
 *
 * Example Encoding/Decoding:
 *   num = 2341
 *   w = 2341 % 10 = 1
 *   d = 2341 / 10 = 234
 *   digit = 3 (234 has 3 digits)
 *   div = 10^(3-1) = 100
 *   x = 234 / 100 = 2    (base)
 *   y = 234 % 100 = 34   (exponent)
 *   Decoded = 2^34
 *
 *   num = 1293
 *   w = 1293 % 10 = 3
 *   d = 1293 / 10 = 129
 *   digit = 3
 *   div = 10^(3-3) = 1
 *   x = 129 / 1 = 129
 *   y = 129 % 1 = 0
 *   Decoded = 129^0 = 1
 *
 * Approach:
 *   1. For each number, extract w and d.
 *   2. Count digits in d to compute div = 10^(digit - w).
 *   3. Split d into base x and exponent y using div.
 *   4. Compute x^y using fast exponentiation (binary exponentiation).
 *   5. Sum all decoded values modulo MOD.
 *
 * Fast Exponentiation (Binary Exponentiation):
 *   Instead of computing x^y by multiplying y times (O(y)),
 *   we use the binary representation of y:
 *     - If y is odd:  result = result * x
 *     - Square x:     x = x * x
 *     - Halve y:      y = y / 2
 *   This reduces time complexity to O(log y).
 *
 * Time Complexity:  O(n * log(max_exponent)) - for n numbers, each with fast pow
 * Space Complexity: O(1) - constant extra space
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    using ll = long long;

    // Modulo constant for large number arithmetic (10^9 + 7)
    static const long long MOD = 1000000007LL;

    // Fast exponentiation using Binary Exponentiation method.
    // Computes (x^y) % MOD in O(log y) time.
    //
    // How it works:
    //   Express y in binary: y = b_k * 2^k + ... + b_1 * 2 + b_0
    //   Then x^y = x^(b_k * 2^k) * ... * x^(b_1 * 2) * x^(b_0)
    //
    //   We iterate through bits of y:
    //     - If current bit is 1 (y is odd): multiply result by current x
    //     - Square x at each step (x -> x^2 -> x^4 -> x^8 ...)
    //     - Right-shift y (y = y / 2)
    long long power(long long x, long long y) {
        long long res = 1;

        // Take x modulo MOD to prevent overflow
        x %= MOD;

        while (y > 0) {
            // If y is odd, multiply current x with result
            if (y % 2 == 1) {
                res = (res * x) % MOD;
            }

            // Square x for next bit position
            x = (x * x) % MOD;

            // Move to next bit of y
            y /= 2;
        }

        return res;
    }

    int sumDecoded(vector<long long>& nums) {
        ll ans = 0;

        // Process each encoded number
        for (ll num : nums) {
            // Extract the last digit as 'w' (used to determine split position)
            ll w = num % 10;

            // Extract the remaining digits as 'd' (contains base and exponent info)
            ll d = num / 10;

            // Count the number of digits in d
            // This helps us calculate where to split d into base and exponent
            int digit = 0;
            ll temp = d;
            while (temp > 0) {
                digit++;
                temp /= 10;
            }

            // Calculate div = 10^(digit - w)
            // This divisor determines the split point in d:
            //   - x (base)  = d / div  -> first (digit - w) digits of d  (actually w digits form y)
            //   - y (exponent) = d % div -> last (digit - w) digits of d
            ll div = 1;
            for (int i = 0; i < digit - w; i++) {
                div *= 10;
            }

            // Split d into base (x) and exponent (y)
            ll x = d / div;  // Base: the higher-order digits
            ll y = d % div;  // Exponent: the lower-order digits

            // Decode the number: decoded = x^y
            ll decode = power(x, y);

            // Add to running sum (with modulo to prevent overflow)
            ans = (ans + decode) % MOD;
        }

        return ans;
    }
};

int main(){
    return 0;
}