/*
=============================================================================
                        TRIE DATA STRUCTURE (Prefix Tree)
=============================================================================

WHAT IS A TRIE?
---------------
A Trie is a tree-like data structure used to store a dynamic set of strings,
where each node represents a single character. It is commonly used for:
  - Fast prefix-based searching (autocomplete, spell checkers)
  - Dictionary implementations
  - IP routing tables

TIME COMPLEXITY:
  - Insert:   O(L) where L = length of the word
  - Search:   O(L)
  - StartsWith: O(L)
  - CountWordsEqualTo: O(L)
  - CountWordsStartingWith: O(L)
  - Erase:   O(L)
All operations are linear in the length of the word, not dependent on
the number of words stored in the Trie.

SPACE COMPLEXITY: O(N * L * 26) worst case, but practically much less
due to shared prefixes between words.

=============================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
=============================================================================
                            TRIE CLASS
=============================================================================
The Trie class encapsulates the entire Trie data structure.
It has:
  - A private inner struct 'Node' representing each node in the Trie
  - A pointer 'root' to the root node (dummy node, represents empty prefix)
  - Public methods: insert, search, startsWith, countWordsEqualTo,
    countWordsStartingWith, erase
=============================================================================
*/
class Trie {

    /*
    -----------------------------------------------------------------------
                            NODE STRUCTURE
    -----------------------------------------------------------------------
    Each node contains:
      1. child[26]: An array of 26 pointers (one for each lowercase letter
                    'a' to 'z'). If child[i] is not nullptr, it means
                    the path for character ('a' + i) exists from this node.

      2. isEnd: A boolean flag. When true, it means the node marks the end
                of a complete word stored in the Trie. This is critical
                because a prefix like "app" might exist without "app" being
                a complete word (only "apple" might be stored).
                isEnd is the FASTEST way to check existence (just a bool check).

      3. wordCount: Tracks how many TIMES the exact word ending at this
                    node has been inserted. For example, inserting "app"
                    twice makes wordCount=2 at the 'p' node. This allows
                    duplicates and precise counting/removal.

      4. prefixCount: Tracks how many words in the Trie PASS THROUGH
                      this node (i.e., have this node's path as a prefix).
                      Every time ANY word is inserted that traverses this
                      node, prefixCount is incremented. This enables
                      counting words that start with a given prefix.

    Example: For inserts "app", "app", "apple", "ape":
      root -> 'a' (prefixCount=4) -> 'p' (prefixCount=3)
                                       -> 'p' (wordCount=2, prefixCount=2)
                                            -> 'l' -> 'e' (wordCount=1)
                                       -> 'e' (wordCount=1)

    The node at 'p' (first) has prefixCount=3 because "app", "app", "apple"
    all pass through it. The node at second 'p' has wordCount=2 because
    "app" was inserted twice.
    -----------------------------------------------------------------------
    */
    struct Node {
        Node* child[26];  // Array of 26 child pointers (for 'a' to 'z')
        bool isEnd;        // Flag: true if this node marks end of a word
        int wordCount;    // Number of times the exact word ends here
        int prefixCount;  // Number of words passing through this node

        // Constructor: initializes a new node
        // - Sets all 26 child pointers to nullptr (no children yet)
        // - Sets isEnd to false (not the end of any word yet)
        // - Sets wordCount to 0 (no word ends here yet)
        // - Sets prefixCount to 0 (no word passes through here yet)
        Node() {
            isEnd = false;
            wordCount = 0;
            prefixCount = 0;
            for(int i = 0; i < 26; i++) {
                child[i] = nullptr;
            }
        }
    };

    Node* root;  // Pointer to the root node of the Trie

public:

    /*
    -----------------------------------------------------------------------
                        TRIE CONSTRUCTOR
    -----------------------------------------------------------------------
    Initializes the Trie by creating a root node.
    The root node is a dummy/empty node that represents the empty prefix "".
    All words in the Trie start as children of this root node.

    Memory: root = new Node() allocates a Node on the heap with all
    children set to nullptr and isEnd set to false.
    -----------------------------------------------------------------------
    */
    Trie() {
        root = new Node();
    }

