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

    unordered_map<Node*, Node*> mp;

    Node* cloneGraph(Node* node) {

        // Empty graph
        if (node == nullptr) {
            return nullptr;
        }

        // If already cloned, return the clone
        if (mp.find(node) != mp.end()) {
            return mp[node];
        }

        // Create clone of current node
        Node* clone = new Node(node->val);

        // Store it BEFORE cloning neighbors
        mp[node] = clone;

        // Clone all neighbors
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(cloneGraph(neighbor));
        }

        return clone;
    }
};


int main(){
    return 0;
}