/*
QUESTION:
An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
Given an integer n, return the nth ugly number.
By convention, 1 is the first ugly number.

Ugly number sequence: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, ...

Example:
Input:  n = 10
Output: 12
Explanation: The 10th ugly number is 12.

---
*/


#include <iostream>
#include <bits/stdc++.h>
using namespace std;


/**********************************************************************************
 * APPROACH 1: Brute Force (Checking every integer)
 *
 * Intuition:
 *   Starting from 1, check every integer if it's ugly by repeatedly dividing
 *   by 2, 3, and 5. If the final result is 1, it's ugly. Count ugly numbers
 *   until we reach the nth one.
 *
 * Algorithm:
 *   1. i = 0, count = 0
 *   2. While count < n:
 *        - Check if (i+1) is ugly:
 *            Divide by 2,3,5 as much as possible.
 *            If result == 1 → it's ugly → count++
 *        - i++
 *   3. Return i
 *
 * Dry Run (n = 5):
 *   i=0 : num=1 → divide: 1→1 → ugly ✓  count=1  i=1
 *   i=1 : num=2 → /2=1 → ugly ✓         count=2  i=2
 *   i=2 : num=3 → /3=1 → ugly ✓         count=3  i=3
 *   i=3 : num=4 → /2=2→/2=1 → ugly ✓   count=4  i=4
 *   i=4 : num=5 → /5=1 → ugly ✓         count=5  i=5
 *   Return i = 5
 *
 *   Dry Run (n = 10):
 *   i=0 : 1  ÷2,3,5 → 1          → ugly  (1)   count=1
 *   i=1 : 2  ÷2 → 1              → ugly  (2)   count=2
 *   i=2 : 3  ÷3 → 1              → ugly  (3)   count=3
 *   i=3 : 4  ÷2→2 ÷2→1          → ugly  (4)   count=4
 *   i=4 : 5  ÷5→1                → ugly  (5)   count=5
 *   i=5 : 6  ÷2→3 ÷3→1          → ugly  (6)   count=6
 *   i=6 : 7  ÷2→7 ÷3→7 ÷5→7 ≠1  → not ugly    count=6
 *   i=7 : 8  ÷2→4→2→1           → ugly  (8)   count=7
 *   i=8 : 9  ÷3→3→1             → ugly  (9)   count=8
 *   i=9 : 10 ÷2→5 ÷5→1          → ugly  (10)  count=9
 *   i=10: 11 ÷2→11 ÷3→11 ÷5→11 ≠1→ not ugly   count=9
 *   i=11: 12 ÷2→6→3 ÷3→1        → ugly  (12)  count=10
 *   Return i = 12
 *
 * Time  : O(K)  where K is the nth ugly number value (approx exponential → TLE)
 * Space : O(1)
 **********************************************************************************/

class Solution {
private:
    int keepsOndividingUntilPossible(int dividend, int divisor){
        while(dividend % divisor == 0)
            dividend /= divisor;
        return dividend;
    }
public:
    int nthUglyNumber(int n) {
        int i=0, count=0;
        while(count < n){
            int isUgly = i+1;
            for(auto factor : {2,3,5})
                isUgly = keepsOndividingUntilPossible(isUgly, factor);
            if(isUgly == 1) count++;
            i++;
        }
        return i;
    }
};


/**********************************************************************************
 * APPROACH 2: Set (Ordered Set / Min-Heap simulation)
 *
 * Intuition:
 *   Every ugly number is formed by multiplying a smaller ugly number by 2, 3, or 5.
 *   Start with 1. Repeatedly take the smallest number from the set (it's the next
 *   ugly number) and insert its multiples by 2, 3, 5. The set automatically handles
 *   duplicates and keeps numbers sorted.
 *
 * Algorithm:
 *   1. Insert 1 into an ordered set (or min-heap).
 *   2. For i = 0 to n-1:
 *        - nthNumber = smallest element in set
 *        - Erase it (pop)
 *        - Insert nthNumber * 2, nthNumber * 3, nthNumber * 5
 *   3. Return nthNumber
 *
 * Dry Run (n = 10):
 *   Initial set = {1}
 *
 *   i=0 : take 1 , remove 1 , insert 2,3,5         → set = {2,3,5}
 *   i=1 : take 2 , remove 2 , insert 4,6,10        → set = {3,4,5,6,10}
 *   i=2 : take 3 , remove 3 , insert 6,9,15        → set = {4,5,6,9,10,15}
 *   i=3 : take 4 , remove 4 , insert 8,12,20       → set = {5,6,8,9,10,12,15,20}
 *   i=4 : take 5 , remove 5 , insert 10,15,25      → set = {6,8,9,10,12,15,20,25}
 *   i=5 : take 6 , remove 6 , insert 12,18,30      → set = {8,9,10,12,15,18,20,25,30}
 *   i=6 : take 8 , remove 8 , insert 16,24,40      → set = {9,10,12,15,16,18,20,24,25,30,40}
 *   i=7 : take 9 , remove 9 , insert 18,27,45      → set = {10,12,15,16,18,20,24,25,27,30,40,45}
 *   i=8 : take 10, remove 10, insert 20,30,50      → set = {12,15,16,18,20,24,25,27,30,40,45,50}
 *   i=9 : take 12, remove 12, insert 24,36,60      → set = {15,16,18,20,24,25,27,30,36,40,45,50,60}
 *         ↑ return 12
 *
 * Time  : O(N log N)  (N insertions in set, each O(log N))
 * Space : O(N)        (set stores intermediate ugly numbers)
 **********************************************************************************/

