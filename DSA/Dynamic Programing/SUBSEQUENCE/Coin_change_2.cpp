#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Coin Change 2

    Given:
        coins[] = coin denominations
        amount  = target amount

    Task:
        Count how many different combinations can make the amount.

    Important:
        1. Each coin can be used unlimited times.
        2. Order does not matter.

    Example:
        coins = {1, 2, 5}, amount = 5

        Valid combinations:
            5
            2 + 2 + 1
            2 + 1 + 1 + 1
            1 + 1 + 1 + 1 + 1

        Answer = 4

    Why this is different from normal minimum coin change?
        Normal coin change asks:
            minimum number of coins

        Coin Change 2 asks:
            total number of combinations
*/

// ============================================================
// PATTERN 1:
// ind means actual index of the coin we are currently allowed to use.
// State: solve(ind, target)
// Meaning: number of ways to make target using coins[0...ind].
// ============================================================

// ================= PATTERN 1: MEMOIZATION =================
class Pattern1Memoization {
public:
    long solve(vector<int>& coins, int ind, int target, vector<vector<long>>& dp) {
        /*
            Algorithm:
                At every index ind, we have two choices:

                1. notTake:
                   Do not use coins[ind].
                   Then we move to the previous coin:
                       solve(ind - 1, target)

                2. take:
                   Use coins[ind].
                   Since each coin can be used unlimited times, we stay on
                   the same index:
                       solve(ind, target - coins[ind])

                Total ways:
                    notTake + take

            Why take keeps ind same?
                Because after taking coins[ind], we are still allowed to take
                the same coin again.
        */

        /*
            Base case:
                When ind == 0, only coins[0] is available.

            Since coins[0] can be used unlimited times, target can be formed
            only if target is exactly divisible by coins[0].

            Example:
                coins[0] = 2

                target = 6:
                    2 + 2 + 2, so 1 way.

                target = 7:
                    impossible, so 0 ways.

            That is why:
                return target % coins[0] == 0

            In C++, true becomes 1 and false becomes 0.
        */
        if (ind == 0) {
            return (target % coins[0] == 0);
        }

        if (dp[ind][target] != -1) return dp[ind][target];

        long notTake = solve(coins, ind - 1, target, dp);

        long take = 0;
        if (coins[ind] <= target) {
            take = solve(coins, ind, target - coins[ind], dp);
        }

        return dp[ind][target] = take + notTake;
    }

    long change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<long>> dp(n, vector<long>(amount + 1, -1));

        return solve(coins, n - 1, amount, dp);
    }
};

// ================= PATTERN 1: TABULATION =================
class Pattern1Tabulation {
public:
    long change(int amount, vector<int>& coins) {
        int n = coins.size();

        /*
            dp[ind][target] means:
                number of ways to make target using coins[0...ind].
        */
        vector<vector<long>> dp(n, vector<long>(amount + 1, 0));

        /*
            Base case conversion:

            Memoization base case:
                if ind == 0:
                    return target % coins[0] == 0

            In tabulation, ind == 0 means row 0.
            So we fill dp[0][target] for every target from 0 to amount.

            If target is divisible by coins[0], there is exactly 1 way:
                use coins[0] target / coins[0] times.

            Otherwise there are 0 ways.
        */
        for (int target = 0; target <= amount; target++) {
            if (target % coins[0] == 0) {
                dp[0][target] = 1;
            }
        }

        /*
            Recursive relation conversion:

            Memoization:
                notTake = solve(ind - 1, target)
                take    = solve(ind, target - coins[ind])

            Tabulation:
                notTake = dp[ind - 1][target]
                take    = dp[ind][target - coins[ind]]

            Notice take uses the same row dp[ind].
            This represents unlimited use of the current coin.
        */
        for (int ind = 1; ind < n; ind++) {
            for (int target = 0; target <= amount; target++) {
                long notTake = dp[ind - 1][target];

                long take = 0;
                if (coins[ind] <= target) {
                    take = dp[ind][target - coins[ind]];
                }

                dp[ind][target] = take + notTake;
            }
        }

        return dp[n - 1][amount];
    }
};

// ================= PATTERN 1: SPACE OPTIMIZATION =================
class Pattern1SpaceOptimized {
public:
    long change(int amount, vector<int>& coins) {
        int n = coins.size();

        /*
            In tabulation:
                dp[ind][target] depends on:
                    dp[ind - 1][target]              -> previous row
                    dp[ind][target - coins[ind]]     -> current row

            So we can keep:
                prev = previous row
                curr = current row

            prev[target] means:
                ways to make target using coins processed before current coin.
        */
        vector<long> prev(amount + 1, 0);

        /*
            Same base case conversion as tabulation row 0:
                prev[target] = 1 if target is divisible by coins[0].
        */
        for (int target = 0; target <= amount; target++) {
            if (target % coins[0] == 0) {
                prev[target] = 1;
            }
        }

        for (int ind = 1; ind < n; ind++) {
            vector<long> curr(amount + 1, 0);

            for (int target = 0; target <= amount; target++) {
                long notTake = prev[target];

                long take = 0;
                if (coins[ind] <= target) {
                    /*
                        take comes from curr, not prev.

                        Why?
                            We stay on the same coin when we take it,
                            because unlimited use is allowed.
                    */
                    take = curr[target - coins[ind]];
                }

                curr[target] = take + notTake;
            }

            prev = curr;
        }

        return prev[amount];
    }
};

// ============================================================
// PATTERN 2:
// idx means number of coins available, not actual array index.
// State: solve(idx, amount)
// Meaning: number of ways to make amount using the first idx coins.
// Current coin is coins[idx - 1].
// ============================================================

