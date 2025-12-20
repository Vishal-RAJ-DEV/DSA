#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// brute force approach
//  time complexity is o(n^2) because of nested loops
int numberOfSubarrays2(vector<int> &nums, int k)
{
    // Initialize counter for total nice subarrays
    int count = 0;

    // Loop over all starting indices
    for (int start = 0; start < nums.size(); start++)
    {
        // Track number of odd elements in current subarray
        int oddCount = 0;

        // Loop over ending indices starting from 'start'
        for (int end = start; end < nums.size(); end++)
        {
            // Check if current number is odd
            if (nums[end] % 2 != 0)
                oddCount++;

            // If odd count exceeds k, break (not nice)
            if (oddCount > k)
                break;

            // If odd count is exactly k, count this subarray
            if (oddCount == k)
                count++;
        }
    }

    // Return total nice subarrays
    return count;
}

// better approach using hashmap
int numberOfSubarrays1(vector<int> &nums, int k)
{

    // Frequency map to track how often a certain odd count has occurred
    unordered_map<int, int> freq;

    // Initialize with 0 count of odd numbers seen so far
    freq[0] = 1;

    // Running count of odd numbers in the current prefix
    int oddCount = 0;

    // Total number of nice subarrays
    int result = 0;

    // Traverse through each element in the array
    for (int num : nums)
    {

        // Check if current number is odd and update count
        if (num % 2 == 1)
            oddCount++;

        // If there exists a prefix with (current odd count - k), add its frequency to result
        if (freq.count(oddCount - k))
        {
            result += freq[oddCount - k];
        }

        // Update the frequency of current odd count
        freq[oddCount]++;
    }

    // Return the total number of valid subarrays
    return result;
}

// optimal approach using sliding window
int atmost(vector<int> &nums, int k)
{
    int left = 0;
    int right = 0;
    int oddcnt = 0;
    int cnt = 0;
    while (right < nums.size())
    {
        if (nums[right] % 2 != 0)
            oddcnt++;
        while (oddcnt > k)
        {
            if (nums[left] % 2 != 0)
            oddcnt--;
            left++;
        }
        // calculate all subaraay where oddcnt is k
        cnt += (right - left + 1);
        right++;
    }
    return cnt;
}
int numberOfSubarrays(vector<int> &nums, int k)
{
    cout<<atmost(nums, k)<<" "<<atmost(nums, k - 1)<<endl;
    return atmost(nums, k) - atmost(nums, k - 1);
}
int main()
{
    vector<int> nums = {1, 1, 2, 1, 1};
    int k = 3;
    cout << numberOfSubarrays(nums, k) << endl;
    return 0;
}
