#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& arr) {
        int n = arr.size();

        int size = 0;
        for (int x : arr) {
            if (x == 1) size++;
        }

        // Edge cases
        if (size == 0) return -1;
        if (size == 1) return 0;

        int ones = 0;
        int maxones = 0;

        for (int i = 0; i < n; i++) {

            // Add current element
            ones += arr[i];

            // Remove element outside the window
            if (i >= size) {
                ones -= arr[i - size];
            }

            // Update maximum ones for a complete window
            if (i >= size - 1) {
                maxones = max(maxones, ones);
            }
        }

        return size - maxones;
    }
};


class Solution {
public:
    int minSwaps(vector<int>& arr) {
        int n = arr.size();

        // Count total number of ones
        int k = 0;
        for (int x : arr) {
            if (x == 1) k++;
        }

        // Handle edge cases
        if (k == 0) return -1;
        if (k == 1) return 0;

        int left = 0, right = 0;
        int ones = 0, maxOnes = 0;

        while (right < n) {

            // Expand window
            ones += arr[right];

            // Shrink window if its size exceeds k
            while (right - left + 1 > k) {
                ones -= arr[left];
                left++;
            }

            // Update maximum ones in a window of size k
            if (right - left + 1 == k) {
                maxOnes = max(maxOnes, ones);
            }

            right++;
        }

        return k - maxOnes;
    }
};



int main(){
    return 0;
}