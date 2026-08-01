/*
===========================================================
QUESTION: Codeforces 1899C - Yarik and Array
(Round 909, Div. 3, problem C)

You are given an array a of n integers (n up to 2*10^5,
sum of n over all test cases <= 2*10^5).
Find the MAXIMUM SUM of a NON-EMPTY subarray (continuous part)
such that no two ADJACENT elements in the chosen subarray
have the SAME PARITY (both even or both odd).
i.e. the parities of adjacent elements must ALTERNATE.

Examples:
  [1, 2, 3]  → acceptable (odd, even, odd)
  [1, 2, 4]  → NOT acceptable (2 and 4 are both even and adjacent)

Sample test cases:
  [1, 2, 3, 4, 5]     → 15  (take entire array: odd,even,odd,even,odd)
  [9, 9, 8, 8]        → 17  (take [9,8] or... max = 9 + 8 = 17)
  [-1, 4, -1, 0, 5, -4] → 8  (best: [4,-1,0,5] = 8, parities alternate)
  [-1000]             → -1000 (single element, subarray must be non-empty)

APPROACH: Kadane's Algorithm (max subarray sum) with one twist.
- Keep 'current' = best sum of a valid subarray ending at i.
- If a[i] has DIFFERENT parity from a[i-1]:
    the subarray can be EXTENDED from the previous one
    (standard Kadane: reset to 0 if current is negative, then add a[i]).
- If a[i] has SAME parity as a[i-1]:
    the previous subarray CANNOT continue → start a NEW subarray
    that consists of only a[i] (current = a[i]).
- maxsum = max(maxsum, current) at every step.

Time Complexity : O(n) per test case
Space Complexity : O(1)
===========================================================
*/

#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin>> n;

    vector<int> a(n);
    for(int i = 0 ; i < n ; i++){
        cin >> a[i];
    }

    
    int current = a[0];
    int maxsum = a[0];

    for(int i = 1;  i < n ; i++){

        if(abs(a[i] % 2 ) != abs(a[i-1] % 2)){
            
            //version 1 to reset current sum if it goes negative
            if( current < 0){
                current = 0;
            }
            current += a[i];

            //version 2 to reset current sum if it goes negative
            // current = max(current + a[i], a[i]);  here we are checking if current + a[i] is less than a[i] then we will reset the current sum to a[i] because it is better to start a new subarray from a[i] rather than continuing with the previous subarray which has a negative sum.


        }else{
            
            current = a[i];
        }
        maxsum = max(maxsum, current);
    }
    cout << maxsum << "\n";
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