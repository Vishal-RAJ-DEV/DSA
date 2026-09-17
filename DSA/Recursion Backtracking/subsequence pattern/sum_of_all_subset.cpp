#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Helper function to generate subset sums recursively
    void findSums(int index, int currentSum, vector<int> &arr, vector<int> &sums)
    {
        // Base case: if we have considered all elements
        if (index == arr.size())
        {
            sums.push_back(currentSum);
            return;
        }

        // Include current element
        findSums(index + 1, currentSum + arr[index], arr, sums);

        // Exclude current element
        findSums(index + 1, currentSum, arr, sums);
    }

    // Main function
    vector<int> subsetSums(vector<int> &arr)
    {
        vector<int> sums;
        findSums(0, 0, arr, sums);
        sort(sums.begin(), sums.end()); // Sort in increasing order
        return sums;
    }

    // using bitmasking to find subset sums
    // Function to find all subset sums using bitmasking
    vector<int> subsetSums(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> sums;

        // There are 2^n possible subsets for n elements.
        // We use numbers from 0 to 2^n - 1 as "masks".
        // Each bit of mask tells whether to pick one element or not.
        //
        // Example: arr = {5, 2, 1}, n = 3
        // mask = 0 -> binary 000 -> pick nothing        -> sum = 0
        // mask = 1 -> binary 001 -> pick arr[0]         -> sum = 5
        // mask = 2 -> binary 010 -> pick arr[1]         -> sum = 2
        // mask = 3 -> binary 011 -> pick arr[0], arr[1] -> sum = 7
        // ...
        // mask = 7 -> binary 111 -> pick all elements   -> sum = 8
        //
        // (1 << n) means 2^n.
        // So this loop runs from 0 to 2^n - 1 and covers every subset.
        for (int mask = 0; mask < (1 << n); mask++)
        {
            int sum = 0; // store sum of current subset
            for (int i = 0; i < n; i++)
            {
                // (1 << i) creates a number with only the ith bit set.
                //
                // Example:
                // i = 0 -> (1 << 0) = 001
                // i = 1 -> (1 << 1) = 010
                // i = 2 -> (1 << 2) = 100
                //
                // mask & (1 << i) checks whether the ith bit of mask is 1.
                // If it is 1, arr[i] belongs to the current subset.
                //
                // Example: mask = 5 -> binary 101
                // i = 0: 101 & 001 = 001, so include arr[0]
                // i = 1: 101 & 010 = 000, so do not include arr[1]
                // i = 2: 101 & 100 = 100, so include arr[2]
                if (mask & (1 << i))
                {
                    sum += arr[i];
                }
            }
            sums.push_back(sum);
        }

        // Sort sums to get increasing order
        sort(sums.begin(), sums.end());
        return sums;
    }
};

// Driver code
int main()
{
    Solution sol;
    vector<int> arr = {5, 2, 1};
    vector<int> result = sol.subsetSums(arr);

    for (int sum : result)
    {
        cout << sum << " ";
    }
    cout << endl;

    cout << "Now using bitmasking approach:" << endl;
    vector<int> resultBitmask = sol.subsetSums(arr);
    for (int sum : resultBitmask)
    {
        cout << sum << " ";
    }
    cout << endl;

    return 0;
}
