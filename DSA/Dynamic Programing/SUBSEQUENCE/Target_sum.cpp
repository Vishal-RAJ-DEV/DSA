#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ================= VERSION 1=================
//there is more way to write the code and this is one of the way to write the code

class Memoization {
public:
    /*
        Problem Intuition:
        For every number in nums, we have exactly two choices:
        1. Put a '+' sign before it.
        2. Put a '-' sign before it.

        Example:
        nums = [1, 1, 1], target = 1

        Some possible expressions:
        +1 +1 -1 = 1
        +1 -1 +1 = 1
        -1 +1 +1 = 1

        We need to count how many different sign combinations can make target.

        What does idx mean?
        idx tells us which element we are deciding right now.

        If idx = 0, we are deciding sign for nums[0].
        If idx = 1, we are deciding sign for nums[1].
        If idx = 2, we are deciding sign for nums[2].

        Every recursive call moves to idx + 1 because after choosing '+' or '-'
        for the current number, we go to the next number.

        What does sum mean?
        sum stores the current value made by all signs chosen so far.

        Example:
        nums = [1, 2, 3]

        If we choose:
        +1, then sum = 1
        +1 -2, then sum = -1
        +1 -2 +3, then sum = 2

        Why totalSum is taken?
        The current sum can become negative also.

        Example:
        nums = [1, 2, 3]
        totalSum = 1 + 2 + 3 = 6

        Minimum possible sum = -6, when we take every number as negative.
        Maximum possible sum =  6, when we take every number as positive.

        So possible sums are from -totalSum to +totalSum.

        But array indexes cannot be negative.
        We cannot write dp[idx][-3].

        That is why we shift every sum by totalSum:
        real sum = -6  -> dp index = -6 + 6 = 0
        real sum =  0  -> dp index =  0 + 6 = 6
        real sum =  6  -> dp index =  6 + 6 = 12

        So dp[idx][sum + totalSum] safely stores negative and positive sums.
    */
    int solve( vector<int>&nums , int & target , int idx , int sum ,vector<vector<int>>&dp , int& totalsum){
        //base case 
        // If idx reached nums.size(), it means we have assigned signs
        // to all numbers. Now we check whether the final sum is target.
        if( sum == target && idx == nums.size()) return 1;

        // If all elements are used but sum is not target, this path is invalid.
        if( idx >= nums.size()) return 0;

        //return overlapping subproblem 
        // sum can be negative, so we use sum + totalsum as the valid DP index.
        if( dp[idx][ sum + totalsum] != -1) return dp[idx][sum + totalsum];

        // Choice 1: Put '+' before nums[idx].
        // Then current sum increases by nums[idx].
        int postive = solve(nums , target , idx + 1 , sum + nums[idx] , dp , totalsum);

        // Choice 2: Put '-' before nums[idx].
        // Then current sum decreases by nums[idx].
        int negative = solve( nums, target , idx + 1 , sum - nums[idx] , dp , totalsum);

        // Total ways from this state = ways from positive choice + negative choice.
        return dp[idx][sum + totalsum] = postive + negative;
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int totalsum = 0;
        //get the total sum of the nums 
        for( int i =0 ; i < n ; i++){
            totalsum += nums[i];
        }
        //here size is 2* totalsum + 1 beacuse if we take negative value -5 then -5+5 = 0th index 
        // and at 5+5 = 10th index , so total size is 2*5+1 = 11 size elements 
        // DP columns represent all possible sums from -totalsum to +totalsum.
        // Since that range has 2 * totalsum + 1 values, this is the required size.
        vector<vector<int>>dp(nums.size() , vector<int>( 2*totalsum + 1, -1));

        // Start from index 0 with current sum 0 because no number has been used yet.
        return solve( nums , target , 0 , 0 , dp , totalsum);
    }
};
class MemoizationAccordingToTabulation {
public:
    /*
        This memoization is written according to the tabulation code below.

        Tabulation state:
        dp[i][sum + totalSum] means:
        using the first i elements, how many ways can we create "sum"?

        So here also:
        solve(i, sum) means:
        using the first i elements of nums, how many ways can we create "sum"?

        Important:
        i is not the actual array index.
        i means number of elements used.

        i = 0 means no elements are used.
        i = 1 means nums[0] is used.
        i = 2 means nums[0] and nums[1] are used.

        Therefore, when we are solving for i elements,
        the current element is nums[i - 1].

        Algorithm direction:
        This version works backward from the final answer.

        We start from:
        solve(n, target)

        Meaning:
        "Using all n elements, how many ways can we make target?"

        Then every recursive call reduces i:
        solve(n, target)
        -> solve(n - 1, some previous sum)
        -> solve(n - 2, some previous sum)
        -> ...
        -> solve(0, 0)

        So the element count goes from n elements to 0 elements.
        At the same time, the required sum is moved backward from target
        toward 0.

        Why target goes toward 0?
        Suppose current element is curr.

        If curr was used with '+' sign, then before using curr,
        we needed sum - curr.

        If curr was used with '-' sign, then before using curr,
        we needed sum + curr.

        So we reverse the decision and ask:
        "What previous sum was needed before this element?"

        Finally, when no elements are left, the only valid required sum is 0.
    */
    int solve(vector<int>& nums,
              int i,
              int sum,
              int totalSum,
              vector<vector<int>>& dp) {

        /*
            Base case according to tabulation:

            dp[0][totalSum] = 1

            In recursion form:
            if i == 0, no elements are used.

            With no elements:
            - sum 0 is possible in 1 way: choose nothing.
            - any other sum is impossible.
        */
        if(i == 0) {
            if(sum == 0)
                return 1;

            return 0;
        }

        /*
            If sum goes outside the possible range,
            it cannot be formed.

            Possible sums are only from -totalSum to +totalSum.
        */
        if(sum < -totalSum || sum > totalSum)
            return 0;

        // sum can be negative, so store it at index sum + totalSum.
        if(dp[i][sum + totalSum] != -1)
            return dp[i][sum + totalSum];

        int curr = nums[i - 1];

        /*
            To make final "sum" using first i elements,
            we have two choices for nums[i - 1]:

            1. Put '+' before curr.
               Previous sum must be: sum - curr
               because (sum - curr) + curr = sum

            2. Put '-' before curr.
               Previous sum must be: sum + curr
               because (sum + curr) - curr = sum

            Notice:
            We are moving from current required sum back to the previous
            required sum.

            That is why this recursion starts from target and keeps moving
            backward until the required sum becomes 0 at i == 0.
        */
        int positive = solve(nums,
                             i - 1,
                             sum - curr,
                             totalSum,
                             dp);

        int negative = solve(nums,
                             i - 1,
                             sum + curr,
                             totalSum,
                             dp);

        return dp[i][sum + totalSum] = positive + negative;
    }

