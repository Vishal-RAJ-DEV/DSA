#include <bits/stdc++.h>
using namespace std;

// TreeNode structure
struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() != postorder.size()) return nullptr;

        // Map each value in inorder to its index
        map<int, int> hm;
        for (int i = 0; i < inorder.size(); i++) {
            hm[inorder[i]] = i;
        }

        // Call recursive builder
        return build(inorder, 0, inorder.size() - 1,
                     postorder, 0, postorder.size() - 1, hm);
    }

private:
    TreeNode* build(vector<int>& inorder, int is, int ie,
                    vector<int>& postorder, int ps, int pe, map<int, int>& hm) {
        if (ps > pe || is > ie) return nullptr;

        // Last element in postorder is root
        TreeNode* root = new TreeNode(postorder[pe]);

        // Find root index in inorder
        int inRoot = hm[postorder[pe]];
        int numsLeft = inRoot - is;

        // Recursively build left and right subtrees
        root->left = build(inorder, is, inRoot - 1,
                           postorder, ps, ps + numsLeft - 1, hm);

        root->right = build(inorder, inRoot + 1, ie,
                            postorder, ps + numsLeft, pe - 1, hm);

        return root;
    }
};

// Inorder printer
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

// Driver
int main() {
    vector<int> inorder = {40, 20, 50, 10, 60, 30};
    vector<int> postorder = {40, 50, 20, 60, 30, 10};

    cout << "Inorder Vector: ";
    for (int x : inorder) cout << x << " ";
    cout << "\nPostorder Vector: ";
    for (int x : postorder) cout << x << " ";
    cout << endl;

    Solution sol;
    TreeNode* root = sol.buildTree(inorder, postorder);

    cout << "Inorder of Unique Binary Tree Created:\n";
    printInorder(root);
    cout << endl;

    return 0;
}
