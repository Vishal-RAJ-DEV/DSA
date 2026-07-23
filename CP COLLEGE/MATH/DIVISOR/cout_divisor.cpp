#include <bits/stdc++.h>
using namespace std;

// -------------------- Typedefs --------------------
using ll = long long;
using ull = unsigned long long;
using ld = long double;

using pii = pair<int,int>;
using pll = pair<ll,ll>;

using vi = vector<int>;
using vll = vector<ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;

// -------------------- Constants --------------------
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

// -------------------- Macros --------------------
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

// -------------------- Fast IO --------------------
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

// -------------------- Input --------------------
template<typename T>
void input(vector<T> &v) {
    for (auto &x : v)
        cin >> x;
}

// -------------------- Output --------------------
template<typename T>
void print(vector<T> &v) {
    for (auto x : v)
        cout << x << " ";
    cout << '\n';
}

// ================================================================
// QUESTION: Count Divisors
// Given an integer n, find the total number of positive divisors of n.
//
// FORMULA (Fundamental Theorem of Arithmetic):
//   If n = p1^e1 * p2^e2 * ... * pk^ek  (prime factorization),
//   then number of divisors = (e1+1) * (e2+1) * ... * (ek+1).
//
//   Reason: Each divisor uses exponent fi where 0 <= fi <= ei,
//   giving (ei+1) choices per prime factor. Multiply all choices.
// ================================================================

// ================================================================
// ALGORITHM EXPLANATION
// ================================================================
//
// We find prime factors by trial division up to sqrt(n).
//
// WHY sqrt(n)?
//   If n has a prime factor p > sqrt(n), then its co-factor n/p must
//   be < sqrt(n). That smaller factor would have already been found
//   by the loop. The only way there's a leftover > sqrt(n) is if
//   n itself is a prime (or 1) after dividing out all small factors.
//   A prime > sqrt(original n) has exponent 1 and contributes *2.
//
// TRACE FOR n = 12:
//   Initial: n = 12, ans = 1
//
//   i = 2:
//     check: 2*2 <= 12 → 4 <= 12 ✓  (enter loop)
//     12 % 2 == 0:
//       cnt = 0
//       while(12 % 2 == 0): cnt=1,  n=6
//       while(6 % 2 == 0):  cnt=2,  n=3
//       → n = 3, cnt = 2
//       ans *= (2+1) = 3
//
//   i = 3 (incremented by for loop):
//     check: 3*3 <= n → 9 <= 3 ✗
//     → LOOP STOPS IMMEDIATELY. i=3 is never processed inside.
//
//   But 3 is a prime factor of 12 with exponent 1!
//   How is it counted?
//
//   After loop: n = 3
//   Since n > 1, we know the remaining n is a prime factor left over
//   (it was never divided out because the loop only goes up to sqrt(n),
//   and sqrt(3) ≈ 1.73, so i=2 was already past sqrt(3) when n became 3).
//
//   This leftover prime has exponent exactly 1, so it contributes
//   (1+1) = 2 to ans.
//
//   ans *= 2 → ans = 3 * 2 = 6
//
//   Final: ans = 6
//   Verification: divisors of 12 = {1,2,3,4,6,12} → count = 6 ✓
//
// KEY INSIGHT:
//   The loop condition i*i <= n is evaluated FRESH each iteration.
//   When n shrinks (from dividing out factors), the upper bound
//   sqrt(n) also shrinks. This means the loop terminates earlier
//   than it would have for the original n.
//
//   The final if(n > 1) catches any remaining prime factor that is
//   > sqrt(the current n). This factor must be prime because any
//   composite factor > sqrt(n) would have a co-factor < sqrt(n)
//   that would have been divided out already.
// ================================================================

// -------------------- Solve --------------------
void solve() {
    int n;
    cin >> n;                     // read the number

    int ans = 1;                  // start with multiplicative identity

    // Only check up to sqrt(current n) — i*i <= n
    // IMPORTANT: n changes inside the loop (n /= i), so the upper
    // bound sqrt(n) gets smaller as we divide out factors.
    for (int i = 2; i * i <= n; i++) {

        if (n % i == 0) {         // i is a prime factor of current n

            int cnt = 0;          // count exponent of prime i

            // Divide out ALL occurrences of prime i from n
            while (n % i == 0) {
                cnt++;
                n /= i;
            }

            // Each prime factor pi^ei contributes (ei+1) ways
            ans *= (cnt + 1);
        }
    }

    // After the loop, if n > 1, the remaining n is a prime factor
    // with exponent exactly 1.
    //
    // Why? Because:
    //   - If n were composite, it would have a prime factor <= sqrt(n)
    //     which the loop would have found. But the loop ended because
    //     i*i > n, meaning n has NO factors <= sqrt(n).
    //   - Therefore n itself is prime (or 1).
    //   - Since we keep dividing, all smaller factors are removed,
    //     leaving either 1 or a single prime factor.
    //
    // A prime with exponent 1 contributes (1+1) = 2 to the product.
    if (n > 1)
        ans *= 2;

    cout << ans << endl;
}

// -------------------- Main --------------------
int main() {

    fastIO();

    int t = 1;
    cin >> t;                     // number of test cases

    while (t--) {
        solve();
    }

    return 0;
}

