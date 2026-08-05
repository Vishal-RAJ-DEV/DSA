#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
        Intuition:

        We know that method 'k' contains a bug.

        So, every method that can be reached from 'k' (directly or indirectly)
        is also considered suspicious because it is invoked by the buggy method.

        ---------------------------------------------------------------

        Step 1:
        Perform DFS from method 'k' and mark every reachable method as suspicious.

        Example:
            0 -> 1 -> 2
            3 -> 2

            k = 1

            Suspicious = {1, 2}
            Non-Suspicious = {0, 3}

        ---------------------------------------------------------------

        Step 2:
        Now check whether this suspicious group can actually be removed.

        The problem says:
        "A group of methods can only be removed if NO method outside the group
        invokes any method inside the group."

        So for every edge (u -> v), we check:

            u = caller method
            v = invoked method

        If:
            u is NOT suspicious
            v IS suspicious

        then an outside method still depends on a suspicious method.

        Removing the suspicious group would break that invocation,
        therefore NONE of the suspicious methods can be removed.

        Example:

            0 -> 1
            1 -> 2

            k = 1

            Suspicious = {1,2}

            Edge:
                0 -> 1

            Here,
                0 = outside
                1 = inside

            Since an outside method invokes an inside method,
            removing {1,2} is NOT allowed.

        If no such edge exists, then it is safe to remove every suspicious method.
    */

    vector<int> mark;

    // DFS to mark every method reachable from k as suspicious.
    void dfs(int node, vector<bool>& vis, vector<vector<int>>& adj) {

        vis[node] = true;
        mark[node] = 1;

        for (auto &child : adj[node]) {
            if (!vis[child]) {
                dfs(child, vis, adj);
            }
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {

        // mark[i] = 1 -> suspicious
        // mark[i] = 0 -> non-suspicious
        mark.resize(n, 0);

        // Build adjacency list.
        vector<vector<int>> adj(n);

        for (auto &it : invocations) {
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
        }

        // Mark all suspicious methods.
        vector<bool> vis(n, false);
        dfs(k, vis, adj);

        /*
            Check every invocation.

            If there exists an edge:

                Non-Suspicious -----> Suspicious

            then the suspicious group cannot be removed because
            an outside method still depends on it.

            In that case, return all methods (remove nothing).
        */
        for (auto &it : invocations) {

            int u = it[0];
            int v = it[1];

            if (mark[u] == 0 && mark[v] == 1) {

                vector<int> ans;

                // Removal is not possible,
                // so return every method.
                for (int i = 0; i < n; i++) {
                    ans.push_back(i);
                }

                return ans;
            }
        }

        /*
            No outside method invokes a suspicious method.

            Therefore, it is safe to remove all suspicious methods.

            Return only the remaining (non-suspicious) methods.
        */
        vector<int> ans;

        for (int i = 0; i < n; i++) {
            if (mark[i] == 0) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};



int main(){
    return 0;
}