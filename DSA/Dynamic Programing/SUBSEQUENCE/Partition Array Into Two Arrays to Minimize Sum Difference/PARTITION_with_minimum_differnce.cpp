#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /*
        This function generates all subset sums for both halves of nums.

        nums has 2 * n elements.
        We split it into:
            left half  -> nums[0] to nums[n - 1]
            right half -> nums[n] to nums[2 * n - 1]

        For every bitmask from 0 to 2^n - 1:
            - If kth bit is ON, we pick kth element from both halves.
            - cnt stores how many elements are picked.
            - leftSum is stored in left[cnt].
            - rightSum is stored in right[cnt].

        So left[x] contains all subset sums made by picking exactly x elements
        from the left half, and right[x] contains all subset sums made by
        picking exactly x elements from the right half.
    */
    void generateSubsetSums(vector<int>& nums, int n, vector<vector<int>>& left,
                            vector<vector<int>>& right) {
        for (int mask = 0; mask < (1 << n); mask++) {
            int cnt = 0;
            int leftSum = 0;
            int rightSum = 0;

            for (int k = 0; k < n; k++) {
                if (mask & (1 << k)) {
                    cnt++;
                    leftSum += nums[k];
                    rightSum += nums[k + n];
                }
            }

            left[cnt].push_back(leftSum);
            right[cnt].push_back(rightSum);
        }
    }

public:
    /*
        Algorithm: Meet in the Middle

        We have 2 * n elements and we need to divide them into two groups of
        exactly n elements each. Let one group sum be s1 and the other group
        sum be s2.

            totalSum = s1 + s2
            difference = |s1 - s2|

        Since s2 = totalSum - s1:

            difference = |s1 - (totalSum - s1)|
                       = |totalSum - 2 * s1|

        So the goal is to choose exactly n elements whose sum s1 is as close
        as possible to totalSum / 2.

        How left and right sums are used:
            1. Split nums into two halves of size n.
            2. Store subset sums by element count:
                   left[i]  -> sums using exactly i elements from left half
                   right[j] -> sums using exactly j elements from right half
            3. If we pick leftCount elements from the left half, then we must
               pick rightCount = n - leftCount elements from the right half.
            4. For every leftSum in left[leftCount], we need a rightSum close
               to:
                   totalSum / 2 - leftSum
               because:
                   s1 = leftSum + rightSum
            5. right[rightCount] is sorted, so lower_bound helps us find the
               closest rightSum efficiently.
    */
    int minimumDifference(vector<int>& nums) {
        int n = nums.size() / 2;
        int totalSum = accumulate(nums.begin(), nums.end(), 0);

        vector<vector<int>> left(n + 1);
        vector<vector<int>> right(n + 1);

        generateSubsetSums(nums, n, left, right);

        // Sort every right[count] list so we can binary search in it.
        for (int count = 0; count <= n; count++) {
            sort(right[count].begin(), right[count].end());
        }

        long long ans = LLONG_MAX;

        // Try every possible number of elements taken from the left half.
        for (int leftCount = 0; leftCount <= n; leftCount++) {
            int rightCount = n - leftCount;

            // For this leftCount, traverse every possible left-side subset sum.
            for (int leftSum : left[leftCount]) {
                double targetRightSum = (double)totalSum / 2.0 - leftSum;

                // We need rightSum close to targetRightSum so that:
                // s1 = leftSum + rightSum is close to totalSum / 2.
                vector<int>& possibleRightSums = right[rightCount];

                auto rightSumIt = lower_bound(possibleRightSums.begin(),
                                              possibleRightSums.end(),
                                              targetRightSum);

                /*
                    Case 1: lower_bound points inside the array.

                    lower_bound gives the first rightSum >= targetRightSum.
                    This value can make s1 closest to totalSum / 2 from the
                    greater-or-equal side, so we check its difference.
                */
                if (rightSumIt != possibleRightSums.end()) {
                    long long s1 = (long long)leftSum + *rightSumIt;
                    long long difference =
                        llabs((long long)totalSum - 2LL * s1);

                    ans = min(ans, difference);
                }

                /*
                    Case 2: Check the value just before lower_bound.

                    The previous rightSum is the largest value <
                    targetRightSum. It can be closer than the lower_bound
                    value, so we must check it also.

                    We only move one step back when rightSumIt is not at
                    begin(), otherwise there is no previous value.
                */
                if (rightSumIt != possibleRightSums.begin()) {
                    rightSumIt--;

                    long long s1 = (long long)leftSum + *rightSumIt;
                    long long difference =
                        llabs((long long)totalSum - 2LL * s1);

                    ans = min(ans, difference);
                }
            }
        }

        return (int)ans;
    }
};
