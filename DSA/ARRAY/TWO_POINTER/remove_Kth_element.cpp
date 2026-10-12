#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
=============================================================================
 LOGIC OF THE CODE  ->  "Remove Element" using the TWO POINTER technique
=============================================================================

 We are given a vector `nums` and a value `val`.
 We must REMOVE every element equal to `val` from the "valid portion"
 of the array, and return the new length.

 We do NOT actually shrink the vector. Instead we overwrite the unwanted
 elements with the wanted ones, and return how many elements are valid.

 ----------------------------------------------------------------------------
 THE TWO POINTERS
 ----------------------------------------------------------------------------
 i (fast pointer) -> scans EVERY element of the original vector, one by one.
                     It always moves forward: i++ happens in the for loop.

 k (slow pointer) -> tracks the position where the NEXT valid element
                     must be written. k only moves forward when we
                     actually keep an element.

 Both start at 0. Initially k = 0 (nothing written yet).

 ----------------------------------------------------------------------------
 THE KEY CONDITION
 ----------------------------------------------------------------------------
     if (nums[i] != val) {   // is this element worth keeping?
         nums[k] = nums[i];  // yes -> copy it to the "write position" k
         k++;                //       and move the write position forward
     }
     // if nums[i] == val  -> do NOTHING.
     // The element is simply skipped: it is never copied,
     // so k does NOT increase. That element will later be
     // overwritten by a valid element, or it will lie beyond
     // the new length k (and therefore be ignored / "removed").

 ----------------------------------------------------------------------------
 WHY DOES k NOT INCREASE WHEN nums[i] == val ?
 ----------------------------------------------------------------------------
 Because we do not want to reserve a slot for an element we are deleting.
 Keeping k still means "the next good element should be written here",
 so the bad element gets overwritten by the next valid one.

 ----------------------------------------------------------------------------
 WHY CAN k FALL BEHIND i ?
 ----------------------------------------------------------------------------
 As long as no element is removed, i and k are equal (each element is
 written back to its own place). The moment we skip an element, i moves
 ahead but k stays put -> k "lags" behind i. From then on, valid elements
 are written into the earlier slots where removed elements used to be,
 effectively compacting the array to the left.

 Invariant (always true after processing index i-1):
     nums[0 .. k-1] contains all valid ( != val ) elements seen so far,
     with no gaps. So at the end, the first k elements are the answer.

 ----------------------------------------------------------------------------
 DRY RUN  (the actual array used in main())
 ----------------------------------------------------------------------------
     nums = { 3, 2, 2, 3, 4, 3, 5 }      val = 3   (3 must be removed)

     i   nums[i]   condition        action                       k after
    ---------------------------------------------------------------------------
      0     3      nums[0]==val     skip, nothing written           0
      1     2      nums[1]!=val     nums[0]=2, k++                 1
      2     2      nums[2]!=val     nums[1]=2, k++                 2
      3     3      nums[3]==val     skip, nothing written           2
      4     4      nums[4]!=val     nums[2]=4, k++                 3
      5     3      nums[5]==val     skip, nothing written           3
      6     5      nums[6]!=val     nums[3]=5, k++                 4

     Memory of nums after every write:
        start : [3, 2, 2, 3, 4, 3, 5]
        i=1   : [2, 2, 2, 3, 4, 3, 5]   (2 written at index 0)
        i=2   : [2, 2, 2, 3, 4, 3, 5]   (2 written at index 1)
        i=4   : [2, 2, 4, 3, 4, 3, 5]   (4 written at index 2, overwrote a 2)
        i=6   : [2, 2, 4, 5, 4, 3, 5]   (5 written at index 3, overwrote a 3)

     Final VALID portion (indices 0 .. k-1 = 0 .. 3):
        [2, 2, 4, 5]      and k = 4

     The tail [4, 3, 5] is garbage/stale data - it is NEVER read again,
     because every loop in main() runs only for i < k. That is exactly
     how "removal" happens without resizing the vector.

 ----------------------------------------------------------------------------
 COMPLEXITY
 ----------------------------------------------------------------------------
     Time  : O(n)  -> every element is visited exactly once.
     Space : O(1)  -> only two integer variables (i, k) are used.
=============================================================================
*/
int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int k = 0; // slow pointer: next write position = number of valid elements found so far
        for(int i = 0 ; i< n ;i++){ // fast pointer: scans the whole original array
            if(nums[i] != val){     // keep this element (it is not the value we remove)
                nums[k] = nums[i];  // compact it to the left at position k
                k++;                // grow the valid portion by one
            }
            // else: element == val, so skip it. k stays unchanged,
            // this slot will be overwritten by the next valid element.
        }
        return k ; // new length = count of elements that are NOT equal to val
    }
int main(){
    vector<int> nums = {3,2,2,3,4,3,5};
    int val = 3;
    int k = removeElement(nums, val);
    cout<<"The new length of the array is: "<<k<<endl;
    cout<<"The modified array is: ";
    // ONLY the first k elements are valid; the rest is leftover garbage.
    for(int i = 0 ; i<k ;i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}
