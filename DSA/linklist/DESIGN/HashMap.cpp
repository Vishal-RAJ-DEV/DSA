#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   APPROACH 1 : CHAINING USING SINGLY LINKED LIST
   ============================================================
   CORE IDEA (Hashing with Chaining) :
   A hash table is just an array of "buckets". The hash function
   maps every key to one bucket index. Multiple keys can map to
   the same bucket (this is called a COLLISION), so each bucket
   holds a linked list of (key, value) pairs that share the same
   hash. This way of resolving collisions by storing multiple
   elements per bucket is called SEPARATE CHAINING.

   - SIZE = 1009 : Number of buckets. Chosen as a LARGE PRIME so
     that key % SIZE spreads keys as evenly as possible across
     the buckets and reduces collisions.

   - hash(key) = key % SIZE : The mapping function. Since keys
     here are integers in the range [0, 10^6] and SIZE is a prime,
     the remainder distributes the keys fairly uniformly.

   - table : vector<Node*>. table[i] is the head pointer of the
     linked list (chain) stored in bucket i. nullptr means the
     bucket is empty.

   - Node   : A node of a chain. Stores {key, value} and a "next"
     pointer to the following node in the same bucket.

   --- put(key, value) ---
     1. Compute idx = hash(key) to find the bucket.
     2. Walk the chain of that bucket.
        - If a node with the SAME key is found, just UPDATE its
          value and return (no duplicate keys are allowed).
        - If the key is not found, we reached the end of the chain.
     3. Insert a new node with {key, value} at the HEAD of the
        chain (node->next = table[idx]; table[idx] = node).
        Inserting at the head is O(1) and needs no traversal
        pointer tracking.

   --- get(key) ---
     1. Compute idx = hash(key).
     2. Walk the chain of bucket idx.
        - If a node with this key exists, return its value.
        - If the chain ends without finding it, the key is NOT in
          the map -> return -1 (the convention for "not found").

   --- remove(key) ---
     1. Compute idx = hash(key).
     2. Walk the chain keeping BOTH curr (current node) and prev
        (previous node) pointers.
        - When the key is found:
            * If prev exists, unlink curr via prev->next = curr->next.
            * Else curr is the HEAD, so update the bucket head to
              curr->next.
            * delete curr and stop.
        - If the chain ends, the key does not exist -> do nothing.

   ALGORITHM :
       Hash table with separate chaining (array of singly linked
       lists). Operations are hash-to-bucket + linear scan of the
       chain. With SIZE = 1009 and random keys, each chain is
       tiny (~1000000/1009 nodes on average), so scans are fast.

   COMPLEXITY :
       put/get/remove :
         Best case   : O(1)  (empty / 1-node chain)
         Average case: O(1 + load factor)  -> effectively O(1)
         Worst case  : O(N)  (all keys collide into one chain)
       Space : O(N) for the nodes + O(SIZE) for the table.
   ============================================================ */

class MyHashMap {
private:

    static const int SIZE = 1009;

    class Node {
    public:

        int key;
        int value;

        Node* next;

        Node(int k, int v) {
            key = k;
            value = v;
            next = nullptr;
        }
    };

    vector<Node*> table;

    int hash(int key) {
        return key % SIZE;
    }

public:

    MyHashMap() {
        table.resize(SIZE, nullptr);
    }

    void put(int key, int value) {

        int idx = hash(key);

        Node* curr = table[idx];

        // Update if key already exists
        while (curr) {

            if (curr->key == key) {
                curr->value = value;
                return;
            }

            curr = curr->next;
        }

        // Insert new node at head
        Node* node = new Node(key, value);

        node->next = table[idx];

        table[idx] = node;
    }

    int get(int key) {

        int idx = hash(key);

        Node* curr = table[idx];

        while (curr) {

            if (curr->key == key)
                return curr->value;

            curr = curr->next;
        }

        return -1;
    }

    void remove(int key) {

        int idx = hash(key);

        Node* curr = table[idx];
        Node* prev = nullptr;

        while (curr) {

            if (curr->key == key) {

                if (prev)
                    prev->next = curr->next;
                else
                    table[idx] = curr->next;

                delete curr;

                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }
};




/* ============================================================
   APPROACH 2 : CHAINING USING VECTOR OF PAIRS
   ============================================================
   CORE IDEA :
   Same hashing concept as Approach 1, but instead of managing
   the chains manually with linked-list nodes, each bucket is a
   vector<vector<pair<int,int>>>. Bucket i is a small dynamic
   array of (key, value) pairs -- i.e. chaining done with a
   std::vector instead of a hand-written linked list.

   - size = 200001 : Number of buckets (a prime).
   - map : vector<vector<pair<int,int>>>. map[i] holds all the
     {key, value} pairs whose hash equals i. Pairs are appended
     in insertion order, so the bucket behaves like a mini-array.
   - hash(key) = key % size : same modular mapping as before.

   --- put(key, value) ---
     1. Compute idx = hash(key).
     2. Loop over every pair in map[idx].
        - If a pair with the SAME key is found, update its value
          (p.second = value) and return.
        - Otherwise the loop finishes without a match.
     3. push_back({key, value}) at the end of the bucket.

   --- get(key) ---
     1. Compute idx = hash(key).
     2. Scan all pairs of map[idx].
        - If p.first == key, return p.second.
        - Not found after the whole scan -> return -1.

   --- remove(key) ---
     1. Compute idx = hash(key).
     2. Scan the bucket by index i.
        - When map[idx][i].first == key, erase that pair from the
          bucket (shifts the remaining pairs left) and return.
        - If no match is found, the key does not exist.

   NOTE (BUG in the given code) :
       Line "map[idx].erase(map[idx].begin() + 1)" erases the
       SECOND element of the bucket unconditionally. The correct
       line should be "map[idx].erase(map[idx].begin() + i)" so
       the element at the found position i is removed. As written,
       remove() deletes the wrong pair and even crashes when the
       bucket has fewer than 2 pairs.

   ALGORITHM :
       Hash table with separate chaining implemented with
       std::vector buckets. Same overall behaviour as Approach 1
       but with array semantics instead of pointer chasing.

   COMPLEXITY :
       put/get   :
         Average case: O(1)  (tiny buckets with a large table)
         Worst case  : O(N)  (every key in one bucket)
       remove    :
         Average case: O(K) where K = bucket length (scan + erase
         shifts elements, so it is O(K) for a K-pair bucket).
       Space : O(N) for the pairs + O(size) for the buckets.
   ============================================================ */

class MyHashMap {
    private:
        static const int size = 200001;
         vector<vector<pair<int , int >>>map;

         int hash (int key){
            return key % size;
         }
public:
    MyHashMap() {
        map.resize(size);
    }
    
    void put(int key, int value) {
        int idx = hash( key );

        for( auto &p : map[idx]){
            if(p.first == key){
                p.second = value; //if present then update it 
                return;
            }
        }
        map[idx].push_back({key , value});//otherise insert it 
    }
    
    int get(int key) {
        int idx = hash( key );

        for( auto &p : map[idx]){
            if( p.first == key) { //serach in the idx for that key 
                return p.second;
            }
        }
        return -1;
    }
    
    void remove(int key) {
        int idx = hash(key);

        for( int i = 0 ; i<map[idx].size() ; i++){
            if( map[idx][i].first == key ){ // in map idx where is many pair , find here ith matchs the key 
                map[idx].erase( map[idx].begin() + 1);
                return;
            }
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */


int main(){
    return 0;
}