#include <iostream>       // Include input/output stream library for cin and cout
using namespace std;       // Use standard namespace to avoid writing std:: before every cin/cout

/*
 * LOGIC EXPLANATION:
 *
 * Combination formula: C(N, R) = N! / (R! * (N-R)!)
 *
 * This code computes C(N, R) using an iterative recurrence relation (NOT factorial-based).
 *
 * Recurrence relation used:
 *   C(N, R) = C(N, R-1) * (N - R + 1) / R
 *
 * Base case:
 *   C(N, 0) = 1  (Choosing 0 items from N has exactly 1 way: pick nothing)
 *   C(N, N) = 1  (Choosing all N items from N has exactly 1 way: pick everything)
 *
 * Optimization:
 *   C(N, R) = C(N, N-R), so if R > N-R, we replace R with N-R to reduce recursion depth.
 *   For example: C(10, 8) = C(10, 2) — computing with R=2 is faster than R=8.
 *
 * Example trace for C(5, 2):
 *   C(5,2) = C(5,1) * (5-2+1) / 2 = C(5,1) * 4 / 2
 *   C(5,1) = C(5,0) * (5-1+1) / 1 = C(5,0) * 5 / 1
 *   C(5,0) = 1                            <-- base case
 *   C(5,1) = 1 * 5 / 1 = 5
 *   C(5,2) = 5 * 4 / 2 = 10
 *   Answer: 10
 */

// Function that recursively computes N choose R (C(N, R))
long long nCr(int N, int R) {
    // BASE CASES:
    // If R is 0, we are choosing 0 elements — there is exactly 1 way (pick nothing).
    // If R equals N, we are choosing all elements — there is exactly 1 way (pick everything).
    if (R == 0 || R == N)
        return 1;

    // SYMMETRY OPTIMIZATION:
    // C(N, R) is always equal to C(N, N-R).
    // So if R is greater than N-R (i.e., R > N/2), we replace R with N-R.
    // This cuts down the number of recursive calls roughly in half.
    // Example: C(100, 98) = C(100, 2) — way fewer steps with R=2.
    if (R > N - R)
        R = N - R;

    // RECURSIVE STEP using the recurrence relation:
    //   C(N, R) = C(N, R-1) * (N - R + 1) / R
    //
    // Why this works:
    //   C(N, R)   = N! / (R! * (N-R)!)
    //   C(N, R-1) = N! / ((R-1)! * (N-R+1)!)
    //
    //   Dividing the two:
    //   C(N, R) / C(N, R-1) = ((R-1)! * (N-R+1)!) / (R! * (N-R)!)
    //                       = (N-R+1) / R
    //
    //   Therefore: C(N, R) = C(N, R-1) * (N - R + 1) / R
    //
    // We keep reducing R by 1 each recursive call until we hit the base case (R=0).
    return nCr(N, R - 1) * (N - R + 1) / R;
}

int main() {
    int N, R;                          // N = total items, R = items to choose
    cin >> N >> R;                     // Read N and R from standard input

    // VALIDITY CHECK:
    // You cannot choose R items from N items if R > N — it's impossible.
    // In that case, the combination is defined as 0.
    if (R > N) {
        cout << 0 << endl;            // Invalid combination, output 0
    } else {
        cout << nCr(N, R) << endl;    // Compute and print C(N, R)
    }

    return 0;                          // End of program
}
