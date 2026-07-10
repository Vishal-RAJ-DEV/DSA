#include <bits/stdc++.h>
using namespace std;

/*
======================================================================
PROBLEM: Reverse Vowels of a String (LeetCode 345)
======================================================================

Given a string s, reverse only all the vowels in the string.
Consonants and other characters stay in their original positions.

Vowels: a, e, i, o, u (both lowercase and uppercase).

Examples:
  s = "hello"         →  "holle"
  s = "leetcode"      →  "leotcede"
  s = "aA"            →  "Aa"

======================================================================
string::npos EXPLANATION
======================================================================

  npos is a static constant defined in std::string. Its value is
  static_cast<size_t>(-1), which is the maximum possible value for
  size_t (usually 18446744073709551615 on 64-bit systems).

  It is used as a special "not found" sentinel return value for
  string methods like find(), rfind(), find_first_of(), etc.

  Pattern:
    if (str.find(ch) == string::npos) {
        // ch was NOT found in str
    }

  In this code:
    vowels.find(word[start]) == string::npos
    → "word[start] is NOT a vowel" (because it wasn't found in "aeiouAEIOU")

======================================================================
STRING METHODS USED HERE
======================================================================

  1. s.length() / s.size()
     Returns the number of characters in the string (size_t).

  2. s.find(ch)
     Searches for character ch in string s.
     Returns the index (0-based) of the first occurrence.
     Returns string::npos if ch is NOT found.

  3. swap(a, b)   (from <algorithm>)
     Swaps the values of a and b. Here used to swap two characters.

======================================================================
APPROACH 1: Two-Pointer with find()  (already implemented below)
======================================================================
  1. Set start = 0, end = n-1.
  2. Move start right until word[start] is a vowel.
  3. Move end left until word[end] is a vowel.
  4. Swap vowels, move both pointers.
  5. Repeat until start >= end.

======================================================================
APPROACH 2: Two-Pointer with unordered_set
======================================================================
  Same logic, but use an unordered_set for O(1) vowel lookup
  instead of string::find() which is O(n) per call.

======================================================================
APPROACH 3: Collect and Reverse
======================================================================
  1. Scan the string, collect all vowels in order into a vector.
  2. Reverse the vector.
  3. Scan again, replacing each vowel with the next from reversed vector.

======================================================================
APPROACH 4: Stack
======================================================================
  1. Push all vowels found onto a stack.
  2. Scan again: when a vowel is encountered, pop from stack to replace it.
*/

// ============================================================
// Approach 1: Two-Pointer with string::find() and string::npos
// ============================================================
class TwoPointerFind {
    /*
    Uses vowels.find(ch) to check if a character is a vowel.
    Returns string::npos if not found (= character is NOT a vowel).
    Otherwise returns the index (ignored, we only care if it's found).

    Time:  O(n) — each find() is O(5) = O(1) since vowels = constant length
    Space: O(1)
    */
public:
    string reverseVowels(string s) {
        int start = 0;
        int end = s.length() - 1;
        string vowels = "aeiouAEIOU";

        while (start < end) {
            // Move start inward while s[start] is NOT a vowel.
            // vowels.find() returns npos when character is NOT in the string.
            while (start < end && vowels.find(s[start]) == string::npos) {
                start++;
            }

            // Move end inward while s[end] is NOT a vowel.
            while (start < end && vowels.find(s[end]) == string::npos) {
                end--;
            }

            // Both start and end point to vowels. Swap them.
            swap(s[start], s[end]);
            start++;
            end--;
        }

        return s;
    }
};

