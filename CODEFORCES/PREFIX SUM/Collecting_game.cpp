#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
===============================================================================
                                INTUITION
===============================================================================

We are allowed to remove an element only if

        score >= element

and after removing it,

        score += element

Question:
For every element ai, if we start with score = ai (after removing ai),
how many more elements can we remove?

-------------------------------------------------------------------------------
Key Observation 1
-------------------------------------------------------------------------------

Suppose the remaining elements are

    5 2 8 1

Should we remove 8 first?

No.

Removing smaller elements first is always better because every removed element
increases our score.

Therefore, the optimal order is ALWAYS increasing order.

Hence, the first thing we do is sort the array.

-------------------------------------------------------------------------------
Key Observation 2
-------------------------------------------------------------------------------

Suppose the sorted array is

Index : 0  1  2  3  4
Value : 1  2  4  5 20

Prefix Sum

1
3
7
12
32

Imagine we have successfully removed every element up to index 2.

Current score

    1 + 2 + 4 = 7

Can we remove the next element?

Need

    score >= next value

    7 >= 5

Yes.

After removing 5,

score becomes

12

Can we remove 20?

Need

12 >= 20

No.

So we stop.

Notice that to know whether we can move from i to i+1,
we only need

        prefixSum[i] >= a[i+1]

This is the main observation.

-------------------------------------------------------------------------------
Key Observation 3 (Reach DP)
-------------------------------------------------------------------------------

Suppose

Value

1 2 4 5 20

We process from RIGHT to LEFT.

Last element

20

can obviously reach only itself.

reach[4]=4

Now check 5.

Current score after removing everything till 5

prefixSum[3]=12

Can 12 remove 20?

No.

So

reach[3]=3

Now check 4.

Current score

prefixSum[2]=7

Can 7 remove 5?

Yes.

If 4 can reach 5,
and 5 already knows how far it can go,

then 4 inherits that answer.

Therefore

reach[2]=reach[3]

This propagation from right to left is the whole trick.

===============================================================================
Algorithm
===============================================================================

1. Store every number with its original index.

2. Sort the numbers.

3. Compute prefix sums.

4. Traverse from right to left.

       If prefixSum[i] >= next value

              reach[i]=reach[i+1]

       Else

              reach[i]=i

5. Put answers back into original order.

===============================================================================
Time Complexity

Sorting      : O(n log n)

Prefix Sum   : O(n)

DP           : O(n)

Overall

O(n log n)

===============================================================================
*/

void solve() {

    int n;
    cin >> n;

    // Store (value, original index)
    vector<pair<ll,int>> a(n);

    for(int i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i;
    }

    // Sort by value because removing smaller elements first is always optimal.
    sort(a.begin(), a.end());

    // ------------------------------------------------------------
    // Prefix Sum
    //
    // pref[i] = sum of first (i+1) smallest elements.
    // ------------------------------------------------------------

    vector<ll> pref(n);

    pref[0] = a[0].first;

    for(int i = 1; i < n; i++)
        pref[i] = pref[i-1] + a[i].first;

    /*
    ------------------------------------------------------------
    reach[i]

    Stores the farthest index we can eventually reach
    if we start from the element at index i.

    Example

    reach[2]=4

    means

    starting from index 2,
    we can remove every element till index 4.

    ------------------------------------------------------------
    */

    vector<int> reach(n);

    // Largest element can only reach itself.
    reach[n-1] = n-1;

    // Compute answers from right to left.
    for(int i = n-2; i >= 0; i--){

        /*
        Can everything till i remove the next element?

        Current score after removing first (i+1) elements

                pref[i]

        Need

                pref[i] >= a[i+1]

        If yes,

        once we reach i+1,
        we can continue exactly as i+1 could.

        Therefore

                reach[i]=reach[i+1]

        Otherwise

        we stop here.

                reach[i]=i
        */

        if(pref[i] >= a[i+1].first)
            reach[i] = reach[i+1];
        else
            reach[i] = i;
    }

    // Restore answers to original order.
    vector<int> ans(n);

    for(int i = 0; i < n; i++){

        /*
        a[i].second

        is the original position before sorting.

        reach[i]

        already equals the number of removable elements
        in the sorted order.

        Put it back to the original index.
        */

        ans[a[i].second] = reach[i];
    }

    for(int x : ans)
        cout << x << " ";

    cout << "\n";
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--)
        solve();

    return 0;
}