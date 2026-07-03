#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countGoodSubstrings(string s) {
        int n = s.size();
        int l = 0 ; int r = 0 ;
        unordered_map<char , int>mpp;
        int cnt = 0;
        int dup = 0;

        // Algorithm:
        // 1. Expand a window with the right pointer until it reaches size 3.
        // 2. Track how many characters are duplicated inside the current window.
        // 3. If the window size is 3 and dup == 0, all 3 characters are distinct.
        // 4. Count that substring, then remove the leftmost character and move on.
        //
        // Intuition:
        // For a fixed size of 3, we do not need to recheck the whole substring every time.
        // We only need to know whether any character frequency became 2 inside the window.
        // If no character repeats, the current 3-length window is a good substring.
        while( r < n){
            mpp[s[r]]++;

            if( mpp[s[r]] == 2)dup++;

            if( r < 2){
                r++;
                continue;   
            }

            if( dup == 0) cnt++;//if there is not duplicate then increase the count 

            // Shrink the window here to keep the size fixed at 3.
            mpp[s[l]]--; 
            if(mpp[s[l]] == 1) dup--; // The repeated character is gone, so the window is unique again.
            l++;
            
            // Move the window forward by one position.
            r++;

        }

        return cnt;
    }
};


int main(){
    string s = "xyzzaz";
    Solution obj;
    int ans = obj.countGoodSubstrings(s);
    cout<<"The number of good substrings of size 3 is: "<<ans<<endl;
    return 0;
}