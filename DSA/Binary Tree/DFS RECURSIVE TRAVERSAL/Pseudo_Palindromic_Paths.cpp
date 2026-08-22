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
 PROBLEM: Pseudo-Palindromic Paths in a Binary Tree
================================================================================

 Given a binary tree with nodes labeled 1-9, count the number of pseudo-
 palindromic paths from root to leaf.

 A path is "pseudo-palindromic" if it can be rearranged into a palindrome.

 PALINDROME RULE:
 A sequence can form a palindrome if:
   - At most ONE digit appears an odd number of times
   - All other digits appear an even number of times

 Examples:
   [1,2,1] → palindrome? 1 appears twice (even), 2 appears once (odd) → YES ✓
   [1,2,3] → palindrome? 1,2,3 all appear once (odd) → NO ✗ (3 odds)
   [2,2,2] → palindrome? 2 appears 3 times (odd) → YES ✓ (1 odd)

================================================================================
 SOLUTION 1: FREQUENCY ARRAY APPROACH
================================================================================

 APPROACH:
 1. Use a frequency array freq[10] to count occurrences of each digit (1-9)
 2. At each node, increment freq[node->val]
 3. At leaf, count how many digits have odd frequency
 4. If oddCount <= 1, path is pseudo-palindromic → return 1
 5. Backtrack: decrement freq[node->val] before returning

 DRY RUN on this tree:
            2
           / \
          3   1
         / \   \
        3   1   2

 Root-to-leaf paths:
 ┌───────────────┬──────────────────┬──────────────┬─────────────────────────┐
 │     Path      │  Freq at Leaf    │ Odd Count    │ Pseudo-Palindromic?     │
 ├───────────────┼──────────────────┼──────────────┼─────────────────────────┤
 │ 2 → 3 → 3     │ {2:1, 3:2}      │ 1 (only 2)   │ YES ✓ (can make 323)   │
 │ 2 → 3 → 1     │ {2:1, 3:1, 1:1} │ 3 (all odd)  │ NO  ✗                  │
 │ 2 → 1 → 2     │ {2:2, 1:1}      │ 1 (only 1)   │ YES ✓ (can make 212)   │
 └───────────────┴──────────────────┴──────────────┴─────────────────────────┘
 Answer = 2

 DFS WITH BACKTRACKING:

 dfs(2, freq=[0,0,0,0,0,0,0,0,0,0])
    │  freq[2]++ → freq=[0,0,1,0,0,0,0,0,0,0]
    │
    ├── dfs(3, freq=[0,0,1,0,0,0,0,0,0,0])
    │      │  freq[3]++ → freq=[0,0,1,1,0,0,0,0,0,0]
    │      │
    │      ├── dfs(3, freq=[0,0,1,1,0,0,0,0,0,0])
    │      │      │  freq[3]++ → freq=[0,0,1,2,0,0,0,0,0,0]
    │      │      │  LEAF! Count odds: freq[2]=1(odd), freq[3]=2(even)
    │      │      │  oddCount = 1 → return 1 ✓
    │      │      │  Backtrack: freq[3]--
    │      │
    │      ├── dfs(1, freq=[0,0,1,1,0,0,0,0,0,0])
    │      │      │  freq[1]++ → freq=[0,1,1,1,0,0,0,0,0,0]
    │      │      │  LEAF! Count odds: 1,2,3 all odd → oddCount=3
    │      │      │  oddCount > 1 → return 0 ✗
    │      │      │  Backtrack: freq[1]--
    │      │
    │      Backtrack: freq[3]--
    │
    ├── dfs(1, freq=[0,0,1,0,0,0,0,0,0,0])
    │      │  freq[1]++ → freq=[0,1,1,0,0,0,0,0,0,0]
    │      │
    │      └── dfs(2, freq=[0,1,1,0,0,0,0,0,0,0])
    │             │  freq[2]++ → freq=[0,1,2,0,0,0,0,0,0,0]
    │             │  LEAF! Count odds: freq[1]=1(odd), freq[2]=2(even)
    │             │  oddCount = 1 → return 1 ✓
    │             │  Backtrack: freq[2]--
    │
    Backtrack: freq[2]--

 Return 1 + 0 + 1 = 2 ✓

