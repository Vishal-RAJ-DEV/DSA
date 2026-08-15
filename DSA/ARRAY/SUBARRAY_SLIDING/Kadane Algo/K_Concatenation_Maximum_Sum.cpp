#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:

    // MOD is used because the final answer can be very large.
    // The problem asks us to return the answer modulo 1e9 + 7.
    static const long long MOD = 1000000007LL;


    // This function applies Kadane's Algorithm on the array
    // repeated 'times' number of times.
    //
    // For example:
    // arr = [1, -2, 3], times = 2
    // The function considers:
    // [1, -2, 3, 1, -2, 3]
    long long kadane(vector<int>& arr, int times) {

        // 'current' stores the maximum subarray sum
        // ending at the current position.
        long long current = 0;

        // 'best' stores the maximum subarray sum found so far.
        long long best = 0;

        // Store the size of the original array.
        int n = arr.size();


        // We traverse the array 'times' number of times.
        // Instead of actually creating a new array,
        // we use i % n to access the corresponding element.
        for (int i = 0; i < n * times; i++) {

            // Either:
            // 1. Extend the previous subarray by adding arr[i % n], or
            // 2. Start a new subarray from the current element.
            //
            // max(0LL, ...) also allows us to choose an empty subarray,
            // which is important because the problem allows answer = 0.
            current = max(0LL, current + arr[i % n]);

            // Update the maximum subarray sum found so far.
            best = max(best, current);
        }

        // Return the maximum subarray sum.
        return best;
    }


    int kConcatenationMaxSum(vector<int>& arr, int k) {

        // Store the size of the original array.
        int n = arr.size();


        // ---------------------------------------------------------
        // CASE 1: k = 1
        // ---------------------------------------------------------
        //
        // When there is only one copy of the array,
        // we simply need the maximum subarray sum of arr.
        if (k == 1) {

            // Run Kadane's Algorithm on one copy of the array
            // and take modulo MOD before returning.
            return kadane(arr, 1) % MOD;
        }


        // ---------------------------------------------------------
        // Calculate the total sum of one complete copy of arr.
        // ---------------------------------------------------------
        //
        // This value is important because if we take complete
        // middle copies of the array, each copy contributes
        // exactly 'totalSum' to our subarray.
        long long totalSum = 0;

        for (int x : arr) {
            totalSum += x;
        }


        // ---------------------------------------------------------
        // Find the maximum prefix sum.
        // ---------------------------------------------------------
        //
        // A prefix is a subarray starting from the first element.
        //
        // Example:
        // arr = [1, 2, -5, 4]
        // Prefixes are:
        // [1]
        // [1, 2]
        // [1, 2, -5]
        // [1, 2, -5, 4]
        //
        // We need the maximum possible prefix because
        // the maximum subarray may start somewhere in the
        // first copy and then continue through later copies.
        long long prefix = 0;

        // Stores the maximum prefix sum found so far.
        // 0 is included because we are allowed to take
        // an empty prefix.
        long long maxPrefix = 0;

        for (int x : arr) {

            // Add the current element to the prefix sum.
            prefix += x;

            // Keep the maximum prefix sum.
            maxPrefix = max(maxPrefix, prefix);
        }


        // ---------------------------------------------------------
        // Find the maximum suffix sum.
        // ---------------------------------------------------------
        //
        // A suffix is a subarray ending at the last element.
        //
        // We calculate it from right to left because
        // we want a subarray that ends at the end of arr.
        long long suffix = 0;

        // Stores the maximum suffix sum found so far.
        // Again, 0 represents taking an empty suffix.
        long long maxSuffix = 0;

        for (int i = n - 1; i >= 0; i--) {

            // Add the current element to the suffix sum.
            suffix += arr[i];

            // Keep the maximum suffix sum.
            maxSuffix = max(maxSuffix, suffix);
        }


        // ---------------------------------------------------------
        // Find the maximum subarray sum using two copies of arr.
        // ---------------------------------------------------------
        //
        // This handles the case where the maximum subarray
        // lies completely inside two consecutive copies.
        //
        // For example:
        // arr = [1, -2, 3]
        //
        // Two copies:
        // [1, -2, 3, 1, -2, 3]
        //
        // We use Kadane's Algorithm instead of actually
        // creating the concatenated array.
        long long bestTwo = kadane(arr, 2);


        // ---------------------------------------------------------
        // Calculate the contribution of the middle copies.
        // ---------------------------------------------------------
        //
        // There are (k - 2) complete copies between the
        // first and last copies.
        //
        // If totalSum is positive, every complete middle copy
        // increases the sum, so we include all (k - 2) middle copies.
        //
        // If totalSum is negative or zero, adding middle copies
        // cannot improve the maximum subarray sum, so we take
        // 0 contribution from them.
        //
        // Example:
        // totalSum = -2
        // k - 2 = 3
        //
        // Taking all 3 middle copies would contribute:
        // -2 * 3 = -6
        //
        // This decreases our subarray sum, so we are better off
        // not using the middle copies at all.
        //
        // Therefore:
        // middle = max(0, totalSum) * (k - 2)
        long long middle = max(0LL, totalSum) * (k - 2);


        // ---------------------------------------------------------
        // Calculate the final answer.
        // ---------------------------------------------------------
        //
        // There are two important possibilities:
        //
        // 1. The maximum subarray lies completely within
        //    two copies of arr.
        //
        //    -> bestTwo
        //
        // 2. The maximum subarray starts with a suffix of the
        //    first copy, takes all useful middle copies,
        //    and ends with a prefix of the last copy.
        //
        //    -> maxSuffix + middle + maxPrefix
        //
        // We take the maximum of these two possibilities.
        long long answer = max(
            bestTwo,
            maxPrefix + middle + maxSuffix
        );


        // Return the answer modulo 1e9 + 7.
        return answer % MOD;
    }
};

int main(){
    return 0;
}