    int findTargetSumWays(vector<int>& nums, int target) {

        int n = nums.size();

        int totalSum = 0;

        for(int num : nums) {
            totalSum += num;
        }

        // If target is outside possible range, answer is 0.
        if(abs(target) > totalSum)
            return 0;

        int range = 2 * totalSum + 1;

        /*
            dp has n + 1 rows because i means number of elements used.

            i = 0 is needed for the base case:
            using 0 elements, only sum 0 is possible.

            Columns represent sums from -totalSum to +totalSum,
            so size is 2 * totalSum + 1.
        */
        vector<vector<int>> dp(n + 1,
                               vector<int>(range, -1));

        /*
            Start from the final question:
            using first n elements, how many ways can we make target?

            Recursion will go from:
            i = n to i = 0

            and from:
            required sum = target back toward required sum = 0.
        */
        return solve(nums,
                     n,
                     target,
                     totalSum,
                     dp);
    }
};
class Tabulation{
public:
    int findTargetSumWays(vector<int>& nums, int target) {

        int n = nums.size();

        int totalSum = 0;

        for(int num : nums) {
            totalSum += num;
        }

        /*
            Tabulation Intuition:

            dp[i][sum + totalSum] means:
            using the first i elements, how many ways can we create "sum"?

            Here i is not the actual array index.
            i means "how many elements have been processed".

            i = 0 means no elements are used.
            i = 1 means nums[0] is used.
            i = 2 means nums[0] and nums[1] are used.

            That is why the current element is nums[i - 1].

            Why totalSum is used again?
            Because sum can be negative, but vector index cannot be negative.
            So we store sum at index sum + totalSum.

            Example:
            totalSum = 5

            sum = -5 is stored at index 0.
            sum =  0 is stored at index 5.
            sum =  5 is stored at index 10.
        */

        // Edge case:
        // target outside possible range

        if(abs(target) > totalSum)
            return 0;

        int range = 2 * totalSum + 1;

        // dp[i][sum + totalSum]
        // = number of ways to reach 'sum'
        // using first i elements

        vector<vector<int>> dp(n + 1,
                               vector<int>(range, 0));

        // Base Case:
        // Using 0 elements,
        // only sum 0 is possible in 1 way

        // sum 0 is stored at index 0 + totalSum.
        /*
            If this tabulation base case was written as a recursion
            base case, it would look like this:

            int solve(int i, int sum) {
                if(i == 0) {
                    if(sum == 0)
                        return 1;

                    return 0;
                }
            }

            Meaning:
            - i == 0 means no elements are used.
            - With no elements, only sum 0 can be formed.
            - So sum 0 has 1 way: choose nothing.
            - Any other sum has 0 ways.

            That is exactly why tabulation writes:
            dp[0][0 + totalSum] = 1;

            We use totalSum shift because real sum 0 is stored at
            index 0 + totalSum.
        */
        dp[0][totalSum] = 1;

        // Process elements one by one

        for(int i = 1; i <= n; i++) {

            // Since i means first i elements, the new element added now is nums[i - 1].
            int curr = nums[i - 1];

            for(int sum = -totalSum;
                sum <= totalSum;
                sum++) {

                //this the value of way to make "sum" using first i-1 elements
                int ways =
                    dp[i - 1][sum + totalSum];

                if(ways > 0) {

                    // Positive sign

                    // If old sum was "sum", then adding +curr makes sum + curr.
                    int positiveSum = sum + curr;

                    dp[i][positiveSum + totalSum]
                        += ways;

                    // Negative sign

                    // If old sum was "sum", then adding -curr makes sum - curr.
                    int negativeSum = sum - curr;

                    dp[i][negativeSum + totalSum]
                        += ways;
                }
            }
        }

        return dp[n][target + totalSum];
    }
};
class SpaceOptimized{
public:
    int findTargetSumWays(vector<int>& nums, int target) {

        int n = nums.size();

        int totalSum = 0;

        for(int num : nums) {
            totalSum += num;
        }

        // If target is outside possible range

        if(abs(target) > totalSum)
            return 0;

        int range = 2 * totalSum + 1;

        /*
            Space Optimization Intuition:

            In tabulation, dp[i] depends only on dp[i - 1].
            So instead of storing the full 2D table, we keep only one previous row.

            prev[sum + totalSum] means:
            before processing the current number, how many ways can we make "sum"?

            curr[sum + totalSum] means:
            after processing the current number, how many ways can we make "sum"?

            The index shift using totalSum is still needed because sums can be negative.
        */

        // prev[sum + totalSum]
        // = number of ways to make 'sum'

        vector<int> prev(range, 0);

        // Base case:
        // Sum 0 possible in 1 way

        prev[totalSum] = 1;

        for(int i = 0; i < n; i++) {

            vector<int> curr(range, 0);

            // Try every sum that was possible before using nums[i].
            for(int sum = -totalSum;
                sum <= totalSum;
                sum++) {

                int ways =
                    prev[sum + totalSum];

                if(ways > 0) {

                    // Take positive sign

                    // Put '+' before nums[i].
                    int positiveSum =
                        sum + nums[i];

                    curr[positiveSum + totalSum]
                        += ways;

                    // Take negative sign

                    // Put '-' before nums[i].
                    int negativeSum =
                        sum - nums[i];

                    curr[negativeSum + totalSum]
                        += ways;
                }
            }

            // Current row becomes previous row for the next element.
            prev = curr;
        }

        return prev[target + totalSum];
    }
};

