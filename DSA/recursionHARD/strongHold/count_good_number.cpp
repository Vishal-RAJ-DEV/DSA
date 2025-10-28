#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
    const long long MOD = 1e9 + 7;  // Modulo value (10^9 + 7) for large number calculations
public:
    // Iterative approach for modular exponentiation
    long long modpow1(long long base, long long pow) {
        long long ans = 1;          // Initialize result to 1 (identity for multiplication)
        base %= MOD;                // Take modulo of base to avoid overflow
        
        while(pow > 0) {            // Continue until power is reduced to 0
            if(pow % 2 == 1) {      // If power is odd
                ans = (ans * base) % MOD;   // Multiply result with current base
                pow -= 1;           // Decrement power by 1 to make it even
            } else {                // If power is even
                base = (base * base) % MOD;  // Square the base
                pow /= 2;           // Halve the power
            }
        }
        return ans;                 // Return final result
    }
    
    // Recursive approach for modular exponentiation
    long long modpow(long long base, long long pow) {
        base %= MOD;                // Take modulo of base to avoid overflow
        if(pow == 0) return 1;      // Base case: anything raised to 0 is 1
        
        if(pow % 2 == 1) {          // If power is odd
            // Calculate base^(pow-1) recursively, then multiply by base
            return (base * modpow(base, pow-1)) % MOD;
        } else {                    // If power is even
            // Calculate (base^2)^(pow/2) recursively
            return modpow((base * base) % MOD, (pow/2)) % MOD;
        }
    }
    
    int countGoodNumbers(long long n) {
        long long even = (n+1)/2;   // Count of even positions (0,2,4,...) in a number of length n
        long long odd = n/2;        // Count of odd positions (1,3,5,...) in a number of length n
        
        long long evenpart = modpow(5, even);  // 5^even (5 options for even positions: 0,2,4,6,8)
        long long oddpart = modpow(4, odd);    // 4^odd (4 options for odd positions: 2,3,5,7)
        
        return (evenpart * oddpart) % MOD;     // Total combinations = 5^even * 4^odd
    }
};
int main(){
    Solution sol;
    long long n;
    cout<<"enter the value of n: "<<endl;
    cin>>n;
    cout<<"count of good numbers of length "<<n<<" is: "<<sol.countGoodNumbers(n)<<endl;
    return 0;
}
