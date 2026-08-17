#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int activitySelection(vector<int>& start, vector<int>& finish) {
        
        int n = start.size();

        // Store {finish, start}
        vector<pair<int, int>> activities;

        for (int i = 0; i < n; i++) {
            activities.push_back({finish[i], start[i]});
        }

        // Sort by finish time
        sort(activities.begin(), activities.end());

        int count = 0;
        int lastFinish = -1;

        for (auto& activity : activities) {
            
            int finishTime = activity.first;
            int startTime = activity.second;

            // Next activity must start strictly after
            // previous activity finishes
            if (startTime > lastFinish) {
                count++;
                lastFinish = finishTime;
            }
        }

        return count;
    }
};


int main(){
    return 0;
}