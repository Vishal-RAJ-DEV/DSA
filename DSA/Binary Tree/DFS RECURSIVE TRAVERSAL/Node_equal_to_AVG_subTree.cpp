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
================================================================================
 PROBLEM: Count Nodes Equal to Average of Subtree
================================================================================

 Given a binary tree, find the number of nodes where the node's value is
 equal to the average of all values in its subtree (including itself).

 A subtree includes the node itself and all its descendants.

 Example:
         4
        / \
       8   5
      / \
     1   3

 For node 4: subtree = {4,8,5,1,3}, sum=21, cnt=5, avg=4 ≠ 4? NO (21/5=4) ✓
 For node 8: subtree = {8,1,3}, sum=12, cnt=3, avg=4 ≠ 8? NO ✗
 For node 5: subtree = {5}, sum=5, cnt=1, avg=5 = 5? YES ✓
 For node 1: subtree = {1}, sum=1, cnt=1, avg=1 = 1? YES ✓
 For node 3: subtree = {3}, sum=3, cnt=1, avg=3 = 3? YES ✓

 Answer = 4 (nodes 4, 5, 1, 3)

================================================================================
 HOW THE CODE WORKS - POST-ORDER DFS APPROACH
================================================================================

 KEY INSIGHT:
 We use POST-ORDER traversal (Left → Right → Root) because to compute the
 average of a subtree, we FIRST need the sum and count from children.

 The DFS function returns a PAIR: {sum_of_subtree, count_of_nodes}

 DRY RUN on this tree:
         4
        / \
       8   5
      / \
     1   3

 DFS TRAVERSAL (Post-Order):

 ┌─────────────────────────────────────────────────────────────────────────────┐
 │                        DFS CALL STACK                                      │
 ├─────────────────────────────────────────────────────────────────────────────┤
 │                                                                             │
 │  dfs(4)                                                                    │
 │    │                                                                       │
 │    ├── dfs(8)                                                              │
 │    │     │                                                                 │
 │    │     ├── dfs(1)                                                        │
 │    │     │     │  left={0,0}, right={0,0}                                 │
 │    │     │     │  sum=0+0+1=1, cnt=0+0+1=1                                │
 │    │     │     │  avg=1/1=1, 1==1? YES ✓ ans=1                            │
 │    │     │     │  return {1, 1}                                            │
 │    │     │                                                                 │
 │    │     ├── dfs(3)                                                        │
 │    │     │     │  left={0,0}, right={0,0}                                 │
 │    │     │     │  sum=0+0+3=3, cnt=0+0+1=1                                │
 │    │     │     │  avg=3/1=3, 3==3? YES ✓ ans=2                            │
 │    │     │     │  return {3, 1}                                            │
 │    │     │                                                                 │
 │    │     │  Back at node 8:                                                │
 │    │     │  left={1,1} (from node 1)                                      │
 │    │     │  right={3,1} (from node 3)                                     │
 │    │     │  sum=1+3+8=12, cnt=1+1+1=3                                     │
 │    │     │  avg=12/3=4, 4==8? NO ✗ ans=2                                  │
 │    │     │  return {12, 3}                                                 │
 │    │                                                                       │
 │    ├── dfs(5)                                                              │
 │    │     │  left={0,0}, right={0,0}                                       │
 │    │     │  sum=0+0+5=5, cnt=0+0+1=1                                      │
 │    │     │  avg=5/1=5, 5==5? YES ✓ ans=3                                  │
 │    │     │  return {5, 1}                                                  │
 │    │                                                                       │
 │    │  Back at node 4:                                                      │
 │    │  left={12,3} (from node 8's subtree)                                 │
 │    │  right={5,1} (from node 5)                                           │
 │    │  sum=12+5+4=21, cnt=3+1+1=5                                          │
 │    │  avg=21/5=4, 4==4? YES ✓ ans=4                                       │
 │    │  return {21, 5}                                                       │
 │                                                                             │
 └─────────────────────────────────────────────────────────────────────────────┘

 FINAL ans = 4 ✓

 VISUAL OF RETURNS (Bottom-Up):

         4
        / \          Returns: {21, 5}
       8   5         avg=21/5=4=4? YES ✓
      / \   |
     1   3  |        Returns: {5, 1}
    |   |   |        avg=5/1=5=5? YES ✓
    v   v   v
   {1,1}{3,1}        Returns: {12, 3}
                     avg=12/3=4≠8? NO

 THE PAIR EXPLAINED:
 ┌─────────────────────────────────────────────────────────────────┐
 │  pair<int, int> = {sum, count}                                  │
 │                                                                 │
 │  left.first  = sum of left subtree                              │
 │  left.second = count of nodes in left subtree                   │
 │                                                                 │
 │  right.first  = sum of right subtree                            │
 │  right.second = count of nodes in right subtree                 │
 │                                                                 │
 │  Current node:                                                  │
 │    sum  = left.sum + right.sum + node.val                       │
 │    cnt  = left.cnt + right.cnt + 1                              │
 │    avg  = sum / cnt                                             │
 └─────────────────────────────────────────────────────────────────┘

 WHY POST-ORDER?
 ┌─────────────────────────────────────────────────────────────────┐
 │  To check if node 4 equals average of its subtree, we need:    │
 │    1. Sum of left subtree (from node 8's result)               │
 │    2. Sum of right subtree (from node 5's result)              │
 │    3. Count of nodes in both subtrees                          │
 │                                                                 │
 │  So we MUST process children FIRST → Post-Order!               │
 └─────────────────────────────────────────────────────────────────┘

================================================================================
*/
class Solution {
public:
    int ans = 0;  // Counter for nodes where val == average of subtree

    // DFS returns pair<int, int> where:
    //   first  = sum of all values in subtree rooted at root
    //   second = count of nodes in subtree rooted at root
    pair<int, int> dfs(TreeNode* root) {
        // Base case: empty subtree has sum=0 and count=0
        if(root == nullptr) {
            return {0, 0};
        }

        // Post-order: first get results from left subtree
        auto left = dfs(root->left);

        // Post-order: then get results from right subtree
        auto right = dfs(root->right);

        // Calculate sum of current subtree:
        // left subtree sum + right subtree sum + current node value
        int sum = left.first + right.first + root->val;

        // Calculate count of nodes in current subtree:
        // left count + right count + 1 (for current node)
        int cnt = left.second + right.second + 1;

        // Calculate average of current subtree (integer division)
        int avg = sum / cnt;

        // Check if current node's value equals the subtree average
        // If yes, increment answer counter
        if(avg == root->val) {
            ans += 1;
        }

        // Return this subtree's sum and count to parent node
        // Parent will use this information to compute its own average
        return {sum, cnt};
    }

    int averageOfSubtree(TreeNode* root) {
        // Start DFS traversal from root
        dfs(root);
        // Return total count of nodes where val == subtree average
        return ans;
    }
};



int main(){
    return 0;
}