/*
===============================================================
DETAILED EXAMPLE WALKTHROUGH: n = 12

Step 1: ans = 1, n = 12

Step 2: i = 2
        check: 2*2 <= 12 → 4 <= 12 ✓
        12 % 2 == 0 → cnt = 0
          while(12 % 2 == 0): cnt=1, n=6
          while(6 % 2 == 0):  cnt=2, n=3
          exit while (3 % 2 != 0)
        ans *= (2+1) = 3
        n = 3

Step 3: i = 3 (for loop increments i)
        check: 3*3 <= n → 9 <= 3 ✗
        → LOOP EXITS immediately.
        i=3 never enters the loop body.

Step 4: After loop, n = 3
        3 > 1 → ans *= 2 → ans = 3 * 2 = 6

Step 5: Output 6

WHY WAS i=3 NOT PROCESSED IN THE LOOP?
  1. The loop condition i*i <= n is CHECKED AT THE START of each
     iteration (including before iteration i=3).
  2. After i=2 ran, n changed from 12 to 3.
  3. Now 3*3 = 9 > 3, so the condition fails → loop terminates.
  4. The remaining n=3 IS a prime factor, but it's "above" the
     current sqrt(n) bound (~1.73), so the loop never reaches it.

  5. The if(n > 1) after the loop is specifically designed for
     this case. It catches the leftover prime that's > sqrt(n).
     Its exponent is 1 because if it had exponent >= 2, then
     i = sqrt(n) would have been <= sqrt(original n) and the
     loop would have found it.

===============================================================
EXAMPLE: n = 84 = 2^2 * 3 * 7

i=2: divides 84 → cnt=2 (84→42→21), ans=3, n=21
i=3: divides 21 → cnt=1 (21→7),    ans=6, n=7
i=4: 4*4=16 > 7 → loop exits
n=7 > 1 → ans *= 2 → ans = 12
Divisors of 84 = 12 ✓  (1,2,3,4,6,7,12,14,21,28,42,84)

===============================================================
TIME COMPLEXITY ANALYSIS

Claim: The overall time is O(sqrt(n)) per test case,
       even with the nested while loop.

WHY THE WHILE LOOP DOES NOT MAKE IT O(n log n):

Let's analyze the TWO loops:

   1. for (int i = 2; i * i <= n; i++)    → runs at most sqrt(n) times
   2. while (n % i == 0) { n /= i; }      → runs ?? times per i

Naively, it looks like O(sqrt(n) * log n), but that's WRONG.

KEY INSIGHT — n SHRINKS GLOBALLY:

  The while loop divides n by i repeatedly. Every division reduces n.
  Crucially, n is SHARED across ALL for-loop iterations — it's the same
  variable that only decreases. So the TOTAL number of while-loop
  iterations across the ENTIRE function is bounded by log2(n).

  Why? Because each while iteration does n /= i (at minimum n /= 2),
  which at least halves n. You can only halve a number ~log2(n) times
  before it reaches 1.

  VISUALIZE THE TOTAL WORK:

    n_original = N

    while loops divide out factors:
      - All factors of 2: n /= 2 repeatedly → at most log2(N) divisions
      - All factors of 3: n /= 3 repeatedly → fewer divisions (n is smaller now)
      - All factors of 5: even fewer
      - ...and so on

    The sum of ALL while-loop iterations across ALL i is O(log N),
    NOT O(number_of_factors * log N).

  Meanwhile, the for-loop runs at most sqrt(N) times (worst case: N is
  prime, so the while-loop never runs, but the for-loop goes all the way
  to sqrt(N) checking every i).

TOTAL = O(sqrt(N)) [for-loop] + O(log N) [while-loop total] = O(sqrt(N))

  Since sqrt(N) grows much faster than log N, the for-loop dominates,
  and the overall complexity is O(sqrt(N)).

CONCRETE EXAMPLE: n = 2^20 = 1,048,576

  The for-loop checks i from 2 to sqrt(n) ≈ 1024 → about 1023 iterations.

  The while-loop only runs for i=2, dividing 20 times (exponent of 2).
  Total while iterations across entire function = 20 ≈ log2(n).

  So total work ≈ 1023 + 20 ≈ 1043, which is O(sqrt(n)).

EDGE CASE — PRIME NUMBER (worst case for for-loop):

  n = 999,983 (a prime)
  The while-loop NEVER runs (n % i != 0 for any i).
  The for-loop runs from i=2 to sqrt(n) ≈ 1000 → ~1000 iterations.
  Total work ≈ 1000 = O(sqrt(n)).

EDGE CASE — POWERS OF 2 (worst case for while-loop):

  n = 2^30 ≈ 1e9
  The for-loop finds i=2, then the while-loop divides 30 times.
  After that, n = 1, so i*i <= 1 fails immediately → loop ends.
  Total work ≈ 30 iterations = O(log n).

BEST CASE — SMALL FACTORS:

  n has many small prime factors → n shrinks fast → for-loop ends early.
  Example: n = 2 * 3 * 5 * 7 * 11 * 13 = 30030
  After i=2, n=15015; after i=3, n=5005; after i=5, n=1001;
  after i=7, n=143; after i=11, n=13; i*i=169 > 13 → exit for-loop.
  Then if(n>1) catches 13.
  Total work is far less than sqrt(30030) ≈ 173.

SUMMARY:
  - for-loop: O(sqrt(n))     — dominated by prime-number worst case
  - while-loop total: O(log n) — across entire function, n only shrinks
  - Overall: O(sqrt(n) + log n) = O(sqrt(n))

Space Complexity: O(1) — only a few integer variables
*/
