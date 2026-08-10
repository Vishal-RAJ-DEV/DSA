#include <bits/stdc++.h>
using namespace std;
/*
1. We need k elements on the LEFT.

2. mid1 = elements taken from a.
   mid2 = k - mid1 = elements taken from b.

3. Check the partition:
      l1 <= r2
      l2 <= r1

4. If correct:
      answer = max(l1, l2)

5. If wrong:
      l1 > r2 → too many from a → move LEFT
      l2 > r1 → too few from a  → move RIGHT


        k elements
       <---------->

a = [  LEFT  |  RIGHT  ]
              ↑
             mid1

b = [  LEFT  |  RIGHT  ]
              ↑
             mid2

       mid1 + mid2 = k
*/


class Solution {
public:
    int kthElement(vector<int>& a, vector<int>& b, int k) {

        int m = a.size();
        int n = b.size();

        // ---------------------------------------------------------
        // IMPORTANT:
        // We do binary search on the smaller array.
        // This gives O(log(min(m,n))) time.
        // ---------------------------------------------------------
        if (m > n) {
            return kthElement(b, a, k);
        }

        // We want exactly k elements on the LEFT side.
        int left = k;

        // ---------------------------------------------------------
        // mid1 = how many elements we take from array a
        // mid2 = how many elements we take from array b
        //
        // Since total elements on LEFT must be k:
        //
        //      mid1 + mid2 = k
        //
        // Therefore:
        //      mid2 = k - mid1
        //
        // low/high make sure that both mid1 and mid2
        // stay inside their valid array ranges.
        // ---------------------------------------------------------
        int low = max(0, k - n);
        int high = min(k, m);

        while (low <= high) {

            // Try taking mid1 elements from array a
            int mid1 = (low + high) >> 1;

            // The remaining elements needed to make k
            // must come from array b.
            int mid2 = k - mid1;


            // -----------------------------------------------------
            // Imagine the arrays divided like this:
            //
            // a = [ LEFT | RIGHT ]
            //           ^
            //         mid1
            //
            // b = [ LEFT | RIGHT ]
            //           ^
            //         mid2
            //
            // l1 = last element on LEFT of a
            // r1 = first element on RIGHT of a
            //
            // l2 = last element on LEFT of b
            // r2 = first element on RIGHT of b
            // -----------------------------------------------------

            int l1 = (mid1 > 0)
                        ? a[mid1 - 1]
                        : INT_MIN;

            int r1 = (mid1 < m)
                        ? a[mid1]
                        : INT_MAX;

            int l2 = (mid2 > 0)
                        ? b[mid2 - 1]
                        : INT_MIN;

            int r2 = (mid2 < n)
                        ? b[mid2]
                        : INT_MAX;


            // -----------------------------------------------------
            // CHECK WHETHER OUR PARTITION IS CORRECT
            //
            // We want every element on LEFT <= every element
            // on RIGHT.
            //
            // We only need to check the two boundary pairs:
            //
            //      l1 <= r2
            //      l2 <= r1
            //
            // If both are true, our partition is correct.
            // -----------------------------------------------------
            if (l1 <= r2 && l2 <= r1) {

                // LEFT contains exactly k elements.
                //
                // Therefore the k-th element is simply the
                // largest element on the LEFT.
                //
                // Largest LEFT element = max(l1, l2)
                return max(l1, l2);
            }


            // -----------------------------------------------------
            // l1 > r2
            //
            // Example:
            //
            // a: [ ... 10 | ... ]
            // b: [ ...  5 | ... ]
            //
            // 10 is on LEFT but 5 is on RIGHT.
            //
            // This means we took TOO MANY elements from a.
            //
            // So move the partition of a to the LEFT.
            // -----------------------------------------------------
            else if (l1 > r2) {
                high = mid1 - 1;
            }


            // -----------------------------------------------------
            // Otherwise:
            //
            // l2 > r1
            //
            // Example:
            //
            // a: [ ... 5 | ... ]
            // b: [ ... 10 | ... ]
            //
            // 10 is on LEFT but 5 is on RIGHT.
            //
            // This means we took TOO FEW elements from a.
            //
            // So move the partition of a to the RIGHT.
            // -----------------------------------------------------
            else {
                low = mid1 + 1;
            }
        }

        // This should never happen if input is valid.
        return -1;
    }
};


int main() {

    vector<int> a = {2, 3, 6, 7, 9};
    vector<int> b = {1, 4, 8, 10};

    int k = 5;

    Solution solution;

    cout << "The " << k
         << "-th element of two sorted arrays is: "
         << solution.kthElement(a, b, k)
         << '\n';

    return 0;
}