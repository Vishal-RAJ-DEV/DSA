#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// APPROACH 1: Brute Force Max-Heap (keep top k smallest)
// ============================================================
// ALGO:
// - Generate ALL possible fractions from the sorted array.
// - Use a max-heap of size k; push each fraction.
// - If heap size exceeds k, pop the largest — so heap always
//   holds the k smallest fractions seen so far.
// - At the end, heap's top is the k-th smallest fraction.
// TC: O(n^2 log k)  |  SC: O(k)
// ============================================================
class Solution_Approach1 {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        sort(begin(arr), end(arr));  // ensure ascending order
        // max-heap stores pairs: (fraction value, {numerator, denominator})
        priority_queue<pair<double, pair<int, int>>> maxHeap;
        int n = arr.size();

        // generate all possible fractions
        for(int i = 0; i < n - 1; i++) {
            for(int j = i + 1; j < n; j++) {
                // push current fraction into max-heap
                maxHeap.push({((double) arr[i] / arr[j]), {arr[i], arr[j]}});

                // keep heap size at most k — pop the largest (top)
                if(maxHeap.size() > k) {
                    maxHeap.pop();  // removes current largest fraction
                }
            }
        }

        // top of max-heap = k-th smallest fraction
        auto res = maxHeap.top().second;
        return {res.first, res.second};
    }
};

// ============================================================
// APPROACH 2: Brute Force Min-Heap (pop k times)
// ============================================================
// ALGO:
// - Generate ALL fractions sorted into a min-heap.
// - Pop from the heap k times; the k-th popped is the answer.
// TC: O(n^2 + k log n^2) ≈ O(n^2 log n)  |  SC: O(n^2)
// ============================================================
class Solution_Approach2 {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        // min-heap: pair<double, {numerator, denominator}>
        priority_queue<pair<double, pair<int, int>>,
                       vector<pair<double, pair<int, int>>>,
                       greater<>> minHeap;
        int N = arr.size();

        // push all fractions into min-heap
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                minHeap.push({(double)arr[i] / arr[j], {arr[i], arr[j]}});
            }
        }

        // pop k times — the k-th pop is the k-th smallest fraction
        pair<int, int> result;
        for (int i = 0; i < k; ++i) {
            result = minHeap.top().second;
            minHeap.pop();
        }

        return {result.first, result.second};
    }
};

// ============================================================
// APPROACH 3: Binary Search on Value (Optimal)
// ============================================================
// ALGO:
// - Since arr is sorted (prime numbers), fractions are between 0 and 1.
// - Binary search the fraction VALUE in range [0, 1].
// - For a candidate `mid`, count how many fractions are ≤ mid
//   using a two-pointer sweep (i for numerator, j for denominator).
// - Also track the maximum fraction ≤ mid encountered — this will
//   be our answer when count == k.
// - Adjust left/right based on whether count < k or > k.
// TC: O(n log precision)  |  SC: O(1)
// ============================================================
class Solution_Approach3 {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        double left = 0, right = 1, mid;  // fraction values ∈ [0,1]
        vector<int> res;

        while (left <= right) {
            mid = left + (right - left) / 2;
            int j = 1;          // denominator pointer (starts at index 1)
            int total = 0;      // count of fractions ≤ mid
            int num = 0, den = 0;
            double maxFrac = 0; // tracks largest fraction ≤ mid

            for (int i = 0; i < n; ++i) {
                // advance j while fraction arr[i]/arr[j] > mid
                // i.e., arr[i] > arr[j] * mid
                while (j < n && arr[i] >= arr[j] * mid) {
                    ++j;
                }

                // all denominators from j to n-1 form fractions ≤ mid
                total += n - j;

                // track the largest fraction ≤ mid (this is our candidate answer)
                if (j < n && maxFrac < arr[i] * 1.0 / arr[j]) {
                    maxFrac = arr[i] * 1.0 / arr[j];
                    num = i;
                    den = j;
                }
            }

            // exactly k fractions ≤ mid → found the k-th smallest
            if (total == k) {
                res = {arr[num], arr[den]};
                break;
            }

            // too many fractions ≤ mid → search left half
            if (total > k) {
                right = mid;
            } else {
                // too few → search right half
                left = mid;
            }
        }

        return res;
    }
};


int main(){
    vector<int> arr = {1, 2, 3, 5};

    Solution_Approach1 s1;
    vector<int> res1 = s1.kthSmallestPrimeFraction(arr, 3);
    cout << "Approach 1 (Max-Heap): " << res1[0] << "/" << res1[1] << endl;

    Solution_Approach2 s2;
    vector<int> res2 = s2.kthSmallestPrimeFraction(arr, 3);
    cout << "Approach 2 (Min-Heap): " << res2[0] << "/" << res2[1] << endl;

    Solution_Approach3 s3;
    vector<int> res3 = s3.kthSmallestPrimeFraction(arr, 3);
    cout << "Approach 3 (Binary Search): " << res3[0] << "/" << res3[1] << endl;

    return 0;
}