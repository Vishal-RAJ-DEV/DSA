


#include <bits/stdc++.h>
using namespace std;

vector<int> moveZeros(int n, vector<int> a) {
    //temporary array:
    vector<int> temp;
    //copy non-zero elements
    //from original -> temp array:
    for (int i = 0; i < n; i++) {
        if (a[i] != 0)
            temp.push_back(a[i]);
    }

    // number of non-zero elements.
    int nz = temp.size();

    //copy elements from temp
    //fill first nz fields of
    //original array:
    for (int i = 0; i < nz; i++) {
        a[i] = temp[i];
    }

    //fill rest of the cells with 0:
    for (int i = nz; i < n; i++) {
        a[i] = 0;
    }
    return a;
}

// Optimized code   Time Complexity: O(n), as we iterate through the array only once.
// Space Complexity: O(1), as we only use a constant amount of space to store the temporary variables.
void moveZeroes1(vector<int>& nums) {
    int n = nums.size();
   int j =-1;
   for(int i=0 ; i<n;i++){
    if(nums[i]==0){
        j=i;
        break;
    }
   }
   if(j == -1) return;
   for(int i = j+1;i<n;i++){
    if(nums[i]!=0){
        swap(nums[i],nums[j]);
        j++;
    }
   }
}

int main()
{
    vector<int> arr = {1, 0, 2, 3, 2, 0, 0, 4, 5, 1};
    int n = 10;
    vector<int> ans = moveZeros(n, arr);
    for (auto &it : ans) {
        cout << it << " ";
    }
    cout << '\n';
    return 0;
}