================================================================================
*/
int dfs(TreeNode* node, vector<int>& freq)
{
    // Base case: null node, no path
    if(node == nullptr)
        return 0;

    // Include current node in path by incrementing its frequency
    freq[node->val]++;

    // If leaf node, check if current path is pseudo-palindromic
    if(node->left == nullptr && node->right == nullptr)
    {
        int oddCount = 0;

        // Count how many digits have odd frequency
        // A palindrome can have at most 1 digit with odd count
        for(int i = 1; i <= 9; i++)
        {
            if(freq[i] % 2 == 1)
                oddCount++;
        }

        // Backtrack: remove current node from path before returning
        freq[node->val]--;

        // If at most 1 odd frequency, path can form palindrome
        if(oddCount <= 1)
            return 1;  // Valid pseudo-palindromic path

        return 0;  // Not pseudo-palindromic
    }

    // Explore left and right subtrees
    int left = dfs(node->left, freq);
    int right = dfs(node->right, freq);

    // Backtrack: remove current node before returning to parent
    freq[node->val]--;

    // Total pseudo-palindromic paths from both subtrees
    return left + right;
}


/*
================================================================================
 SOLUTION 2: BIT MANIPULATION APPROACH
================================================================================

 WHY BIT MANIPULATION?
 Instead of using a frequency array and counting odds at each leaf,
 we can use a single integer as a BITMASK to track parity (odd/even)
 of each digit's frequency.

 HOW THE BITMASK WORKS:
 ┌─────────────────────────────────────────────────────────────────────────────┐
 │  Bit Position:   9   8   7   6   5   4   3   2   1   0                    │
 │  Digit:          9   8   7   6   5   4   3   2   1  (unused)             │
 │                                                                             │
 │  Each bit represents whether a digit has appeared ODD (1) or EVEN (0) times│
 └─────────────────────────────────────────────────────────────────────────────┘

 KEY BIT OPERATIONS:

 1. SET/TOGGLE BIT: mask ^= (1 << node->val)
    ─────────────────────────────────────────
    XOR with a mask that has only bit at position node->val set.

    If digit appears: 0 → 1 (odd count)
                      1 → 0 (even count, toggled back)

    Example: digit=3, mask before = 0000000100 (digit 2 seen once)
             1 << 3 = 0000001000
             mask ^ (1<<3) = 0000001100 (digits 2 AND 3 seen odd times)

 2. CHECK IF AT MOST 1 BIT SET: (mask & (mask - 1)) == 0
    ─────────────────────────────────────────────────────
    This is a classic bit trick!
    mask - 1 clears the LOWEST set bit of mask.

    If mask has 0 bits set (empty):  0 & (-1) = 0 ✓ (0 odds)
    If mask has 1 bit set:           mask & (mask-1) = 0 ✓ (1 odd)
    If mask has 2+ bits set:         mask & (mask-1) ≠ 0 ✗ (2+ odds)

    Examples:
    ┌──────────────┬────────────┬─────────────┬────────────────────┐
    │ mask (binary)│ mask - 1   │ mask&(m-1)  │ At most 1 bit set?│
    ├──────────────┼────────────┼─────────────┼────────────────────┤
    │ 0000000000   │ 1111111111 │ 0000000000  │ YES (0 bits)      │
    │ 0000001000   │ 0000000111 │ 0000000000  │ YES (1 bit)       │
    │ 0000001100   │ 0000001011 │ 0000001000  │ NO  (2 bits)      │
    │ 0000001110   │ 0000001101 │ 0000001100  │ NO  (3 bits)      │
    └──────────────┴────────────┴─────────────┴────────────────────┘

 DRY RUN on this tree:
            2
           / \
          3   1
         / \   \
        3   1   2

 DFS TRAVERSAL:

 dfs(2, mask=0000000000)
    │  mask ^= (1 << 2) → mask = 0000000100 (bit 2 set, digit 2 seen once)
    │
    ├── dfs(3, mask=0000000100)
    │      │  mask ^= (1 << 3) → mask = 0000001100 (bits 2,3 set)
    │      │
    │      ├── dfs(3, mask=0000001100)
    │      │      │  mask ^= (1 << 3) → mask = 0000000100 (bit 3 toggled off)
    │      │      │  LEAF! Check: mask & (mask-1) = 0000000100 & 0000000011
    │      │      │            = 0000000000 == 0 → YES ✓ (1 odd: digit 2)
    │      │      │  return 1
    │      │
    │      ├── dfs(1, mask=0000001100)
    │      │      │  mask ^= (1 << 1) → mask = 0000001110 (bits 1,2,3 set)
    │      │      │  LEAF! Check: mask & (mask-1) = 0000001110 & 0000001101
    │      │      │            = 0000001100 ≠ 0 → NO ✗ (3 odds)
    │      │      │  return 0
    │      │
    │      return 1 + 0 = 1
    │
    ├── dfs(1, mask=0000000100)
    │      │  mask ^= (1 << 1) → mask = 0000000110 (bits 1,2 set)
    │      │
    │      └── dfs(2, mask=0000000110)
    │             │  mask ^= (1 << 2) → mask = 0000000010 (bit 2 toggled off)
    │             │  LEAF! Check: mask & (mask-1) = 0000000010 & 0000000001
    │             │            = 0000000000 == 0 → YES ✓ (1 odd: digit 1)
    │             │  return 1
    │
    return 1 + 1 = 2 ✓

 BITMASK VISUALIZATION THROUGH TRAVERSAL:

 Path: 2 → 3 → 3
 ┌───────┬──────────────┬─────────────┬───────────────────────────┐
 │ Node  │ mask (binary)│ mask (dec)  │ Meaning                   │
 ├───────┼──────────────┼─────────────┼───────────────────────────┤
 │ start │ 0000000000   │     0       │ No digits seen            │
 │ 2     │ 0000000100   │     4       │ {2: odd}                  │
 │ 3     │ 0000001100   │    12       │ {2: odd, 3: odd}          │
 │ 3     │ 0000000100   │     4       │ {2: odd, 3: even} ← 3 removed│
 └───────┴──────────────┴─────────────┴───────────────────────────┘
 At leaf: mask=4 (binary 100), only 1 bit set → PSEUDO-PALINDROMIC ✓

 Path: 2 → 3 → 1
 ┌───────┬──────────────┬─────────────┬───────────────────────────┐
 │ Node  │ mask (binary)│ mask (dec)  │ Meaning                   │
 ├───────┼──────────────┼─────────────┼───────────────────────────┤
 │ start │ 0000000000   │     0       │ No digits seen            │
 │ 2     │ 0000000100   │     4       │ {2: odd}                  │
 │ 3     │ 0000001100   │    12       │ {2: odd, 3: odd}          │
 │ 1     │ 0000001110   │    14       │ {2: odd, 3: odd, 1: odd}  │
 └───────┴──────────────┴─────────────┴───────────────────────────┘
 At leaf: mask=14 (binary 1110), 3 bits set → NOT PSEUDO-PALINDROMIC ✗

 ADVANTAGE OVER SOLUTION 1:
 - No need for array initialization or cleanup
 - No loop to count odds at each leaf
 - Single integer operation: O(1) check
 - No backtracking needed (XOR is self-reversing!)

================================================================================
*/
class Solution {
public:

    // DFS function using bitmask to track digit frequency parity
    // mask: integer where bit i is 1 if digit i appeared odd times
    int dfs(TreeNode* node, int mask)
    {
        // Base case: null node
        if(node == nullptr)
            return 0;

        // Toggle bit at position node->val using XOR
        // If digit appears odd times → bit becomes 1
        // If digit appears even times → bit becomes 0
        mask ^= (1 << node->val);

        // Leaf node: check if path is pseudo-palindromic
        if(node->left == nullptr && node->right == nullptr)
        {
            // BIT TRICK: mask & (mask - 1) clears the lowest set bit
            // If result is 0, then mask has at most 1 bit set
            // → At most 1 digit has odd frequency → PSEUDO-PALINDROMIC
            if((mask & (mask - 1)) == 0)
                return 1;

            return 0;
        }

        // Recurse on children (mask is passed by value, not reference)
        // So left and right subtrees get independent copies
        return dfs(node->left, mask) +
               dfs(node->right, mask);
    }

    int pseudoPalindromicPaths(TreeNode* root)
    {
        // Start with mask = 0 (no digits seen yet)
        return dfs(root, 0);
    }
};



int main(){
    return 0;
}