
#include <bits/stdc++.h>
using namespace std;

// Problem Statement: Given a sorted array of N integers and an integer x, write a program to find the upper bound of x.

// Pre-requisite: Binary Search algorithm

// Examples

// Example 1:
// Input Format: N = 4, arr[] = {1,2,2,3}, x = 2
// Result: 3
// Explanation: Index 3 is the smallest index such that arr[3] > x.

// Example 2:
// Input Format: N = 6, arr[] = {3,5,8,9,15,19}, x = 9
// Result: 4
// Explanation: Index 4 is the smallest index such that arr[4] > x.

/*
 * UPPER BOUND: Find the smallest index such that arr[index] > x
 *
 * Example: arr = {3, 5, 8, 9, 15, 19}, x = 9
 *   Index 0: arr[0]=3  > 9? NO
 *   Index 1: arr[1]=5  > 9? NO
 *   Index 2: arr[2]=8  > 9? NO
 *   Index 3: arr[3]=9  > 9? NO   (not strictly greater)
 *   Index 4: arr[4]=15 > 9? YES  ← upper bound
 *   Index 5: arr[5]=19 > 9? YES
 *   Answer = 4 (smallest index where condition is true)
 *
 * HOW TO RECOGNIZE THIS PATTERN:
 * -------------------------
 * This is also a "FIRST TRUE in a sorted boolean array" problem.
 *
 * The array has a MONOTONIC property when we define:
 *   predicate(i) = (arr[i] > x)
 *
 * This creates a boolean array like:
 *   arr = {3, 5, 8, 9, 15, 19}, x = 9
 *   pred = {F, F, F, F, T, T}    ← FALSEs on left, TRUEs on right
 *
 * We want the FIRST TRUE (leftmost index where predicate is true).
 *
 * MONOTONIC PROPERTY:
 * -------------------------
 * The predicate creates a partition: [FALSE...FALSE | TRUE...TRUE]
 * Once arr[i] > x becomes TRUE, it stays TRUE for all j > i
 * (because array is sorted in non-decreasing order).
 *
 * ELIMINATION STRATEGY:
 * -------------------------
 * At each step, we look at mid:
 *   - If predicate(mid) is TRUE  → mid COULD be answer, but maybe
 *     there's a smaller TRUE to the LEFT. So save mid as candidate
 *     and eliminate RIGHT half: high = mid - 1
 *   - If predicate(mid) is FALSE → mid is NOT the answer, and nothing
 *     to the left can be TRUE either. Eliminate LEFT half: low = mid + 1
 *
 * We eliminate one side each iteration → O(log n)
 *
 * WHERE IS THE ANSWER STORED?
 * -------------------------
 * We use a variable `ans` initialized to n (out of bounds).
 * Every time predicate is TRUE, we save mid to ans and keep searching left.
 * When low > high, ans holds the first index where predicate was true.
 * If no TRUE exists, ans = n (meaning x is >= all elements).
 *
 * DIFFERENCE FROM LOWER BOUND:
 * -------------------------
 *   Lower bound: arr[mid] >= x  (includes equality)
 *   Upper bound: arr[mid] > x   (strictly greater)
 *
 * This small difference changes which elements are in the TRUE partition.
 */

int upperBound(vector<int> &arr, int x, int n) {
    int low = 0, high = n - 1;
    int ans = n;  // Default: if no element > x, return n (out of bounds)

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] > x) {
            // predicate is TRUE: mid is a candidate answer
            ans = mid;           // Save this as best answer so far
            high = mid - 1;      // ELIMINATE RIGHT: look for smaller index on left
        }
        else {
            // predicate is FALSE: mid can't be answer, left side also can't
            low = mid + 1;       // ELIMINATE LEFT: look on right side
        }
    }

    // ans holds the FIRST index where arr[i] > x
    // If no such index exists, ans = n (out of bounds)
    return ans;
}

/*
 * =====================================================
 * ALTERNATIVE: Using low/high to return (no ans variable)
 * =====================================================
 *
 * Instead of tracking `ans` separately, we can use `low` directly.
 *
 * KEY INSIGHT:
 * -------------------------
 * When the loop ends (low > high), `low` always points to the
 * first index where predicate is TRUE.
 *
 * WHY?
 * -------------------------
 * - When predicate is FALSE at mid: low = mid + 1
 *   (low moves PAST all FALSEs, toward the first TRUE)
 * - When predicate is TRUE at mid: high = mid - 1
 *   (high moves LEFT of mid, but low stays or moves right)
 * - Loop ends when low > high
 * - At that point, low is exactly at the first TRUE position
 *
 * VISUAL TRACE: arr = {3, 5, 8, 9, 15, 19}, x = 9
 *   pred = {F, F, F, F, T, T}
 *
 *   Iter 1: low=0, high=5, mid=2 → pred[2]=F → low=3
 *   Iter 2: low=3, high=5, mid=4 → pred[4]=T → high=3
 *   Iter 3: low=3, high=3, mid=3 → pred[3]=F → low=4
 *   Iter 4: low=4, high=3 → STOP
 *   low = 4 ← first TRUE! (correct answer)
 *
 * IF NO TRUE EXISTS:
 *   low will end up at n (one past the last index)
 *   This is the "not found" case, same as ans = n in Method 1
 *
 * COMPARISON:
 * -------------------------
 *   Method 1 (ans variable): explicit tracking, easier to understand
 *   Method 2 (return low):   cleaner code, relies on loop invariant
 *
 * Both are O(log n) and correct.
 */

// METHOD 1: Using ans variable (original)
int upperBound(vector<int> &arr, int x, int n) {
    int low = 0, high = n - 1;
    int ans = n;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] > x) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return ans;
}

// METHOD 2: Using low to return (no ans variable)
int upperBoundLow(vector<int> &arr, int x, int n) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] > x) {
            // TRUE: first TRUE could be at mid or to the left
            // Set high = mid - 1 to search left half
            // low stays, will eventually land on first TRUE
            high = mid - 1;
        }
        else {
            // FALSE: this and everything left is FALSE
            // Move low past mid to search right half
            low = mid + 1;
        }
    }

    // When loop ends: low = first index where arr[i] > x
    // If no such index, low = n (out of bounds)
    return low;
}

int main()
{
    vector<int> arr = {3, 5, 8, 9, 15, 19};
    int n = 6, x = 9;

    int ind1 = upperBound(arr, x, n);
    cout << "Method 1 (ans variable): " << ind1 << "\n";

    int ind2 = upperBoundLow(arr, x, n);
    cout << "Method 2 (return low):   " << ind2 << "\n";

    return 0;
}

//time complexity is o(log n);
//space complexity is o(1);