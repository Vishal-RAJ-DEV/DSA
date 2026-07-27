#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
Function : addString()
Purpose  : Adds a small integer (9999) to a very large
           number stored as a string.

Example:
"12345" + 9999 = "22344"

Time  : O(N)
Space : O(1)
----------------------------------------------------------
*/
string addString(string num, int x)
{
    // Start from the last digit of the string.
    int i = num.size() - 1;

    // Carry generated during addition.
    int carry = 0;

    /*
        Continue while:

        1) There are digits left in num.
        OR
        2) There are digits left in x (9999).
        OR
        3) A carry still exists.

        This ensures every digit gets processed.
    */
    while (i >= 0 || x > 0 || carry > 0)
    {
        /*
            Current digit of the large number.

            If all digits are processed,
            treat the digit as 0.
        */
        int digit1 = (i >= 0) ? num[i] - '0' : 0;

        /*
            Current digit of x.

            Example:
            x = 9999

            digit2:
            9
            9
            9
            9
        */
        int digit2 = x % 10;

        /*
            Add

            current digit of num
            + current digit of x
            + previous carry
        */
        int sum = digit1 + digit2 + carry;

        /*
            Store only the last digit.

            Example

            sum = 17

            Store 7
            Carry 1
        */
        if (i >= 0)
        {
            // Replace current digit.
            num[i] = char(sum % 10 + '0');
        }
        else
        {
            /*
                If the original number is finished
                but digits/carry still remain,

                insert them at the beginning.

                Example

                9999
                +1
                ----
                10000

                Here the leading 1 is inserted.
            */
            num.insert(num.begin(), char(sum % 10 + '0'));
        }

        // Save carry for next iteration.
        carry = sum / 10;

        // Remove the processed digit from x.
        x /= 10;

        // Move to the previous digit.
        i--;
    }

    return num;
}

/*
----------------------------------------------------------
Function : multiplyString()

Purpose:

Multiply a very large number by 9999.

Example

123 × 9999 = 1229877

Time  : O(N)

Space : O(N)
----------------------------------------------------------
*/
string multiplyString(string num, int x)
{
    // Carry generated after multiplication.
    int carry = 0;

    /*
        Digits are generated from right to left.

        Therefore we store them in reverse order first.
    */
    string ans = "";

    // Traverse from last digit.
    for (int i = num.size() - 1; i >= 0; i--)
    {
        /*
            Multiply current digit by x.

            Also add previous carry.

            Example

            digit = 2

            x = 9999

            carry = 1999

            product

            = 2*9999 +1999
        */
        int product = (num[i] - '0') * x + carry;

        /*
            Store only the last digit.

            Example

            product = 19998

            Store

            8
        */
        ans.push_back(char(product % 10 + '0'));

        /*
            Remaining digits become carry.

            Example

            19998

            carry =1999
        */
        carry = product / 10;
    }

    /*
        If carry still remains,

        append every digit.

        Example

        carry

        1199

        Store

        9
        9
        1
        1
    */
    while (carry > 0)
    {
        ans.push_back(char(carry % 10 + '0'));
        carry /= 10;
    }

    /*
        Digits were generated

        Right -> Left

        Therefore reverse them.

        Example

        Stored

        889911

        Reverse

        119988
    */
    reverse(ans.begin(), ans.end());

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read very large number as a string.
    string N;
    cin >> N;

    // Print N + 9999.
    cout << addString(N, 9999) << '\n';

    // Print N * 9999.
    cout << multiplyString(N, 9999) << '\n';

    return 0;
}