class Solution {
public:
    int nthUglyNumber(int n) {
        set<long> st;
        long nthNumber = 1;
        st.insert(nthNumber);

        for(int i=0; i<n; i++){
            nthNumber = *st.begin();
            st.erase(nthNumber);
            st.insert(nthNumber*2);
            st.insert(nthNumber*3);
            st.insert(nthNumber*5);
        }

        return nthNumber;
    }
};


/**********************************************************************************
 * APPROACH 3: Dynamic Programming (Three Pointers) — Most Optimal
 *
 * Intuition:
 *   Ugly numbers form a sequence. Each new ugly number is the minimum of:
 *     (some previous ugly number * 2, some previous ugly number * 3, some previous ugly number * 5)
 *   We maintain three pointers x, y, z that point to the smallest ugly number
 *   that hasn't yet been multiplied by 2, 3, 5 respectively.
 *   Pick the smallest product, advance the pointer(s) that produced it
 *   (to avoid duplicates, advance ALL matching pointers).
 *
 * Algorithm:
 *   1. dp[0] = 1, x=y=z=0
 *   2. For i = 1 to n-1:
 *        dp[i] = min(dp[x]*2, dp[y]*3, dp[z]*5)
 *        If dp[i] == dp[x]*2 → x++
 *        If dp[i] == dp[y]*3 → y++
 *        If dp[i] == dp[z]*5 → z++
 *   3. Return dp[n-1]
 *
 * Dry Run (n = 10):
 *
 *   dp = [1, _, _, _, _, _, _, _, _, _]
 *   x=0 y=0 z=0
 *
 *   i=1 : candidates = 1*2=2, 1*3=3, 1*5=5 → min=2 → dp[1]=2
 *         2 == dp[0]*2 → x=1
 *         dp = [1, 2]
 *
 *   i=2 : candidates = 2*2=4, 1*3=3, 1*5=5 → min=3 → dp[2]=3
 *         3 == dp[0]*3 → y=1
 *         dp = [1, 2, 3]
 *
 *   i=3 : candidates = 2*2=4, 2*3=6, 1*5=5 → min=4 → dp[3]=4
 *         4 == dp[1]*2 → x=2
 *         dp = [1, 2, 3, 4]
 *
 *   i=4 : candidates = 3*2=6, 2*3=6, 1*5=5 → min=5 → dp[4]=5
 *         5 == dp[0]*5 → z=1
 *         dp = [1, 2, 3, 4, 5]
 *
 *   i=5 : candidates = 3*2=6, 2*3=6, 2*5=10 → min=6 → dp[5]=6
 *         6 == dp[2]*2 → x=3
 *         6 == dp[1]*3 → y=2
 *         dp = [1, 2, 3, 4, 5, 6]
 *
 *   i=6 : candidates = 4*2=8, 3*3=9, 2*5=10 → min=8 → dp[6]=8
 *         8 == dp[3]*2 → x=4
 *         dp = [1, 2, 3, 4, 5, 6, 8]
 *
 *   i=7 : candidates = 5*2=10, 3*3=9, 2*5=10 → min=9 → dp[7]=9
 *         9 == dp[2]*3 → y=3
 *         dp = [1, 2, 3, 4, 5, 6, 8, 9]
 *
 *   i=8 : candidates = 5*2=10, 4*3=12, 2*5=10 → min=10 → dp[8]=10
 *         10 == dp[4]*2 → x=5
 *         10 == dp[1]*5 → z=2
 *         dp = [1, 2, 3, 4, 5, 6, 8, 9, 10]
 *
 *   i=9 : candidates = 6*2=12, 4*3=12, 3*5=15 → min=12 → dp[9]=12
 *         12 == dp[5]*2 → x=6
 *         12 == dp[3]*3 → y=4
 *         dp = [1, 2, 3, 4, 5, 6, 8, 9, 10, 12]
 *
 *   Return dp[9] = 12 ✓
 *
 * Time  : O(N)
 * Space : O(N)
 **********************************************************************************/

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);
        dp[0]=1;
        int x=0, y=0, z=0;

        for(int i=1; i<n; i++){
            dp[i] = min(dp[x]*2, min(dp[y]*3, dp[z]*5));

            if(dp[i] == 2*dp[x]) x++;
            if(dp[i] == 3*dp[y]) y++;
            if(dp[i] == 5*dp[z]) z++;
        }

        return dp[n-1];
    }
};


int main(){
    return 0;
}
