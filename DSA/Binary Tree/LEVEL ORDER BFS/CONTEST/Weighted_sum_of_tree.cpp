#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
============================================================
TOPIC:
    Tree Traversal + Depth/Height Calculation

PATTERN:
    1. Parent Array → Adjacency List
    2. BFS Level-Order Traversal
    3. Depth Calculation
    4. Tree Height Calculation
    5. Bottom-Up / Depth-Based Contribution

CORE IDEA:
    For every node:

        weight = nums[i] * (height - depth[i] + 1)

    Therefore, we first need:
        1. The depth of every node.
        2. The height of the tree.

    Once we have both, we simply calculate the contribution
    of every node.

------------------------------------------------------------
WHY BFS?
------------------------------------------------------------

    The parent array gives us:

        parent[i] = parent of node i

    We convert it into an adjacency list:

        parent
           ↓
        children

    Then BFS starts from the root (node 0).

    Root has depth = 1.

    For every child:

        depth[child] = depth[parent] + 1

    While doing BFS, the maximum depth encountered is the
    height of the tree.

------------------------------------------------------------
IMPORTANT FORMULA:
------------------------------------------------------------

    weight(i) = nums[i] * (height - depth[i] + 1)

    Example:

        height = 4
        node depth = 2
        nums[i] = 10

        weight = 10 * (4 - 2 + 1)
               = 10 * 3
               = 30

------------------------------------------------------------
PATTERN TO REMEMBER:
------------------------------------------------------------

    parent array
         ↓
    build adjacency list
         ↓
    BFS / DFS
         ↓
    calculate depth
         ↓
    maximum depth = height
         ↓
    calculate contribution of every node

------------------------------------------------------------
TIME COMPLEXITY:
------------------------------------------------------------

    Building tree       → O(n)
    BFS                 → O(n)
    Calculating answer  → O(n)

    Total               → O(n)

------------------------------------------------------------
SPACE COMPLEXITY:
------------------------------------------------------------

    Adjacency list      → O(n)
    Depth array         → O(n)
    Queue               → O(n)

    Total               → O(n)
============================================================
*/

class Solution {
public:

    long long weightedSum(vector<int>& parent, vector<int>& nums) {

        int n = parent.size();

        /*
        ----------------------------------------------------
        STEP 1: BUILD THE TREE
        ----------------------------------------------------

        parent[i] tells us who the parent of node i is.

        Example:

            parent = [-1, 0, 0, 1]

        Tree:

                0
               / \
              1   2
             /
            3

        We convert this into:

            children[0] = {1, 2}
            children[1] = {3}
        */

        vector<vector<int>> children(n);

        for (int i = 1; i < n; i++) {

            // i is a child of parent[i]
            children[parent[i]].push_back(i);
        }


        /*
        ----------------------------------------------------
        STEP 2: FIND DEPTH OF EVERY NODE
        ----------------------------------------------------

        Root is node 0.

        The problem says:

            root depth = 1

        Therefore:

            depth[0] = 1

        Using BFS:

            depth[child] = depth[parent] + 1

        Example:

                0              depth = 1
               / \
              1   2            depth = 2
             /
            3                  depth = 3
        */

        vector<int> depth(n);

        // Root has depth 1
        depth[0] = 1;

        queue<int> q;

        // Start BFS from root
        q.push(0);


        /*
        ----------------------------------------------------
        STEP 3: FIND TREE HEIGHT
        ----------------------------------------------------

        Height = maximum depth of any node.

        While processing every node, update:

            height = max(height, depth[node])
        */

        int height = 1;


        while (!q.empty()) {

            // Get the current node
            int node = q.front();
            q.pop();


            // Update tree height
            height = max(height, depth[node]);


            /*
            Process all children of current node.

            If:

                depth[node] = 2

            then:

                depth[child] = 3
            */

            for (int child : children[node]) {

                depth[child] = depth[node] + 1;

                q.push(child);
            }
        }


        /*
        ----------------------------------------------------
        STEP 4: CALCULATE WEIGHTED SUM
        ----------------------------------------------------

        Formula given by the problem:

            weight(i)
                = nums[i] * (height - depth[i] + 1)

        Why +1?

        Suppose:

            height = 4
            depth = 4

        This node is at the deepest level.

            height - depth + 1
            = 4 - 4 + 1
            = 1

        So its multiplier is 1.

        For root:

            depth = 1

            height - 1 + 1
            = height

        So root gets the largest multiplier.
        */

        long long ans = 0;


        for (int i = 0; i < n; i++) {

            /*
            Calculate contribution of node i.

            1LL is used so multiplication happens using
            long long and avoids integer overflow.
            */

            long long weight =
                1LL * nums[i] *
                (height - depth[i] + 1);


            // Add this node's contribution to answer
            ans += weight;
        }


        /*
        ----------------------------------------------------
        STEP 5: RETURN FINAL ANSWER
        ----------------------------------------------------
        */

        return ans;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> parent(n), nums(n);
    for (int i = 0; i < n; i++) cin >> parent[i];
    for (int i = 0; i < n; i++) cin >> nums[i];

    Solution sol;
    cout << sol.weightedSum(parent, nums) << '\n';

    return 0;
}