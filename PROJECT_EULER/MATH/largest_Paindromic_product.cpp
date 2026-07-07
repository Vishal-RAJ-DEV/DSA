#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
For each test case, you are given a number n.
You have to find the largest palindrome number that is less than n
and can be written as the product of two 3-digit numbers.

Constraints:
- 1 <= T <= 100
- 101101 < N < 1000000

What is a palindrome number?
- A palindrome reads the same from left to right and right to left.
- Example: 121, 9009, 12321

Example idea:
- 91 x 99 = 9009
- 9009 is a palindrome.
- In this problem, we only care about products of two 3-digit numbers,
  meaning both numbers must lie between 100 and 999.

Constraint intuition:
- For every test case, checking all products of 3-digit numbers again would be wasteful.
- There are only a limited number of products formed by 3-digit numbers.
- So a better idea is to precompute all palindrome products once,
  sort them, and then answer each query quickly using binary search.

Main intuition of this code:
- Generate every product i * j where i and j are 3-digit numbers.
- Keep only those products that are palindromes.
- Store them in a vector.
- Sort the vector and remove duplicates.
- For each input n, find the largest palindrome strictly smaller than n.

Why binary search works:
- After sorting, all palindrome products are in increasing order.
- We use lower_bound to find the first value that is greater than or equal to n.
- The answer we want is the element just before that position.
*/

bool ispalindrome(int n) {
    // Keep a copy so we can compare the reversed number with the original number.
    int num = n;
    int rev = 0;

    // Reverse the digits of n.
    while (num > 0) {
        int digit = num % 10;
        rev = (rev * 10) + digit;
        num /= 10;
    }

    return n == rev;
}

void storePalindrome(vector<int>& palindrome) {
    /*
    Generate all products of two 3-digit numbers.
    We start j from i to avoid checking both (i, j) and (j, i),
    because they give the same product.
    */
    for (int i = 100; i <= 999; i++) {
        for (int j = i; j <= 999; j++) {
            int pro = i * j;

            // Store the product only if it is a palindrome.
            if (ispalindrome(pro)) {
                palindrome.push_back(pro);
            }
        }
    }

    // Sort all palindrome products so binary search can be used later.
    sort(palindrome.begin(), palindrome.end());

    // Remove duplicate palindrome values created by different factor pairs.
    palindrome.erase(unique(palindrome.begin(), palindrome.end()), palindrome.end());
}

int main() {
    vector<int> palindrome;

    // Precompute once before answering any test cases.
    storePalindrome(palindrome);

    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        int n;
        cin >> n;

        /*
        lower_bound gives the first palindrome that is >= n.
        We need the largest palindrome < n, so we move one step back.
        */
        auto it = lower_bound(palindrome.begin(), palindrome.end(), n);

        --it;
        cout << *it << endl;
    }
    return 0;
}
