#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// PROBLEM (LeetCode 2224 - Minimum Number of Operations to Convert Time):
// Given two strings "HH:MM" (current and correct), in one operation you can
// increase the time by 1, 5, 15, or 60 minutes. Find the minimum operations
// needed to convert current into correct. current <= correct always.

// WHY GREEDY WORKS:
// The allowed increments are {60, 15, 5, 1}. Each larger value is a multiple
// of all smaller ones. So using as many of the largest increment as possible
// is always optimal — any replacement of a large increment with smaller ones
// would only increase the count. This is essentially a "coin change" problem
// where the coin denominations are canonical (divisible chain), so greedy is optimal.

// APPROACH:
// 1. Convert both times to total minutes since 00:00
// 2. Compute diff = correct - current
// 3. Try increments from largest to smallest (60 -> 15 -> 5 -> 1)
// 4. For each increment, add diff/increment to answer, set diff %= increment
// Time  : O(1)
// Space : O(1)

class Solution {
public:
    int convertTime(string current, string correct) {
        // Convert "HH:MM" to total minutes
        int curr = stoi(current.substr(0, 2)) * 60 +
                   stoi(current.substr(3, 2));

        int corr = stoi(correct.substr(0, 2)) * 60 +
                   stoi(correct.substr(3, 2));

        int diff = corr - curr;
        vector<int> time = {60, 15, 5, 1};
        int ans = 0;

        for (int t : time) {
            ans += diff / t;
            diff %= t;
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // Test 1: "02:30" -> "04:35" = diff 125 min
    // 125/60 = 2 (120 min), rem 5 -> 5/5 = 1 => total 3
    cout << sol.convertTime("02:30", "04:35") << endl; // 3

    // Test 2: "11:00" -> "11:01" = diff 1 min => 1
    cout << sol.convertTime("11:00", "11:01") << endl; // 1

    // Test 3: "00:00" -> "23:59" = diff 1439 min
    // 1439/60=23 (1380), rem 59 -> 59/15=3 (45), rem 14 -> 14/5=2 (10), rem 4 -> 4/1=4 => total 32
    cout << sol.convertTime("00:00", "23:59") << endl; // 32

    return 0;
}
