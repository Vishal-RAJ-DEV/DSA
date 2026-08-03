#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   APPROACH 1 : HASH SET WITH CHAINING (LINKED LIST BUCKETS)
   ============================================================
   CORE IDEA (Hashing with Chaining) :
   A hash set stores unique keys. It uses an array of "buckets",
   and the hash function maps every key to one bucket index.
   Because several keys can map to the same bucket (a COLLISION),
   each bucket holds a singly linked list of keys that share the
   same hash. Resolving collisions this way (several elements in
   one bucket) is called SEPARATE CHAINING.

   - SIZE = 1009 : Number of buckets, chosen as a PRIME so that
     key % SIZE spreads keys uniformly and reduces collisions.
   - hash(key) = key % SIZE : maps a key to its bucket index.
   - table : vector<Node*>. table[i] is the head pointer of the
     chain in bucket i; nullptr means the bucket is empty.
   - Node  : holds one key and a "next" pointer to the following
     node of the same chain. (A set stores only the key, not a
     value -- unlike a map.)

   --- add(key) ---
     1. Compute idx = hash(key).
     2. Walk the chain of bucket idx.
        - If a node with this key exists, the set already has the
          key, so do NOTHING and return (sets disallow duplicates).
        - If the chain ends, the key is new.
     3. Create a new node and insert it at the HEAD of the chain
        (node->next = table[idx]; table[idx] = node). Inserting at
        the head is O(1) and needs no prev-pointer bookkeeping.

   --- remove(key) ---
     1. Compute idx = hash(key).
     2. Walk the chain keeping both curr (current) and prev
        (previous) pointers.
        - When the key is found:
            * If prev exists, unlink curr via prev->next = curr->next.
            * Else curr is the HEAD, so update the bucket head to
              curr->next.
            * delete curr and stop.
        - If the chain ends, the key does not exist -> do nothing.

   --- contains(key) ---
     1. Compute idx = hash(key).
     2. Walk the chain.
        - Return true as soon as a matching key is found.
        - Return false if the whole chain is scanned without a match.

   ALGORITHM :
       Hash table with separate chaining (array of singly linked
       lists). Every operation is hash-to-bucket + a linear scan
       of that bucket's chain. With SIZE = 1009 and random keys,
       each chain holds ~N/1009 nodes, so scans stay tiny.

   COMPLEXITY :
       add/remove/contains :
         Best case   : O(1)  (empty or 1-node chain)
         Average case: O(1 + load factor)  -> effectively O(1)
         Worst case  : O(N)  (all keys collide into one chain)
       Space : O(N) for the nodes + O(SIZE) for the table.
   ============================================================ */

class MyHashSet {
private:

    static const int SIZE = 1009;   // Prime number of buckets

    class Node {
    public:
        int key;
        Node* next;

        Node(int k) {
            key = k;
            next = nullptr;
        }
    };

    vector<Node*> table;

    int hash(int key) {
        return key % SIZE;
    }

public:

    MyHashSet() {
        table.resize(SIZE, nullptr);
    }

    void add(int key) {

        int idx = hash(key);

        Node* curr = table[idx];

        // If key already exists, do nothing
        while (curr) {
            if (curr->key == key)
                return;
            curr = curr->next;
        }

        // Insert at head
        Node* node = new Node(key);
        node->next = table[idx];
        table[idx] = node;
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

    bool contains(int key) {

        int idx = hash(key);

        Node* curr = table[idx];

        while (curr) {

            if (curr->key == key)
                return true;

            curr = curr->next;
        }

        return false;
    }
};



/* ============================================================
   APPROACH 2 : BOOLEAN ARRAY (DIRECT-ADDRESS TABLE)
   ============================================================
   CORE IDEA :
   This is the simplest possible hash set. There is NO hash
   function and NO collision handling at all. Because the problem
   guarantees keys are integers in the range [0, 10^6], we can
   use the key ITSELF as an array index (this is called a
   DIRECT-ADDRESS TABLE).

   - present : vector<bool> of size 1,000,001.
     present[key] is true if 'key' is in the set, false otherwise.
     (A bool per possible key -- one slot for every allowed value.)

   --- add(key) ---
       Set present[key] = true. If it was already true, this is a
       no-op, which automatically preserves the "no duplicates"
       property of a set.

   --- remove(key) ---
       Set present[key] = false. Removing a key that is not in
       the set is harmless (it is already false).

   --- contains(key) ---
       Just read and return present[key]. One array lookup tells
       us whether the key exists.

   ALGORITHM :
       Direct addressing -- each possible key has a dedicated
       memory slot, so membership is a single array access.
       No hashing, no pointers, no collisions.

   COMPLEXITY :
       add/remove/contains : O(1) every time (single array access)
       Space : O(max_key + 1) = O(10^6) -- fixed, always allocated
               regardless of how many keys are actually stored.

   TRADE-OFF vs APPROACH 1 :
       This is much faster (O(1) guaranteed, no scanning) and much
       simpler, but it only works because the key range is small
       and known in advance. Approach 1 works for arbitrary / huge
       key ranges and uses memory proportional to the number of
       stored keys, but hashing costs extra and chains can grow.
   ============================================================ */

class MyHashSet {
    private: vector<bool> present;
public:
    MyHashSet() {
        present.resize(1000001 ,false);
    }
    
    void add(int key) {
        present[key] = true;
    }
    
    void remove(int key) {
        present[key] = false;
    }
    
    bool contains(int key) {
        return present[key];
    }
};



int main(){
    return 0;
}