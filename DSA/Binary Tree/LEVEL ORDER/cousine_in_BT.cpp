#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    bool isCousins(TreeNode *root, int x, int y)
    {

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {

            int sz = q.size();

            TreeNode *px = nullptr;
            TreeNode *py = nullptr;

            while (sz--)
            {

                TreeNode *node = q.front();
                q.pop();

                if (node->left)
                {
                    if (node->left->val == x)
                        px = node;
                    if (node->left->val == y)
                        py = node;

                    q.push(node->left);
                }

                if (node->right)
                {
                    if (node->right->val == x)
                        px = node;
                    if (node->right->val == y)
                        py = node;

                    q.push(node->right);
                }
            }

            if (px && py)
                return px != py;

            if (px || py)
                return false;
        }

        return false;
    }
};
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {

            int sz = q.size();
            bool foundX = false, foundY = false;

            while (sz--) {

                TreeNode* node = q.front();
                q.pop();

                if (node->val == x) foundX = true;
                if (node->val == y) foundY = true;

                // Same parent => siblings, not cousins
                if (node->left && node->right) {
                    int l = node->left->val;
                    int r = node->right->val;

                    if ((l == x && r == y) || (l == y && r == x))
                        return false;
                }

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            if (foundX && foundY)
                return true;

            if (foundX || foundY)
                return false;
        }

        return false;
    }
};

class Solution
{
public:
    int dx = -1, dy = -1;
    TreeNode *px = nullptr, *py = nullptr;

    void dfs(TreeNode *node, TreeNode *parent, int depth, int x, int y)
    {
        if (!node)
            return;

        if (node->val == x)
        {
            dx = depth;
            px = parent;
        }

        if (node->val == y)
        {
            dy = depth;
            py = parent;
        }

        dfs(node->left, node, depth + 1, x, y);
        dfs(node->right, node, depth + 1, x, y);
    }

    bool isCousins(TreeNode *root, int x, int y)
    {
        dfs(root, nullptr, 0, x, y);

        return dx == dy && px != py;
    }
};

int main()
{
    return 0;
}