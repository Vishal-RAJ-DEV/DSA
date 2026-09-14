#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    long long countLessEqual(vector<long long>& A,
                             vector<long long>& B,
                             long long x) {

        long long count = 0;

        for (long long a : A) {

            // a > 0
            // Products increase as B increases.
            // Valid values form a prefix:
            // YES YES YES NO NO
            if (a > 0) {

                int low = 0;
                int high = B.size();

                while (low < high) {

                    int mid = low + (high - low) / 2;

                    if ((__int128)a * B[mid] <= x) {
                        low = mid + 1;
                    }
                    else {
                        high = mid;
                    }
                }

                count += low;
            }

            // a < 0
            // Products decrease as B increases.
            // Valid values form a suffix:
            // NO NO NO YES YES
            else if (a < 0) {

                int low = 0;
                int high = B.size();

                while (low < high) {

                    int mid = low + (high - low) / 2;

                    if ((__int128)a * B[mid] <= x) {
                        high = mid;
                    }
                    else {
                        low = mid + 1;
                    }
                }

                count += B.size() - low;
            }

            // a == 0
            else {

                // 0 * B[j] = 0
                if (x >= 0) {
                    count += B.size();
                }
            }
        }

        return count;
    }


    long long kthSmallestProduct(vector<int>& nums1,
                                 vector<int>& nums2,
                                 long long k) {

        vector<long long> A(nums1.begin(), nums1.end());
        vector<long long> B(nums2.begin(), nums2.end());

        // Iterate over the smaller array.
        if (A.size() > B.size()) {
            swap(A, B);
        }

        // ---------------------------------------
        // OPTION 2:
        // Find actual minimum and maximum product
        // ---------------------------------------

        long long p1 = A.front() * B.front();
        long long p2 = A.front() * B.back();
        long long p3 = A.back() * B.front();
        long long p4 = A.back() * B.back();

        long long low = min({p1, p2, p3, p4});
        long long high = max({p1, p2, p3, p4});


        // ---------------------------------------
        // Binary search on the answer
        // ---------------------------------------

        while (low < high) {

            long long mid = low + (high - low) / 2;

            // Number of products <= mid
            long long count = countLessEqual(A, B, mid);

            if (count >= k) {

                // mid is large enough.
                // Try a smaller value.
                high = mid;

            } else {

                // Not enough products <= mid.
                // Need a larger value.
                low = mid + 1;
            }
        }

        return low;
    }
};




class Solution {
public:
    long long countLessEqual(vector<long long>& A,
                             vector<long long>& B,
                             long long x) {

        long long count = 0;

        for (long long a : A) {

            if (a > 0) {

                int low = 0;
                int high = B.size();

                while (low < high) {
                    int mid = low + (high - low) / 2;

                    if ((__int128)a * B[mid] <= x)
                        low = mid + 1;
                    else
                        high = mid;
                }

                count += low;
            }

            else if (a < 0) {

                int low = 0;
                int high = B.size();

                while (low < high) {
                    int mid = low + (high - low) / 2;

                    if ((__int128)a * B[mid] <= x)
                        high = mid;
                    else
                        low = mid + 1;
                }

                count += B.size() - low;
            }

            else {
                if (x >= 0)
                    count += B.size();
            }
        }

        return count;
    }

    long long kthSmallestProduct(vector<int>& nums1,
                                 vector<int>& nums2,
                                 long long k) {

        vector<long long> A(nums1.begin(), nums1.end());
        vector<long long> B(nums2.begin(), nums2.end());

        if (A.size() > B.size())
            swap(A, B);

        long long low = -10000000000LL;
        long long high = 10000000000LL;

        while (low < high) {

            long long mid = low + (high - low) / 2;

            long long count = countLessEqual(A, B, mid);

            if (count >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};


int main(){
    return 0;
}