//=================VERSION 2 ===================
//this is proper way to write the code and this is more readable than version 1
//where we convert the target sum problem into count subsets with sum k
//read  notes to get the intuition of the code and how we convert the target sum problem into count subsets with sum k

/*
    VERSION 2 ALGORITHM:

    First thought:
    We can generate all possibilities by putting '+' or '-' before every
    number and count the expressions that become equal to target.

    But this creates 2^n possibilities, so we use a DP idea from:
    Count Partitions With Given Difference / Count Subsets With Sum K.

    Main Intuition:
    Suppose all numbers with '+' sign form one group and all numbers with
    '-' sign form another group.

    Example:
    nums = [a, b, c, d, e]

    Expression:
    +a -b -c +d +e

    This can be seen as:
    positive group = a + d + e
    negative group = b + c

    Let:
    S1 = sum of positive group
    S2 = sum of negative group

    Because negative group is subtracted:
    S1 - S2 = target        ---- (1)

    Total sum of all elements:
    S1 + S2 = totalSum      ---- (2)

    From equation (2):
    S1 = totalSum - S2

    Put this in equation (1):
    totalSum - S2 - S2 = target
    totalSum - 2*S2 = target
    2*S2 = totalSum - target
    S2 = (totalSum - target) / 2

    So the problem becomes:
    Count the number of subsets whose sum is:
    (totalSum - target) / 2

    Why?
    Every subset with sum S2 can be treated as the group that gets '-'.
    All remaining numbers automatically become the '+' group.

    Edge Cases:
    1. If abs(target) > totalSum, answer is 0.
       Because even if we put all signs in one direction, we cannot cross
       the total sum range.

    2. If totalSum - target is odd, answer is 0.
       Because S2 must be an integer subset sum.

    3. Zero handling:
       If nums contains 0, then picking 0 or not picking 0 both keep the
       sum same, but they are two different choices.

       That is why the memoization base case has:
       if target == 0 and nums[0] == 0, return 2.
*/

