#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    Logic behind the condition:

    We need to count subarrays of size k whose average is greater than or equal
    to threshold.

    Average of a window = sum / k

    So the condition becomes:
    sum / k >= threshold

    Multiply both sides by k:
    sum >= threshold * k

    This conversion is very useful because while sliding the window, updating
    the sum is easy:
    - add the new element entering the window
    - remove the old element leaving the window

    But directly updating the average every time is not convenient.
    That is why we track the window sum instead of the average.
    */
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = arr.size();
        int left = 0;
        int cnt = 0;
        int sum = 0;

        // This is the minimum sum required for any window of size k
        // to have average >= threshold.
        int target = k * threshold;

        /*
        Algorithm:

        1. Traverse the array using index i as the right end of the window.
        2. Add arr[i] to the current window sum.
        3. When the window size becomes exactly k:
           - check whether sum >= target
           - if yes, increase the answer count
        4. Then slide the window forward by:
           - removing arr[left] from sum
           - incrementing left

        This way, every element is added once and removed once,
        so the total time complexity is O(n).
        */
        for (int i = 0; i < n; i++) {
            // Expand the window by including the current element.
            sum += arr[i];

            // Process the window only when its size becomes exactly k.
            if (i - left + 1 == k) {
                // If current window sum is large enough, its average
                // is also >= threshold.
                if (sum >= target) {
                    cnt++;
                }

                // Remove the leftmost element so that the next window
                // can start from left + 1.
                sum -= arr[left];
                left++;
            }
        }

        return cnt;
    }
};

int main(){
    Solution sol;
    vector<int> arr = {2, 2, 2, 2, 5, 5, 5, 8};
    int k = 3;
    int threshold = 4;

    int result = sol.numOfSubarrays(arr, k, threshold);
    cout << "Number of subarrays of size " << k << " with average >= " << threshold << ": " << result << endl;

    return 0;
}