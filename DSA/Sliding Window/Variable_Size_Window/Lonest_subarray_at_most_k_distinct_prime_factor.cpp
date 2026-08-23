/*
================================================================================
PROBLEM: Longest Subarray with at Most K Distinct Prime Factors
================================================================================

Given an array of integers, find the length of the longest subarray where
the total number of DISTINCT prime factors across ALL elements in the
subarray is at most k.

APPROACH (3 phases):
  Phase 1: Build SPF (Smallest Prime Factor) array using Sieve
  Phase 2: Precompute distinct prime factors for each number using SPF
  Phase 3: Sliding window tracking distinct prime count

================================================================================
PART 1: SMALLEST PRIME FACTOR (SPF) - SIEVE OF ERATOSTHENES
================================================================================

What is SPF?
  spf[x] = smallest prime factor of x
  Example: spf[12] = 2  (2 is smallest prime dividing 12)
           spf[9]  = 3  (3 is smallest prime dividing 9)
           spf[7]  = 7  (7 is prime, so its smallest factor is itself)

Why do we need SPF?
  To quickly factorize any number into distinct prime factors.
  Without SPF: O(sqrt(x)) per number to factorize
  With SPF:    O(log x) per number to factorize (just keep dividing by spf)

STEP-BY-STEP SPF BUILDING (mx = 12 as example):
--------------------------------------------------

STEP 1: Initialize spf[i] = i for all i

  Index:  0  1  2  3  4  5  6  7  8  9  10  11  12
  SPF:   [0][1][2][3][4][5][6][7][8][9][10][11][12]
           ^  ^  ^  ^  ^  ^  ^  ^  ^  ^   ^   ^   ^
           x  x  P  P  x  P  x  P  x  P   x   P   x
  (P=prime, x=composite. Primes start as their own SPF.)

STEP 2: Sieve - for each prime i, mark its unvisited multiples

  i=2: spf[2]==2? YES (2 is prime)
    Mark: 4->2, 6->2, 8->2, 10->2, 12->2

  Index:  0  1  2  3  4  5  6  7  8  9  10  11  12
  SPF:   [0][1][2][3][2][5][2][7][2][9][ 2][11][ 2]
                       ^        ^       ^        ^
                    4=2*2     6=2*3   10=2*5   12=2*6

  i=3: spf[3]==3? YES (3 is prime)
    Mark: 9->3 (12 already has spf=2, SKIP)

  Index:  0  1  2  3  4  5  6  7  8  9  10  11  12
  SPF:   [0][1][2][3][2][5][2][7][2][3][ 2][11][ 2]
                                       ^
                                    9=3*3

  i=4: 4*4=16 > 12 -> STOP

  FINAL SPF: [0][1][2][3][2][5][2][7][2][3][2][11][2]

================================================================================
PART 2: HOW getFactors() WORKS USING SPF
================================================================================

To factorize x into DISTINCT primes:
  1. Look up p = spf[x]  (smallest prime dividing x)
  2. Add p to factors list
  3. Divide out ALL occurrences of p from x (while x % p == 0, x /= p)
  4. Repeat until x == 1

  getFactors(12, spf):
    x=12, p=spf[12]=2, factors=[2], divide: 12/2=6, 6/2=3 (stop), x=3
    x=3,  p=spf[3]=3,  factors=[2,3], divide: 3/3=1, x=1
    x=1 -> STOP. Return [2, 3]

    12 -> spf=2 -> 6 -> spf=2 -> 3 -> spf=3 -> 1 -> STOP
           add 2                      add 3

  getFactors(9, spf):
    x=9, p=3, factors=[3], 9/3=3, 3/3=1 -> STOP. Return [3]

  getFactors(8, spf):
    x=8, p=2, factors=[2], 8/2=4/2=2/2=1 -> STOP. Return [2]

================================================================================
PART 3: FULL SLIDING WINDOW TRACE (nums = [6, 8, 9, 4, 12], k = 2)
================================================================================

Precomputed factors:
  nums[0]=6  -> [2, 3]     nums[3]=4  -> [2]
  nums[1]=8  -> [2]        nums[4]=12 -> [2, 3]
  nums[2]=9  -> [3]

Initial: left=0, distinct=0, ans=0

STEP 1: right=0, nums[0]=6, factors=[2,3]
  ADD: freq[2]: 0->1 (NEW, distinct:0->1), freq[3]: 0->1 (NEW, distinct:1->2)
  Window: [6], distinct=2 <= 2 OK
  freq={2:1, 3:1}, ans=max(0,1)=1

  ┌───┐
  │ 6 │  distinct={2,3}=2  <=k=2
  └───┘
  L=0 R=0  window_len=1  ans=1

STEP 2: right=1, nums[1]=8, factors=[2]
  ADD: freq[2]: 1->2 (already present, no new distinct)
  Window: [6,8], distinct=2 <= 2 OK
  freq={2:2, 3:1}, ans=max(1,2)=2

  ┌───┬───┐
  │ 6 │ 8 │  distinct={2,3}=2  <=k=2
  └───┴───┘
  L=0 R=1  window_len=2  ans=2

STEP 3: right=2, nums[2]=9, factors=[3]
  ADD: freq[3]: 1->2 (already present, no new distinct)
  Window: [6,8,9], distinct=2 <= 2 OK
  freq={2:2, 3:2}, ans=max(2,3)=3

  ┌───┬───┬───┐
  │ 6 │ 8 │ 9 │  distinct={2,3}=2  <=k=2
  └───┴───┴───┘
  L=0 R=2  window_len=3  ans=3

STEP 4: right=3, nums[3]=4, factors=[2]
  ADD: freq[2]: 2->3 (already present, no new distinct)
  Window: [6,8,9,4], distinct=2 <= 2 OK
  freq={2:3, 3:2}, ans=max(3,4)=4

  ┌───┬───┬───┬───┐
  │ 6 │ 8 │ 9 │ 4 │  distinct={2,3}=2  <=k=2
  └───┴───┴───┴───┘
  L=0 R=3  window_len=4  ans=4

STEP 5: right=4, nums[4]=12, factors=[2,3]
  ADD: freq[2]: 3->4 (no new), freq[3]: 2->3 (no new)
  Window: [6,8,9,4,12], distinct=2 <= 2 OK
  freq={2:4, 3:3}, ans=max(4,5)=5

  ┌───┬───┬───┬───┬────┐
  │ 6 │ 8 │ 9 │ 4 │ 12 │  distinct={2,3}=2  <=k=2
  └───┴───┴───┴───┴────┘
  L=0 R=4  window_len=5  ans=5

FINAL ANSWER: 5

================================================================================
WINDOW SHRINKING TRACE (nums = [2, 3, 5, 7], k = 2)
================================================================================

Precomputed factors: [2], [3], [5], [7]
Initial: left=0, distinct=0, ans=0

STEP 1: right=0, nums[0]=2, factors=[2]
  ADD: freq[2]: 0->1 (NEW, distinct:0->1)
  distinct=1 <= 2 OK. Window=[2]. ans=1

  ┌───┐
  │ 2 │  distinct={2}=1  OK
  └───┘
  L=0 R=0  ans=1

STEP 2: right=1, nums[1]=3, factors=[3]
  ADD: freq[3]: 0->1 (NEW, distinct:1->2)
  distinct=2 <= 2 OK. Window=[2,3]. ans=2

  ┌───┬───┐
  │ 2 │ 3 │  distinct={2,3}=2  OK
  └───┴───┘
  L=0 R=1  ans=2

STEP 3: right=2, nums[2]=5, factors=[5]  *** MUST SHRINK ***
  ADD: freq[5]: 0->1 (NEW, distinct:2->3)
  distinct=3 > 2 NOT OK!

  ┌───┬───┬───┐
  │ 2 │ 3 │ 5 │  distinct={2,3,5}=3  NOT OK!
  └───┴───┴───┘

  SHRINK 1: Remove nums[left=0]=2, factors=[2]
    freq[2]: 1->0 (prime 2 gone, distinct:3->2)
    left++ -> left=1

  ┌───┬───┐
  │ 3 │ 5 │  distinct={3,5}=2  OK
  └───┴───┘
  L=1 R=2  ans=max(2,2)=2

STEP 4: right=3, nums[3]=7, factors=[7]  *** MUST SHRINK ***
  ADD: freq[7]: 0->1 (NEW, distinct:2->3)
  distinct=3 > 2 NOT OK!

  ┌───┬───┬───┐
  │ 3 │ 5 │ 7 │  distinct={3,5,7}=3  NOT OK!
  └───┴───┴───┘

  SHRINK 1: Remove nums[left=1]=3, factors=[3]
    freq[3]: 1->0 (prime 3 gone, distinct:3->2)
    left++ -> left=2

  ┌───┬───┐
  │ 5 │ 7 │  distinct={5,7}=2  OK
  └───┴───┘
  L=2 R=3  ans=max(2,2)=2

FINAL ANSWER: 2

================================================================================
SUMMARY
================================================================================

Algorithm: Sliding Window + SPF (Sieve of Eratosthenes)

1. SPF Array: spf[i] stores the smallest prime factor of i.
   Built using a modified sieve in O(mx * log(log(mx))).

2. Factorization: Each number is factorized into DISTINCT primes
   using the SPF array in O(log x) per number.

3. Sliding Window:
   - Expand right pointer, add prime factors to frequency map
   - If distinct primes > k, shrink from left until valid
   - Track maximum valid window length

Time:  O(mx * log(log(mx)) + n * log(mx))
Space: O(mx + n)
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // -----------------------------------------------------------------------
    // GET DISTINCT PRIME FACTORS OF x USING THE SPF ARRAY
    // -----------------------------------------------------------------------
    // HOW IT WORKS:
    //   We repeatedly look up spf[x] (smallest prime dividing x),
    //   add that prime to our list, then divide out ALL copies of that
    //   prime from x. We repeat until x becomes 1.
    //
    // WHY DIVIDE OUT ALL COPIES?
    //   We only want DISTINCT primes. E.g., for x=12:
    //     12 = 2 * 2 * 3  ->  distinct primes = {2, 3}, NOT {2, 2, 3}
    //
    // TRACE for x=12:
    //   Iteration 1: x=12, p=spf[12]=2, factors=[2]
    //     Divide out 2s: 12/2=6, 6/2=3, 3%2!=0 -> stop. x=3
    //   Iteration 2: x=3, p=spf[3]=3, factors=[2,3]
    //     Divide out 3s: 3/3=1 -> stop. x=1
    //   Iteration 3: x=1 -> STOP. Return [2, 3]
    //
    // TRACE for x=8:
    //   Iteration 1: x=8, p=2, factors=[2], 8/2=4/2=2/2=1, x=1
    //   Iteration 2: x=1 -> STOP. Return [2]
    //
    // TRACE for x=9:
    //   Iteration 1: x=9, p=3, factors=[3], 9/3=3/3=1, x=1
    //   Iteration 2: x=1 -> STOP. Return [3]
    // -----------------------------------------------------------------------
    vector<int> getFactors(int x, vector<int>& spf) {

        vector<int> factors;

        while (x > 1) {

            int p = spf[x];       // smallest prime dividing x

            factors.push_back(p); // collect this distinct prime

            // Remove ALL occurrences of prime p from x
            // so we never add p twice (ensures DISTINCT primes)
            while (x % p == 0) {
                x /= p;
            }
        }

        return factors;
    }

    // -----------------------------------------------------------------------
    // MAIN FUNCTION: FIND LONGEST SUBARRAY WITH AT MOST K DISTINCT PRIME FACTORS
    // -----------------------------------------------------------------------
    // STRATEGY:
    //   Phase 1: Build SPF (Smallest Prime Factor) array  -> O(mx log log mx)
    //   Phase 2: Precompute distinct primes for each nums[i] using SPF -> O(n log mx)
    //   Phase 3: Sliding window to find longest valid subarray -> O(n)
    //
    // SLIDING WINDOW IDEA:
    //   - Maintain window [left ... right]
    //   - freq[prime] = how many times this prime appears in the window
    //   - distinct = count of primes with freq > 0
    //   - Expand right: add primes of nums[right]
    //   - If distinct > k: shrink from left until distinct <= k
    //   - Update answer with window size at each step
    // -----------------------------------------------------------------------
    int longestSubarray(vector<int>& nums, int k) {

        int n = nums.size();

        // -------------------------------------------------------------------
        // PHASE 1: BUILD SPF ARRAY (SIEVE OF ERATOSTHENES)
        // -------------------------------------------------------------------
        // mx = maximum element in nums (we only need SPF up to mx)
        // spf[i] = smallest prime factor of i
        //
        // Step 1: Initialize spf[i] = i for all i (0 to mx)
        //   Initially, every number "is its own smallest factor"
        //   Primes will keep their value, composites will be overwritten
        //
        // Step 2: For each number i from 2 to sqrt(mx):
        //   If spf[i] == i, then i is PRIME (never overwritten by smaller prime)
        //   Mark all multiples of i starting from i*i:
        //     If spf[j] == j (not yet marked), set spf[j] = i
        // -------------------------------------------------------------------
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> spf(mx + 1);

        // Step 1: Initialize each number as its own SPF
        //   spf[0]=0, spf[1]=1, spf[2]=2, spf[3]=3, spf[4]=4, ...
        for (int i = 0; i <= mx; i++) {
            spf[i] = i;
        }

        // Step 2: Sieve - mark smallest prime factor for composites
        //   Loop from i=2 to i*i <= mx
        //   If spf[i]==i, it means i is prime (no smaller prime divided it)
        //   Then mark all multiples j of i (starting from i*i):
        //     Only update spf[j] if it hasn't been set by a smaller prime
        //
        //   WHY START FROM i*i?
        //     Multiples smaller than i*i (like 2*i, 3*i, ..., (i-1)*i)
        //     have ALREADY been marked by smaller primes (2, 3, ..., i-1)
        //
        //   EXAMPLE TRACE (mx=12):
        //     i=2 (prime): mark 4->2, 6->2, 8->2, 10->2, 12->2
        //     i=3 (prime): mark 9->3 (12 already has spf=2, skip)
        //     i=4: 4*4=16 > 12, STOP
        for (int i = 2; i * i <= mx; i++) {

            if (spf[i] == i) {

                for (int j = i * i; j <= mx; j += i) {

                    if (spf[j] == j) {
                        spf[j] = i;  // i is the smallest prime factor of j
                    }
                }
            }
        }

        // -------------------------------------------------------------------
        // PHASE 2: PRECOMPUTE DISTINCT PRIME FACTORS FOR EACH nums[i]
        // -------------------------------------------------------------------
        // factors[i] = list of distinct prime factors of nums[i]
        // Example: nums = [6, 8, 9, 4, 12]
        //   factors[0] = [2, 3]   (6 = 2 * 3)
        //   factors[1] = [2]      (8 = 2^3)
        //   factors[2] = [3]      (9 = 3^2)
        //   factors[3] = [2]      (4 = 2^2)
        //   factors[4] = [2, 3]   (12 = 2^2 * 3)
        // -------------------------------------------------------------------
        vector<vector<int>> factors(n);

        for (int i = 0; i < n; i++) {
            factors[i] = getFactors(nums[i], spf);
        }

        // -------------------------------------------------------------------
        // PHASE 3: SLIDING WINDOW
        // -------------------------------------------------------------------
        // freq[prime] = count of how many numbers in current window have
        //               this prime as a factor
        // distinct    = number of primes with freq[prime] > 0
        //
        // INVARIANT: At the end of each iteration, the window [left..right]
        //   has at most k distinct prime factors (is valid)
        //
        // ALGORITHM:
        //   for right = 0 to n-1:
        //     1. ADD nums[right]: increment freq of each prime in factors[right]
        //        If freq goes from 0->1, a NEW distinct prime appeared
        //     2. SHRINK: while distinct > k, remove nums[left]'s primes,
        //        decrement freq, if freq goes to 1->0, one less distinct prime
        //        left++
        //     3. UPDATE: ans = max(ans, window_size)
        // -------------------------------------------------------------------
        vector<int> freq(mx + 1, 0);  // frequency of each prime in window

        int left = 0;       // left boundary of window
        int distinct = 0;   // count of distinct primes in current window
        int ans = 0;        // best answer so far

        for (int right = 0; right < n; right++) {

            // -----------------------------------------------------------
            // STEP 1: EXPAND WINDOW - ADD nums[right]
            // -----------------------------------------------------------
            // For each prime factor p of nums[right]:
            //   - If freq[p] was 0, this is a NEW prime -> distinct++
            //   - Increment freq[p]
            //
            // EXAMPLE: right=0, nums[0]=6, factors[0]=[2,3]
            //   p=2: freq[2] was 0 -> distinct becomes 1, freq[2]=1
            //   p=3: freq[3] was 0 -> distinct becomes 2, freq[3]=1
            // -----------------------------------------------------------
            for (int p : factors[right]) {

                if (freq[p] == 0) {
                    distinct++;     // new prime entering the window
                }

                freq[p]++;
            }

            // -----------------------------------------------------------
            // STEP 2: SHRINK WINDOW - REMOVE FROM LEFT (if needed)
            // -----------------------------------------------------------
            // While we have MORE than k distinct primes:
            //   Remove nums[left]'s prime factors from window
            //   For each prime p of nums[left]:
            //     Decrement freq[p]
            //     If freq[p] becomes 0 -> one less distinct prime
            //   left++
            //
            // EXAMPLE of shrinking: nums=[2,3,5,7], k=2
            //   After adding 5: distinct=3 > 2, SHRINK!
            //     Remove nums[0]=2, factors=[2], freq[2]:1->0, distinct:3->2
            //     left++ -> left=1. Window is now [3,5], distinct=2 <= 2
            // -----------------------------------------------------------
            while (distinct > k) {

                for (int p : factors[left]) {

                    freq[p]--;

                    if (freq[p] == 0) {
                        distinct--;     // prime no longer in window
                    }
                }

                left++;     // shrink window from left
            }

            // -----------------------------------------------------------
            // STEP 3: UPDATE ANSWER
            // -----------------------------------------------------------
            // Current window [left..right] is VALID (distinct <= k)
            // Window length = right - left + 1
            // -----------------------------------------------------------
            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};


int main(){
    return 0;
}