#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxHeight(vector<int>& height, vector<int>& width, vector<int>& length) {
        int n = height.size();

        vector<vector<int>> boxes;

        for (int i = 0; i < n; i++) {
            int h = height[i];
            int w = width[i];
            int l = length[i];

            boxes.push_back({max(w, l), min(w, l), h});
            boxes.push_back({max(h, l), min(h, l), w});
            boxes.push_back({max(h, w), min(h, w), l});
        }

        // Sort by base area in descending order
        sort(boxes.begin(), boxes.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] * a[1] > b[0] * b[1];
        });

        int m = boxes.size();

        vector<int> dp(m);

        int ans = 0;

        for (int i = 0; i < m; i++) {
            dp[i] = boxes[i][2];

            for (int j = 0; j < i; j++) {
                if (boxes[j][0] > boxes[i][0] &&
                    boxes[j][1] > boxes[i][1]) {

                    dp[i] = max(dp[i], dp[j] + boxes[i][2]);
                }
            }

            ans = max(ans, dp[i]);
        }

        return ans;
    }
};


class Solution {
public:
    vector<vector<int>> boxes;
    vector<int> dp;

    int solve(int i) {
        if (dp[i] != -1) return dp[i];

        int ans = boxes[i][2]; // Current box's height

        for (int j = i + 1; j < boxes.size(); j++) {
            // Can box j be placed above box i?
            if (boxes[j][0] < boxes[i][0] &&
                boxes[j][1] < boxes[i][1]) {

                ans = max(ans, boxes[i][2] + solve(j));
            }
        }

        return dp[i] = ans;
    }

    int maxHeight(vector<int>& height, vector<int>& width,
                  vector<int>& length, int n) {

        boxes.clear();

        // Generate 3 rotations for every box
        for (int i = 0; i < n; i++) {
            int h = height[i];
            int w = width[i];
            int l = length[i];

            boxes.push_back({max(w, l), min(w, l), h});
            boxes.push_back({max(h, l), min(h, l), w});
            boxes.push_back({max(h, w), min(h, w), l});
        }

        // Sort by base area in descending order
        sort(boxes.begin(), boxes.end(), [](const vector<int>& a,
                                            const vector<int>& b) {
            return a[0] * a[1] > b[0] * b[1];
        });

        int m = boxes.size();
        dp.assign(m, -1);

        int ans = 0;

        // Any orientation can be the bottom box
        for (int i = 0; i < m; i++) {
            ans = max(ans, solve(i));
        }

        return ans;
    }
};



int main(){
    return 0;
}