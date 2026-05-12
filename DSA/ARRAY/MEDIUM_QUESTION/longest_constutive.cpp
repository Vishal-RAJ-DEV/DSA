// Longest Consecutive Sequence in an Array
//Problem Statement: You are given an array of ‘N’ integers. You need to find the length of the longest sequence which contains the consecutive elements.
#include <bits/stdc++.h>
using namespace std;

//Brute force approach (O(N log N) time complexity due to sorting)
int longestConsecutive1(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        sort(nums.begin() , nums.end());
        int n = nums.size();
        int lastSmaller = INT_MAX;
        int cnt = 0;
        int longest = 1;
        for(int i = 0 ;i<n;i++){
            if(nums[i] - 1 == lastSmaller){//if the last number is lesser then current number then its a series number so increse the count 
                cnt+=1;
                lastSmaller = nums[i];
            }
            else if(lastSmaller != nums[i]){
                cnt = 1; //new series comes reset the cnt 
                lastSmaller = nums[i]; //and set the new start of the series 
            }
            longest = max(longest , cnt);
        }
        return longest;
    }

//Optimal approach (O(N) time complexity and O(N) space complexity)
int longestSuccessiveElements(vector<int>&a) {
    int n = a.size();
    if (n == 0) return 0;

    int longest = 1;
    unordered_set<int> st;
    //put all the array elements into set:
    for (int i = 0; i < n; i++) {
        st.insert(a[i]);
    }

    //Find the longest sequence:
    for (auto it : st) {
        //if 'it' is a starting number:
        if (st.find(it - 1) == st.end()) {
            //find consecutive numbers:
            int cnt = 1;
            int x = it;
            while (st.find(x + 1) != st.end()) {
                x = x + 1;
                cnt = cnt + 1;
            }
            longest = max(longest, cnt);
        }
    }
    return longest;

}

int main()
{
    vector<int> a = {100, 200, 1, 2, 3, 4};
    int ans = longestSuccessiveElements(a);
    cout << "The longest consecutive sequence is " << ans << "\n";
    return 0;
}

