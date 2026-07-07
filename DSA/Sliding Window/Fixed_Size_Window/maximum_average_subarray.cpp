#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Approach 1: Fixed-size sliding window.
//
// Idea:
// - We only care about subarrays of length exactly k.
// - Build the sum of the current window as we move right.
// - Once the window size becomes k, compute its average.
// - Before moving to the next window, remove the leftmost element.
//
// Why this works:
// If we already know the sum of a window, the next window can be formed by
// adding one new element on the right and removing one old element from the left.
// That keeps each step O(1), so the whole algorithm is O(n).
class SolutionSlidingWindow {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        long long sum = 0;
        double bestAverage = -1e18;
        int l = 0;

        for( int r = 0 ; r < n ; r++){
            // Expand the window by including nums[r].
            sum += nums[r];

            // When the window size reaches k, we can evaluate it.
            if( r - l + 1 == k){
                bestAverage = max(bestAverage, (double)sum / k);

                // Shrink from the left so the next window also has size k.
                sum -= nums[l];
                l++;
            }
        }

        return bestAverage;
    }
};

// Approach 2: Prefix sum.
//
// Idea:
// - Build prefix[i], the sum of the first i elements.
// - Then any window sum nums[l..r] can be computed as:
//   prefix[r + 1] - prefix[l]
// - After that, every window of size k is checked in O(1) time.
//
// Why this works:
// Prefix sums store cumulative totals, so we can get any subarray sum by
// subtracting two prefix values. This is also O(n), but uses extra memory.
class SolutionPrefixSum {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);

        // prefix[i + 1] stores sum of nums[0..i].
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // Start with the first window of size k.
        double best = (double)(prefix[k] - prefix[0]) / k;

        // Check every other window of length k.
        for (int i = k; i < n; i++) {
            long long windowSum = prefix[i + 1] - prefix[i + 1 - k];
            best = max(best, (double)windowSum / k);
        }

        return best;
    }
};

int main(){
    vector<int> nums = {1,12,-5,-6,50,3};
    int k = 4;

    // Use the sliding-window solution.
    SolutionSlidingWindow obj1;
    double ans1 = obj1.findMaxAverage(nums, k);

    // Use the prefix-sum solution.
    SolutionPrefixSum obj2;
    double ans2 = obj2.findMaxAverage(nums, k);

    cout << fixed << setprecision(5);
    cout << "Sliding window answer: " << ans1 << endl;
    cout << "Prefix sum answer: " << ans2 << endl;

    return 0;
}
