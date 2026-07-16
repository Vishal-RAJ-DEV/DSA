/*
    Question: LeetCode 107 - Binary Tree Level Order Traversal II

    Given the root of a binary tree, return the bottom-up level order traversal
    of its nodes' values. (i.e., from left to right, level by level from leaf to root).

    Example:
        Input: root = [3,9,20,null,null,15,7]
        Output: [[15,7],[9,20],[3]]

    Explanation:
        Level order traversal from top:    [ [3], [9,20], [15,7] ]
        Reversed (bottom-up) is:           [ [15,7], [9,20], [3] ]
*/

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

/*
    Approach 1: Using Map (level -> nodes mapping)

    Idea:
        - Perform a standard level-order BFS traversal.
        - Store each level's nodes in a map<int, vector<int>> where
          key = level number (0 at root).
        - After traversal, iterate the map in REVERSE order using
          reverse iterators (rbegin / rend) to collect levels
          from bottom-most to top-most.

    Time Complexity : O(N) - each node visited once
    Space Complexity: O(N) - map stores all nodes + queue
*/
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {

        vector<vector<int>> ans;

        if(root == nullptr)
            return ans;

        queue<TreeNode*> q;
        map<int, vector<int>> mp;

        q.push(root);

        int level = 0;

        while(!q.empty()){

            int size = q.size();

            while(size--){

                TreeNode* node = q.front();
                q.pop();

                mp[level].push_back(node->val);

                if(node->left)
                    q.push(node->left);

                if(node->right)
                    q.push(node->right);
            }

            level++;
        }

        for(auto it = mp.rbegin(); it != mp.rend(); it++){
            ans.push_back(it->second);
        }

        return ans;
    }
};


/*
    Approach 2: Using Stack (LIFO to reverse order)

    Idea:
        - Perform the same level-order BFS traversal.
        - Instead of a map, push each complete level (as a vector)
          onto a stack.
        - After traversal, pop from the stack one by one and push
          into ans. Since stack is LIFO, the bottom-most level
          (last level pushed) comes out first, giving bottom-up order.

    Time Complexity : O(N) - each node visited once
    Space Complexity: O(N) - stack stores all levels + queue
*/
class Solution2 {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {

        vector<vector<int>> ans;

        if(root == nullptr)
            return ans;

        queue<TreeNode*> q;
        stack<vector<int>> st;

        q.push(root);

        while(!q.empty()){

            int size = q.size();
            vector<int> level;

            while(size--){

                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                if(node->left)
                    q.push(node->left);

                if(node->right)
                    q.push(node->right);
            }

            st.push(level);
        }

        while(!st.empty()){

            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }
};
int main(){
    return 0;
}
