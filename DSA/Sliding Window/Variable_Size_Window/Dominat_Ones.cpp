#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    ========================================================================
    PROBLEM: Count Substrings Where Ones Dominate
    ========================================================================
    Given a binary string s (only '0' and '1'), count the number of substrings
    where the number of '1's is at least the SQUARE of the number of '0's.

    Condition:  ones >= zeros²

    A substring s[i...j] is valid iff:
        count('1' in [i,j])  >=  (count('0' in [i,j]))²

    ========================================================================
    WHY THIS CONDITION?
    ========================================================================
    "Dominant ones" means ones dominate zeros so strongly that even squaring
    the zero count doesn't surpass the one count. This is a much stricter
    condition than just ones >= zeros (which would be trivial).

    ========================================================================
    INTUITION & BRUTE FORCE
    ========================================================================
    O(n²) approach: check every substring [i,j], compute ones/zeros via
    prefix sum, validate condition. For n = 10⁵, O(n²) is too slow.

    ========================================================================
    OPTIMIZATION INSIGHT — Skip & Shift
    ========================================================================
    When we fix the start i and scan j from i to n-1, the substring grows.
    As j increases, zeros and ones both change. We can PREDICT how far we
    can jump without checking every position:

    There are three possible cases for substring [i,j]:

    ┌─────────────────────────────────────────────────────────────────────┐
    │ CASE 1: zeros² > ones  (INVALID — too few ones for the zeros)      │
    │     We need more '1's. Each new char adds AT MOST 1 one.           │
    │     Deficit = zeros² - ones  (minimum ones still needed)           │
    │     Skip = deficit positions ahead (optimistic — assumes all '1')  │
    │     j += deficit - 1  (loop does j++, so total skip = deficit)     │
    │                                                                     │
    │ CASE 2: zeros² == ones  (EXACTLY VALID)                            │
    │     Count it and continue to next j naturally (j++).               │
    │                                                                     │
    │ CASE 3: zeros² < ones   (VALID — surplus of ones)                  │
    │     Current substring is valid. We can EXTEND j further and the    │
    │     substring may STAY valid for several more positions.           │
    │                                                                     │
    │     Worst case: all new chars are '0' (zeros increase, ones fixed).│
    │     We remain valid while: (zeros + k)² ≤ ones                     │
    │                          →  zeros + k ≤ √ones                     │
    │                          →  k ≤ √ones - zeros                     │
    │                                                                     │
    │     shift = floor(√ones) - zeros  ← max safe extension             │
    │     Count shift additional substrings [i,j+1]...[i,j+shift].       │
    │     Jump j to j + shift (last valid position).                     │
    └─────────────────────────────────────────────────────────────────────┘

    ========================================================================
    VISUAL TRACE
    ========================================================================
    s = "11100", n = 5
    cntOnes = [1, 2, 3, 3, 3]

    i=0:
      j=0 (val='1'): ones=1, zeros=0, 0<1 → CASE 3
        result+=1 ([0,0])
        shift=√1-0=1, next=1, result+=1 ([0,1]), j=1, j++→2

      j=2 (val='1'): ones=3, zeros=0, 0<3 → CASE 3
        result+=1 ([0,2])
        shift=√3-0=1, next=3, result+=1 ([0,3]), j=3, j++→4

      j=4 (val='0'): ones=3, zeros=2, 4>3 → CASE 1
        skipIdx=4-3=1, j+=0, j=4, j++→5 exit
      → i=0 contributed 4 substrings

    i=1:
      j=1: ones=2, zeros=0, 0<2 → CASE 3, result+=1 ([1,1])
        shift=√2-0=1, next=2, result+=1 ([1,2]), j=2, j++→3
      j=3: ones=2, zeros=1, 1<2 → CASE 3, result+=1 ([1,3])
        shift=√2-1=0, result+=0, j=3, j++→4
      j=4: ones=2, zeros=2, 4>2 → CASE 1
        skipIdx=4-2=2, j+=1, j=5 exit
      → i=1 contributed 3 substrings

    i=2: contributes 2 ([2,2], [2,3])
    i=3: contributes 0
    i=4: contributes 0
    Total = 9

    Brute force verification: 9 valid substrings ✓

    ========================================================================
    TIME & SPACE COMPLEXITY
    ========================================================================
    Time:  O(n · √n) in worst case — each i may skip many positions,
           but the inner loop advances at least 1 step per skip.
           More precisely, it's much faster than O(n²) because large
           skips avoid checking every position.
    Space: O(n) for the prefix sum array.

    ========================================================================
    IMPORTANT NOTE ON sqrt(ones)
    ========================================================================
    C++ sqrt(double) can have floating-point precision issues for
    perfect squares (e.g., sqrt(25) might give 4.9999999 instead of 5.0).
    We use intSqrt() below with a small epsilon correction to ensure
    correct floor value.
    */

