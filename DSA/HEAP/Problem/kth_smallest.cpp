#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// approach 1: using the sort function for Kth smallest
int kthSmallest_sort(vector<int> &arr, int k)
{
    sort(arr.begin(), arr.end());
    return arr[k - 1]; // Changed from arr[arr.size() - k] to arr[k - 1]
}

// approach 2: using max heap for Kth smallest
int findKthSmallest(vector<int> &nums, int k)
{
    priority_queue<int> pq; // Changed from min heap to max heap (removed greater<int>)
    
    for (int i = 0; i < k; i++)
    {
        pq.push(nums[i]);
    }

    for (int i = k; i < nums.size(); i++)
    {
        if (nums[i] < pq.top()) // Changed from > to <
        {
            pq.pop();
            pq.push(nums[i]);
        }
    }
    return pq.top();
}

// using the quickselect algorithm for Kth smallest
class Solution
{
public:
    // Function to get the Kth smallest element
    int kthSmallestElement(vector<int> &nums, int k)
    {
        // Return -1, if the Kth smallest element does not exist
        if (k > nums.size())
            return -1;

        // Pointers to mark the part of working array
        int left = 0, right = nums.size() - 1;

        // Until the Kth smallest element is found
        while (true)
        {
            // Get the pivot index
            int pivotIndex = randomIndex(left, right);

            // Update the pivotIndex
            pivotIndex = partition(nums, left, right, pivotIndex);

            // If Kth smallest element is found, return
            if (pivotIndex == k - 1)
                return nums[pivotIndex];

            // Else adjust the end pointers in array
            else if (pivotIndex > k - 1)
                right = pivotIndex - 1;
            else
                left = pivotIndex + 1;
        }
        return -1;
    }

private:
    // Function to get a random index
    int randomIndex(int &left, int &right)
    {
        int len = right - left + 1;
        return (rand() % len) + left;
    }

    int partition(vector<int> &arr, int low, int high, int pivotIndex)
    {
        int pivot = arr[pivotIndex];

        // First, move pivot to end to avoid confusion
        swap(arr[pivotIndex], arr[low]);

        int i = low + 1;
        int j = high;

        while (i <= j)
        {
            // Find element from left that should be on right (larger than pivot)
            while (i <= j && arr[i] <= pivot) // Changed from >= to <=
            {
                i++;
            }
            // Find element from right that should be on left (smaller than pivot)
            while (i <= j && arr[j] > pivot) // Changed from < to >
            {
                j--;
            }

            if (i < j)
            {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }

        // Place pivot in correct position
        swap(arr[low], arr[j]);
        return j;
    }
};

int main()
{
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    int k = 2;
    cout << "Kth smallest element using sort function: " << kthSmallest_sort(arr, k) << endl;
    cout << "Kth smallest element using max heap: " << findKthSmallest(arr, k) << endl;
    Solution sol;
    cout << "Kth smallest element using quickselect: " << sol.kthSmallestElement(arr, k) << endl;

    return 0;
}