// ================= PATTERN 2: MEMOIZATION =================
class Pattern2Memoization {
public:
    vector<vector<long>> memo;

    long change(int amount, vector<int>& coins) {
        int n = coins.size();
        memo.assign(n + 1, vector<long>(amount + 1, -1));

        return solve(coins, n, amount);
    }

    long solve(vector<int>& coins, int idx, int amount) {
        /*
            Algorithm:
                idx tells how many coins are available.

                If idx = 3, available coins are:
                    coins[0], coins[1], coins[2]

                Current coin:
                    coins[idx - 1]

                Choices:

                1. skip:
                   Do not use coins[idx - 1].
                   Then only first idx - 1 coins remain:
                       solve(idx - 1, amount)

                2. take:
                   Use coins[idx - 1].
                   Since unlimited use is allowed, idx stays same:
                       solve(idx, amount - coins[idx - 1])

                Total ways:
                    skip + take
        */

        /*
            Base case 1:
                if amount == 0, return 1

            Why?
                We successfully formed the amount.
                There is exactly one way to complete this path:
                    choose nothing more.
        */
        if (amount == 0) return 1;

        /*
            Base case 2:
                if idx == 0, return 0

            Why?
                No coins are available.
                If amount is still greater than 0, we cannot form it.

            Notice:
                amount == 0 is checked before idx == 0.
                So solve(0, 0) correctly returns 1, not 0.
        */
        if (idx == 0) return 0;

        if (memo[idx][amount] != -1) return memo[idx][amount];

        long skip = solve(coins, idx - 1, amount);

        long take = 0;
        if (coins[idx - 1] <= amount) {
            take = solve(coins, idx, amount - coins[idx - 1]);
        }

        return memo[idx][amount] = take + skip;
    }
};

// ================= PATTERN 2: TABULATION =================
class Pattern2Tabulation {
public:
    long change(int amount, vector<int>& coins) {
        int n = coins.size();

        /*
            dp[idx][amt] means:
                number of ways to make amt using the first idx coins.

            idx = 0 means:
                no coins are available.

            idx = 1 means:
                only coins[0] is available.

            idx = n means:
                all coins are available.
        */
        vector<vector<long>> dp(n + 1, vector<long>(amount + 1, 0));

        /*
            Base case conversion 1:

            Memoization:
                if amount == 0 return 1

            Tabulation:
                amount == 0 means column 0.

            For every idx, dp[idx][0] = 1 because amount 0 can be made by
            choosing no more coins.
        */
        for (int idx = 0; idx <= n; idx++) {
            dp[idx][0] = 1;
        }

        /*
            Base case conversion 2:

            Memoization:
                if idx == 0 return 0

            Tabulation:
                idx == 0 means row 0.

            dp[0][amt] remains 0 for amt > 0 because no positive amount can
            be formed using zero coins.

            dp[0][0] is already 1 from the first base case.
        */

        /*
            Recursive relation conversion:

            Memoization:
                skip = solve(idx - 1, amt)
                take = solve(idx, amt - coins[idx - 1])

            Tabulation:
                skip = dp[idx - 1][amt]
                take = dp[idx][amt - coins[idx - 1]]

            Again, take uses the same row because the current coin can be
            taken again.
        */
        for (int idx = 1; idx <= n; idx++) {
            for (int amt = 1; amt <= amount; amt++) {
                long skip = dp[idx - 1][amt];

                long take = 0;
                if (coins[idx - 1] <= amt) {
                    take = dp[idx][amt - coins[idx - 1]];
                }

                dp[idx][amt] = take + skip;
            }
        }

        return dp[n][amount];
    }
};

// ================= PATTERN 2: SPACE OPTIMIZATION =================
class Pattern2SpaceOptimized {
public:
    long change(int amount, vector<int>& coins) {
        int n = coins.size();

        /*
            From Pattern 2 tabulation:
                dp[idx][amt] depends on:
                    dp[idx - 1][amt]              -> previous row
                    dp[idx][amt - coins[idx - 1]] -> current row

            We can use one 1D dp array.

            dp[amt] means:
                number of ways to make amt using the coins processed so far.

            For each coin, we move amt from coin to amount.

            Why left to right?
                Because unlimited use is allowed.

                When we do:
                    dp[amt] += dp[amt - coin]

                dp[amt - coin] may already include the current coin.
                That is exactly what we want for unbounded coin change.
        */
        vector<long> dp(amount + 1, 0);

        /*
            Base case conversion:
                amount 0 can always be made in 1 way:
                    choose nothing.

            This is the 1D version of:
                dp[idx][0] = 1 for every idx
        */
        dp[0] = 1;

        for (int idx = 1; idx <= n; idx++) {
            int coin = coins[idx - 1];

            for (int amt = coin; amt <= amount; amt++) {
                /*
                    old dp[amt] is skip:
                        ways without using this coin

                    dp[amt - coin] is take:
                        ways after using this coin at least once
                */
                dp[amt] += dp[amt - coin];
            }
        }

        return dp[amount];
    }
};

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 5;

    Pattern1Memoization p1Memo;
    Pattern1Tabulation p1Tab;
    Pattern1SpaceOptimized p1Space;

    Pattern2Memoization p2Memo;
    Pattern2Tabulation p2Tab;
    Pattern2SpaceOptimized p2Space;

    cout << p1Memo.change(amount, coins) << endl;
    cout << p1Tab.change(amount, coins) << endl;
    cout << p1Space.change(amount, coins) << endl;

    cout << p2Memo.change(amount, coins) << endl;
    cout << p2Tab.change(amount, coins) << endl;
    cout << p2Space.change(amount, coins) << endl;

    return 0;
}
