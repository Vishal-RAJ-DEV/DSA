#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Disjoint Set Union (DSU) / Union Find

Operations:
1. findUPar(x)      -> Finds the leader (ultimate parent) of x.
2. unionBySize(u,v) -> Merges the components containing u and v.
3. Connected?       -> findUPar(u) == findUPar(v)

Time Complexity:
find()  -> O(α(N))
union() -> O(α(N))

α(N) = Inverse Ackermann Function (almost constant)
===============================================================================
*/

class DSU {
public:
    // parent[i] -> stores the parent (or leader) of node i
    // size[i] -> stores the size of the component whose leader is i
    vector<int> parent, size;

    // Constructor: Initialize DSU for n nodes
    DSU(int n) {

        // Allocate memory for parent array
        parent.resize(n);

        // Allocate memory for size array and initialize every size to 1
        size.resize(n, 1);

        // Initially every node is its own parent
        // Each node forms an independent component
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find the Ultimate Parent (Leader) of a node
    int findUPar(int node) {

        // Base Case:
        // If node is its own parent, it is the leader
        if (node == parent[node])
            return node;

        // Path Compression:
        // Store the ultimate parent directly to flatten the tree
        // This makes future find operations much faster
        return parent[node] = findUPar(parent[node]);
    }

    // Merge two components using Union by Size
    void unionBySize(int u, int v) {

        // Find the leaders of both nodes
        int pu = findUPar(u);
        int pv = findUPar(v);

        // If both nodes already belong to the same component,
        // no merging is required
        if (pu == pv) return;

        // Attach the smaller component under the larger component
        if (size[pu] < size[pv]) {

            // Make pv the new leader
            parent[pu] = pv;

            // Update the size of the merged component
            size[pv] += size[pu];
        }
        else {

            // Make pu the new leader
            parent[pv] = pu;

            // Update the size of the merged component
            size[pu] += size[pv];
        }
    }
};

int main() {

    int n = 7;

    DSU ds(n);

    /*
        Initially

        0 1 2 3 4 5 6

        Components

        {0}
        {1}
        {2}
        {3}
        {4}
        {5}
        {6}
    */

    ds.unionBySize(0, 1);
    ds.unionBySize(1, 2);

    /*
        Component

            0
           / \
          1   2
    */

    ds.unionBySize(3, 4);

    /*
        Component

        3
        |
        4
    */

    ds.unionBySize(5, 6);

    /*
        Component

        5
        |
        6
    */

    cout << "Checking Connectivity\n\n";

    // Check whether two nodes belong to same component
    if (ds.findUPar(0) == ds.findUPar(2))
        cout << "0 and 2 are Connected\n";
    else
        cout << "0 and 2 are NOT Connected\n";

    if (ds.findUPar(2) == ds.findUPar(5))
        cout << "2 and 5 are Connected\n";
    else
        cout << "2 and 5 are NOT Connected\n";

    cout << "\n";

    // Merge two components
    ds.unionBySize(2, 5);

    /*
            0
           / \
          1   2
               |
               5
               |
               6

        3
        |
        4
    */

    if (ds.findUPar(0) == ds.findUPar(6))
        cout << "After Union : 0 and 6 are Connected\n";
    else
        cout << "After Union : 0 and 6 are NOT Connected\n";

    cout << "\nParent Array\n";

    for (int i = 0; i < n; i++)
        cout << ds.parent[i] << " ";

    cout << "\n\nSize Array\n";

    for (int i = 0; i < n; i++)
        cout << ds.size[i] << " ";

    cout << "\n";

    return 0;
}