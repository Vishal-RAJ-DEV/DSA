#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPalindromes(string s) {

        const int MOD = 1e9 + 7;
        int n = s.size();

        // --------------------------------------------------
        // 1. Build rightPair
        // --------------------------------------------------

        long long rightPair[10][10] = {};
        long long tempFreq[10] = {};

        // Scan RIGHT -> LEFT
        for (int i = n - 1; i >= 0; i--) {

            int x = s[i] - '0';

            // x comes before every digit already present
            // in tempFreq.
            for (int d = 0; d < 10; d++) {
                rightPair[x][d] += tempFreq[d];
            }

            // Current x is now available to the left.
            tempFreq[x]++;
        }

        // --------------------------------------------------
        // 2. Initialize rightFreq
        // --------------------------------------------------

        long long rightFreq[10] = {};

        for (char ch : s) {
            rightFreq[ch - '0']++;
        }

        // --------------------------------------------------
        // 3. LEFT starts empty
        // --------------------------------------------------

        long long leftFreq[10] = {};
        long long leftPair[10][10] = {};

        long long ans = 0;

        // --------------------------------------------------
        // 4. Move CENTER from LEFT -> RIGHT
        // --------------------------------------------------

        for (int i = 0; i < n; i++) {

            int x = s[i] - '0';

            // ----------------------------------------------
            // Step 1: Remove center from RIGHT
            // ----------------------------------------------

            rightFreq[x]--;

            // ----------------------------------------------
            // Step 2: Remove all pairs starting with x
            // from RIGHT.
            //
            // After removing x, rightFreq[d] tells us
            // how many d's are still to the right.
            // ----------------------------------------------

            for (int d = 0; d < 10; d++) {
                rightPair[x][d] -= rightFreq[d];
            }

            // ----------------------------------------------
            // Step 3: Match LEFT pair with reversed
            // RIGHT pair.
            //
            // LEFT  = a b
            // RIGHT = b a
            // ----------------------------------------------

            for (int a = 0; a < 10; a++) {
                for (int b = 0; b < 10; b++) {

                    ans += leftPair[a][b] * rightPair[b][a];
                    ans %= MOD;
                }
            }

            // ----------------------------------------------
            // Step 4: Move x from CENTER -> LEFT
            // ----------------------------------------------

            // x can become the SECOND character
            // of every new pair:
            //
            // d -> x
            //
            // for every d already in LEFT.
            for (int d = 0; d < 10; d++) {
                leftPair[d][x] += leftFreq[d];
            }

            // ----------------------------------------------
            // Step 5: Add x to LEFT frequency
            // ----------------------------------------------

            leftFreq[x]++;
        }

        return ans;
    }
};


int main(){
    return 0;
}