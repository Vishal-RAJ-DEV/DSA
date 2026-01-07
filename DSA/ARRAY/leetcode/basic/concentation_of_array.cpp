#include <iostream>
#include <bits/stdc++.h>
using namespace std;
    vector<int> getConcatenation(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            ans[i] = nums[i % n];
        }
        return ans;
    }
int main(){
    vector<int> nums = {1, 2, 3};
    vector<int> result = getConcatenation(nums);
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}

// the error that should be remembere is that , never assing the size of vector like this vector<int> ans( 2*n) and use the push_back function to insert elements into the vector.
// because when we do vector<int> ans( 2*n) it creates a vector of size 2*n with all elements initialized to 0
// and when we do ans.push_back( nums[i % n]) it adds elements at the end of the vector, increasing its size beyond 2*n
// so the final size of the vector becomes more than 2*n and the first 2*n elements remain 0 which is not what we want.
// to fix this either we can use vector<int> ans; and then use push_back to add elements
// or we can use vector<int> ans( 2*n) and then directly assign values like ans[i] = nums[i % n];   