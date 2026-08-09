#include <bits/stdc++.h>
using namespace std;


/*
===========================================================
              MEMOIZATION / TOP-DOWN DP
===========================================================

INTUITION:

We want to divide the string into palindrome substrings
using the minimum number of cuts.

For example:

    s = "aab"

    "a" | "a" | "b"  -> 2 cuts
    "aa" | "b"        -> 1 cut

    Answer = 1


-----------------------------------------------------------
ROLE OF start AND end
-----------------------------------------------------------

start = beginning of the remaining problem.

For:

    s = "aab"

    start = 0 -> remaining string = "aab"
    start = 1 -> remaining string = "ab"
    start = 2 -> remaining string = "b"

Therefore:

    solve(start)

means:

    Minimum cuts required for s[start...n-1].


end is NOT the DP state.

end is used to try every possible ending position
for the current palindrome.

For example, if:

    start = 0

then:

    end = 0 -> "a"
    end = 1 -> "aa"
    end = 2 -> "aab"

Only palindrome substrings can be selected.


The partition looks like:

    [ start ........ end ] [ end+1 ........ n-1 ]
          palindrome            remaining problem

Once we choose s[start...end], the remaining problem
starts from:

    end + 1


-----------------------------------------------------------
RECURRENCE
-----------------------------------------------------------

If s[start...end] is a palindrome:

    cuts = 1 + solve(end + 1)

The +1 represents the cut after the current palindrome.


-----------------------------------------------------------
BASE CASE
-----------------------------------------------------------

If start == n:

    Nothing remains -> 0 cuts.

If the entire remaining substring:

    s[start...n-1]

is already a palindrome:

    No cut is required -> 0 cuts.


-----------------------------------------------------------
MEMOIZATION
-----------------------------------------------------------

dp[start] stores:

    Minimum cuts required for s[start...n-1]

Different partition paths can reach the same start.

For example, solve(2) can be reached through:

    "a" -> "a" -> solve(2)

or:

    "aa" -> solve(2)

But solve(2) represents the same remaining string.

Therefore we calculate it once and store it.
===========================================================
*/

class PalindromePartitionMemoization {
public:

    bool isPalindrome(string &s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end])
                return false;

            start++;
            end--;
        }

        return true;
    }

    int solve(string &s, int start, vector<int> &dp) {

        int n = s.size();

        if (start == n ||
            isPalindrome(s, start, n - 1))
            return 0;

        if (dp[start] != -1)
            return dp[start];

        int ans = INT_MAX;

        for (int end = start; end < n; end++) {

            if (isPalindrome(s, start, end)) {

                int cuts = 1 + solve(s, end + 1, dp);

                ans = min(ans, cuts);
            }
        }

        return dp[start] = ans;
    }

    int minCut(string s) {

        int n = s.size();

        vector<int> dp(n, -1);

        return solve(s, 0, dp);
    }
};


/*
===========================================================
              TABULATION / BOTTOM-UP DP
===========================================================

We convert:

    solve(start)

into:

    dp[start]


The meaning remains the same:

    dp[start]
    =
    Minimum cuts required for s[start...n-1]


-----------------------------------------------------------
WHY RIGHT TO LEFT?
-----------------------------------------------------------

The recursive transition is:

    solve(start)
        |
        v
    solve(end + 1)

Therefore:

    dp[start]
        depends on
    dp[end + 1]

Since:

    end + 1 > start

the larger-index states must be calculated first.

Therefore:

    dp[n]
    dp[n-1]
    dp[n-2]
    ...
    dp[0]

So we iterate from RIGHT -> LEFT.


-----------------------------------------------------------
BASE CASE
-----------------------------------------------------------

Recursive:

    start == n
        -> 0 cuts

Tabulation:

    dp[n] = 0


If the complete remaining substring is palindrome:

    s[start...n-1]

then:

    dp[start] = 0


-----------------------------------------------------------
TRANSITION
-----------------------------------------------------------

Memoization:

    1 + solve(end + 1)

Tabulation:

    1 + dp[end + 1]

Because dp[end + 1] has already been calculated.


-----------------------------------------------------------
START AND END IN TABULATION
-----------------------------------------------------------

start:

    Beginning of the current remaining problem.

end:

    Try every possible ending position of the
    current palindrome.

For example:

    s = "aab"
    start = 0

    end = 0 -> "a"
    end = 1 -> "aa"
    end = 2 -> "aab"

If s[start...end] is palindrome:

    current cut
        +
    dp[end + 1]

Take the minimum.


-----------------------------------------------------------
IMPORTANT
-----------------------------------------------------------

This version directly calls:

    isPalindrome(s, start, end)

instead of precomputing a palindrome table.

Therefore:

    Time  = O(n^3)
    Space = O(n)

The optimized version using pal[start][end] can reduce
the time complexity to O(n^2).
===========================================================
*/

class PalindromePartitionTabulation {
public:

    bool isPalindrome(string &s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end])
                return false;

            start++;
            end--;
        }

        return true;
    }

    int minCut(string s) {

        int n = s.size();

        vector<int> dp(n + 1, 0);

        for (int start = n - 1; start >= 0; start--) {

            if (isPalindrome(s, start, n - 1)) {
                dp[start] = 0;
                continue;
            }

            int ans = INT_MAX;

            for (int end = start; end < n; end++) {

                if (isPalindrome(s, start, end)) {

                    int cuts = 1 + dp[end + 1];

                    ans = min(ans, cuts);
                }
            }

            dp[start] = ans;
        }

        return dp[0];
    }
};


int main() {

    string s = "aab";

    PalindromePartitionMemoization memo;

    cout << "Memoization Answer: "
         << memo.minCut(s)
         << endl;


    PalindromePartitionTabulation tab;

    cout << "Tabulation Answer: "
         << tab.minCut(s)
         << endl;

    return 0;
}