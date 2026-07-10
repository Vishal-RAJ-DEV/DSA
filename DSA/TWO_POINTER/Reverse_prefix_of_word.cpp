#include <bits/stdc++.h>
using namespace std;

/*
======================================================================
PROBLEM: Reverse Prefix of Word (LeetCode 2000)
======================================================================

Given a string word and a character ch, reverse the segment of the
string from index 0 up to and including the FIRST occurrence of ch.
If ch is not found, return the original string unchanged.

Examples:
  word = "abcdefd", ch = 'd'  →  "dcbaefd"
  (reverse prefix "abcd" → "dcba", keep rest "efd")

  word = "xyxzxe", ch = 'z'  →  "zxyxxe"
  (reverse "xyz" → "zyx", keep "xxe")

  word = "abcd", ch = 'z'    →  "abcd"
  (ch not found, return original)

======================================================================
APPROACH 1: Two-Pointer Swap (O(n))
======================================================================

1. Find the first index where word[i] == ch.
2. Use two pointers: i = 0, j = idx (the found index).
3. Swap word[i] and word[j], then i++, j-- until i >= j.

======================================================================
APPROACH 2: Using STL reverse (O(n))
======================================================================

Use reverse() from <algorithm> with iterators:
  reverse(word.begin(), word.begin() + idx + 1);

======================================================================
APPROACH 3: Stack (O(n) time, O(n) space)
======================================================================

Push characters from 0 to idx onto a stack, then pop them back
to form the reversed prefix + remaining suffix.

======================================================================
COMPLEXITY (all approaches):
  Time: O(n)
  Space: O(1) for two-pointer/hybrid and reverse, O(n) for stack
*/

// ============================================================
// Approach 1: Two-Pointer Swap (Optimal)
// ============================================================
class TwoPointerSwap {
    /*
    Two pointers i (start) and j (first occurrence index).
    Swap characters and move towards each other.
    */
public:
    string reversePrefix(string word, char ch) {
        int idx = word.find(ch);
        if (idx == -1) return word;

        int i = 0, j = idx;
        while (i < j) {
            swap(word[i], word[j]);
            i++;
            j--;
        }
        return word;
    }
};

// ============================================================
// Approach 2: Using STL reverse()
// ============================================================
class StlReverse {
    /*
    reverse(begin, end) reverses the range [begin, end).
    We pass begin and begin + idx + 1 to reverse the prefix.
    */
public:
    string reversePrefix(string word, char ch) {
        int idx = word.find(ch);
        if (idx != -1) {
            reverse(word.begin(), word.begin() + idx + 1);
        }
        return word;
    }
};

// ============================================================
// Approach 3: Using Stack
// ============================================================
class StackApproach {
    /*
    1. Push characters 0..idx onto a stack.
    2. Pop them back into the string (reverses the prefix).
    3. The rest (idx+1..end) remains unchanged.
    */
public:
    string reversePrefix(string word, char ch) {
        int idx = word.find(ch);
        if (idx == -1) return word;

        stack<char> st;
        for (int i = 0; i <= idx; i++) {
            st.push(word[i]);
        }

        for (int i = 0; i <= idx; i++) {
            word[i] = st.top();
            st.pop();
        }

        return word;
    }
};

// ============================================================
// Approach 4: Built-in find + manual swap (Hybrid)
// ============================================================
class HybridApproach {
    /*
    1. Find idx of ch using word.find().
    2. Run a loop from 0 to idx/2 and swap symmetric positions.
    */
public:
    string reversePrefix(string word, char ch) {
        int idx = word.find(ch);
        if (idx == -1) return word;

        for (int i = 0; i < (idx + 1) / 2; i++) {
            swap(word[i], word[idx - i]);
        }
        return word;
    }
};

int main() {
    string word = "abdefdab";
    char ch = 'd';

    TwoPointerSwap sol1;
    cout << "Two Pointer Swap:  " << sol1.reversePrefix(word, ch) << endl;

    StlReverse sol2;
    cout << "STL reverse:      " << sol2.reversePrefix(word, ch) << endl;

    StackApproach sol3;
    cout << "Stack:            " << sol3.reversePrefix(word, ch) << endl;

    HybridApproach sol4;
    cout << "Hybrid (for-loop):" << sol4.reversePrefix(word, ch) << endl;

    return 0;
}