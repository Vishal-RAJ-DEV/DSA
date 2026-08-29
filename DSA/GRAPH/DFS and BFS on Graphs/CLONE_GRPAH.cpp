#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};



class Solution {
public:

    // Maps original node -> its clone. Prevents revisiting (cycle handling)
    // and avoids creating duplicate clones for nodes with multiple parents.
    unordered_map<Node*, Node*> mp;

    // DFS-based deep clone of an undirected connected graph.
    // Returns the clone of the given node (entry point of cloned graph).
    Node* cloneGraph(Node* node) {

        // Base case: empty graph — nothing to clone
        if (node == nullptr) {
            return nullptr;
        }

        // If this node was already cloned in a previous recursive call
        // (via another path), return its existing clone immediately.
        // This also breaks cycles — without this, recursion would loop forever.
        if (mp.find(node) != mp.end()) {
            return mp[node];
        }

        // Create a brand-new clone node with the same value as the original.
        Node* clone = new Node(node->val);

        // Register the clone in the map BEFORE recursing into neighbors.
        // This is critical: when a neighbor's recursion loops back to this
        // node (cycle), it will find the clone here and stop recursing.
        mp[node] = clone;

        // Recursively clone every neighbor of the current node.
        // Each recursive call returns the clone of that neighbor,
        // which gets appended to this clone's neighbor list.
        // Result: the cloned node's neighbor list mirrors the original.
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(cloneGraph(neighbor));
        }

        // Return the fully constructed clone (with all its neighbors cloned)
        return clone;
    }
};


int main(){
    return 0;
}