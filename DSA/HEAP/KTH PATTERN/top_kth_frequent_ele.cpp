#include <bits/stdc++.h>
using namespace std;
/*347. Top K Frequent Elements
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
Example 1:

Input: nums = [1,1,1,2,2,3], k = 2

Output: [1,2]

Example 2:

Input: nums = [1], k = 1

Output: [1]

Example 3:

Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2

Output: [1,2]

 */
// A priority queue is a special type of queue where each element has a priority, and elements with higher priority are served before lower priority ones.
// In a normal queue → elements come out in first-in-first-out (FIFO) order.
// In a priority queue → elements come out in order of their priority, not arrival time.
// 👉 In programming, a priority queue is usually implemented using a heap:
// Max-Heap → the largest element comes out first.
// Min-Heap → the smallest element comes out first.

vector<int> topKFrequent(vector<int>& nums, int k) {
    // Step 1: Count frequencies using a hash map
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;               // Increment count for each number
    }

    // Step 2: Use a max-heap (priority queue) ordered by frequency
    // The priority queue stores pairs of (frequency, element)
    priority_queue<pair<int, int>> maxHeap;

    // Insert all elements from the frequency map into the heap
    for (auto& entry : freq) {
        maxHeap.push({entry.second, entry.first});  // Push {frequency, number}
    }

    // Step 3: Extract the k elements with highest frequencies
    vector<int> result;
    for (int i = 0; i < k; i++) {
        result.push_back(maxHeap.top().second);  // Add the number to result
        maxHeap.pop();                           // Remove from heap
    }

    return result;
}
// her the time complexity is O(N log N) because we are inserting N elements into the priority queue, and each insertion takes O(log N) time. The space complexity is O(N) due to the hash map and the priority queue storing up to N elements.

int main() {
    vector<int> nums = {1,1,1,2,2,3};
    int k = 2;

    vector<int> ans = topKFrequent(nums, k);

    cout << "Top " << k << " frequent elements: ";
    for (int x : ans) cout << x << " ";
    cout << endl;

    return 0;
}
