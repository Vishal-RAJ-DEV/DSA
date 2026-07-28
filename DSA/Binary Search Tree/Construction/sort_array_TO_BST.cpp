#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/**
 * Algorithm:
 * 1. Since the array is sorted, always choose the middle element as the root.
 * 2. Recursively build the left subtree using the left half of the array.
 * 3. Recursively build the right subtree using the right half of the array.
 * 4. Continue this process until the subarray becomes empty (low > high).
 * 5. Return the root node after connecting its left and right subtrees.
 *
 * Logic:
 * - The middle element divides the array into two nearly equal halves,
 *   producing a height-balanced Binary Search Tree (BST).
 * - All elements on the left of the middle are smaller, so they form the
 *   left subtree.
 * - All elements on the right of the middle are larger, so they form the
 *   right subtree.
 * - The recursion naturally builds the tree in a top-down manner, and during
 *   backtracking, each subtree gets connected to its parent node.
 *
 * Time Complexity: O(n)
 * - Every element is visited exactly once to create one tree node.
 *
 * Space Complexity: O(log n)
 * - Recursive call stack for a balanced BST.
 * - Worst case (if unbalanced choice is made): O(n), but here it remains O(log n).
 */

class Solution {
public:
    TreeNode* solve(int low, int high, vector<int>& nums) {

        // Base case:
        // If the current subarray is invalid, no node can be created.
        if (low > high) return nullptr;

        // Find the middle element.
        // It becomes the root of the current subtree.
        int mid = low + (high - low) / 2;

        // Create a new node using the middle element.
        TreeNode* node = new TreeNode(nums[mid]);

        // Recursively construct the left subtree
        // using elements from low to mid - 1.
        node->left = solve(low, mid - 1, nums);

        // Recursively construct the right subtree
        // using elements from mid + 1 to high.
        node->right = solve(mid + 1, high, nums);

        // Return the root of the constructed subtree.
        return node;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {

        // Start with the entire array.
        // The recursive function will keep selecting the middle element
        // of each subarray to build a height-balanced BST.
        return solve(0, nums.size() - 1, nums);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-10, -3, 0, 5, 9};

    TreeNode* root = sol.sortedArrayToBST(nums);

    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    };

    cout << "Inorder traversal of the BST: ";
    inorder(root);
    cout << endl;

    return 0;
}
