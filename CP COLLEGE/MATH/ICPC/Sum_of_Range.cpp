#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    int64 A, B;
    cin >> A >> B;

    /*
        FORMULA: Arithmetic Progression (AP) Sum Formula

        If a sequence has:
            First term = a
            Last term  = l
            Number of terms = n

        Then the sum is:

                n (a + l)
            S = ---------
                    2

        This works because the numbers are equally spaced.

        --- Why does the formula work? (Intuition) ---

        Consider:  1 + 2 + 3 + 4 + 5

        Write them in reverse underneath:

            1 + 2 + 3 + 4 + 5
            5 + 4 + 3 + 2 + 1
            -----------------
            6 + 6 + 6 + 6 + 6

        Each column sums to 6 (= first + last), and there are 5 columns.

        So,  2 * S = 5 * 6
                S = (5 * 6) / 2 = 15

        Generalizing:
            2 * S = n * (first + last)
                S = n * (first + last) / 2
    */
    int64 l = min(A, B);
    int64 r = max(A, B);

    /*
        TOTAL SUM of all integers from l to r (inclusive)

        Example: l=4, r=6
        Sequence: 4, 5, 6
        First = 4, Last = 6, n = (6 - 4 + 1) = 3

        total = (4 + 6) * 3 / 2 = 10 * 3 / 2 = 15
    */
    int64 total = (l + r) * (r - l + 1) / 2;

    // --- EVEN SUM ---
    // First even number in the range (round up to nearest even)
    int64 firstEven = (l % 2 == 0) ? l : l + 1;
    // Last even number in the range (round down to nearest even)
    int64 lastEven  = (r % 2 == 0) ? r : r - 1;

    int64 evenSum = 0;

    if (firstEven <= lastEven) {
        /*
            Even numbers within [l, r] form an AP with common difference 2.

            Example: l=4, r=10
            Even numbers: 4, 6, 8, 10
            firstEven = 4, lastEven = 10

            Number of terms:
                cnt = (10 - 4) / 2 + 1 = 3 + 1 = 4

            Sum:
                evenSum = 4 * (4 + 10) / 2 = 4 * 14 / 2 = 28
        */
        int64 cnt = (lastEven - firstEven) / 2 + 1;
        evenSum = cnt * (firstEven + lastEven) / 2;
    }

    // --- ODD SUM ---
    // Odd sum = Total sum - Even sum
    int64 oddSum = total - evenSum;

    cout << total << "\n";
    cout << evenSum << "\n";
    cout << oddSum << "\n";

    return 0;
}