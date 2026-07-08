#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canBeValid(string s, string locked) {
        /*
        INTUITION:
        We have a string of '(' and ')' where some positions are "locked" (can't change)
        and others are "unlocked" (locked[i] == '0'), which we can freely set to '(' or ')'.
        Unlocked positions act as wildcards — we can decide their value later.

        The core insight is a TWO-PASS GREEDY approach:

        LEFT-TO-RIGHT PASS:
        - Treat every unlocked char as '(' (increase balance).
        - Fixed '(' increases balance, fixed ')' decreases it.
        - If balance ever goes negative, we have too many ')' — impossible.
        - This checks: "Can we assign wildcards so that no prefix has more ')' than '('?"
          Every wildcard used as '(' to keep balance from going negative.

        RIGHT-TO-LEFT PASS:
        - Treat every unlocked char as ')' (increase balance).
        - Fixed ')' increases balance, fixed '(' decreases it.
        - If balance ever goes negative, we have too many '(' — impossible.
        - This checks: "Can we assign wildcards so that no suffix has more '(' than ')'?"
          Every wildcard used as ')' to keep balance from going negative.

        WHY BOTH PASSES ARE NEEDED:
        - The left pass ensures we never have a prefix with excess ')' (we supply '(' from wildcards).
        - The right pass ensures we never have a suffix with excess '(' (we supply ')' from wildcards).
        - Together they guarantee a valid assignment exists for the ENTIRE string.

        VISUAL EXAMPLE:
        s =       " ) ( ) ( ) ( 0 0 0 0 0 0 )"
        locked =  " 1 1 1 1 1 1 0 0 0 0 0 0 1"
        n = 13 (odd) → return false immediately (odd length can never be valid).

        s =       " ) ( ) ( 0 0 0 0 ) ("
        locked =  " 1 1 1 1 0 0 0 0 1 1"
        n = 10 (even).

        Left→Right:
        i=0: ')' fixed → balance=-1 → negative → return false.
        Indeed the first char is locked ')', so impossible.

        s =       " ( ) 0 0 0 0 ) ( ) ("
        locked =  " 1 1 0 0 0 0 1 1 1 1"

        Left→Right (wildcards = '('):
        i=0: '(' fixed → bal=1
        i=1: ')' fixed → bal=0
        i=2: '0'→'('  → bal=1
        i=3: '0'→'('  → bal=2
        i=4: '0'→'('  → bal=3
        i=5: '0'→'('  → bal=4
        i=6: ')' fixed → bal=3
        i=7: '(' fixed → bal=4
        i=8: ')' fixed → bal=3
        i=9: '(' fixed → bal=4
        Never negative → OK.

        Right→Left (wildcards = ')'):
        i=9: '(' fixed → bal=-1 → negative → return false.
        Why? The suffix starting at i=9 has '(' with no matching ')' after it;
        wildcards before it can't help because we're going backwards and
        treating them as ')'.

        So both directions must pass. One direction alone is NOT sufficient.
        The left pass alone could "over-correct" by using too many wildcards
        as '(' in the left portion, leaving insufficient wildcards to match
        those '(' on the right side. The right pass catches this.
        */

        if( s.size() % 2 != 0)return false;
        int balance = 0;

        // LEFT-TO-RIGHT: treat unlocked as '('
        // Ensures no prefix has more ')' than '('
        for(int i = 0 ;  i < s.size() ; i++){
            if( s[i] == '(' || locked[i] == '0')balance++;
            else balance--;

            if( balance < 0) return false;
        }

        balance = 0 ;
        // RIGHT-TO-LEFT: treat unlocked as ')'
        // Ensures no suffix has more '(' than ')'
        for( int i = s.size() - 1 ; i >=0 ; i--){
            if(s[i] == ')' || locked[i] == '0')balance++;
            else balance--;

            if(balance < 0)return false ;
        }

        return true;
    }
};


int main(){
    Solution sol;

    // Test 1: Odd length → false
    cout << "Test 1 (odd length): "
         << sol.canBeValid(")()()(000000)", "1111110000001")
         << " (expected 0)" << endl;

    // Test 2: First char locked ')' → false
    cout << "Test 2 (first char locked ')'): "
         << sol.canBeValid(")()(0000)(", "1111000011")
         << " (expected 0)" << endl;

    // Test 3: Valid with wildcards — wildcards can become ")(" to form "()()"
    cout << "Test 3 (valid with wildcards): "
         << sol.canBeValid("()00", "1100")
         << " (expected 1)" << endl;

    // Test 4: All unlocked, even length → can always be valid
    cout << "Test 4 (all unlocked, even): "
         << sol.canBeValid("(((())))", "00000000")
         << " (expected 1)" << endl;

    // Test 5: All locked, valid string
    cout << "Test 5 (all locked, valid): "
         << sol.canBeValid("()()", "1111")
         << " (expected 1)" << endl;

    // Test 6: All locked, invalid string
    cout << "Test 6 (all locked, invalid): "
         << sol.canBeValid("())(", "1111")
         << " (expected 0)" << endl;

    // Test 7: Edge case — empty string (even, trivially valid)
    cout << "Test 7 (empty string): "
         << sol.canBeValid("", "")
         << " (expected 1)" << endl;

    // Test 8: Only wildcards
    cout << "Test 8 (only wildcards, even): "
         << sol.canBeValid("000000", "000000")
         << " (expected 1)" << endl;

    // Test 9: Leetcode example
    cout << "Test 9 (leetcode example): "
         << sol.canBeValid("))()))", "010100")
         << " (expected 1)" << endl;

    // Test 10: Single char odd → false
    cout << "Test 10 (single char, locked '('): "
         << sol.canBeValid("(", "1")
         << " (expected 0)" << endl;

    return 0;
}