    /*
    -----------------------------------------------------------------------
                            INSERT FUNCTION
    -----------------------------------------------------------------------
    Purpose: Inserts a word into the Trie.

    How it works (step-by-step):
      1. Start at the root node (curr = root).
      2. For each character in the word:
         a. Convert character to index: index = ch - 'a'
            - 'a' maps to 0, 'b' maps to 1, ..., 'z' maps to 25
         b. If no child exists at child[index], create a new Node there.
            This means we are building the path for this word character
            by character.
         c. Move curr to that child node (curr = curr->child[index]).
      3. After processing all characters, mark the last node as isEnd = true.
         This indicates that a complete word ends at this node.

    Example: Inserting "cat"
      - Start at root
      - 'c' (index 2): root->child[2] is nullptr, so create new Node.
        Move curr to this new node.
      - 'a' (index 0): curr->child[0] is nullptr, so create new Node.
        Move curr to this new node.
      - 't' (index 19): curr->child[19] is nullptr, so create new Node.
        Move curr to this new node.
      - Mark curr->isEnd = true (word "cat" ends here).

    Time Complexity: O(L) where L = length of the word.
    -----------------------------------------------------------------------
    */
    void insert(string word) {
        // Start traversal from the root node
        Node* curr = root;

        // Process each character of the word one by one
        for(char ch : word) {
            // Convert character to array index: 'a'->0, 'b'->1, ..., 'z'->25
            int index = ch - 'a';

            // If no node exists for this character, create a new node
            if(curr->child[index] == nullptr) {
                curr->child[index] = new Node();
            }

            // Move to the child node for this character
            curr = curr->child[index];

            // Increment prefixCount: this node is part of the path for
            // the word being inserted, so one more word passes through it
            curr->prefixCount++;
        }

        // Increment wordCount: marks that one more copy of this exact
        // word now ends at this node
        curr->wordCount++;

        // Set isEnd = true: marks that at least one complete word ends here.
        // isEnd is the quick boolean check used by search() to verify
        // that a complete word exists at this node (not just a prefix).
        curr->isEnd = true;
    }

    /*
    -----------------------------------------------------------------------
                            SEARCH FUNCTION
    -----------------------------------------------------------------------
    Purpose: Checks if a given word exists completely in the Trie.

    How it works (step-by-step):
      1. Start at the root node (curr = root).
      2. For each character in the word:
         a. Convert character to index: index = ch - 'a'
         b. If no child exists at child[index], the word does NOT exist
            in the Trie. Return false immediately.
         c. Move curr to that child node.
      3. After traversing all characters, check curr->isEnd.
         - If isEnd is true: the word exists (return true).
         - If isEnd is false: only a prefix exists, not the full word
           (return false).

    Example: Searching "cat" vs "ca"
      After inserting "cat":
      - Searching "cat": traverses c->a->t, then checks isEnd at 't'.
        isEnd = true => word exists.
      - Searching "ca": traverses c->a, then checks isEnd at 'a'.
        isEnd = false => "ca" is not a complete word, only a prefix.

    Time Complexity: O(L) where L = length of the word.
    -----------------------------------------------------------------------
    */
    bool search(string word) {
        // Start traversal from the root node
        Node* curr = root;

        // Process each character of the word
        for(char ch : word) {
            // Convert character to array index
            int index = ch - 'a';

            // If the path doesn't exist, word is not in Trie
            if(curr->child[index] == nullptr) {
                return false;
            }

            // Move to the next node
            curr = curr->child[index];
        }

        // Check if this node marks the end of a complete word
        // isEnd is a fast boolean check: true means a word ends here
        return curr->isEnd;
    }

    /*
    -----------------------------------------------------------------------
                        STARTSWITH FUNCTION
    -----------------------------------------------------------------------
    Purpose: Checks if any word in the Trie starts with the given prefix.

    How it works (step-by-step):
      1. Start at the root node (curr = root).
      2. For each character in the prefix:
         a. Convert character to index: index = ch - 'a'
         b. If no child exists at child[index], no word in the Trie
            starts with this prefix. Return false immediately.
         c. Move curr to that child node.
      3. If we successfully traverse all characters of the prefix,
         return true (some word in the Trie starts with this prefix).

    Note: Unlike search(), we do NOT check isEnd here.
    We only need to verify that the prefix path exists in the Trie.

    Example: After inserting "apple":
      - startsWith("app"): traverses a->p->p. Path exists => true.
      - startsWith("apl"): traverses a->p, then 'l' at index 11.
        child[11] is nullptr => false.

    Time Complexity: O(L) where L = length of the prefix.
    -----------------------------------------------------------------------
    */
    bool startsWith(string prefix) {
        // Start traversal from the root node
        Node* curr = root;

        // Process each character of the prefix
        for(char ch : prefix) {
            // Convert character to array index
            int index = ch - 'a';

            // If the path doesn't exist, no word has this prefix
            if(curr->child[index] == nullptr) {
                return false;
            }

            // Move to the next node
            curr = curr->child[index];
        }

        // Successfully traversed the entire prefix - it exists
        return true;
    }

