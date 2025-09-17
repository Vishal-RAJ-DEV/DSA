
// Example 1:
// Input Format: N = 4, a[] = {7, 15, 6, 3}, h = 8
// Result: 5
// Explanation: If Koko eats 5 bananas/hr, he will take 2, 3, 2, and 1 hour to eat the piles accordingly. So, he will take 8 hours to complete all the piles. 

// 📋 Binary Search Trace Steps for minimumRateToEatBananas

// Iteration 1:
// low = 1, high = 11
// mid = (1 + 11) / 2 = 6
// calculateTotalHours(v, 6) = ceil(3/6) + ceil(6/6) + ceil(7/6) + ceil(11/6)
//                          = 1 + 1 + 2 + 2 = 6
// totalH <= h → ✅ Yes
// Action: Try slower → high = 5

// Iteration 2:
// low = 1, high = 5
// mid = (1 + 5) / 2 = 3
// calculateTotalHours(v, 3) = ceil(3/3) + ceil(6/3) + ceil(7/3) + ceil(11/3)
//                          = 1 + 2 + 3 + 4 = 10
// totalH > h → ❌ No
// Action: Too slow → low = 4

// Iteration 3:
// low = 4, high = 5
// mid = (4 + 5) / 2 = 4
// calculateTotalHours(v, 4) = ceil(3/4) + ceil(6/4) + ceil(7/4) + ceil(11/4)
//                          = 1 + 2 + 2 + 3 = 8
// totalH <= h → ✅ Yes
// Action: Try slower → high = 3

// End Condition:
// low = 4, high = 3 → low > high
// ✅ Return low = 4 (Minimum eating rate)



#include <bits/stdc++.h>
using namespace std;

int findMax(vector<int> &v) {  // Find the maximum element in the vector
    int maxi = v[0];
    int n = v.size();
    //find the maximum:
    for (int i = 0; i < n; i++) {
        maxi = max(maxi, v[i]);
    }
    return maxi;
}

long long  calculateTotalHours(vector<int> &v, int bananasPerHour) {  //this is for calculating total hours
    long long  totalH = 0;
    int n = v.size();
    //find total hours:
    for (int i = 0; i < n; i++) {
        totalH += ceil((double)(v[i]) / (double)(bananasPerHour));  // Calculate hours for each pile    
    }
    return totalH;
}

int minimumRateToEatBananas(vector<int> v, int h) {  // Find the minimum rate to eat bananas
    int low = 1, high = findMax(v);

    //apply binary search:
    while (low <= high) {
        int mid = (low + high) / 2;
        long long  totalH = calculateTotalHours(v, mid);
        if (totalH <= h) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return low;
}

int main()
{
    vector<int> v = {7, 15, 6, 3};
    int h = 8;
    int ans = minimumRateToEatBananas(v, h);
    cout << "Koko should eat atleast " << ans << " bananas/hr.\n";
    return 0;
}
