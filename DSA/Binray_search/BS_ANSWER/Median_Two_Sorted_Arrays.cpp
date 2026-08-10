#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//              partition
//                 ↓

// A = [ ...... LEFT ...... | ...... RIGHT ...... ]

// B = [ ...... LEFT ...... | ...... RIGHT ...... ]

//                  ↓

//         LEFT has half elements

//                  ↓

//       max(left) <= min(right)

//                  ↓

//             median

// And the four values:
//         Aleft | Aright
//         ----------------
//         Bleft | Bright

// The condition is:
//         Aleft <= Bright
//         Bleft <= Aright
// If:

//         Aleft > Bright
//         move A partition left.
// If:
//         Bleft > Aright
//         move A partition right.

// That's the binary search.

//Time complexity is here O(log(min(n,m)))	with the space complexity O(1)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {

        // Always binary search on the smaller array
        if (A.size() > B.size()) {
            swap(A, B);
        }

        int n = A.size();
        int m = B.size();

        int low = 0;
        int high = n;

        int half = (n + m + 1) / 2;

        while (low <= high) {

            // Partition A
            int i = low + (high - low) / 2;

            // Partition B
            int j = half - i;

            int Aleft  = (i == 0) ? INT_MIN : A[i - 1];
            int Aright = (i == n) ? INT_MAX : A[i];

            int Bleft  = (j == 0) ? INT_MIN : B[j - 1];
            int Bright = (j == m) ? INT_MAX : B[j];

            // Correct partition
            if (Aleft <= Bright && Bleft <= Aright) {

                // Odd total length
                if ((n + m) % 2 == 1) {
                    return max(Aleft, Bleft);
                }

                // Even total length
                return (max(Aleft, Bleft) +
                        min(Aright, Bright)) / 2.0;
            }

            // Too many elements taken from A
            else if (Aleft > Bright) {
                high = i - 1;
            }

            // Too few elements taken from A
            else {
                low = i + 1;
            }
        }

        return 0.0;
    }
};


int main(){
    return 0;
}