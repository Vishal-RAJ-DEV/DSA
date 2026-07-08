#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    ========================================================================
    QUESTION (LeetCode 2454 — Next Greater Element IV / Second Greater Element)
    ========================================================================
    Given an array nums, for each element nums[i], find the NEXT GREATER
    element that is GREATER than nums[i] AND appears AFTER its own next
    greater element. In other words, find the SECOND greater element to
    the right of nums[i].

    More formally:
    - The "first greater" of nums[i] = nums[j] where j > i, nums[j] > nums[i],
      and j is the smallest such index.
    - The "second greater" of nums[i] = nums[k] where k > j, nums[k] > nums[i],
      and k is the smallest such index (i.e., the next greater AFTER the
      first greater).
    - If no second greater exists, answer = -1.

    Example:
    nums = [2, 4, 0, 9, 6]
    i=0 (2): first greater = 4 (i=1), second greater = 9 (i=3) → ans=9
    i=1 (4): first greater = 9 (i=3), second greater = 6... no, 6<4, so -1 → ans=-1
              Actually wait: 9 > 4 at i=3, then after i=3 we have 6 at i=4 which is
              not > 4. So no second greater → ans=-1
    i=2 (0): first greater = 9 (i=3), second greater = 6 (i=4, 6>0) → ans=6
    i=3 (9): no greater to the right → ans=-1
    i=4 (6): no greater to the right → ans=-1
    Result: [9, -1, 6, -1, -1]

    ========================================================================
    INTUITION — Why Two Stacks?
    ========================================================================
    Each element goes through a TWO-STAGE pipeline:

           Current Element
                 │
                 ▼
          ┌──────────────┐
          │   st1         │  ← waiting for 1st greater
          │ (Monotonic)   │
          └──────────────┘
                 │
                 ▼      Found 1st greater → move to st2
          ┌──────────────┐
          │   st2         │  ← waiting for 2nd greater
          │ (Monotonic)   │
          └──────────────┘
                 │
                 ▼      Found 2nd greater → answer assigned
               DONE

    A SINGLE stack can only track ONE stage at a time.
    We need TWO stacks because we're tracking TWO different "waiting" stages:
      - st1: indices waiting for their FIRST greater element
      - st2: indices that FOUND their first greater and now wait for their SECOND

    Both stacks maintain MONOTONIC DECREASING order (bottom → top):
    nums[stack.top()] is the SMALLEST among elements in that stack.
    This means when we encounter a new nums[i], it immediately qualifies
    as the "greater" for everyone at the top of the stack whose value
    is smaller than nums[i].

    ========================================================================
    ALGORITHM (Left → Right Traversal)
    ========================================================================
    For each nums[i]:

    STEP 1 — Resolve st2 (second greater found)
        While nums[i] > nums[st2.top()]:
            → nums[i] is the SECOND GREATER for st2.top()
            → ans[st2.top()] = nums[i]
            → pop from st2

    STEP 2 — Find first greater (move st1 → temp)
        While nums[i] > nums[st1.top()]:
            → nums[i] is the FIRST GREATER for st1.top()
            → pop from st1 and push into temp (a temporary stack)

    STEP 3 — Move temp → st2 (preserve relative order)
        While temp is not empty:
            → pop from temp and push into st2
        Why use temp? Without temp, if we pushed directly from st1 to st2,
        the order would reverse (since st1 pops in decreasing order of
        index). The temp stack reverses it back, so elements enter st2
        in the SAME relative order they had in st1 (increasing index).
        This is critical: earlier elements should get their second greater
        before later ones.

    STEP 4 — Push current index into st1
        Every element starts in st1, waiting for its first greater.

    ========================================================================
    VISUAL TRACE
    ========================================================================
    nums = [2, 4, 0, 9, 6]

    i=0 (val=2):
      st2=[]  → nothing to resolve
      st1=[]  → nothing to move
      st1.push(0) → st1=[0]

    i=1 (val=4):
      st2=[]                    → nothing to resolve
      st1 top=2, 4>2            → pop 0 from st1, push to temp
      temp=[0], st1=[]
      temp→st2                  → st2=[0]
      st1.push(1)               → st1=[1]

    i=2 (val=0):
      st2 top=2, 0>2? NO       → nothing to resolve
      st1 top=4, 0>4? NO       → nothing to move
      st1.push(2)               → st1=[1,2]   (4,0 in monotonic decreasing: 4>0)

    i=3 (val=9):
      st2 top=2, 9>2            → ans[0]=9, pop → st2=[]
      st1 top=2 (val=0), 9>0    → pop 2 from st1 → temp=[2]
      st1 top=1 (val=4), 9>4    → pop 1 from st1 → temp=[2,1]
      st1=[]
      temp→st2                  → st2=[1,2]   (indices 1 then 2 — correct order)
      st1.push(3)               → st1=[3]

    i=4 (val=6):
      st2 top=2 (val=0), 6>0    → ans[2]=6, pop → st2=[1]
      st2 top=1 (val=4), 6>4    → ans[1]=6, pop → st2=[]
      st1 top=3 (val=9), 6>9? NO→ nothing to move
      st1.push(4)               → st1=[3,4]

    ans = [9, 6, 6, -1, -1]... wait, that's wrong for i=1!
    Let me re-check:

    Actually ans[1] should be -1 because after first greater (9 at i=3),
    there is no element > 4 after i=3. But my trace says ans[1]=6.

    Let me re-trace carefully:
    
    After i=3 processing, st2 = [1,2] where 1 has value 4, 2 has value 0.
    
    i=4 (val=6):
      st2 top = 2 (val=0). 6 > 0 → ans[2]=6. Pop → st2=[1]
      st2 top = 1 (val=4). 6 > 4 → ans[1]=6. Pop → st2=[]
      
    But ans[1] should be -1 because 6's first greater (9) is at i=3,
    and after i=3 there's no element > 4. But 6 itself is NOT after
    the first greater of 4 — wait, let me re-read the problem.

    "Second greater" = the next greater after the FIRST greater.
    For nums[1]=4: first greater is 9 at i=3. After i=3, we have nums[4]=6.
    6 is > 4, and it appears after the first greater (9 at i=3).
    So 6 IS the second greater of 4!

    Oh right! So ans[1]=6 is correct. My earlier manual analysis was wrong.

    So result = [9, 6, 6, -1, -1]

    Let me verify: ans[0]=9, ans[1]=6, ans[2]=6, ans[3]=-1, ans[4]=-1.
    This matches the algorithm's output. ✓

    ========================================================================
    COMPLEXITY
    ========================================================================
    Time: O(n) — each index pushed/popped at most once from each stack.
    Space: O(n) — two stacks + answer array.

    ========================================================================
    MEMORY TRICK
    ========================================================================
    st1 = "Waiting for the 1st Greater"
    st2 = "Waiting for the 2nd Greater"
    Every element follows: st1 → (found 1st) → st2 → (found 2nd) → answer
    */

    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();

        // st1 stores indices of elements waiting to find their FIRST greater
        // Maintains monotonic decreasing order (top = smallest value)
        stack<int> st1;

        // st2 stores indices of elements that have found their FIRST greater
        // and are now waiting to find their SECOND greater
        // Also maintains monotonic decreasing order
        stack<int> st2;

        // Default -1 means no second greater exists
        vector<int> ans(n, -1);

        // Left-to-right traversal
        for (int i = 0; i < n; i++) {

            // ─────────────────────────────────────────────────────────
            // STEP 1: Resolve SECOND greater for elements in st2
            // ─────────────────────────────────────────────────────────
            // nums[i] qualifies as the "next greater" for everyone in st2
            // whose value is smaller than nums[i]. Since st2 is monotonic
            // decreasing (top is smallest), we check the top repeatedly.
            while (!st2.empty() && nums[i] > nums[st2.top()]) {
                // nums[i] is the SECOND GREATER element for st2.top()
                ans[st2.top()] = nums[i];
                // This element has found both its greater elements → remove it
                st2.pop();
            }

            // ─────────────────────────────────────────────────────────
            // STEP 2: Find FIRST greater for elements in st1
            // ─────────────────────────────────────────────────────────
            // nums[i] qualifies as the "first greater" for everyone in st1
            // whose value is smaller than nums[i].
            // We pop them from st1 and collect in a temp stack.
            stack<int> temp;
            while (!st1.empty() && nums[i] > nums[st1.top()]) {
                temp.push(st1.top());
                st1.pop();
            }

            // ─────────────────────────────────────────────────────────
            // STEP 3: Move temp → st2 (preserving original order)
            // ─────────────────────────────────────────────────────────
            // Without temp, elements would enter st2 in reverse order
            // (since st1 pops in decreasing index order — latest first).
            // The temp stack reverses that reversal, so elements are
            // pushed into st2 in INCREASING index order (same as they
            // were in st1). This ensures earlier elements get their
            // second greater before later ones.
            while (!temp.empty()) {
                st2.push(temp.top());
                temp.pop();
            }

            // ─────────────────────────────────────────────────────────
            // STEP 4: Push current index into st1
            // ─────────────────────────────────────────────────────────
            // Every element starts its journey here, waiting to find
            // its first greater element to the right.
            st1.push(i);
        }

        return ans;
    }
};