    /*
    -----------------------------------------------------------------------
                    COUNT WORDS EQUAL TO FUNCTION
    -----------------------------------------------------------------------
    Purpose: Returns how many times a specific word has been inserted
             into the Trie. If the word was never inserted, returns 0.

    How it works (step-by-step):
      1. Start at the root node (curr = root).
      2. For each character in the word:
         a. Convert character to index: index = ch - 'a'
         b. If no child exists at child[index], the word was never
            inserted. Return 0 immediately.
         c. Move curr to that child node.
      3. After traversing all characters, return curr->wordCount.
         - wordCount = 0 => word was never inserted
         - wordCount = 1 => word was inserted once
         - wordCount = N => word was inserted N times

    Difference from search():
      - search() returns true/false (exists or not)
      - countWordsEqualTo() returns the EXACT COUNT of insertions

    Example: After inserting "app" twice, "apple" once:
      countWordsEqualTo("app")   => 2  (inserted twice)
      countWordsEqualTo("apple") => 1  (inserted once)
      countWordsEqualTo("ap")    => 0  (not a complete word)

    Time Complexity: O(L) where L = length of the word.
    -----------------------------------------------------------------------
    */
    int countWordsEqualTo(string word) {
        // Start traversal from the root node
        Node* curr = root;

        // Process each character of the word
        for(char ch : word) {
            // Convert character to array index
            int index = ch - 'a';

            // If the path doesn't exist, word was never inserted
            if(curr->child[index] == nullptr) {
                return 0;
            }

            // Move to the next node
            curr = curr->child[index];
        }

        // Return the count of how many times this word was inserted
        return curr->wordCount;
    }

    /*
    -----------------------------------------------------------------------
                COUNT WORDS STARTING WITH FUNCTION
    -----------------------------------------------------------------------
    Purpose: Returns how many words in the Trie start with the given
             prefix. If no word has this prefix, returns 0.

    How it works (step-by-step):
      1. Start at the root node (curr = root).
      2. For each character in the prefix:
         a. Convert character to index: index = ch - 'a'
         b. If no child exists at child[index], no word has this prefix.
            Return 0 immediately.
         c. Move curr to that child node.
      3. After traversing all characters, return curr->prefixCount.
         prefixCount at this node tells us how many words pass through
         (i.e., have) this path as a prefix.

    Difference from startsWith():
      - startsWith() returns true/false (at least one word or not)
      - countWordsStartingWith() returns the EXACT COUNT of words

    Example: After inserting "app", "apple", "ape", "bat":
      countWordsStartingWith("ap")  => 3  ("app", "apple", "ape")
      countWordsStartingWith("app") => 2  ("app", "apple")
      countWordsStartingWith("b")   => 1  ("bat")
      countWordsStartingWith("c")   => 0  (no words start with 'c')

    Time Complexity: O(L) where L = length of the prefix.
    -----------------------------------------------------------------------
    */
    int countWordsStartingWith(string prefix) {
        // Start traversal from the root node
        Node* curr = root;

        // Process each character of the prefix
        for(char ch : prefix) {
            // Convert character to array index
            int index = ch - 'a';

            // If the path doesn't exist, no word has this prefix
            if(curr->child[index] == nullptr) {
                return 0;
            }

            // Move to the next node
            curr = curr->child[index];
        }

        // Return how many words pass through this node (have this prefix)
        return curr->prefixCount;
    }

