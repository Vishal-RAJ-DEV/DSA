/*
=============================================================================
        LEETCODE 211 - Design Add and Search Words Data Structure
=============================================================================

Problem: Design a data structure that supports adding new words and
         finding if a string matches any previously added string.
         word may contain dots '.' where dots can be matched with any letter.

Operations:
  - addWord(word):    Adds word to the data structure
  - search(word):     Returns true if word matches any stored string
                      ('.' can match any letter)

Example:
  addWord("bad"), addWord("dad"), addWord("mad")
  search("pad")  => false  (no word "pad")
  search("bad")  => true   (exact match)
  search(".ad")  => true   ('.' matches 'b', 'd', or 'm')
  search("b..")  => true   ('.' matches 'a' then 'd')

=============================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class WordDictionary {

    /*
    -----------------------------------------------------------------------
                            NODE STRUCTURE
    -----------------------------------------------------------------------
    Each node contains:
      1. child[26]: Array of 26 pointers for 'a' to 'z'.
      2. isEnd:     Boolean flag marking end of a complete word.

    Example: After adding "bad", "dad", "mad":

                (root)
              /   |   \
             b    d    m
             |    |    |
             a    a    a
             |    |    |
             d(*) d(*) d(*)

    (*) = isEnd is true
    -----------------------------------------------------------------------
    */
    struct Node {
        Node* child[26];
        bool isEnd;

        Node() {
            isEnd = false;
            for(int i = 0; i < 26; i++) {
                child[i] = nullptr;
            }
        }
    };

    Node* root;

