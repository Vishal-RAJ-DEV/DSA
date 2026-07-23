#include <bits/stdc++.h>
using namespace std;

class Memoization {
public:
    /*
    Time Complexity: O(N*K),There are N*K states therefore at max ‘N*K’ new problems will be solved.
    Space Complexity: O(N*K) + O(N),We are using a recursion stack space(O(N)) and a 2D array ( O(N*K)).    
    */
    // Recursive helper function to check if a subset sum equals target
    bool subsetSumUtil(int ind, int target, vector<int>& arr, vector<vector<int>>& dp) {
        /*
            Base Case Logic / Intuition:

            State meaning:
            subsetSumUtil(ind, target) tells us whether we can make "target"
            using elements from index 0 to index ind.

            Base case 1:
            if (target == 0) return true;

            Why?
            A target sum of 0 is always possible by choosing no element.
            This is called the empty subset.

            Example:
            arr = [2, 3, 7], target = 0
            We do not need to pick anything, so answer is true.

            Base case 2:
            if (ind == 0) return arr[0] == target;

            Why?
            If we are standing at index 0, only one element is available: arr[0].
            So the target can be formed only if arr[0] itself is equal to target.

            Example:
            arr[0] = 5
            target = 5 -> true, because we can pick 5.
            target = 3 -> false, because there is no other element to use.
        */

        // Base case: target achieved
        if (target == 0) return true;

        // Base case: at the first index, check if it equals the target
        if (ind == 0) return arr[0] == target;

        // Check memoization table
        if (dp[ind][target] != -1) return dp[ind][target];

        // Choice 1: do not take the current element
        bool notTaken = subsetSumUtil(ind - 1, target, arr, dp);

        // Choice 2: take the current element if possible
        bool taken = false;
        if (arr[ind] <= target) {
            taken = subsetSumUtil(ind - 1, target - arr[ind], arr, dp);
        }

        // Store result in DP table
        return dp[ind][target] = notTaken || taken;
    }

    // Main function to check if subset with sum = k exists
    bool subsetSumToK(int n, int k, vector<int>& arr) {
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        return subsetSumUtil(n - 1, k, arr, dp);
    }
};




class Tabulation {
public:
    //Time Complexity: O(N*K),There are two nested loops
    //Space Complexity: O(N*K), We are using an external array of size ‘N*K’. Stack Space is eliminated.

    // Function to check if there is a subset of 'arr' with a sum equal to 'k'
    bool subsetSumToK(int n, int k, vector<int> &arr) {
        // Initialize a 2D DP array with dimensions (n x k+1) to store subproblem results
        vector<vector<bool>> dp(n, vector<bool>(k + 1, false));

        /*
            How Recursive Base Cases Convert To Tabulation Initialization:

            In recursion, the state is:
            subsetSumUtil(ind, target)

            In tabulation, the same state becomes:
            dp[ind][target]

            Meaning:
            dp[ind][target] = true means we can form "target" using elements
            from index 0 to index ind.

            Recursive base case 1:
            if (target == 0) return true;

            Tabulation conversion:
            dp[i][0] = true for every index i.

            Intuition:
            Sum 0 can be formed at any row/index by taking an empty subset.
            It does not matter how many elements are available; choosing none
            always gives sum 0.

            Recursive base case 2:
            if (ind == 0) return arr[0] == target;

            Tabulation conversion:
            dp[0][arr[0]] = true, if arr[0] <= k.

            Intuition:
            In the first row, only arr[0] is available.
            So the only positive target that can be made is arr[0] itself.

            Example:
            arr = [3, 4, 5], k = 6

            dp[i][0] = true:
            target 0 can be made for every i by taking no elements.

            dp[0][3] = true:
            using only the first element 3, we can make target 3.

            Other values in row 0 stay false:
            using only 3, we cannot make 1, 2, 4, 5, or 6.
        */

        // Base case: If the target sum is 0, we can always achieve it by taking no elements
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }

        // Base case: If the first element of 'arr' is less than or equal to 'k', set dp[0][arr[0]] to true
        if (arr[0] <= k) {
            dp[0][arr[0]] = true;
        }

        // Fill the DP array iteratively
        for (int ind = 1; ind < n; ind++) {
            for (int target = 1; target <= k; target++) {
                // If we don't take the current element, the result is the same as the previous row
                bool notTaken = dp[ind - 1][target];

                // If we take the current element, subtract its value from the target and check the previous row
                bool taken = false;
                if (arr[ind] <= target) {
                    taken = dp[ind - 1][target - arr[ind]];
                }

                // Store the result in the DP array for the current subproblem
                dp[ind][target] = notTaken || taken;
            }
        }

        // The final result is stored in dp[n-1][k]
        return dp[n - 1][k];
    }
};


class SpaceOptimization {
public:
    // Function to check if there is a subset of 'arr' with sum equal to 'k' using space optimization
    bool subsetSumToK(int n, int k, vector<int> &arr) {
        // Initialize a vector 'prev' to represent the previous row of the DP table
        vector<bool> prev(k + 1, false);

        /*
            How Recursive Base Cases Convert To Space Optimization:

            In full tabulation:
            dp[ind][target] depends only on the previous row dp[ind - 1].

            Because of this, we do not need to store the whole 2D table.
            We only store:
            prev -> previous row
            cur  -> current row

            For the first row, prev acts like dp[0].

            Recursive base case 1:
            if (target == 0) return true;

            Space optimization conversion:
            prev[0] = true;

            Intuition:
            Target 0 is always possible by taking no elements.
            Since prev initially represents the first row, prev[0] must be true.

            Recursive base case 2:
            if (ind == 0) return arr[0] == target;

            Space optimization conversion:
            prev[arr[0]] = true, if arr[0] <= k.

            Intuition:
            At the beginning, only arr[0] is available.
            So in the first row, the only positive sum possible is arr[0].

            Why cur[0] = true inside the loop?
            Every new row also needs the target 0 base case.
            For any index ind, sum 0 is possible by taking no element.

            Example:
            arr = [3, 4, 5], k = 6

            Initial prev represents row 0:
            prev[0] = true  -> target 0 possible by empty subset
            prev[3] = true  -> target 3 possible by taking arr[0]

            When moving to the next index, cur[0] is again set to true
            because target 0 remains possible for every row.
        */

        // Base case: sum 0 can always be formed by empty subset
        prev[0] = true;

        // Base case: if first element <= k, mark true
        if (arr[0] <= k) {
            prev[arr[0]] = true;
        }

        // Iterate over all elements from second to last
        for (int ind = 1; ind < n; ind++) {
            vector<bool> cur(k + 1, false);
            cur[0] = true; // sum 0 is always possible

            for (int target = 1; target <= k; target++) {
                bool notTaken = prev[target]; // skip current element
                bool taken = false;

                if (arr[ind] <= target) {
                    taken = prev[target - arr[ind]]; // take current element
                }

                cur[target] = notTaken || taken; // store result for current target
            }

            prev = cur; // move to next iteration
        }

        // Final answer: can we form sum k using all elements?
        return prev[k];
    }
};

// Driver code
int main() {
    vector<int> arr = {1, 2, 3, 4};
    int k = 4;
    int n = arr.size();

    Memoization memo;
    if (memo.subsetSumToK(n, k, arr))
        cout << "Subset with the given target found";
    else
        cout << "Subset with the given target not found";

    return 0;
}
