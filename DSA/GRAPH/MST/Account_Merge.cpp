/*
PROBLEM: Accounts Merge (LeetCode 721)

You are given a list of accounts where each account is:
  [name, email1, email2, ...]

Two accounts belong to the same person if they share at least one common email.
Merge such accounts — for each person, return [name, sorted emails].

Example:
  Input:
    ["John","a","b"]
    ["John","b","c"]
    ["Mary","d"]

  Output:
    ["John","a","b","c"]
    ["Mary","d"]

Approach: DSU (Disjoint Set Union)
  - Treat each account index as a DSU node.
  - Map each email to the first account where it appeared.
  - If an email repeats, union the current account with the previous one.
  - Group emails by DSU leader, sort, prepend name, return.

Time: O(M log M)  |  Space: O(M + N)
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, size;

    // Constructor
    // Initially every account is its own parent
    // and every component has size = 1.
    DSU(int n) {

        parent.resize(n);
        size.resize(n, 1);

        for (int i = 0; i < n; i++) {
            parent[i] = i;        // Every node is its own leader initially
        }
    }

    // Find the Ultimate Parent (Leader)
    // Also performs Path Compression to flatten the tree.
    int find(int node) {

        if (parent[node] == node)
            return node;          // Node itself is the leader

        return parent[node] = find(parent[node]); // Path Compression
    }

    // Union By Size
    // Merge two components by attaching the
    // smaller component under the larger one.
    void unite(int u, int v) {

        int pu = find(u);         // Leader of u
        int pv = find(v);         // Leader of v

        if (pu == pv)
            return;               // Already in same component

        // Attach smaller component under larger component
        if (size[pu] < size[pv]) {

            parent[pu] = pv;
            size[pv] += size[pu];

        }
        else {

            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

class Solution {
public:

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {

        //------------------------------------------------------------
        // Step 0 : Create DSU
        //
        // Every account index is treated as one node.
        //
        // Example
        //
        // Account 0
        // Account 1
        // Account 2
        //
        // Initially
        //
        // 0    1    2
        //
        // All are separate components.
        //------------------------------------------------------------

        int n = accounts.size();

        DSU dsu(n);

        //------------------------------------------------------------
        // emailToAccount
        //
        // Stores
        //
        // email  -> first account where it appeared
        //
        // Example
        //
        // john@gmail.com -> 0
        // abc@gmail.com  -> 2
        //
        // If we ever see the same email again,
        // we know both accounts belong to the same person.
        //------------------------------------------------------------

        unordered_map<string, int> emailToAccount;

        //------------------------------------------------------------
        // Step 1 : Traverse every account
        //
        // We inspect every email.
        //
        // If email is new
        //      store it.
        //
        // If email already exists
        //      merge current account with previous account.
        //------------------------------------------------------------

        for (int i = 0; i < n; i++) {

            // Traverse every email of current account.
            // j starts from 1 because
            // accounts[i][0] is the person's name.
            for (int j = 1; j < accounts[i].size(); j++) {

                string email = accounts[i][j];   // Current email

                // Email never seen before
                if (emailToAccount.find(email) == emailToAccount.end()) {

                    // Store this email with current account index
                    emailToAccount[email] = i;
                }
                else {

                    // Email already exists.
                    //
                    // Example
                    //
                    // Account0
                    // a
                    // b
                    //
                    // Account1
                    // b
                    // c
                    //
                    // Since "b" is common,
                    // Account0 and Account1 belong
                    // to the same person.
                    //
                    // Merge them.

                    dsu.unite(i, emailToAccount[email]);
                }
            }
        }

        //------------------------------------------------------------
        // Step 2 : Group emails according to DSU Leader
        //
        // After all unions,
        //
        // Example
        //
        //      0
        //      |
        //      1
        //
        //      2
        //
        // Account0 and Account1 have same leader.
        //
        // We collect all emails belonging
        // to the same leader.
        //------------------------------------------------------------

        unordered_map<int, vector<string>> mergedEmails;

        //------------------------------------------------------------
        // Traverse every unique email.
        //
        // emailToAccount contains
        //
        // email -> account index
        //
        // We convert it into
        //
        // leader -> all emails
        //------------------------------------------------------------

        for (auto &it : emailToAccount) {

            string email = it.first;        // Current email

            int accountIndex = it.second;   // Account where email appeared

            // Find the leader of this account
            int leader = dsu.find(accountIndex);

            // Put email inside leader's group
            mergedEmails[leader].push_back(email);
        }

        //------------------------------------------------------------
        // Step 3 : Build Final Answer
        //
        // mergedEmails now contains
        //
        // Leader
        //      ↓
        // [email1,email2,email3]
        //
        // We sort emails
        // Add person's name
        // Push into answer.
        //------------------------------------------------------------

        vector<vector<string>> ans;

        for (auto &it : mergedEmails) {

            int leader = it.first;          // Component leader

            vector<string> emails = it.second; // Emails of this person

            // Emails should be sorted
            sort(emails.begin(), emails.end());

            vector<string> temp;

            // Name of the person.
            //
            // Since every account in one component
            // belongs to the same person,
            // any account's name can be used.
            // We use the leader account's name.
            temp.push_back(accounts[leader][0]);

            // Add all sorted emails
            for (string &email : emails) {
                temp.push_back(email);
            }

            // Store one merged account
            ans.push_back(temp);
        }

        //------------------------------------------------------------
        // Return merged accounts.
        //------------------------------------------------------------

        return ans;
    }
};

/*
======================== ACCOUNTS MERGE FLOW ========================

Input:

Account 0 : John -> a, b
Account 1 : John -> b, c
Account 2 : Mary -> d

--------------------------------------------------------------------
Step 1 : Treat each account index as a DSU node.

Initially

0      1      2
^      ^      ^
|      |      |
Each account is its own component.

parent = [0,1,2]

--------------------------------------------------------------------
Step 2 : Build email -> account map

Traverse every account and every email.

Account 0

a  -> not seen -> store (a -> 0)
b  -> not seen -> store (b -> 0)

Map:

a -> 0
b -> 0

------------------------------------------------

Account 1

b -> already exists in Account 0

=> Both accounts belong to same person

Union(1,0)

Now DSU becomes

0
|
1

Next email

c -> not seen

Store

c -> 1

Map becomes

a -> 0
b -> 0
c -> 1

------------------------------------------------

Account 2

d -> not seen

Store

d -> 2

Final emailToAccount Map

a -> 0
b -> 0
c -> 1
d -> 2

--------------------------------------------------------------------
Step 3 : DSU after all unions

0
|
1

2

Meaning

Component 1

Account0
Account1

Component 2

Account2

--------------------------------------------------------------------
Step 4 : Group emails according to DSU Leader

Traverse every (email -> account)

a -> account 0

find(0)=0

Group

Leader 0

a

-------------------------

b -> account 0

find(0)=0

Leader 0

a
b

-------------------------

c -> account 1

find(1)=0

Leader 0

a
b
c

-------------------------

d -> account 2

find(2)=2

Leader 2

d

Final Groups

Leader 0

a
b
c

Leader 2

d

--------------------------------------------------------------------
Step 5 : Build Answer

Leader 0

Sort

a
b
c

Name

accounts[0][0] = John

Result

John
a
b
c

-------------------------

Leader 2

Sort

d

Name

accounts[2][0] = Mary

Result

Mary
d

--------------------------------------------------------------------
Final Answer

[
    ["John","a","b","c"],
    ["Mary","d"]
]

Key Idea

Email identifies a person.

If two accounts share an email,
Union their account indices.

After all unions,
Accounts having the same leader belong to the same person.

Group all emails by leader,
Sort them,
Add the person's name,
Return the answer.

Time Complexity : O(M log M)
M = Total number of emails

Space Complexity : O(M + N)

====================================================================
*/

int main(){
    return 0;
}