    /*
    -----------------------------------------------------------------------
                            ERASE FUNCTION
    -----------------------------------------------------------------------
    Purpose: Removes ONE occurrence of a word from the Trie.
             If the word was inserted 3 times, one call removes one copy.
             If the word doesn't exist, the function does nothing.

    How it works (step-by-step):
      1. VERIFICATION PHASE: Check if the word exists in the Trie.
         a. Start at root, traverse each character.
         b. If any character's path doesn't exist => word not found, return.
         c. After full traversal, check if wordCount > 0.
         d. If wordCount == 0 => word not found, return.

      2. DECREMENT PHASE: Remove one occurrence of the word.
         a. Reset curr to root.
         b. Traverse the word again, character by character.
         c. At EACH node along the path, decrement prefixCount by 1.
            (This node no longer "passes through" one copy of this word)
         d. At the final node (end of word), decrement wordCount by 1.
            (One copy of this word is removed)

    Why TWO passes?
      - First pass: validate the word exists (avoid corrupting the Trie)
      - Second pass: safely decrement counts along the path

    Example: Inserting "app" twice, then erasing once:
      After 2 inserts: node 'p' has wordCount=2, prefixCount=2
      After 1 erase:  node 'p' has wordCount=1, prefixCount=1
      The word "app" still exists once (wordCount=1).

    Example: Erasing a word that doesn't exist:
      erase("xyz") => first pass fails (path doesn't exist), returns immediately.

    When wordCount reaches 0 after erase:
      - isEnd is set back to false (no complete word ends here anymore)
      - search() will now correctly return false for this word
      - The path nodes still exist (shared with other words)

    Time Complexity: O(L) where L = length of the word.
    -----------------------------------------------------------------------
    */
    void erase(string word) {
        Node* curr = root;

        // ---- VERIFICATION PHASE ----
        // Check if the word actually exists before trying to erase it
        for(char ch : word) {
            int index = ch - 'a';

            // Path doesn't exist - word was never inserted, nothing to erase
            if(curr->child[index] == nullptr) {
                return;
            }
            curr = curr->child[index];
        }

        // If wordCount is 0, the word doesn't exist - nothing to erase
        if(curr->wordCount == 0) {
            return;
        }

        // ---- DECREMENT PHASE ----
        // Reset to root and traverse again to decrement counts
        curr = root;

        // Traverse each character and decrement prefixCount at each node
        // Each node along the path loses one "pass-through" word
        for(char ch : word) {
            int index = ch - 'a';
            curr = curr->child[index];
            curr->prefixCount--;  // One fewer word passes through here
        }

        // Decrement wordCount: one copy of this word is removed
        curr->wordCount--;

        // If wordCount reaches 0, no complete word ends here anymore.
        // Set isEnd back to false so search() correctly returns false.
        if(curr->wordCount == 0) {
            curr->isEnd = false;
        }
    }
};

