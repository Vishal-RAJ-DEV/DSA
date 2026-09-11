/*
 ============================================================================
 Problem: Encode and Decode Strings (LeetCode 535 / LintCode 659)
 ============================================================================

 Description:
   Design an algorithm to encode a list of strings into a single string,
   and then decode that single string back into the original list of strings.

 Why is this problem tricky?
   - Strings themselves can contain ANY character, including delimiters like
     commas, spaces, pipes, etc.
   - If we simply join strings with a comma: "Hello,World" → works fine.
     But what if a string CONTAINS a comma? e.g. {"Hel,lo", "World"}
     Joining gives: "Hel,lo,World" → on decode, we can't tell where one
     string ends and the next begins.
   - So we need a DELIMITER-FREE approach that guarantees unambiguous decoding.

 ============================================================================
 Approach: Length-Prefix Encoding with '#' Delimiter
 ============================================================================

 Key Idea:
   For each string, encode it as: [length][#][actual string]

   - length: the number of characters in the string (as a number)
   - #     : a fixed separator character (never appears in the length)
   - string: the actual content

 Why this works:
   - The '#' character acts as a marker that tells us: "the number before
     this '#' is the length of the next string"
   - Since we KNOW the exact length, we can extract exactly that many
     characters from the encoded string — no ambiguity!
   - '#' will NOT appear in the length part because length is purely numeric.

 ============================================================================
 Walkthrough Example: {"Hello", "World"}
 ============================================================================

 ENCODING:
   "Hello" → length = 5 → encode as: "5#Hello"
   "World" → length = 5 → encode as: "5#World"
   Combined: "5#Hello5#World"

 DECODING (parsing "5#Hello5#World"):
   Step 1: i=0, read digits until '#' → len=5, skip '#'
           Extract 5 chars from position 1: "Hello"
           i moves to 6

   Step 2: i=6, read digits until '#' → len=5, skip '#'
           Extract 5 chars from position 7: "World"
           i moves to 12 → end of string

   Result: {"Hello", "World"} ✓

 ============================================================================
 Another Example: {"Hi", "There", "!"}
 ============================================================================

   "Hi"    → length=2 → "2#Hi"
   "There" → length=5 → "5#There"
   "!"     → length=1 → "1#!"

   Encoded: "2#Hi5#There1#!"

   Decoding: reads 2→"Hi", reads 5→"There", reads 1→"!"  ✓

 ============================================================================
 Algorithm
 ============================================================================

 ENCODE(vector<string>& s):
   1. Initialize an empty string "encoded"
   2. For each string str in s:
      a. Append the LENGTH of str as a number
      b. Append '#' as a delimiter
      c. Append the actual string str
   3. Return the encoded string

 DECODE(string& s):
   1. Initialize index i = 0 and result vector
   2. While i < length of encoded string:
      a. Read consecutive digits before '#' → this gives us "len"
      b. Skip the '#' character
      c. Extract 'len' characters from current position → this is the original string
      d. Push extracted string to result
      e. Move index i forward by 'len'
   3. Return result vector

 ============================================================================
 Complexity Analysis
 ============================================================================

 Time Complexity:
   - Encode:  O(N) where N = total characters across all strings
              (we visit each character exactly once)
   - Decode:  O(N) where N = length of encoded string
              (we visit each character exactly once)

 Space Complexity:
   - Encode:  O(N) for the encoded string
   - Decode:  O(N) for storing the result strings + original strings

 ============================================================================
*/

#include <iostream>
#include<vector>
using namespace std;

// Encodes the array of strings into a single string
// Format per string: [length][#][actual string]
// Example: "Hello" → "5#Hello"
string encode(vector<string>& s) {
    string encoded;

    for (string &str : s) {
        encoded += to_string(str.length()); // store length as string
        encoded += '#';                     // fixed separator (not in digits)
        encoded += str;                     // actual string content
    }

    return encoded;
}

// Decodes the encoded string back into the array of strings
// Reads length → skips '#' → extracts that many characters → repeat
// Example: "5#Hello5#World" → {"Hello", "World"}
vector<string> decode(string& s) {
    vector<string> result;
    int i = 0;
    int n = s.length();

    while (i < n) {
        int len = 0;

        // Extract the length: read digits until we hit '#'
        // e.g., "5#..." → len becomes 5
        while (s[i] != '#') {
            len = len * 10 + (s[i] - '0'); // convert char digit to int
            i++;
        }

        i++; // skip the '#' delimiter

        // Extract exactly 'len' characters starting from position i
        // This is the original string that was encoded
        string temp = s.substr(i, len);
        result.push_back(temp);

        i += len; // move past the extracted string
    }

    return result;
}

int main() {
    vector<string> s = {"Hello", "World"};

    string encoded = encode(s);
    // encoded = "5#Hello5#World"

    vector<string> decoded = decode(encoded);
    // decoded = {"Hello", "World"}

    for (int i = 0; i < decoded.size(); i++) {
        cout << decoded[i];
        if (i + 1 < decoded.size()) cout << " ";
    }
    // Output: Hello World

    return 0;
}