class MemoizationVersion2 {
public:
    // Function to count number of ways to assign '+' or '-' to reach target
    int findTargetSumWays(vector<int>& nums, int target) {
        // Calculate the total sum of the array
        int totalSum = accumulate(nums.begin(), nums.end(), 0);

        /*
            We need subsetSum = (totalSum - target) / 2.

            If target is outside possible range, no expression can make it.
            If totalSum - target is odd, subsetSum becomes a fraction,
            which is impossible because array elements are integers.
        */
        if (abs(target) > totalSum || (totalSum - target) % 2 != 0)
            return 0;

        // Our problem reduces to subset sum with sum = (totalSum - target) / 2
        int subsetSum = (totalSum - target) / 2;

        // Initialize memo table with -1
        vector<vector<int>> dp(nums.size(), vector<int>(subsetSum + 1, -1));

        // Call recursive function with memoization
        return countSubsets(nums, nums.size() - 1, subsetSum, dp);
    }

private:
    // Recursive function with memoization
    int countSubsets(vector<int>& nums, int ind, int target, vector<vector<int>>& dp) {
        /*
            State:
            countSubsets(ind, target) means:
            count the number of subsequences from index 0 to ind
            whose sum is equal to target.

            Base case:
            When ind == 0, only nums[0] is available.

            If nums[0] == 0 and target == 0:
            There are 2 ways:
            1. Do not pick 0
            2. Pick 0

            Both make sum 0, but they are different subsequences.
        */
        if (ind == 0) {
            if (target == 0 && nums[0] == 0) return 2; // {pick or not pick 0}
            if (target == 0 || target == nums[0]) return 1; // Either pick or skip
            return 0; // Otherwise no valid way
        }

        // Return if already computed
        if (dp[ind][target] != -1) return dp[ind][target];

        // Exclude current element
        int notPick = countSubsets(nums, ind - 1, target, dp);

        // Include current element if it is <= target
        int pick = 0;
        if (nums[ind] <= target)
            pick = countSubsets(nums, ind - 1, target - nums[ind], dp);

        // Store and return result
        return dp[ind][target] = pick + notPick;
    }
};