private:
    // Integer square root (floor) — safe from floating-point errors
    int intSqrt(int x) {
        int r = (int)sqrt(x);
        // Adjust if floating-point rounding gave us the wrong value
        while ((long long)(r + 1) * (r + 1) <= x) r++;
        while ((long long)r * r > x) r--;
        return r;
    }

public:
    int numberOfSubstrings(string s) {
        int n = s.size();

        // ─────────────────────────────────────────────────────────────
        // Step 1: Build prefix sum of ones count
        // cntOnes[i] = total number of '1' in s[0...i]
        // ─────────────────────────────────────────────────────────────
        vector<int> cntOnes(n, 0);
        cntOnes[0] = (s[0] == '1') ? 1 : 0;
        for (int i = 1; i < n; i++) {
            cntOnes[i] = cntOnes[i - 1] + ((s[i] == '1') ? 1 : 0);
        }

        int result = 0;

        // ─────────────────────────────────────────────────────────────
        // Step 2: Fix start i, expand j rightwards
        // ─────────────────────────────────────────────────────────────
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {

                // Count of '1's in substring s[i...j] via prefix sum
                int ones = cntOnes[j] - ((i - 1 >= 0) ? cntOnes[i - 1] : 0);
                // Count of '0's = total length - ones
                int zeros = (j - i + 1) - ones;

                // ─────────────────────────────────────────────────────
                // CASE 1: zeros² > ones  → INVALID
                // ─────────────────────────────────────────────────────
                // We need (deficit) more '1's to satisfy the condition.
                // Each new character adds at most one '1', so we skip
                // ahead by deficit positions (optimistic — assumes all
                // skipped chars are '1'; if not, we'll re-check and
                // skip again in a later iteration).
                if ((long long)zeros * zeros > ones) {
                    int deficit = (long long)zeros * zeros - ones;
                    // Loop does j++, so we only add deficit-1 here
                    j += deficit - 1;
                    // Clamp j to n-1 to avoid overflow/out-of-bounds
                    if (j >= n) j = n - 1;
                }

                // ─────────────────────────────────────────────────────
                // CASE 2: zeros² == ones → EXACTLY VALID
                // ─────────────────────────────────────────────────────
                else if ((long long)zeros * zeros == ones) {
                    result += 1;  // count this substring
                }

                // ─────────────────────────────────────────────────────
                // CASE 3: zeros² < ones  → VALID with surplus
                // ─────────────────────────────────────────────────────
                else {
                    result += 1;  // count current substring [i, j]

                    // How many MORE characters can we append (in the
                    // worst case where all are '0') before the condition
                    // breaks?
                    // Need: (zeros + k)² ≤ ones
                    //     → zeros + k ≤ √ones
                    //     → k ≤ √ones - zeros
                    int shift = intSqrt(ones) - zeros;
                    int next = j + shift;

                    if (next >= n - 1) {
                        // All remaining substrings [i,j+1]...[i,n-1]
                        // are valid — count them all and break to
                        // move to the next start position i.
                        result += (n - 1 - j);
                        break;
                    } else {
                        // Count 'shift' additional valid substrings:
                        // [i,j+1], [i,j+2], ..., [i,j+shift]
                        result += shift;
                    }

                    // Jump j to the last valid position.
                    // The loop's j++ will advance to the first
                    // position that needs re-checking.
                    j = next;
                }
            }
        }

        return result;
    }
};


int main(){
    Solution sol;

    auto run = [&](const string& s, int expected) {
        int got = sol.numberOfSubstrings(s);
        cout << "s = \"" << s << "\" → " << got
             << " (expected " << expected << ")"
             << (got == expected ? " ✓" : " ✗") << endl;
    };

    // Test 1: All ones — every substring is valid
    run("111", 6);     // 3+2+1 = 6

    // Test 2: All zeros — no valid substring
    run("000", 0);

    // Test 3: Mixed — trace example from comments
    run("11100", 9);   // verified by manual trace

    // Test 4: Single '1'
    run("1", 1);       // [0,0] only

    // Test 5: Single '0'
    run("0", 0);

    // Test 6: Alternating
    run("1010", 6);    // verified by brute force

    // Test 7: Longer alternating
    run("10101", 9);   // verified by brute force

    // Test 8: LeetCode-style example (three 0's then four 1's)
    run("0001111", 15); // verified by brute force

    // Test 9: Empty string (edge case)
    run("", 0);

    return 0;
}