public:

    WordDictionary() {
        root = new Node();
    }

    /*
    -----------------------------------------------------------------------
                            ADDWORD FUNCTION
    -----------------------------------------------------------------------
    Purpose: Inserts a word into the WordDictionary.

    How it works:
      1. Start at root.
      2. For each character, create child node if it doesn't exist.
      3. Move to that child.
      4. Mark the final node as isEnd = true.

    Time Complexity: O(L) where L = length of the word.
    -----------------------------------------------------------------------
    */
    void addWord(string word) {
        Node* curr = root;

        for(char ch : word) {
            int index = ch - 'a';

            if(curr->child[index] == nullptr) {
                curr->child[index] = new Node();
            }

            curr = curr->child[index];
        }

        curr->isEnd = true;
    }

    /*
    -----------------------------------------------------------------------
                        SEARCH FUNCTION (WITH WILDCARDS)
    -----------------------------------------------------------------------
    Purpose: Checks if any stored word matches the given pattern.
             '.' can match ANY lowercase letter.

    MAIN IDEA:
      - Normal characters: follow the exact path (like regular Trie search).
      - Dot '.': try ALL 26 children recursively. If ANY branch matches
        the remaining pattern, return true.

    -----------------------------------------------------------------------
    STEP-BY-STEP WORKING WITH DIAGRAM
    -----------------------------------------------------------------------

    Example Trie after: addWord("bad"), addWord("dad"), addWord("mad")

                      (root)
                    /   |   \
                  'b'  'd'  'm'
                   |    |    |
                  'a'  'a'  'a'
                   |    |    |
                  'd'  'd'  'd'
                 (T)  (T)  (T)

    (T) = isEnd = true

    =======================================================================
    SEARCH EXAMPLE 1: search("pad")
    =======================================================================

    Pattern: "pad"
    Index:    0  1  2

    Step 1: index=0, char='p'
            - 'p' is NOT '.', so go to child['p'-'a'] = child[15]
            - root->child[15] == nullptr (no 'p' branch)
            - RETURN FALSE immediately

            (root)
          /   |   \
        'b'  'd'  'm'
         |
        'a'
         |
        'd'

            'p' branch doesn't exist => FALSE

    =======================================================================
    SEARCH EXAMPLE 2: search("bad")
    =======================================================================

    Pattern: "bad"
    Index:    0  1  2

    Step 1: index=0, char='b'
            - 'b' is NOT '.', go to child['b'-'a'] = child[1]
            - root->child[1] exists => move to 'b' node

    Step 2: index=1, char='a'
            - 'a' is NOT '.', go to child['a'-'a'] = child[0]
            - 'b' node->child[0] exists => move to 'a' node

    Step 3: index=2, char='d'
            - 'd' is NOT '.', go to child['d'-'a'] = child[3]
            - 'a' node->child[3] exists => move to 'd' node

    Step 4: index=3, word.size() reached
            - Check curr->isEnd
            - isEnd = TRUE => RETURN TRUE

            (root)
              |
             'b'  <-- Step 1
              |
             'a'  <-- Step 2
              |
             'd' <-- Step 3
            (T)   <-- Step 4: isEnd=true => TRUE

    =======================================================================
    SEARCH EXAMPLE 3: search(".ad")   <-- WILDCARD
    =======================================================================

    Pattern: ".ad"
    Index:    0  1  2

    Step 1: index=0, char='.'
            - '.' matches ANY letter, so try ALL 26 children of root

            Try child[0] ('a'):  No 'a' branch at root => skip
            Try child[1] ('b'):  'b' branch exists!
                => recurse: searchHelper(".ad", 1, 'b' node)

                Step 2: index=1, char='a'
                        - 'a' is NOT '.', go to child[0]
                        - 'b' node->child[0] exists => move to 'a' node

                Step 3: index=2, char='d'
                        - 'd' is NOT '.', go to child[3]
                        - 'a' node->child[3] exists => move to 'd' node

                Step 4: index=3, word.size() reached
                        - isEnd = TRUE => return TRUE

            Since child[1] returned TRUE, we RETURN TRUE immediately.
            (We don't need to try 'd' or 'm' branches)

            (root)
              |
             'b'  <-- '.' matched 'b'
              |
             'a'  <-- 'a' matched
              |
             'd'  <-- 'd' matched
            (T)   <-- isEnd=true => TRUE

    NOTE: '.' matched 'b', but it COULD have also matched 'd' or 'm':
            (root)
          /   |   \
        'b'  'd'  'm'    <-- '.' could match ANY of these
         |    |    |
        'a'  'a'  'a'
         |    |    |
        'd'  'd'  'd'
       (T)  (T)  (T)

    Since we found a match at 'b', we stop early (short-circuit).

    =======================================================================
    SEARCH EXAMPLE 4: search("b..")   <-- TWO WILDCARDS
    =======================================================================

    Pattern: "b.."
    Index:    0  1  2

    Step 1: index=0, char='b'
            - 'b' is NOT '.', go to child[1]
            - root->child[1] exists => move to 'b' node

    Step 2: index=1, char='.'
            - '.' matches ANY letter, try ALL 26 children of 'b' node

            Try child[0] ('a'):  'a' branch exists!
                => recurse: searchHelper("b..", 2, 'a' node)

                Step 3: index=2, char='.'
                        - '.' matches ANY letter, try ALL 26 children of 'a' node

                        Try child[0] ('a'):  nullptr => skip
                        Try child[1] ('b'):  nullptr => skip
                        ...
                        Try child[3] ('d'):  'd' branch exists!
                            => recurse: searchHelper("b..", 3, 'd' node)

                            Step 4: index=3, word.size() reached
                                    - isEnd = TRUE => return TRUE

                        Since child[3] returned TRUE, return TRUE

                Since child[0] returned TRUE, return TRUE

            Since child[0] returned TRUE, we RETURN TRUE immediately.

            (root)
              |
             'b'  <-- Step 1: 'b' matched
              |
             'a'  <-- Step 2: '.' matched 'a'
              |
             'd'  <-- Step 3: '.' matched 'd'
            (T)   <-- Step 4: isEnd=true => TRUE

    ALTERNATIVE PATH (if "bad" didn't exist):
            (root)
              |
             'b'
              |
             'a'  <-- '.' tried 'a', but "ba?" has no match
              |
            (no other children)

            Then '.' would try child[1] ('b'): nullptr => skip
            ... until it finds a valid path or exhausts all 26.

    -----------------------------------------------------------------------
    RECURSIVE TREE FOR search("b..")
    -----------------------------------------------------------------------

                        searchHelper("b..", 0, root)
                                    |
                            char='b', go to 'b' node
                                    |
                        searchHelper("b..", 1, 'b' node)
                                    |
                            char='.', try all 26
                           /        |        \
                    try 'a'      try 'b'    try 'c' ...
                        |            |           |
            searchHelper("b..",2,'a')  nullptr     nullptr
                        |
                char='.', try all 26
               /         |         \
        try 'a'      try 'b'    try 'd' ...
            |            |           |
        nullptr      nullptr   searchHelper("b..",3,'d')
                                        |
                                  index==3, isEnd=true
                                        |
                                     return TRUE
                                        |
                    (backtrack) return TRUE
                                        |
                    (backtrack) return TRUE
                                        |
                    (backtrack) return TRUE

    -----------------------------------------------------------------------
    TIME COMPLEXITY
    -----------------------------------------------------------------------
    - addWord:   O(L) where L = word length
    - search:    O(26^d * L) worst case, where d = number of dots
      * With max 2 dots (given constraint): O(26^2 * L) = O(676 * L)
      * In practice, much faster because many branches are nullptr
    -----------------------------------------------------------------------
    */
    bool search(string word) {
        return searchHelper(word, 0, root);
    }

