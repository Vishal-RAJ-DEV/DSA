#include <iostream>
#include <bits/stdc++.h>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

// =====================================================
// APPROACH 1: Map-based Swaps
// Algorithm:
//   1. Create a sorted copy of the array
//   2. Map each value to its current index using a hashmap
//   3. Iterate through the array:
//      - If an element is already at its correct position (matches sorted), skip
//      - Otherwise, swap it with the element at its correct sorted position
//      - Update both indices in the hashmap after swapping
//      - Increment swap count
//   4. Return total swaps
//
// Logic: This is a greedy approach — at each step, if arr[i] is wrong,
//         we place the correct element (sorted[i]) into position i by swapping.
//         The map tracks where each value currently lives for O(1) lookup.
// =====================================================
class Solution {
public:

    int minimumSwaps(vector<int>& arr) {

        vector<int> sorted = arr;                    // Create a sorted copy of the level values
        sort(sorted.begin(), sorted.end());          // Sort to know target positions

        unordered_map<int,int> pos;                  // Map: value -> its current index in arr

        for(int i = 0; i < arr.size(); i++)          // Build initial position map
            pos[arr[i]] = i;

        int swaps = 0;                               // Count total swaps needed

        for(int i = 0; i < arr.size(); i++) {

            if(arr[i] == sorted[i])                  // Already at correct position — skip
                continue;

            swaps++;                                 // Need one swap to fix this position

            int correctIndex = pos[sorted[i]];       // Where is the correct element currently?

            pos[arr[i]] = correctIndex;              // Update map: arr[i] moves to correctIndex
            pos[sorted[i]] = i;                      // Update map: sorted[i] (correct element) moves to i

            swap(arr[i], arr[correctIndex]);         // Place correct element at i, move wrong element out
        }

        return swaps;                                // Return total swaps for this level
    }

    int minimumOperations(TreeNode* root) {

        queue<TreeNode*> q;                          // Queue for level-order traversal (BFS)
        q.push(root);

        int ans = 0;                                 // Total minimum operations across all levels

        while(!q.empty()) {

            int n = q.size();                        // Number of nodes at the current level
            vector<int> level;                       // Stores values of this level

            while(n--) {                             // Process all nodes of the current level

                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);          // Collect value at this level

                if(node->left)                       // Enqueue left child for next level
                    q.push(node->left);

                if(node->right)                      // Enqueue right child for next level
                    q.push(node->right);
            }

            ans += minimumSwaps(level);              // Add swaps needed to sort this level
        }

        return ans;                                  // Return total across all levels
    }
};


// =====================================================
// APPROACH 2: Cycle Detection
// Algorithm:
//   1. Create an array of pairs: (value, original_index)
//   2. Sort the pairs by value — this tells us where each value SHOULD go
//   3. Use a visited[] array to detect cycles in the permutation
//   4. For each unvisited element, follow the cycle:
//      - Start at index i, go to arr[i].second (the correct position of current value)
//      - Keep going until we loop back to start
//      - Count cycle size
//   5. Minimum swaps for a cycle = cycleSize - 1
//   6. Total swaps = sum of (cycleSize - 1) for all cycles
//
// Logic: If we have a permutation, the optimal way to sort it is to
//         decompose it into cycles. Each cycle of length k needs exactly
//         (k - 1) swaps to fix. This is the minimum possible because
//         each swap can place at most one element in its correct position.
//         Example: [3,1,2] -> sorted [(1,1),(2,2),(3,0)]
//                  Cycle: 0 -> 2 -> 1 -> 0, cycleSize=3, swaps=2
// =====================================================
class Solution {
public:
    // Returns minimum swaps required to sort the array
    int minimumSwaps(vector<int>& nums) {
        int n = nums.size();

        // Store (value, original index) pairs
        vector<pair<int, int>> arr;
        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});             // Pair: value + its current position
        }

        // Sort according to values — after sorting, arr[j].second tells us
        // where the value that belongs at index j currently sits
        sort(arr.begin(), arr.end());

        vector<bool> visited(n, false);              // Track elements already placed correctly
        int swaps = 0;                               // Count total swaps

        for (int i = 0; i < n; i++) {

            // If already visited, or the element is already at its correct position (self-loop), skip
            if (visited[i] || arr[i].second == i)
                continue;

            int cycleSize = 0;                       // Count nodes in the current cycle
            int j = i;                               // Start of the cycle

            // Traverse the cycle: at each step, jump to where the current element SHOULD go
            while (!visited[j]) {
                visited[j] = true;                   // Mark this index as processed
                j = arr[j].second;                   // Follow the cycle: move to the index where current value belongs
                cycleSize++;                         // Increment cycle length
            }

            swaps += (cycleSize - 1);                // A cycle of size k needs exactly (k-1) swaps
        }

        return swaps;                                // Return total swaps for this level
    }

    int minimumOperations(TreeNode* root) {

        queue<TreeNode*> q;                          // Queue for level-order traversal (BFS)
        q.push(root);

        int ans = 0;                                 // Total minimum operations across all levels

        while (!q.empty()) {

            int size = q.size();                     // Number of nodes at the current level
            vector<int> level;                       // Stores values of this level

            while (size--) {                         // Process all nodes of the current level

                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);          // Collect value at this level

                if (node->left)                      // Enqueue left child for next level
                    q.push(node->left);

                if (node->right)                     // Enqueue right child for next level
                    q.push(node->right);
            }

            ans += minimumSwaps(level);              // Add swaps needed to sort this level
        }

        return ans;                                  // Return total across all levels
    }
};

int main(){
    return 0;
}
