


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

// dry run 

// nums = [1, 0, 3, 0, 5]

// Step 1: Find the first zero

// j = -1 initially

// Loop i = 0 → 4:

// nums[0] = 1 → not zero

// nums[1] = 0 → ✅ found zero → set j = 1, break

// Now: j = 1



// Step 2: Move non-zero elements after j

// Loop i = j+1 = 2 to 4:

// i = 2: nums[2] = 3 (non-zero)

// swap(nums[2], nums[1]) → [1, 3, 0, 0, 5]


// increment j → 2

// i = 3: nums[3] = 0 (zero) → skip

// i = 4: nums[4] = 5 (non-zero)

// swap(nums[4], nums[2]) → [1, 3, 5, 0, 0]


// increment j → 3

// Final Output:

// nums = [1, 3, 5, 0, 0]