private:

    // Recursive helper: matches word[index..end] starting from node 'curr'
    bool searchHelper(string& word, int index, Node* curr) {

        // BASE CASE: all characters matched
        // Return true only if this node marks end of a complete word
        if(index == word.size()) {
            return curr->isEnd;
        }

        char ch = word[index];

        // CASE 1: Current character is a DOT '.'
        // '.' can match ANY letter, so we must try ALL 26 children
        // If ANY child leads to a full match, return true
        if(ch == '.') {
            for(int i = 0; i < 26; i++) {
                if(curr->child[i] != nullptr) {
                    // Recursively check if remaining pattern matches
                    if(searchHelper(word, index + 1, curr->child[i])) {
                        return true;  // Found a match, no need to try more
                    }
                }
            }
            // Tried all 26 children, none matched
            return false;
        }

        // CASE 2: Current character is a NORMAL LETTER
        // Go to the specific child for this letter
        int idx = ch - 'a';

        // If path doesn't exist, no match possible
        if(curr->child[idx] == nullptr) {
            return false;
        }

        // Continue matching remaining characters
        return searchHelper(word, index + 1, curr->child[idx]);
    }
};

/*
=============================================================================
                            MAIN FUNCTION
=============================================================================
Demonstrates WordDictionary with addWord and search operations.
=============================================================================
*/
int main() {

    WordDictionary wordDictionary;

    // ---- ADD WORDS ----
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    wordDictionary.addWord("bat");
    wordDictionary.addWord("band");

    // ---- SEARCH OPERATIONS ----
    cout << "=== SEARCH RESULTS ===" << endl;

    // Exact matches
    cout << "search(\"bad\"):  " << (wordDictionary.search("bad") ? "true" : "false") << endl;   // true
    cout << "search(\"dad\"):  " << (wordDictionary.search("dad") ? "true" : "false") << endl;   // true
    cout << "search(\"mad\"):  " << (wordDictionary.search("mad") ? "true" : "false") << endl;   // true
    cout << "search(\"bat\"):  " << (wordDictionary.search("bat") ? "true" : "false") << endl;   // true
    cout << "search(\"band\"): " << (wordDictionary.search("band") ? "true" : "false") << endl;  // true

    // No match
    cout << "search(\"pad\"):  " << (wordDictionary.search("pad") ? "true" : "false") << endl;   // false
    cout << "search(\"xyz\"):  " << (wordDictionary.search("xyz") ? "true" : "false") << endl;   // false

    // Single dot wildcard
    cout << "search(\".ad\"):  " << (wordDictionary.search(".ad") ? "true" : "false") << endl;   // true
    cout << "search(\"b.t\"):  " << (wordDictionary.search("b.t") ? "true" : "false") << endl;   // true
    cout << "search(\".at\"):  " << (wordDictionary.search(".at") ? "true" : "false") << endl;   // true

    // Two dot wildcards
    cout << "search(\"b..\"):  " << (wordDictionary.search("b..") ? "true" : "false") << endl;   // true
    cout << "search(\"...\"):  " << (wordDictionary.search("...") ? "true" : "false") << endl;   // true
    cout << "search(\"d.d\"):  " << (wordDictionary.search("d.d") ? "true" : "false") << endl;   // true
    cout << "search(\"..d\"):  " << (wordDictionary.search("..d") ? "true" : "false") << endl;   // true
    cout << "search(\"b...\"): " << (wordDictionary.search("b...") ? "true" : "false") << endl;  // false (4 letters, no 4-letter word starting with b)

    cout << endl;

    /*
    =====================================================================
    EXPECTED OUTPUT:
    =====================================================================
    === SEARCH RESULTS ===
    search("bad"):  true
    search("dad"):  true
    search("mad"):  true
    search("bat"):  true
    search("band"): true
    search("pad"):  false
    search("xyz"):  false
    search(".ad"):  true
    search("b.t"):  true
    search(".at"):  true
    search("b.."):  true
    search("..."):  true
    search("d.d"):  true
    search("..d"):  true
    search("b..."): false
    =====================================================================
    */

    return 0;
}