int main(){
    Solution sol;

    auto print = [](const vector<int>& v) {
        cout << "[";
        for (size_t i = 0; i < v.size(); i++) {
            cout << v[i];
            if (i + 1 < v.size()) cout << ",";
        }
        cout << "]";
    };

    // Test 1: Example from comment
    vector<int> t1 = {2,4,0,9,6};
    cout << "Test 1: "; print(t1); cout << " -> ";
    print(sol.secondGreaterElement(t1));
    cout << " (expected [9,6,6,-1,-1])" << endl;

    // Test 2: Descending — no greater elements at all
    vector<int> t2 = {5,4,3,2,1};
    cout << "Test 2: "; print(t2); cout << " -> ";
    print(sol.secondGreaterElement(t2));
    cout << " (expected [-1,-1,-1,-1,-1])" << endl;

    // Test 3: Ascending — each gets the element two steps ahead
    vector<int> t3 = {1,2,3,4,5};
    cout << "Test 3: "; print(t3); cout << " -> ";
    print(sol.secondGreaterElement(t3));
    cout << " (expected [3,4,5,-1,-1])" << endl;

    // Test 4: Single element
    vector<int> t4 = {10};
    cout << "Test 4: "; print(t4); cout << " -> ";
    print(sol.secondGreaterElement(t4));
    cout << " (expected [-1])" << endl;

    // Test 5: Two elements — no second greater possible
    vector<int> t5 = {1,2};
    cout << "Test 5: "; print(t5); cout << " -> ";
    print(sol.secondGreaterElement(t5));
    cout << " (expected [-1,-1])" << endl;

    // Test 6: Duplicates — strictly greater is needed
    vector<int> t6 = {5,5,5,5};
    cout << "Test 6: "; print(t6); cout << " -> ";
    print(sol.secondGreaterElement(t6));
    cout << " (expected [-1,-1,-1,-1])" << endl;

    // Test 7: Leetcode example
    vector<int> t7 = {2,4,0,9,6};
    cout << "Test 7: "; print(t7); cout << " -> ";
    print(sol.secondGreaterElement(t7));
    cout << " (expected [9,6,6,-1,-1])" << endl;

    return 0;
}
