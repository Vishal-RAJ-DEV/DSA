
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
==========================================================================
PROBLEM: Mice and Cheese
==========================================================================
There are n cheeses arranged in a line (index 0 to n-1).
- reward1[i] = points gained if Mouse 1 eats cheese i
- reward2[i] = points gained if Mouse 2 eats cheese i
- Mouse 1 eats EXACTLY k cheeses, Mouse 2 eats the remaining (n - k) cheeses.
- Goal: MAXIMIZE total points.

APPROACH (Greedy):
The key insight is to find which k cheeses give the BIGGEST ADVANTAGE
to Mouse 1 over Mouse 2. The "advantage" is reward1[i] - reward2[i].
If this value is large and positive, Mouse 1 should eat that cheese.
==========================================================================
*/


// ========================== SOLUTION 1 ==========================
// Direct approach: Build list of (difference, index) pairs
// Sort descending, assign top k cheeses to Mouse 1, rest to Mouse 2
// Time: O(n log n), Space: O(n)
class Solution1 {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size();

        // Store (difference, original_index) for each cheese
        // diff = reward1[i] - reward2[i] means how much EXTRA
        // Mouse 1 gives compared to Mouse 2 for cheese i
        vector<pair<int, int>> diff;

        for (int i = 0; i < n; i++) {
            diff.push_back({
                reward1[i] - reward2[i],
                i
            });
        }

        // Sort in descending order (largest difference first)
        // This puts the cheeses where Mouse 1 has the BIGGEST advantage at the front
        sort(diff.rbegin(), diff.rend());

        int ans = 0;

        // After sorting, the first k entries are the k cheeses
        // where Mouse 1 gives the most benefit
        for (int i = 0; i < n; i++) {
            if (i < k) {
                // These k cheeses go to Mouse 1 (highest diff = biggest gain)
                ans += reward1[diff[i].second];
            } else {
                // Remaining cheeses go to Mouse 2
                ans += reward2[diff[i].second];
            }
        }

        return ans;
    }
};


// ========================== SOLUTION 2 ==========================
// Incremental approach: Start with Mouse 2 eating ALL cheeses
// Then add the top k differences to "transfer" those cheeses to Mouse 1
// Time: O(n log n), Space: O(n)
//
// KEY INSIGHT:
// If Mouse 2 eats ALL cheeses, total = sum(reward2)
// When we switch cheese i from Mouse 2 to Mouse 1, the total CHANGES by:
//   (reward1[i] - reward2[i]) = diff[i]
// So we want to pick the k cheeses with the LARGEST positive diff
// to maximize the total.
class Solution2 {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size();

        int ans = 0;
        vector<int> diff;

        // Step 1: Start with the assumption that Mouse 2 eats EVERYTHING
        // This gives us a baseline total = sum of all reward2 values
        for (int i = 0; i < n; i++) {
            ans += reward2[i];          // Baseline: Mouse 2 eats all
            diff.push_back(reward1[i] - reward2[i]); // Gain if Mouse 1 takes over
        }

        // Step 2: Sort differences in descending order
        // Largest gains (biggest reward1 - reward2) come first
        sort(diff.rbegin(), diff.rend());

        // Step 3: Pick the top k differences and add them to the baseline
        // Each diff[i] represents how much MORE we get by switching
        // cheese from Mouse 2 to Mouse 1
        for (int i = 0; i < k; i++) {
            ans += diff[i];  // Transfer cheese from Mouse 2 to Mouse 1
        }

        return ans;
    }
};


int main(){
    return 0;
}


/*
==========================================================================
EXAMPLE to see the difference:
==========================================================================
reward1 = [1, 1, 3, 4]
reward2 = [4, 4, 1, 1]
k = 2

SOLUTION 1 WALKTHROUGH:
  diff[0] = (1-4, 0) = (-3, 0)
  diff[1] = (1-4, 1) = (-3, 1)
  diff[2] = (3-1, 2) = ( 2, 2)
  diff[3] = (4-1, 3) = ( 3, 3)

  After sorting descending: [(3,3), (2,2), (-3,0), (-3,1)]

  i=0 (i < k=2): Mouse 1 eats cheese 3 -> +reward1[3] = +4
  i=1 (i < k=2): Mouse 1 eats cheese 2 -> +reward1[2] = +3
  i=2 (i >= k=2): Mouse 2 eats cheese 0 -> +reward2[0] = +4
  i=3 (i >= k=2): Mouse 2 eats cheese 1 -> +reward2[1] = +4

  Total = 4 + 3 + 4 + 4 = 15

SOLUTION 2 WALKTHROUGH:
  Baseline (Mouse 2 eats all): ans = 4+4+1+1 = 10
  diff = [1-4, 1-4, 3-1, 4-1] = [-3, -3, 2, 3]

  After sorting descending: [3, 2, -3, -3]

  Add top k=2 diffs: ans += 3 + 2 = 5
  Final ans = 10 + 5 = 15

Both give same answer 15, but Solution 2 is more elegant:
  - Starts with worst case (Mouse 2 eats everything)
  - Adds only the GAIN from switching
==========================================================================


==========================================================================
DIFFERENCES BETWEEN THE TWO SOLUTIONS:
==========================================================================
1. STARTING POINT:
   - Solution 1: Starts from scratch (ans = 0), picks each cheese individually
   - Solution 2: Starts with Mouse 2 eating ALL cheeses (ans = sum of reward2)

2. HOW THEY COMPUTE THE ANSWER:
   - Solution 1: ans = sum of reward1 for top k cheeses + sum of reward2 for rest
   - Solution 2: ans = sum of all reward2 + sum of top k differences

3. DATA STRUCTURE:
   - Solution 1: Uses vector<pair<int,int>> to store (diff, index)
   - Solution 2: Uses vector<int> to store only the diff values

4. WHY BOTH WORK:
   Mathematically equivalent. Solution 2 is based on the identity:
     sum(reward1 for k cheeses) + sum(reward2 for rest)
     = sum(all reward2) + sum(diff for those k cheeses)

   This is a common pattern in greedy problems:
     "Start with baseline, then add improvements"
==========================================================================
*/