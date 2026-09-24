#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// PROBLEM: Restore IP Addresses
// Given a string s containing only digits, return all valid IP addresses
// that can be formed by inserting dots into s.
// A valid IP address consists of exactly four integers, each in range [0, 255],
// separated by single dots, and cannot contain leading zeros.
// Example: "25525511135" -> ["255.255.11.135", "255.255.111.35"]
// ============================================================================

class Solution {
public:

    // --------------------------------------------------------------------------
    // RECURSIVE BACKTRACKING FUNCTION
    //
    // Parameters:
    //   idx   - current index in string s (we have processed characters 0..idx-1)
    //   curr  - the IP address string being built so far (e.g. "255.255")
    //   res   - final result vector where valid IPs are stored
    //   s     - the original input string
    //   parts - number of IP segments (octets) already added to curr
    //
    // GOAL: Try all possible segment lengths (1, 2, or 3) starting at position idx,
    //       pick valid segments, and recurse. When 4 valid segments are placed and
    //       the entire string is consumed, we have a valid IP address.
    // --------------------------------------------------------------------------
    void solve(int idx, string &curr, vector<string>& res, string s, int parts) {

        // ------------------------------------------------------------------
        // BASE CASE: We have placed 4 segments (a valid IP has exactly 4 parts)
        // ------------------------------------------------------------------
        if (parts == 4) {
            // Check if we have consumed the ENTIRE input string.
            // If idx == s.size(), all characters were used -> valid IP.
            // If idx < s.size(), there are leftover digits -> invalid, so skip.
            if (idx == s.size()) {
                // We built a complete valid IP address, add it to results.
                res.push_back(curr);
                return;
            }
            // If we have 4 parts but leftover characters exist, this path is invalid.
            // Return without adding to results (backtrack).
        }

        // ------------------------------------------------------------------
        // TRY ALL POSSIBLE SEGMENT LENGTHS: 1, 2, or 3 digits
        // Each IP segment (octet) can be 1 to 3 digits long (range 0-255).
        // ------------------------------------------------------------------
        int value = 0; // Tracks the numeric value of the current segment being built

        for (int len = 1; len <= 3; len++) {

            // ----------------------------------------------------------------
            // BOUNDARY CHECK: If segment extends beyond the string, stop.
            // e.g. if idx=5 and s.size()=7, then len=3 means idx+len=8 > 7 -> stop
            // We cannot take more characters than what remain in the string.
            // ----------------------------------------------------------------
            if (idx + len > s.size()) {
                break;
            }

            // ----------------------------------------------------------------
            // LEADING ZERO CHECK: A segment like "01" or "001" is invalid.
            // If the first character of this segment is '0' and length > 1,
            // it means we are forming a number with leading zero -> invalid.
            // "0" alone (len==1) is valid, but "01", "00", "012" are not.
            // ----------------------------------------------------------------
            if (len > 1 && s[idx] == '0') {
                break;
            }

            // ----------------------------------------------------------------
            // BUILD THE NUMERIC VALUE of the current segment character by character.
            //
            // Example: s = "255", idx = 0
            //   len=1: value = 0*10 + (s[0]-'0') = 2         -> "2"
            //   len=2: value = 2*10 + (s[1]-'0') = 25        -> "25"
            //   len=3: value = 25*10 + (s[2]-'0') = 255      -> "255"
            //
            // We accumulate digit by digit to check if value exceeds 255.
            // ----------------------------------------------------------------
            value = value * 10 + ((s[idx + len - 1]) - '0');

            // ----------------------------------------------------------------
            // RANGE CHECK: Each segment must be in [0, 255].
            // If value > 255, no larger segment starting here will be valid
            // (value only increases as len increases), so return (prune the branch).
            // ----------------------------------------------------------------
            if (value > 255) return;

            // ----------------------------------------------------------------
            // ADD DOT SEPARATOR: If we already have at least one segment (parts > 0),
            // we need to place a '.' before adding the new segment.
            // Example: curr = "255", parts=1 -> curr becomes "255."
            //          curr = "", parts=0 -> no dot needed (first segment).
            // ----------------------------------------------------------------
            if (parts > 0) {
                curr += '.';
            }

            // ----------------------------------------------------------------
            // APPEND THE CURRENT SEGMENT to curr.
            // s.substr(idx, len) extracts 'len' characters starting at position idx.
            // Example: s = "25525511135", idx=0, len=3 -> substr = "255"
            //          s = "25525511135", idx=3, len=3 -> substr = "255"
            //          s = "25525511135", idx=6, len=2 -> substr = "11"
            // ----------------------------------------------------------------
            curr += s.substr(idx, len);

            // ------------------------------------------------------------------
            // RECURSE: Move to the next position in the string (idx + len)
            //          and increment parts count (we just placed one more segment).
            //
            // Example flow: s = "25525511135"
            //   Call 1: idx=0, parts=0, curr="" -> try "255" -> curr="255", parts=1
            //   Call 2: idx=3, parts=1, curr="255" -> try "255" -> curr="255.255", parts=2
            //   Call 3: idx=6, parts=2, curr="255.255" -> try "11" -> curr="255.255.11", parts=3
            //   Call 4: idx=8, parts=3, curr="255.255.11" -> try "135" -> curr="255.255.11.135", parts=4
            //   Call 5: parts==4 and idx==11==s.size() -> VALID! Add to result.
            // ------------------------------------------------------------------
            solve(idx + len, curr, res, s, parts + 1);

            // ----------------------------------------------------------------
            // BACKTRACK: Undo the addition of the current segment so we can
            // try the next segment length (len=2, len=3, etc.) in the loop.
            //
            // We need to remove:
            //   - the segment itself (len characters)
            //   - the dot before it IF parts > 0 (1 character for '.')
            //
            // So total characters to remove = len + (parts > 0 ? 1 : 0)
            //
            // Example: curr was "255.255.11", we want to try len=3 instead of len=2.
            //   len=2 was "11", dot was ".", so remove 2+1=3 chars.
            //   curr.resize(curr.size() - 3) -> curr becomes "255.255"
            //   Then we can try "111" (len=3) and curr becomes "255.255.111"
            // ----------------------------------------------------------------
            curr.resize(curr.size() - len - (parts > 0 ? 1 : 0));
        }

        // After trying all segment lengths (1, 2, 3) starting at idx,
        // if no valid IP was found, this function simply returns,
        // and the caller backtracks further up the recursion tree.
    }

