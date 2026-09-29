#include <iostream>
#include <bits/stdc++.h>
using namespace std;

    // =========================================================================
    // PROBLEM: Ugly Number I (LeetCode 263)
    // -------------------------------------------------------------------------
    // A number is "ugly" if its prime factors contain ONLY 2, 3, 5.
    //   1 is ugly (by definition, it has no prime factors).
    //   6 = 2*3         -> ugly
    //   8 = 2*2*2       -> ugly
    //   14 = 2*7        -> NOT ugly (has prime factor 7)
    //   n <= 0          -> NOT ugly (only positive numbers can be ugly)
    //
    // Examples: isUgly(6)=true, isUgly(14)=false, isUgly(1)=true.
    // =========================================================================
    // APPROACH / LOGIC: strip out all allowed prime factors
    // -------------------------------------------------------------------------
    // Key idea: if we divide n by 2, 3, 5 as many times as possible, we
    // remove every occurrence of those primes.
    //   - If n was ugly, nothing is left except 1.
    //   - If n had any other prime factor (e.g. 7, 11, 13...), it survives
    //     the divisions, so the remainder will be > 1.
    // So: keep dividing out 2s, then 3s, then 5s. Check remainder == 1.
    //
    // Example dry run:
    //   n = 12 = 2*2*3:
    //     divide by 2 -> 6 -> 3 (no more 2s)
    //     divide by 3 -> 1 (no more 3s)
    //     divide by 5 -> still 1. remainder==1 -> ugly.
    //   n = 14 = 2*7:
    //     divide by 2 -> 7
    //     7 % 3 != 0, 7 % 5 != 0, so remainder = 7 != 1 -> NOT ugly.
    //
    // Time: O(log n) divisions. Space: O(1).
    // =========================================================================
    bool isUgly(int n) {
        // Ugly numbers are defined only for positive integers.
        if (n<= 0 ) return false;

        // Step 1: remove ALL factors of 2.
        // e.g. 12 -> 6 -> 3. Loop stops when n is odd.
        while(n % 2 == 0  ) n /= 2 ;

        // Step 2: remove ALL factors of 3.
        // e.g. 9 -> 3 -> 1. Runs on the already 2-free remainder.
        while(n % 3 == 0 ) n /= 3;

        // Step 3: remove ALL factors of 5.
        while(n % 5 == 0) n /= 5;

        // If n was ugly, only 1 remains. Otherwise the leftover (>1) is
        // 1 or a product of disallowed primes (7, 11, ...), so not ugly.
        return n == 1;

    }

int main(){
    int n;
    cin >> n;
    // Prints 1 (true) if ugly, 0 (false) otherwise.
    cout << isUgly(n) << endl;
    return 0;
}