/*
=============================================================================
                            MAIN FUNCTION
=============================================================================
Demonstrates all six Trie operations: insert, search, startsWith,
countWordsEqualTo, countWordsStartingWith, and erase.
=============================================================================
*/
int main() {

    // Create a Trie object
    Trie trie;

    // ---- INSERT OPERATIONS ----
    // Insert words into the Trie (some with duplicates to show counting)
    trie.insert("apple");     // 1st insert of "apple"
    trie.insert("apple");     // 2nd insert of "apple" (duplicate)
    trie.insert("app");       // "app" (prefix of "apple")
    trie.insert("app");       // 2nd insert of "app"
    trie.insert("app");       // 3rd insert of "app"
    trie.insert("banana");    // "banana"
    trie.insert("bat");       // "bat"
    trie.insert("band");      // "band"
    trie.insert("cat");       // "cat"

    // ---- SEARCH OPERATIONS ----
    cout << "=== SEARCH RESULTS ===" << endl;
    cout << "Search 'apple':  " << (trie.search("apple") ? "Found" : "Not Found") << endl;
    cout << "Search 'app':    " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "Search 'ap':     " << (trie.search("ap") ? "Found" : "Not Found") << endl;
    cout << "Search 'bat':    " << (trie.search("bat") ? "Found" : "Not Found") << endl;
    cout << "Search 'band':   " << (trie.search("band") ? "Found" : "Not Found") << endl;
    cout << endl;

    // ---- COUNT WORDS EQUAL TO ----
    // Shows how many times each word was inserted
    cout << "=== COUNT WORDS EQUAL TO ===" << endl;
    cout << "Count 'apple':  " << trie.countWordsEqualTo("apple") << endl;  // 2
    cout << "Count 'app':    " << trie.countWordsEqualTo("app") << endl;    // 3
    cout << "Count 'ap':     " << trie.countWordsEqualTo("ap") << endl;     // 0
    cout << "Count 'bat':    " << trie.countWordsEqualTo("bat") << endl;    // 1
    cout << "Count 'banana': " << trie.countWordsEqualTo("banana") << endl; // 1
    cout << "Count 'xyz':    " << trie.countWordsEqualTo("xyz") << endl;    // 0
    cout << endl;

    // ---- COUNT WORDS STARTING WITH ----
    // Shows how many words share a given prefix
    cout << "=== COUNT WORDS STARTING WITH ===" << endl;
    cout << "StartsWith 'ap':    " << trie.countWordsStartingWith("ap") << endl;   // 5
    cout << "StartsWith 'app':   " << trie.countWordsStartingWith("app") << endl;  // 5
    cout << "StartsWith 'apple': " << trie.countWordsStartingWith("apple") << endl; // 2
    cout << "StartsWith 'b':     " << trie.countWordsStartingWith("b") << endl;    // 3
    cout << "StartsWith 'ba':    " << trie.countWordsStartingWith("ba") << endl;   // 3
    cout << "StartsWith 'bat':   " << trie.countWordsStartingWith("bat") << endl;  // 1
    cout << "StartsWith 'c':     " << trie.countWordsStartingWith("c") << endl;    // 1
    cout << "StartsWith 'd':     " << trie.countWordsStartingWith("d") << endl;    // 0
    cout << endl;

    // ---- ERASE OPERATIONS ----
    cout << "=== ERASE OPERATIONS ===" << endl;

    // Erase one copy of "app" (was inserted 3 times)
    cout << "Erasing 'app' (was inserted 3 times)..." << endl;
    trie.erase("app");
    cout << "Count 'app' after erase: " << trie.countWordsEqualTo("app") << endl;  // 2

    // Erase one copy of "apple" (was inserted 2 times)
    cout << "Erasing 'apple' (was inserted 2 times)..." << endl;
    trie.erase("apple");
    cout << "Count 'apple' after erase: " << trie.countWordsEqualTo("apple") << endl; // 1

    // Try to erase a word that doesn't exist
    cout << "Erasing 'xyz' (never inserted)..." << endl;
    trie.erase("xyz");
    cout << "Count 'xyz' after erase: " << trie.countWordsEqualTo("xyz") << endl; // 0

    // Erase remaining "apple" (was 1, now 0)
    cout << "Erasing 'apple' again (last copy)..." << endl;
    trie.erase("apple");
    cout << "Count 'apple' after erase: " << trie.countWordsEqualTo("apple") << endl; // 0
    cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not Found") << endl; // Not Found
    cout << endl;

    // ---- FINAL STATE ----
    cout << "=== FINAL COUNTS ===" << endl;
    cout << "Count 'app':    " << trie.countWordsEqualTo("app") << endl;    // 2
    cout << "Count 'banana': " << trie.countWordsEqualTo("banana") << endl; // 1
    cout << "Count 'bat':    " << trie.countWordsEqualTo("bat") << endl;    // 1
    cout << "Count 'band':   " << trie.countWordsEqualTo("band") << endl;   // 1
    cout << "Count 'cat':    " << trie.countWordsEqualTo("cat") << endl;    // 1
    cout << endl;

    /*
    =====================================================================
    EXPECTED OUTPUT:
    =====================================================================
    === SEARCH RESULTS ===
    Search 'apple':  Found
    Search 'app':    Found
    Search 'ap':     Not Found
    Search 'bat':    Found
    Search 'band':   Found

    === COUNT WORDS EQUAL TO ===
    Count 'apple':  2
    Count 'app':    3
    Count 'ap':     0
    Count 'bat':    1
    Count 'banana': 1
    Count 'xyz':    0

    === COUNT WORDS STARTING WITH ===
    StartsWith 'ap':    5
    StartsWith 'app':   5
    StartsWith 'apple': 2
    StartsWith 'b':     3
    StartsWith 'ba':    3
    StartsWith 'bat':   1
    StartsWith 'c':     1
    StartsWith 'd':     0

    === ERASE OPERATIONS ===
    Erasing 'app' (was inserted 3 times)...
    Count 'app' after erase: 2
    Erasing 'apple' (was inserted 2 times)...
    Count 'apple' after erase: 1
    Erasing 'xyz' (never inserted)...
    Count 'xyz' after erase: 0
    Erasing 'apple' again (last copy)...
    Count 'apple' after erase: 0
    Search 'apple': Not Found

    === FINAL COUNTS ===
    Count 'app':    2
    Count 'banana': 1
    Count 'bat':    1
    Count 'band':   1
    Count 'cat':    1
    =====================================================================
    */

    return 0;
}