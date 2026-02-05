#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// approch 1 : using the sort function
int kthLargest_sort(vector<int> &arr, int k)
{
    sort(arr.begin(), arr.end());
    return arr[arr.size() - k];
}
// approch 2 : using min heap
int findKthLargest(vector<int> &nums, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < k; i++)
    {
        pq.push(nums[i]);
    }

    for (int i = k; i < nums.size(); i++)
    {
        if (nums[i] > pq.top())
        {
            pq.pop();
            pq.push(nums[i]);
        }
    }
    return pq.top();
}


//using the quickselect algorithm
class Solution
{
public:
    // Function to get the Kth largest element
    int kthLargestElement(vector<int> &nums, int k)
    {
        // Return -1, if the Kth largest element does not exist
        if (k > nums.size())
            return -1;

        // Pointers to mark the part of working array
        int left = 0, right = nums.size() - 1;

        // Until the Kth largest element is found
        while (true)
        {
            // Get the pivot index
            int pivotIndex = randomIndex(left, right);

            // Update the pivotIndex
            pivotIndex = partition(nums, left, right, pivotIndex); // send the random pivot index  to partition function

            // If Kth largest element is found, return
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
        // length of the array
        int len = right - left + 1;

        // Return a random index from the array
        return (rand() % len) + left;
    }

    int partition(vector<int> &arr, int low, int high, int pivotIndex)
    {
        int pivot = arr[pivotIndex];

        // First, move pivot to end to avoid confusion
        swap(arr[pivotIndex], arr[low]);

        int i = low + 1; // start from the next element of pivot so that we can compare it with pivot
        int j = high;

        while (i <= j)
        {
            // Find element from left that should be on right (smaller than pivot)
            while (i <= j && arr[i] >= pivot)
            {
                i++;
            }
            // Find element from right that should be on left (larger than pivot)
            while (i <= j && arr[j] < pivot)
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
        swap(arr[low], arr[j]); // swap pivot with element at j index so that pivot is at its correct position
        return j;
    }
};

int main()
{
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    int k = 2;
    cout << "Kth largest element using sort function: " << kthLargest_sort(arr, k) << endl;
    cout << "Kth largest element using min heap: " << findKthLargest(arr, k) << endl;
    Solution sol;
    cout << "Kth largest element using quickselect: " << sol.kthLargestElement(arr, k) << endl;

    return 0;
}
