#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * PROBLEM: Find the Transition Point
 * ---------------------------------------------------------------
 * Given a sorted binary array (only 0s and 1s), find the index
 * of the FIRST occurrence of 1. This is called the "transition point"
 * because it's where the array transitions from 0s to 1s.
 *
 * If there is no 1 in the array, return -1.
 *
 * INPUT:  A sorted array of 0s and 1s
 * OUTPUT: Index of first 1, or -1 if no 1 exists
 *
 * EXAMPLES:
 *   arr = {0, 0, 0, 1, 1, 1}  →  transition point = 3 (first 1)
 *   arr = {0, 0, 0, 0}        →  transition point = -1 (no 1s)
 *   arr = {1, 1, 1, 1}        →  transition point = 0 (first element)
 *   arr = {0, 1}              →  transition point = 1
 *
 * WHAT IS A TRANSITION POINT?
 * ---------------------------------------------------------------
 * The transition point is the BOUNDARY where 0s end and 1s begin.
 *
 *   arr = {0, 0, 0, 1, 1, 1}
 *               ↑
 *          transition point (index 3)
 *
 *   Left of transition:  all 0s
 *   Right of transition: all 1s (including the transition point itself)
 *
 * MONOTONIC PROPERTY:
 * ---------------------------------------------------------------
 * The array has this structure when viewed as a boolean array:
 *   predicate(i) = (arr[i] == 1)
 *
 *   pred = {F, F, F, T, T, T}   ← FALSEs on left, TRUEs on right
 *
 * This is the classic "FIRST TRUE" pattern:
 *   - Once arr[i] == 1, all arr[j] == 1 for j > i
 *   - We want the LEFTMOST TRUE (first occurrence of 1)
 *
 * This is exactly the same pattern as LOWER BOUND!
 *   Lower bound: first index where arr[i] >= x
 *   Here:        first index where arr[i] == 1
 *
 * HOW THE CODE WORKS:
 * ---------------------------------------------------------------
 * We use binary search to find the first 1:
 *
 *   At each step, look at mid:
 *     - If arr[mid] == 1:  mid COULD be answer, but maybe there's
 *       a 1 further LEFT. Save mid as candidate, search left: right = mid - 1
 *     - If arr[mid] == 0:  mid is NOT the answer, and nothing to the
 *       left can be 1 either (sorted!). Search right: left = mid + 1
 *
 * VISUAL TRACE: arr = {0, 0, 0, 1, 1, 1}
 *
 *   Iter 1: left=0, right=5, mid=2 → arr[2]=0 → left=3
 *   Iter 2: left=3, right=5, mid=4 → arr[4]=1 → ans=4, right=3
 *   Iter 3: left=3, right=3, mid=3 → arr[3]=1 → ans=3, right=2
 *   Iter 4: left=3, right=2 → STOP
 *   Return ans = 3 ✓
 *
 * WHY USE `ans` VARIABLE?
 * ---------------------------------------------------------------
 * We could return `left` directly (like in lower bound),
 * but here we use `ans` to explicitly track the last valid mid.
 * Both approaches work:
 *   - ans approach: save mid when TRUE, keep searching left
 *   - left approach: when loop ends, left = first index where arr[i]==1
 *
 * If no 1 exists, ans stays at -1 (initialized value).
 */

class Solution {
public:
    int transitionPoint(vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;

        // ans = -1 means "no 1 found yet"
        // If we never find a 1, we return -1
        int ans = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == 1) {
                // Found a 1! This could be the transition point.
                // But there might be another 1 further LEFT (smaller index).
                ans = mid;           // Save this as candidate answer
                right = mid - 1;     // Search LEFT for earlier occurrence
            }
            else {
                // arr[mid] == 0: too small, no 1 here or to the left
                left = mid + 1;      // Search RIGHT
            }
        }

        // ans = index of first 1, or -1 if no 1 exists
        return ans;
    }
};



int main(){
    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0 ; i < n ; i++){
        cin >> arr[i];
    }

    Solution sol;
    int transition_index = sol.transitionPoint(arr);
    if(transition_index != -1){
        cout << "Transition point (first occurrence of 1) is at index: " << transition_index << endl;
    } else {
        cout << "No transition point found (no 1s in the array)." << endl;
    }
    
    return 0;
}