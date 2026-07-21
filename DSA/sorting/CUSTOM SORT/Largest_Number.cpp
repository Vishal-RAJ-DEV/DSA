#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// LeetCode 179: Largest Number
//
// Intuition:
//   Sorting numbers numerically does not work. For [3, 30], the largest
//   arrangement is "330" (3 then 30), not "303" (30 then 3). So we need
//   a custom comparator that decides order based on which concatenation
//   yields a larger result: if a+b > b+a, then a should precede b.
//
//   This comparator is transitive, so standard sorting works.
//   Edge case: if the largest element is "0", the whole number is "0".

// --- Approach 1: std::sort with custom lambda (idiomatic) ---
// Time: O(n log n), Space: O(n)

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> arr;

        for (int num : nums) {
            arr.push_back(to_string(num));
        }

        // Custom comparator: whichever concatenation is larger wins
        sort(arr.begin(), arr.end(), [](const string& a, const string& b) {
            return a + b > b + a;
        });

        // If the first element is "0", all are zero
        if (arr[0] == "0") return "0";

        string ans = "";
        for (const string& num : arr) {
            ans += num;
        }
        return ans;
    }
};

// --- Approach 2: Bubble Sort (same comparator, O(n^2) variant) ---
// Time: O(n^2), Space: O(n)

typedef long long ll;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string ansa = "";
        int n = nums.size();

        // Handle all-zero case early
        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) break;
            if (i == n - 1 && nums[n - 1] == 0)
                return "0";
        }

        vector<string> ans;
        for (int i = 0; i < n; i++) {
            ans.push_back(to_string(nums[i]));
        }

        // Bubble sort using the same a+b > b+a comparator
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++) {
                string a = ans[j];
                string b = ans[j + 1];

                if (a + b > b + a) {
                    continue; // already in correct order
                } else {
                    swap(ans[j + 1], ans[j]);
                }
            }
        }

        for (auto t : ans) {
            ansa += t;
        }
        return ansa;
    }
};

int main() {
    return 0;
}