// ============================================================
// Approach 2: Two-Pointer with unordered_set (O(1) lookup)
// ============================================================
class TwoPointerSet {
    /*
    * Uses unordered_set<char> for O(1) vowel checking.
    * Same two-pointer logic as Approach 1.
    * Slightly faster in practice due to hash-based lookup.
    */
public:
    string reverseVowels(string s) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u',
                                      'A', 'E', 'I', 'O', 'U'};
        int start = 0;
        int end = s.length() - 1;

        while (start < end) {
            // Check if s[start] is NOT in vowel set
            while (start < end && vowels.find(s[start]) == vowels.end()) {
                start++;
            }

            // Check if s[end] is NOT in vowel set
            while (start < end && vowels.find(s[end]) == vowels.end()) {
                end--;
            }

            swap(s[start], s[end]);
            start++;
            end--;
        }

        return s;
    }
};

// ============================================================
// Approach 3: Collect, Reverse, Replace
// ============================================================
class CollectAndReverse {
    /*
    * Step 1: Traverse the string and push all vowels into a vector.
    * Step 2: Reverse the vector (or use a stack).
    * Step 3: Traverse again; whenever we hit a vowel, replace it
    *          with the next vowel from the reversed vector.

    Example:
      s = "hello"
      vowels collected: {'e', 'o'}
      reversed: {'o', 'e'}
      Replace: "holle"
    */
public:
    string reverseVowels(string s) {
        vector<char> vowels;
        string vowelSet = "aeiouAEIOU";

        // Collect vowels in order
        for (char c : s) {
            if (vowelSet.find(c) != string::npos) {
                vowels.push_back(c);
            }
        }

        // Reverse the collected vowels
        reverse(vowels.begin(), vowels.end());

        // Replace vowels in original string
        int idx = 0;
        for (char &c : s) {
            if (vowelSet.find(c) != string::npos) {
                c = vowels[idx++];
            }
        }

        return s;
    }
};

// ============================================================
// Approach 4: Stack
// ============================================================
class StackApproach {
    /*
    * Push all vowels onto a stack.
    * Then traverse the string: when a vowel is encountered,
    * pop from stack and replace.

    Stack pops in LIFO order, which naturally reverses the sequence.

    Example:
      s = "hello"
      stack push: 'e' → 'o'  (stack top = 'o')
      traverse: h→skip, e→pop('o'), l→skip, l→skip, o→pop('e')
      Result: "holle"
    */
public:
    string reverseVowels(string s) {
        string vowels = "aeiouAEIOU";
        stack<char> st;

        // Push all vowels onto stack
        for (char c : s) {
            if (vowels.find(c) != string::npos) {
                st.push(c);
            }
        }

        // Pop vowels back — naturally reverses order
        for (char &c : s) {
            if (vowels.find(c) != string::npos) {
                c = st.top();
                st.pop();
            }
        }

        return s;
    }
};

// ============================================================
// Approach 5: Two-Pointer with isVowel() helper (char array)
// ============================================================
class TwoPointerHelperFunction {
    /*
    * Same two-pointer approach but using a helper function
    * instead of find() or set.
    * Useful when you want to avoid string operations entirely.
    */
    bool isVowel(char c) {
        c = tolower(c);  // convert to lowercase for single check
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

public:
    string reverseVowels(string s) {
        int start = 0;
        int end = s.length() - 1;

        while (start < end) {
            while (start < end && !isVowel(s[start])) start++;
            while (start < end && !isVowel(s[end])) end--;
            swap(s[start], s[end]);
            start++;
            end--;
        }

        return s;
    }
};

int main() {
    string input = "hello";
    cout << "Original:     " << input << endl;

    TwoPointerFind sol1;
    cout << "Two-Pointer:  " << sol1.reverseVowels(input) << endl;

    TwoPointerSet sol2;
    cout << "Set lookup:   " << sol2.reverseVowels(input) << endl;

    CollectAndReverse sol3;
    cout << "Collect+Rev:  " << sol3.reverseVowels(input) << endl;

    StackApproach sol4;
    cout << "Stack:        " << sol4.reverseVowels(input) << endl;

    TwoPointerHelperFunction sol5;
    cout << "Helper func:  " << sol5.reverseVowels(input) << endl;

    return 0;
}