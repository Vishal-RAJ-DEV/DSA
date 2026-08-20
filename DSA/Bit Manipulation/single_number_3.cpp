/*
================================================================================================
                    SINGLE NUMBER III - FULL EXPLANATION
================================================================================================

QUESTION:
---------
Given an integer array nums, where EXACTLY TWO elements appear only once
and all other elements appear EXACTLY TWICE, find the two unique elements.

Return the two unique elements in any order.

EXAMPLES:
---------
  Example 1: nums = [1, 2, 1, 3, 2, 5]
    Unique elements: 3 and 5
    Answer: [3, 5]

  Example 2: nums = [-1, 0]
    Unique elements: -1 and 0
    Answer: [-1, 0]

  Example 3: nums = [1, 2]
    Both are unique (no duplicates)
    Answer: [1, 2]

------------------------------------------------------------------------------------------------

THE ALGORITHM (3 Steps):
-------------------------

  STEP 1: XOR all numbers
    - All numbers that appear twice cancel out (a ^ a = 0)
    - Result = a ^ b (XOR of the two unique numbers)
    - We don't know a and b yet, but we know their XOR

  STEP 2: Find the rightmost set bit in (a ^ b)
    - Since a != b, a ^ b has at least one bit set to 1
    - xorAll & (-xorAll) isolates the RIGHTMOST set bit
    - This bit tells us ONE position where a and b DIFFER
    - IMPORTANT: Use unsigned int to avoid overflow with INT_MIN!

  STEP 3: Divide numbers into two groups using that bit
    - Group 1: numbers where that bit is SET -> XOR them to get one unique number
    - Group 2: numbers where that bit is CLEAR -> XOR them to get the other

WHY THIS WORKS:
  - Numbers that appear twice always end up in the SAME group
    (they have the same bit at that position)
  - So they cancel out within their group
  - The two unique numbers end up in DIFFERENT groups
    (they differ at that bit position)
  - XOR of each group = the unique number in that group

------------------------------------------------------------------------------------------------

THE OVERFLOW BUG FIX:
  Line 17: int bit = xorAll & (-xorAll);

  PROBLEM: When xorAll = -2147483648 (INT_MIN = 1000...000 in binary),
           -xorAll would be +2147483648 which CANNOT fit in a 32-bit signed int.
           This causes UNDEFINED BEHAVIOR.

  FIX: Use unsigned int for the negation:
           int bit = xorAll & (-(unsigned int)xorAll);

  WHY: unsigned int can hold 2147483648 (range 0 to 4294967295)
       The bitwise AND still extracts the rightmost set bit correctly.

  Alternative fix: int bit = xorAll & (~xorAll + 1);
                   (two's complement: -x = ~x + 1, same thing)

================================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {

        int xorAll = 0;

        // STEP 1: XOR all numbers together
        //
        // Key property of XOR:
        //   - a ^ a = 0      (same numbers cancel)
        //   - a ^ 0 = a      (XOR with 0 gives the number)
        //   - XOR is commutative and associative
        //
        // So all numbers appearing twice cancel to 0.
        // Result = (unique1) ^ (unique2)
        //
        // Example: [1, 2, 1, 3, 2, 5]
        //   1^2^1^3^2^5 = (1^1)^(2^2)^3^5 = 0^0^3^5 = 3^5 = 6 (110 in binary)
        for (int num : nums) {
            xorAll ^= num;
        }

        // STEP 2: Find the rightmost set bit in xorAll
        //
        // xorAll = a ^ b, where a and b are the two unique numbers.
        // Since a != b, xorAll has at least one bit set to 1.
        //
        // xorAll & (-xorAll) isolates the RIGHTMOST set bit.
        //
        // HOW IT WORKS:
        //   - In two's complement, -x = (~x + 1)
        //   - This flips all bits and adds 1
        //   - Result: only the rightmost set bit survives in the AND
        //
        // Example: xorAll = 6 (binary: 110)
        //   -xorAll in unsigned = ...11111010 (two's complement of 6)
        //   110 & ...11111010 = 010 = 2
        //   Rightmost set bit of 6 is bit 1 (value 2)
        //
        // WHY unsigned int:
        //   - If xorAll = -2147483648 (INT_MIN = 1000...000)
        //   - Negating it as signed int OVERFLOWS (can't represent +2147483648)
        //   - unsigned int can hold it: range 0 to 4294967295
        //   - The AND operation works correctly either way
        int bit = xorAll & (-(unsigned int)xorAll);

        int x = 0;
        int y = 0;

        // STEP 3: Divide all numbers into two groups based on that bit
        //
        // Group 1: numbers where 'bit' is SET (1)  -> XOR into x
        // Group 2: numbers where 'bit' is CLEAR (0) -> XOR into y
        //
        // WHY this separates the two unique numbers:
        //   - unique1 and unique2 DIFFER at this bit position (by definition)
        //   - So one goes to Group 1, the other to Group 2
        //
        // WHY duplicates cancel out:
        //   - Any number appearing twice has the SAME bit at this position
        //   - Both copies go to the SAME group
        //   - They XOR to 0 within that group
        //
        // Example: [1, 2, 1, 3, 2, 5], xorAll=6 (110), bit=2 (010)
        //   Group 1 (bit 1 is SET):   2, 2       -> 2^2 = 0
        //   Group 2 (bit 1 is CLEAR): 1, 1, 3, 5 -> 1^1^3^5 = 0^3^5 = 6
        //   Wait, that gives x=0, y=6... let me recheck.
        //   Actually: bit=2 means bit position 1 (the 2's place)
        //   2 = 010 -> bit 1 is SET -> Group 1
        //   1 = 001 -> bit 1 is CLEAR -> Group 2
        //   3 = 011 -> bit 1 is SET -> Group 1
        //   5 = 101 -> bit 1 is CLEAR -> Group 2
        //   Group 1: 2^2^3 = 0^3 = 3  (unique: 3)
        //   Group 2: 1^1^5 = 0^5 = 5  (unique: 5)
        //   Answer: [3, 5] ✓
        for (int num : nums) {

            if (num & bit)
                x ^= num;   // Group 1: bit is SET
            else
                y ^= num;   // Group 2: bit is CLEAR
        }

        // x and y now hold the two unique numbers
        return {x, y};
    }
};



int main(){
    Solution sol;

    // Test 1: [1, 2, 1, 3, 2, 5] -> unique: 3, 5
    vector<int> nums1 = {1, 2, 1, 3, 2, 5};
    vector<int> result1 = sol.singleNumber(nums1);
    cout << "Test 1: [" << result1[0] << ", " << result1[1] << "]" << endl;

    // Test 2: [-1, 0] -> unique: -1, 0
    vector<int> nums2 = {-1, 0};
    vector<int> result2 = sol.singleNumber(nums2);
    cout << "Test 2: [" << result2[0] << ", " << result2[1] << "]" << endl;

    // Test 3: [1, 2] -> unique: 1, 2
    vector<int> nums3 = {1, 2};
    vector<int> result3 = sol.singleNumber(nums3);
    cout << "Test 3: [" << result3[0] << ", " << result3[1] << "]" << endl;

    // Test 4: INT_MIN edge case (the bug we fixed)
    vector<int> nums4 = {-2147483648, 1, -2147483648, 2};
    vector<int> result4 = sol.singleNumber(nums4);
    cout << "Test 4: [" << result4[0] << ", " << result4[1] << "]" << endl;

    return 0;
}