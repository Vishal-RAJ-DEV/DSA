#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Problem idea:
// Find the maximum sum of any subarray of length exactly k such that all
// elements inside that window are distinct.
//
// This file shows two different sliding-window implementations for the same task.
//
// How both approaches are similar:
// - Both maintain a window [l..r].
// - Both keep a running sum of the elements in the window.
// - Both only consider windows of size exactly k.
// - Both move the window from left to right one step at a time.
//
// How they are different:
// - Approach 1 uses an unordered_map to count frequencies.
//   It allows duplicates in the window temporarily, then checks if the window
//   contains exactly k distinct values using mpp.size() == k.
// - Approach 2 uses an unordered_set and immediately removes duplicates
//   before accepting the current window.
//
// In both cases, the sliding window is the core idea:
// - expand by moving r right
// - shrink by moving l right when the window becomes invalid or too large

// Approach 1: frequency map + fixed window size.
class SolutionFrequencyMap {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int , int>mpp;
        int r = 0 ; int l  = 0 ;
        long long sum = 0;
        long long maxi = 0;

                // Slide the right end of the window across the array.
        while( r < n ){
                    // Include nums[r] in the current window.
          sum += nums[r];
          mpp[nums[r]]++;

                        // If the window grew larger than k, remove the leftmost element.
            if( r - l +1 > k ){
                sum-= nums[l];
                mpp[nums[l]]--;
                if( mpp[nums[l]] == 0) mpp.erase(nums[l]);
                l++;
            }

                    // When the window size is exactly k, check whether all values are distinct.
          if( r - l+1 == k && mpp.size() == k){
            maxi = max(maxi , sum);
          }

                    // Move right boundary forward.
          r++;

        }

        return maxi;
    }
};

// Approach 2: unordered_set + duplicate removal.
//
// This version keeps the window distinct at all times.
// If nums[r] is already present, we move l forward and erase elements until
// nums[r] becomes unique in the current window.
//
// Then we insert nums[r], update the sum, and if the window is bigger than k,
// we shrink it from the left.
//
// Difference from Approach 1:
// - Approach 1 waits until the window has size k and then checks the count.
// - Approach 2 actively maintains uniqueness while expanding the window.
class SolutionUniqueWindow {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        unordered_set<int> st;
        long long sum = 0, maxi = 0;
        int l = 0;

        for (int r = 0; r < nums.size(); r++) {

                        // If nums[r] is already in the window, remove elements from the left
                        // until nums[r] becomes unique.
            while (st.count(nums[r])) {
                st.erase(nums[l]);
                sum -= nums[l];
                l++;
            }

                        // Now nums[r] is unique in the current window, so we can add it.
            st.insert(nums[r]);
            sum += nums[r];

                        // If the window became larger than k, remove from the left.
            while (r - l + 1 > k) {
                st.erase(nums[l]);
                sum -= nums[l];
                l++;
            }

                        // If the window size is exactly k, all elements are distinct,
                        // so this is a valid candidate.
            if (r - l + 1 == k) {
                maxi = max(maxi, sum);
            }
        }

        return maxi;
    }
};
using namespace std;
int main(){
    vector<int> nums = {1, 2, 3, 4, 5};
    int k = 3;
    SolutionUniqueWindow sol;
    long long ans = sol.maximumSubarraySum(nums, k);
    cout << "Maximum sum of distinct subarray of size " << k << " is: " << ans << endl;
        
    return 0;
}
