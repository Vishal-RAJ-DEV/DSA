#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int transitionPoint(vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;
        
        int ans = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == 1) {
                ans = mid;

                // There might be another 1 on the left
                right = mid - 1;
            }
            else {
                // arr[mid] == 0
                left = mid + 1;
            }
        }

        return ans;
    }
};



int main(){
    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0 ; i < n ; i++){
        cin >> arr[i];
    }

    Solution sol;
    int transition_index = sol.transitionPoint(arr);
    if(transition_index != -1){
        cout << "Transition point (first occurrence of 1) is at index: " << transition_index << endl;
    } else {
        cout << "No transition point found (no 1s in the array)." << endl;
    }
    
    return 0;
}