/*
 * Problem: Concatenate Binary Representations
 * 
 * Given an integer n, concatenate the binary representations of all integers 
 * from 1 to n in order and return the resulting binary string as a decimal integer.
 * 
 * Example: n = 3
 * 1 -> "1", 2 -> "10", 3 -> "11"
 * Concatenated: "11011" -> 27 (in decimal)
 * 
 * Constraints: Result should be returned modulo 10^9 + 7
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Approach 1: Optimized approach using power of 2 detection
class Solution {
    int mod = 1e9 + 7;
public:
    int concatenatedBinary(int n) {
        long long ans = 0;
        int shifts = 0;  // Number of bits required for current number
        
        for(int i = 1; i <= n; i++) {
            // Check if i is a power of 2 using bit manipulation
            // If i & (i-1) == 0, then i is a power of 2
            // Powers of 2: 1(1bit), 2(2bits), 4(3bits), 8(4bits), etc.
            if((i & (i - 1)) == 0) {
                shifts++;  // Increment bit length when we reach next power of 2
            }
            
            // Concatenate binary representation:
            // 1. Left shift current answer by 'shifts' bits to make space
            // 2. Add current number i to fill the created space
            // Example: ans=1("1"), i=2("10") with 2 bits
            // ans << 2 = "100", then "100" + "10" = "110" (binary of 6)
            ans = ((ans << shifts) % mod + i) % mod;
        }

        // Return result as integer (binary representation is conceptual,
        // actual storage is in decimal format)
        return (int)ans;
    }
};

// Approach 2: Direct bit counting approach
class Solution1 {
    int mod = 1e9 + 7;
public:
    int concatenatedBinary(int n) {
        long long ans = 0;
        
        for(int i = 1; i <= n; i++) {
            // Count the number of bits required to represent number i
            int shifts = 0;
            int num = i;
            
            // Count bits by right shifting until number becomes 0
            while(num) {
                num = num >> 1;  // Right shift: removes rightmost bit (equivalent to num/2)
                shifts++;         // Count each bit
            }
            
            // Concatenate binary representation:
            // 1. Shift current answer left by 'shifts' bits to make space for new number
            // 2. Add the current number i to the shifted result
            // Example: ans=1("1"), i=2("10") needs 2 bits
            // ans << 2 = "100", then "100" + "10" = "110" (decimal 6)
            ans = ((ans << shifts) % mod + i) % mod;  // Apply modulo to prevent overflow
        }
        
        // Return result as integer (binary is conceptual, stored as decimal)
        return (int)ans;
    }
};

int main() {
    int n = 3;  // Example: concatenate binary of numbers 1, 2, 3
                // 1 -> "1", 2 -> "10", 3 -> "11" 
                // Concatenated: "11011" = 27 in decimal
    
    Solution obj;
    cout << "Result: " << obj.concatenatedBinary(n) << endl;
    
    return 0;
}
