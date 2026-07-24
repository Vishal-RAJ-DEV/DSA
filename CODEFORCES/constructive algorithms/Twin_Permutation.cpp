#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Twin Permutation - Codeforces):
We have an array 'a' which is a permutation of numbers 1 to n.
We need to construct ANOTHER permutation 'b' of numbers 1 to n
such that the sequence (a[i] + b[i]) is NON-DECREASING.

In other words:
  a[1] + b[1] <= a[2] + b[2] <= ... <= a[n] + b[n]

We can choose any permutation for b.

EXAMPLE:
n = 5, a = [4, 1, 5, 2, 3]
One valid b = [4, 5, 2, 3, 1] -> sums = [8, 6, 7, 5, 4] (not non-decreasing!)
Better b = [4, 1, 5, 2, 3]??? No, b must also be a permutation.

Correct answer for this case: b = [2, 5, 1, 4, 3]
Check: 4+2=6, 1+5=6, 5+1=6, 2+4=6, 3+3=6 -> all equal -> non-decreasing!

=========================================================
INTUITION & APPROACH (The "Make All Sums Equal" Trick):
=========================================================

Step 1: What are we trying to achieve?
We want a[i] + b[i] to be non-decreasing.
The EASIEST way to guarantee this is to make ALL sums EQUAL.
If every sum is the same (e.g., 6 <= 6 <= 6 <= 6 <= 6), then
non-decreasing is automatically true.

So instead of thinking "How do I make them increasing?"
think: "Can I make every sum equal?"
That is the KEY INSIGHT.

Step 2: Can every sum be equal?
'a' is a permutation of 1..n. After sorting it becomes: 1 2 3 4 ... n.
To make every pair have the same sum, we need:
  1 pairs with n  -> sum = n+1
  2 pairs with n-1 -> sum = n+1
  3 pairs with n-2 -> sum = n+1
  ...
  n pairs with 1  -> sum = n+1

So the smallest 'a' gets the largest 'b', second smallest gets second
largest, and so on. This is the ONLY way to keep every sum identical.

Step 3: Why sort first?
Given a = [4, 1, 5, 2, 3], how do we know which element is the smallest?
We don't — unless we sort. So we first store each a[i] with its original
index, then sort by value. Now we know:
  Smallest value (1) is at original index 1
  Second smallest (2) is at index 3
  Third smallest (3) is at index 4
  Fourth smallest (4) is at index 0
  Largest (5) is at index 2

Now we can assign the LARGEST b-value (n) to the SMALLEST a-value,
then put that b-value back at the correct original index.

Step 4: Why assign largest first? (Balancing)
Think of balancing weights. If you give:
  a = [1, 2, 3, 4, 5]
  b = [1, 2, 3, 4, 5] (same order)
  sums = [2, 4, 6, 8, 10] -> increasing but NOT equal.

But if we give:
  b = [5, 4, 3, 2, 1] (reversed)
  sums = [6, 6, 6, 6, 6] -> ALL EQUAL!

Every large number in 'a' is balanced by a small number in 'b'.
Every small number in 'a' is balanced by a large number in 'b'.
This is the same idea used in many greedy problems:
  "Pair the smallest with the largest to balance the result."

Step 5: Summary of Algorithm
1. Store each a[i] with its original index as (value, index).
2. Sort by value (ascending).
3. Create array b of size n.
4. Assign cur = n down to 1 to the sorted positions:
     b[original_index_of_smallest_a] = n
     b[original_index_of_second_smallest_a] = n-1
     ...
     b[original_index_of_largest_a] = 1
5. Print b.

RESULT: All sums = smallest_a + largest_b = 1 + n = n+1.
         Constraint satisfied trivially.

EXAMPLE WALKTHROUGH:
n = 5, a = [2, 5, 1, 4, 3]

Store with indices:
  v = [(2,0), (5,1), (1,2), (4,3), (3,4)]

Sort by value:
  v = [(1,2), (2,0), (3,4), (4,3), (5,1)]
        ^       ^       ^       ^       ^
      smallest                      largest

Assign cur = 5,4,3,2,1 to these:
  b[2] = 5   (smallest a=1 gets largest b=5)
  b[0] = 4   (second smallest a=2 gets b=4)
  b[4] = 3
  b[3] = 2
  b[1] = 1   (largest a=5 gets smallest b=1)

Final b = [4, 1, 5, 2, 3]

Check sums:
  a[0]+b[0] = 2+4 = 6
  a[1]+b[1] = 5+1 = 6
  a[2]+b[2] = 1+5 = 6
  a[3]+b[3] = 4+2 = 6
  a[4]+b[4] = 3+3 = 6

All sums = 6 = n+1. Non-decreasing? 6 <= 6 <= 6 <= 6 <= 6 ✓
*/

void solve() {
    int n;
    cin >> n;

    // Store {value, original_index} for each a[i]
    vector<pair<int, int>> v;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back({x, i});
    }

    // Sort by value — now we know which is smallest, which is largest
    sort(v.begin(), v.end());

    vector<int> b(n);

    // Assign largest b-values (n down to 1) to smallest a-values
    int cur = n;
    for (int i = 0; i < n; i++) {
        b[v[i].second] = cur--;
    }

    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}