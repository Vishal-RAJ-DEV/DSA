/*
Question: Codeforces 1669F - Eating Candies
There are n candies with weights w[i] placed left to right.
Alice eats any number of candies from the left (contiguous prefix).
Bob eats any number of candies from the right (contiguous suffix).
They cannot eat the same candy.
Goal: Maximize total candies eaten such that Alice's total weight == Bob's total weight.

Approach: Two-pointer (greedy)
- l = left pointer (Alice), r = right pointer (Bob)
- Track sum_alice (prefix) and sum_bob (suffix)
- If sum_alice < sum_bob: Alice eats more from left (l++)
- If sum_alice > sum_bob: Bob eats more from right (r--)
- If equal: record ans = total candies eaten so far, then continue
- After loop ends, one final check for equality (edge case when pointers cross exactly at equality)
Since both pointers only move inward, total candies eaten (l + n-1-r) increases monotonically,
so the last recorded equality gives the maximum answer.
Time: O(n), Space: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    int l = 0, r = n - 1;
    int alice = 0, bob = 0;
    int ans = 0;

    while(l <= r){
        if(alice < bob){
            alice += a[l];
            l++;
        }
        else if(alice > bob){
            bob += a[r];
            r--;
        }
        else{
            ans = l + (n - 1 - r);
            alice += a[l];
            l++;
        }
    }

    if(alice == bob){
        ans = l + (n - 1 - r);
    }

    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}