    // --------------------------------------------------------------------------
    // MAIN FUNCTION: Entry point to solve the Restore IP Addresses problem.
    //
    // Initializes the recursion with:
    //   idx   = 0  (start from the beginning of the string)
    //   curr  = "" (empty IP being built)
    //   parts = 0  (no segments placed yet)
    // --------------------------------------------------------------------------
    vector<string> restoreIpAddresses(string s) {
        string curr = "";           // Accumulator string for building the IP address
        vector<string> res;         // Result vector to store all valid IP addresses
        int parts = 0;             // Counter for how many segments we have placed (0 to 4)

        // Start the recursive backtracking from index 0 with 0 parts placed.
        solve(0, curr, res, s, parts);

        return res;
    }
};

// --------------------------------------------------------------------------
// DRIVER CODE
// --------------------------------------------------------------------------
int main() {
    Solution sol;

    // Example 1: "25525511135"
    // Expected: ["255.255.11.135", "255.255.111.35"]
    string s1 = "25525511135";
    vector<string> result1 = sol.restoreIpAddresses(s1);
    cout << "Input: " << s1 << endl;
    cout << "Output: ";
    for (string ip : result1) {
        cout << ip << " ";
    }
    cout << endl << endl;

    // Example 2: "0000"
    // Expected: ["0.0.0.0"]
    string s2 = "0000";
    vector<string> result2 = sol.restoreIpAddresses(s2);
    cout << "Input: " << s2 << endl;
    cout << "Output: ";
    for (string ip : result2) {
        cout << ip << " ";
    }
    cout << endl << endl;

    // Example 3: "101023"
    // Expected: ["1.0.10.23", "1.0.102.3", "10.1.0.23", "10.10.2.3", "101.0.2.3"]
    string s3 = "101023";
    vector<string> result3 = sol.restoreIpAddresses(s3);
    cout << "Input: " << s3 << endl;
    cout << "Output: ";
    for (string ip : result3) {
        cout << ip << " ";
    }
    cout << endl;

    return 0;
}
