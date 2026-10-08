/*
================================================================================
  Problem : B. Did Not Go to Print
  Contest : Codeforces Round 1125 (Div. 3)  ->  contest id 2275  (07-10-26)
  Link    : https://codeforces.com/contest/2275/problem/B
  Tags    : data structures, implementation   (STACK / LIFO simulation)
================================================================================

 ----------------------------------------------------------------------------
 WHAT IS THE QUESTION ?
 ----------------------------------------------------------------------------
 There are n documents, numbered 1..n. Initially the printer memory is EMPTY.
 The friends gave n commands, the i-th command is one character of string s
 (s has length n, s[i-1] is the command for document i):

   '1'  SCAN      : document i is put INTO the memory, ON TOP of everything
                    already stored there.   (document i is NOT printed yet)
   '2'  PRINT MEM : if memory is NOT empty -> the TOPMOST stored document is
                    printed and removed from memory
                       (in this case document i itself is NOT printed!)
                    if memory IS empty     -> document i itself is printed
                       (document i IS printed)
   '3'  QUICK     : document i is printed immediately (memory is untouched)

 Task: find the INDICES of all documents that were NEVER printed,
       in increasing order, and print:
           line 1 : k  (how many documents were not printed)
           line 2 : the k indices separated by spaces
                    (if k = 0 the second line is EMPTY)

 Constraints: 1 <= t <= 1e4, 1 <= n <= 2e5, sum of n over all tests <= 2e5
               characters of s are '1', '2', '3'

 ----------------------------------------------------------------------------
 THE KEY OBSERVATION -> WHY A STACK ?
 ----------------------------------------------------------------------------
 "placed on top of everything already there"  +  "prints the topmost document"
 means the memory behaves exactly like a STACK (Last-In First-Out / LIFO).
 So we keep a stack of the indices of documents that were scanned ('1')
 but not printed yet.

 A document ends up NOT PRINTED in exactly these cases:

  (A) It was scanned with '1' and was NEVER popped by a later '2'
      -> it is still sitting in memory at the end  -> NOT printed.
         (these are the indices left inside `st` after the scan)

  (B) Its own command was '2' WHILE the memory was non-empty.
      Because in that situation the printer printed the top stored document
      instead of document i  -> document i is NOT printed.
      (these are the positions i where we successfully pop -> arr[i] = 1)

  Documents that ARE printed (so they must NOT appear in the answer):
      - every document scanned by '1' that a later '2' popped out,
      - every document whose command was '2' on an EMPTY memory
        (then the device prints document i itself),
      - every document whose command was '3' (quick print).

  => That is why the code only needs to handle '1' and '2':
     a '3' never enters memory and always prints itself, so it can never
     be part of the answer and it must not touch the stack at all.
     The `else if(ch == '2')` chain simply ignores '3' (and any other char).

 ----------------------------------------------------------------------------
 HOW THE LOGIC FOLLOWS (one left-to-right pass)
 ----------------------------------------------------------------------------
     arr[i] = 1   means   "document i was NOT printed"   (0 = printed)
     st            = stack of document numbers scanned by '1' and still
                     waiting in memory (top of stack = most recent scan)

     for every position i = 1..n (1-based document numbers):
         s[i-1] == '1' : push i into st          (doc i goes INTO memory)
         s[i-1] == '2' : if st is not empty  -> the printer takes the TOPMOST
                         stored document: pop it (that document IS printed),
                         and document i itself is not printed -> arr[i] = 1
                         if st is empty      -> document i prints itself,
                         it IS printed -> nothing is marked
         s[i-1] == '3' : ignored -> document i printed, memory unchanged

     after the loop: everything still inside st was scanned but never printed
                     -> mark those indices too (case A above)

     finally collect all i with arr[i] == 1 (already in increasing order,
     because we walk 1..n) and print the count + the list.

 WORKED EXAMPLE  (sample 4: n = 6, s = "112332")
     i=1 '1' -> push 1              st = [1]
     i=2 '1' -> push 2              st = [1,2]
     i=3 '2' -> pop 2 (doc2 printed), arr[3] = 1 (doc3 not printed), st = [1]
     i=4 '3' -> nothing             st = [1]      (doc4 printed by quick print)
     i=5 '3' -> nothing             st = [1]      (doc5 printed by quick print)
     i=6 '2' -> pop 1 (doc1 printed), arr[6] = 1 (doc6 not printed), st = []
     leftovers in st: none
     answer = {3, 6}  ->  prints "2" then "3 6"   (matches the sample)

 WHY THE GREEDY "TOPMOST" IS EXACTLY RIGHT:
     the printer always removes the TOPMOST (= latest scanned) document, so
     LIFO pop order is not an optimisation choice - it is the real behaviour
     of the device. Using anything other than a stack would simulate a
     different machine and give a wrong set of unprinted documents.

 COMPLEXITY:  each character is pushed/popped at most once
     Time  : O(n) per test case, O(total n) = O(2e5) overall
     Memory: O(n) for the stack + O(n) for arr/ans
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;              // number of documents = length of the command string
    string s;           // s[i-1] = command for document i  (chars '1','2','3')
    cin>>n>>s;

    // arr[i] = 1  ->  document i was NOT printed (0 -> printed). Size n+1 so we
    // can use 1-based document numbers directly (index 0 is never used).
    vector<int>arr(n + 1, 0);
    // stack of documents scanned by '1' that are still inside the printer
    // memory (top of the stack = the topmost / most recently scanned one)
    vector<int>st;

    // single left-to-right pass over all n commands
    for(int i = 1; i <= n ; i++){
        char ch = s[i-1];                 // command of document i (0-based string)

        if( ch == '1'){
            // SCAN: document i is placed on top of the memory, not printed yet
            st.push_back(i);
        }
        else if(ch == '2'){
            // PRINT FROM MEMORY:
            if(!st.empty()){
                // memory non-empty -> the TOPMOST stored document is printed
                // and removed: pop it (that document IS printed, so it must
                // NOT be marked), while document i itself stays unprinted.
                st.pop_back();
                arr[i] = 1;               // document i was not printed
            }
            // memory empty -> the device prints document i itself:
            // nothing to mark (document i is printed) and the stack stays empty.
        }
        // ch == '3' (quick print): document i is printed immediately and the
        // memory is untouched -> falls through, correctly marks nothing.

        // any character other than '1'/'2'/'3' can never occur (statement).
    }

    // Documents scanned by '1' that were never popped by a later '2' are
    // still in memory at the end -> they were never printed (case A).
    for(int x: st){
        arr[x] = 1;
    }

    // Gather every unprinted document. The loop goes 1 -> n, so `ans` is
    // automatically in increasing order, as the output requires.
    vector<int>ans;
    for(int i = 1; i <= n ; i++){
        if(arr[i]){
            ans.push_back(i);
        }
    }

    // Output format: first line = k, second line = the k indices (space
    // separated). If k = 0 the second line is empty (just endl).
    cout<<ans.size()<<endl;
    for(int j = 0 ; j < ans.size() ; j++){
        if(j)cout<< " ";                  // no leading space before the first index
        cout<<ans[j];
    }

    cout<<endl;
}

int main() {
    int t;
    cin >> t;                             // number of test cases

    while (t--) {
        solve();
    }

    return 0;
}
