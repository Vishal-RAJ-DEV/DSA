#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    long long minArraySum(vector<int>& nums) {
        // Use a set to get unique numbers and sort them
        set<int> uniqueNums(nums.begin(), nums.end());
        vector<int> sortedUnique(uniqueNums.begin(), uniqueNums.end());
        
        long long totalSum = 0;
        
        for (int x : nums) {
            int bestReplacement = x;
            
            // For each number, find the smallest divisor present in the array
            // We only need to check numbers smaller than x
            for (int divisor : sortedUnique) {
                if (divisor >= x) break; 
                
                if (x % divisor == 0) {
                    bestReplacement = divisor;
                    break; // Since sortedUnique is ascending, the first divisor found is the smallest
                }
            }
            totalSum += bestReplacement;
        }
        
        return totalSum;
    }
};
int main(){
    Solution sol;
    vector<int> nums = {10, 15, 20, 25};
    cout << sol.minArraySum(nums) << endl; // Output the minimum array sum after replacements
    return 0;
}
