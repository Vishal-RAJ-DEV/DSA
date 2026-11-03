/*
========================================================================================
 PROBLEM: Maximum Erasure Value  (LeetCode 1695)
========================================================================================

 You are given an array of positive integers 'nums'.
 You have to choose a SUBARRAY that contains ONLY UNIQUE (all distinct) elements,
 and among all such subarrays, return the MAXIMUM SUM of its elements.

 Example:
   nums = [4,2,4,5,6]
   Best subarray = [2,4,5,6]  -> sum = 17   (all unique)
   [4,2,4] is invalid because 4 repeats.

 In other words:
   "Find the contiguous subarray with all distinct elements that has the largest sum."

 NOTE:
   - This is a VARIABLE SIZE WINDOW problem because the window keeps growing
     on the right and shrinks from the left only when a duplicate appears.
   - It is NOT the classic "longest subarray" problem -> here we maximise the SUM,
     not the length.

========================================================================================
 APPROACH 1: Sliding Window + Frequency Map (run-sum)
========================================================================================
 Idea:
   - Maintain a window [left ... right] that always has ALL UNIQUE elements.
   - 'score' = running sum of the current window (so no prefix array needed).
   - 'mpp'   = frequency of each element inside the window.

   Steps for every new element nums[i] (right pointer):
   1) While nums[i] is already inside the window (its frequency == 1),
      remove elements from the LEFT one by one:
          score -= nums[left]
          mpp[nums[left]]--
          left++
      This shrinks the window until the duplicate is gone.
   2) Now the window is duplicate-free, so ADD nums[i]:
          score += nums[i]
          mpp[nums[i]]++
   3) Update answer: maxsum = max(maxsum, score).

   Time  : O(n)  -> each element enters and leaves the window at most once.
   Space : O(n)  -> map stores at most all distinct elements.

========================================================================================
 APPROACH 2: Sliding Window + Last Seen Index + Prefix Sum
========================================================================================
 Idea:
   - Instead of shrinking the window step by step, JUMP the left border directly
     past the previous occurrence of the duplicate.
   - prefix[i] = sum of first i elements, so sum(left..right) = prefix[right+1] - prefix[left].

   Steps:
   1) Build prefix sum array.
   2) 'lastSeen[x]' = last index where value x was found.
   3) For each right:
        - If x was seen before AND that occurrence is still inside the window
          (lastSeen[x] >= left), then jump:
                left = lastSeen[x] + 1
        - Record lastSeen[x] = right.
        - Current window sum = prefix[right+1] - prefix[left].
        - Update maxSum.

   Time  : O(n)
   Space : O(n) for prefix array + map.

========================================================================================
 APPROACH 3: Brute Force (two nested loops)
========================================================================================
 Idea:
   - Fix the start of the subarray at index i.
   - Expand j from i to n-1, keep adding elements into a set.
   - The moment a duplicate is found (set already contains nums[j]),
     stop - any longer subarray from this 'i' will also be invalid.
   - Otherwise keep updating the answer.

   Time  : O(n^2)  -> worst case (all distinct) every i runs to the end.
   Space : O(n)    -> set holds the current subarray elements.

   This is the simplest but slowest solution; useful to understand the problem
   before optimising to the O(n) sliding window.

========================================================================================
 NOTE: All three classes are named 'Solution' so that each approach can be compared
 side by side. Only ONE of them should be uncommented/renamed at a time to compile.
========================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// --------------------- APPROACH 1: Sliding Window + Map ---------------------
class Solution {
public:
    // Window [left...i] always holds unique elements, 'score' = its sum
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int>mpp;   // frequency of elements inside the window

        int score = 0;               // running sum of the current window
        int left = 0;                // left border of the window
        int maxsum =0;               // best answer found so far
        for(int i = 0 ; i <n ; i++){

            // Duplicate found: shrink from the left until nums[i] is removed
            // from the window (all elements of window become unique again)
            while(mpp[nums[i]] == 1){
                score-= nums[left];       // subtract leaving element
                mpp[nums[left]]--;        // decrease its frequency
                left++;                   // move window start forward
            }

            // Window is now duplicate-free -> include current element
            score+=nums[i];
            mpp[nums[i]]++; //add its occurence to the map
            maxsum = max(maxsum , score); // update best unique-subarray sum


        }
        return maxsum;
    }
};

// ---------------- APPROACH 2: Last Seen Index + Prefix Sum ----------------
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        // prefix[i] = sum of nums[0..i-1], so sum(left..right) = prefix[right+1]-prefix[left]
        vector<long long> prefix(n + 1, 0);
        unordered_map<int, int> lastSeen;  // value -> its most recent index

        // Build prefix sum array
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        int left = 0;
        long long maxSum = 0;

        for (int right = 0; right < n; right++) {

            int x = nums[right];

            // If x already exists inside the current window, JUMP left
            // directly past its previous occurrence (no step-by-step shrinking)
            if (lastSeen.count(x) && lastSeen[x] >= left) {
                left = lastSeen[x] + 1;
            }

            lastSeen[x] = right;   // remember the latest position of x

            // Sum of unique window [left..right] using prefix sums
            long long currentSum = prefix[right + 1] - prefix[left];

            maxSum = max(maxSum, currentSum);
        }

        return static_cast<int>(maxSum);
    }
};

// ---------------------- APPROACH 3: Brute Force ----------------------
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        int maxSum = 0;

        // Try every possible starting index i
        for (int i = 0; i < n; i++) {
            unordered_set<int> st;   // stores elements of current subarray
            int sum = 0;

            // Expand the subarray to the right as far as elements stay unique
            for (int j = i; j < n; j++) {

                // Duplicate hit -> this and any longer subarray from i is invalid
                if (st.count(nums[j])) {
                    break;
                }

                st.insert(nums[j]);
                sum += nums[j];

                maxSum = max(maxSum, sum);
            }
        }

        return maxSum;
    }
};



int main(){
    return 0;
}