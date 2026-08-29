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


/*
 * PROBLEM: Count Good Leaf Nodes Pairs
 * ---------------------------------------------------------------
 * Given a binary tree and an integer distance, count the number
 * of good leaf node pairs.
 *
 * A "good pair" is two leaf nodes where the distance between them
 * (number of edges on the path) is <= distance.
 *
 * INPUT:  Binary tree root, integer distance
 * OUTPUT: Number of good leaf node pairs
 *
 * EXAMPLE:
 *         1
 *        / \
 *       2   3
 *      / \
 *     4   5
 *
 *   Leaf nodes: 4, 5, 3
 *   Distance between leaves:
 *     (4,5): 4→2→5 = 2 edges
 *     (4,3): 4→2→1→3 = 3 edges
 *     (5,3): 5→2→1→3 = 3 edges
 *
 *   If distance = 3:
 *     (4,5): 2 <= 3 ✅ good pair
 *     (4,3): 3 <= 3 ✅ good pair
 *     (5,3): 3 <= 3 ✅ good pair
 *   Answer = 3
 *
 * INTUITION: BOTTOM-UP DFS
 * ---------------------------------------------------------------
 * The key idea is to think from each node's perspective:
 *
 *   "Which leaf nodes in my subtree are at what distance from me?"
 *
 * For each node, we collect distances of all leaf nodes below it.
 * Then we PAIR leaves from left subtree with leaves from right subtree.
 *
 * WHY?
 *   If left subtree has a leaf at distance l from current node,
 *   and right subtree has a leaf at distance r from current node,
 *   then the path between those two leaves goes THROUGH current node:
 *
 *         current
 *        /       \
 *    left leaf   right leaf
 *      (l)         (r)
 *
 *   Total distance = l + r + 2
 *     - l edges from left leaf to current node
 *     - r edges from right leaf to current node
 *     - +2 because l and r don't count the edges from current to children
 *
 *   Wait, actually: l = distance from current's child to leaf
 *   So total = l + 1 (to current) + r + 1 (to current) = l + r + 2
 *
 * HOW THE CODE WORKS:
 * ---------------------------------------------------------------
 * 1. DFS returns a list of distances from current node to all
 *    leaf nodes in its subtree.
 *
 * 2. Base case: if node is a leaf, return {0} (distance 0 to itself)
 *
 * 3. Recursively get distances from left and right children
 *
 * 4. COUNT GOOD PAIRS:
 *    For every l in left distances and r in right distances:
 *      if l + r + 2 <= maxDistance → it's a good pair → ans++
 *
 * 5. RETURN distances to parent:
 *    Merge left and right distances, increment each by 1
 *    (because parent is 1 edge further away)
 *    Only keep distances < maxDistance (pruning: useless to pass
 *    distances that are already too large)
 *
 * VISUAL EXAMPLE:
 *         1 (maxDistance=3)
 *        / \
 *       2   3
 *      / \
 *     4   5
 *
 *   Node 4 (leaf): return {0}
 *   Node 5 (leaf): return {0}
 *
 *   Node 2:
 *     left = {0} (from 4)
 *     right = {0} (from 5)
 *     Pair: 0 + 0 + 2 = 2 <= 3 → ans++ (pair 4-5)
 *     Return: {1} (both leaves are 1 edge from node 2)
 *
 *   Node 3 (leaf): return {0}
 *
 *   Node 1:
 *     left = {1} (from node 2, representing leaves 4,5)
 *     right = {0} (from node 3)
 *     Pair: 1 + 0 + 2 = 3 <= 3 → ans++ (pair 4-3 or 5-3)
 *     Actually: left has {1}, right has {0}
 *     1 + 0 + 2 = 3 <= 3 → ans++ (represents leaf 4 or 5 paired with 3)
 *
 *   Wait, node 2 returns {1} which represents BOTH leaves 4 and 5.
 *   But the list only has one entry {1}... that's because
 *   leaves at the SAME distance are merged.
 *
 *   Actually, looking more carefully:
 *     Node 2: left={0}, right={0}
 *     Pair count: 0+0+2=2 <=3 → 1 pair (4-5)
 *     Return {1, 1}? No, return {1} (merged)
 *
 *   Hmm, let me re-examine... The code pushes l+1 for each l in left,
 *   and r+1 for each r in right. So node 2 returns {0+1, 0+1} = {1, 1}
 *   which gets merged into result.
 *
 *   Actually the result vector can have duplicate distances!
 *   Each entry represents ONE leaf node at that distance.
 *
 *   Node 2:
 *     left = {0} (leaf 4)
 *     right = {0} (leaf 5)
 *     Pair: 0+0+2=2 <=3 → 1 pair (4-5) ✓
 *     Return: {0+1} ∪ {0+1} = {1, 1}
 *     (Two entries: one for leaf 4, one for leaf 5, both distance 1 from node 2)
 *
 *   Node 1:
 *     left = {1, 1} (leaves 4 and 5, each distance 1 from node 2)
 *     right = {0} (leaf 3)
 *     Pairs:
 *       1+0+2=3 <=3 → ans++ (leaf 4 with leaf 3)
 *       1+0+2=3 <=3 → ans++ (leaf 5 with leaf 3)
 *     Total ans = 3 ✓
 *
 * WHY PRUNE (l+1 < maxDistance)?
 * ---------------------------------------------------------------
 * If a leaf is already at distance >= maxDistance from current node,
 * passing it up to parent makes it even FURTHER (distance+1).
 * It can never form a good pair with anything, so we discard it.
 * This keeps the lists small and the algorithm efficient.
 */

class Solution {
public:
    int ans = 0;           // Total count of good leaf node pairs
    int maxDistance;        // Maximum allowed distance for a good pair

    // Returns a list of distances from `node` to all leaf nodes in its subtree
    // Each entry in the list represents ONE leaf node at that distance
    vector<int> dfs(TreeNode* node) {

        // Base case: empty node contributes nothing
        if (node == nullptr) {
            return {};
        }

        // Base case: leaf node is at distance 0 from itself
        if (node->left == nullptr && node->right == nullptr) {
            return {0};
        }

        // Recursively get leaf distances from left and right subtrees
        vector<int> left = dfs(node->left);
        vector<int> right = dfs(node->right);

        // COUNT GOOD PAIRS:
        // For each leaf in left subtree at distance l from current node,
        // and each leaf in right subtree at distance r from current node,
        // the path between them is: l + r + 2
        //   (l edges from left leaf to current's child)
        //   + 1 (child to current)
        //   + 1 (current to right's child)
        //   + r edges (right's child to right leaf)
        // = l + r + 2
        for (int l : left) {
            for (int r : right) {

                if (l + r + 2 <= maxDistance) {
                    ans++;
                }
            }
        }

        // RETURN distances to parent:
        // Merge left and right leaf distances, each incremented by 1
        // because parent is 1 edge further away than current node
        vector<int> result;

        for (int l : left) {
            // PRUNE: only keep if this leaf can still form a good pair
            // when passed up to parent (distance will be l+1 from parent)
            if (l + 1 < maxDistance) {
                result.push_back(l + 1);
            }
        }

        for (int r : right) {
            if (r + 1 < maxDistance) {
                result.push_back(r + 1);
            }
        }

        return result;
    }

    int countPairs(TreeNode* root, int distance) {

        maxDistance = distance;

        dfs(root);

        return ans;
    }
};


int main(){
    return 0;
}