#include <bits/stdc++.h>
using namespace std;
/*
----------------------------------------------------
BASE X -> DECIMAL

Logic:

We process the number from left to right.

For every new digit:
    answer = answer * base + digit

Why?

Suppose we have already formed the number "123".
When the next digit is '4',

1234 = 123 * 10 + 4

Similarly, in base X,

New Number = Previous Number * X + Current Digit

Character to digit conversion:

'0' - '9'  -> c - '0'
'A' - 'Y'  -> c - 'A' + 10

Time Complexity : O(number of digits)
Space Complexity: O(1)
----------------------------------------------------
*/

/*
----------------------------------------------------
DECIMAL -> BASE X

Logic:

Repeatedly divide the number by the base.

In each iteration:
1. remainder = number % base
   -> This is the next digit in the new base.

2. Convert the remainder to a character.
   0-9  -> '0' + rem
   10-34 -> 'A' + (rem - 10)

3. Store the digit.

4. number = number / base

The digits are obtained from Least Significant Digit
to Most Significant Digit, so reverse the string
at the end.

Time Complexity : O(log_base(N))
Space Complexity: O(log_base(N))
----------------------------------------------------
*/


void solve()
{
    int T;
    cin >> T;

    if (T == 1)
    {
        // Base X -> Decimal
        string N;
        int X;
        cin >> N >> X;

        long long ans = 0;

        for (char c : N)
        {
            int digit;

            if (c >= '0' && c <= '9')
                digit = c - '0';
            else
                digit = c - 'A' + 10;

            ans = ans * X + digit;
        }

        cout << ans << "\n";
    }
    else
    {
        // Decimal -> Base X
        long long N;
        int X;
        cin >> N >> X;

        if (N == 0)
        {
            cout << 0 << "\n";
            return;
        }

        string ans = "";

        while (N > 0)
        {
            int rem = N % X;

            if (rem < 10)
                ans += char(rem + '0');
            else
                ans += char(rem - 10 + 'A');

            N /= X;
        }

        reverse(ans.begin(), ans.end());

        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}