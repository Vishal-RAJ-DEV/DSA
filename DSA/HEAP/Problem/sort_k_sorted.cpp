#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    // Function to sort the array using brute force
    vector<int> sortNearlySortedArray(vector<int>& arr, int k) {
        // Sort the entire array
        sort(arr.begin(), arr.end());

        // Return the sorted array
        return arr;
    }
};

//optimal approach : using min heap
//time complexity : O(n log k) and space complexity : O(k) where n is the size of the array and k is the given parameter
// The min heap will contain at most k+1 elements at any time, so the space complexity is O(k).
class Solution {
public:
    // Function to sort a k-sorted array using a min heap
    vector<int> sortNearlySortedArray(vector<int>& arr, int k) {
        // Create a min heap using priority_queue with greater comparator
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Store the final sorted result
        vector<int> result;

        // Push first k+1 elements into the heap
        for (int i = 0; i <= k && i < arr.size(); i++) {
            minHeap.push(arr[i]);
        }

        // Process the remaining elements of the array
        for (int i = k + 1; i < arr.size(); i++) {
            // Push the smallest element from the heap to the result
            result.push_back(minHeap.top());
            minHeap.pop();

            // Push the current element into the heap
            minHeap.push(arr[i]);
        }

        // Pop remaining elements from the heap
        while (!minHeap.empty()) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }

        // Return the sorted array
        return result;
    }
};

// Driver code
int main() {
    vector<int> arr = {6, 5, 3, 2, 8, 10, 9};
    int k = 3;

    Solution obj;
    vector<int> sortedArr = obj.sortNearlySortedArray(arr, k);

    for (int num : sortedArr) {
        cout << num << " ";
    }

    return 0;
}