class TabulationVersion2 {
public:
    // Function to find number of ways to assign + or - to reach the target
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();

        // First calculate the total sum of all numbers
        int totalSum = accumulate(nums.begin(), nums.end(), 0);

        /*
            We are counting subsets with sum:
            newTarget = (totalSum - target) / 2

            If target is outside possible range or newTarget is not an
            integer, there is no valid answer.
        */
        if (abs(target) > totalSum || (totalSum - target) % 2 != 0) return 0;

        // We now need to count subsets with sum = (totalSum - target) / 2
        int newTarget = (totalSum - target) / 2;

        /*
            dp[i][j] means:
            number of ways to make sum j using the first i numbers.

            i = 0 means no numbers are used.
            j = 0 means target sum is 0.
        */
        vector<vector<int>> dp(n + 1, vector<int>(newTarget + 1, 0));

        /*
            Base case:
            Sum 0 can always be formed by taking no elements.

            So dp[i][0] = 1 for every i.

            Important for zero:
            The loop below starts j from 0, so if nums[i - 1] == 0,
            then:
            dp[i][0] = dp[i - 1][0] + dp[i - 1][0]

            This correctly doubles the count because picking 0 and not
            picking 0 are two different choices.
        */
        for (int i = 0; i <= n; i++) dp[i][0] = 1;

        // Fill DP table iteratively
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= newTarget; j++) {
                // Not pick: exclude current element nums[i - 1]
                dp[i][j] = dp[i - 1][j];

                // Pick: include current element if it does not exceed current target j
                if (nums[i - 1] <= j) {
                    dp[i][j] += dp[i - 1][j - nums[i - 1]];
                }
            }
        }

        return dp[n][newTarget];
    }
};


class SpaceOptimizedVersion2 {
public:
    // Function to count number of ways to assign signs to reach the target
    int findTargetSumWays(vector<int>& nums, int target) {
        // Step 1: calculate total sum of array
        int total = accumulate(nums.begin(), nums.end(), 0);

        // Step 2: check feasibility
        if (abs(target) > total || (total - target) % 2 != 0) return 0;

        // Step 3: new target for subset sum problem
        int newTarget = (total - target) / 2;

        /*
            Space Optimized Conversion:

            In 2D tabulation:
            dp[i][j] depends on:
            1. dp[i - 1][j]              -> not pick
            2. dp[i - 1][j - nums[i-1]]  -> pick

            So every row depends only on the previous row.

            Normally we can optimize 2D dp into two arrays:
            prev and curr.

            But here we can optimize further into only one dp array.

            dp[j] means:
            number of ways to make sum j using the elements processed so far.

            For every num:
            dp[j] = dp[j] + dp[j - num]

            Meaning:
            - old dp[j] is the not-pick value
            - dp[j - num] is the pick value

            Why do we iterate j from right to left?
            Because this is 0/1 subsequence logic.
            Each element can be used only once.

            If we go left to right, then dp[j - num] may already be updated
            using the current num, so the same element may be counted again.

            By going right to left:
            dp[j - num] still belongs to the previous state before using
            the current num.

            That is how one array safely behaves like prev and curr together.

            Zero handling:
            If num == 0, then:
            dp[j] += dp[j - 0]
            dp[j] += dp[j]

            This doubles the number of ways, which is correct because
            zero can be picked or skipped without changing the sum.
        */

        // Step 4: initialize dp array of size newTarget + 1 with 0
        vector<int> dp(newTarget + 1, 0);

        // Step 5: base case: one way to form sum 0 (by choosing nothing)
        dp[0] = 1;

        // Step 6: iterate over each number
        for (int num : nums) {
            // Step 7: update dp array from right to left
            for (int j = newTarget; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }

        // Step 8: final answer
        return dp[newTarget];
    }
};
int main(){
    SpaceOptimizedVersion2 sol;
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    cout << sol.findTargetSumWays(nums, target) << endl;
    return 0;
}
