#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t; // Read the number of test cases
    while (t--)
    {
        int n;
        cin >> n; // Read the number of cells in the current test case
        string s;
        cin >> s; // Read the string representing the row of cells
        
        // Initialize a flag to check for three continuous empty cells
        bool continuous_three_empty_cells = false;
        // Initialize a counter for the total number of empty cells
        int total_count_of_empty_cells = 0;

        // Iterate through the cells
        for (int i = 0; i < n; i++) // Loop through each cell
        {
            // Check if there are three continuous empty cells
            if (s[i] == '.' && i + 1 < n && s[i + 1] == '.' && i + 2 < n && s[i + 2] == '.')
            {
                continuous_three_empty_cells = true; // Set the flag to true if found
                break; // No need to check further if we found three continuous empty cells
            }
            // Count the number of empty cells
            if (s[i] == '.')
                total_count_of_empty_cells++;
        }

        // If there are three continuous empty cells, only 2 actions are needed
        if (continuous_three_empty_cells)
            cout << 2 << endl;
        else
            // Otherwise, the number of actions needed is equal to the number of empty cells
            cout << total_count_of_empty_cells << endl;
    }
    return 0;
}

// Time Complexity (TC): O(n) = O(100)
// Space Complexity (SC): O(n) = O(100)

/*
================================================================
QUESTION (Codeforces 1900A - "Cover in Water"):

We have a row of n cells. Some cells are blocked ('#'), some are
empty ('.'). We want all empty cells to have water. We have two
types of actions:
  1. Place water in an empty cell. (costs 1, counted)
  2. Move water from any water-filled cell to any empty cell.
     (costs 0, unlimited, not counted)

Special automatic rule: If a cell i (2 <= i <= n-1) is empty and
BOTH cells i-1 and i+1 contain water, then cell i automatically
becomes filled with water (for free).

Find the MINIMUM number of type-1 actions needed so that every
empty cell eventually has water.

================================================================
INTUITION:

The key insight is the "infinite water generator" created by
3 consecutive empty cells.

If we have a pattern like:  #  .  .  .  #
                           i-1 i  i+1

Step 1: Place water at i-1 and i+1 (2 type-1 actions).
        #  W  .  W  #

Step 2: Cell i is empty, and both i-1 and i+1 have water.
        By the automatic rule, cell i auto-fills for free.
        #  W  W  W  #
            ↑ auto-filled

Step 3: Use a type-2 action (free) to MOVE water from cell i
        to any other empty cell in the row.
        #  W  .  W  #     (water at i moved elsewhere)

Step 4: Cell i is empty again, but both i-1 and i+1 STILL have
        water → cell i auto-fills AGAIN!
        #  W  W  W  #

This loop (fill → move → auto-refill → move again) creates an
INFINITE water source at the middle cell. Since type-2 actions
cost nothing, we can use this to fill EVERY empty cell in the
entire row with just 2 type-1 actions.

Thus:  If ANY 3 consecutive empty cells exist → answer = 2.

If no such triple exists, then every contiguous empty segment
has length at most 2. No infinite regeneration is possible:
  - A single '.' needs 1 pour (no neighbor has water on both sides)
  - Two consecutive '.' need 2 pours (neither cell gets auto-filled)
So the answer is simply the TOTAL COUNT of empty cells.

================================================================
ALGORITHM:

1. For each test case, read n (size) and string s (row).
2. Initialize:
   - continuous_three_empty_cells = false  (flag for finding "...")
   - total_count_of_empty_cells = 0        (counter for '.' chars)

3. Iterate i from 0 to n-1:
   a) FIRST check if s[i], s[i+1], s[i+2] are all '.' (triple found).
      If yes: set flag = true and BREAK (no need to continue).
   b) If no triple at i, then count s[i] if it is '.'.

   NOTE: The triple check comes BEFORE the count increment for
   s[i]. This ensures that if s[i] starts a triple, we break
   immediately and don't waste time counting further.

4. If flag is true → print 2
   Else → print total_count_of_empty_cells

================================================================
WHY THE CHECK ORDER MATTERS (subtle detail):

The code checks for triple BEFORE counting s[i]. This means:
- If s[i] == '.' but s[i+1] != '.' (not a triple), then s[i]
  gets counted normally.
- If s[i] == '.', s[i+1] == '.', but s[i+2] != '.' (only a
  double), then s[i] is counted. On the NEXT iteration (i+1),
  s[i+1] is also checked and counted similarly.
- If a triple IS found, we break immediately. The count variable
  only contains dots before the triple, but we don't use it since
  we print 2.

================================================================
EXAMPLE WALKTHROUGH:

Test case 1: s = "#...#..."  (n=7)
  i=0: s[0]='#', no triple, not counted.
  i=1: s[1]='.', s[2]='.', s[3]='.' → triple found! flag=true, break.
  Output: 2
  (The triple at positions 1-3 acts as infinite water source to
   fill position 4 too)

Test case 2: s = "#.#.#"  (n=5)
  i=0: '#', not counted.
  i=1: '.', s[2]='#', s[3]='.' → not a triple. Counted: cnt=1.
  i=2: '#', not counted.
  i=3: '.', s[4]='#', i+2>=n → no triple check. Counted: cnt=2.
  i=4: '#', not counted.
  No triple found. Output: 2 (total empty cells)

Test case 3: s = ".##."  (n=4)
  i=0: '.', s[1]='#', no triple. Counted: cnt=1.
  i=1: '#', not counted.
  i=2: '#', not counted.
  i=3: '.', i+2>=n → no triple check. Counted: cnt=2.
  No triple found. Output: 2.

================================================================
TIME & SPACE COMPLEXITY:
  Time: O(n) per test case — single pass through the string.
  Space: O(n) — storing the input string.
================================================================
*/