#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
==========================================================
APPROACH 1: BRUTE FORCE (minimumWindowSubstring)
==========================================================
IDEA: Check every possible substring of s, find the smallest one
      that contains all characters of t.

HOW IT WORKS:
1. Store frequency of each char in t (original map)
2. For each starting index i in s:
   - Copy original map
   - Expand end index j from i to n-1
   - Decrease count when char found in map
   - If map becomes empty -> all chars of t found
   - Track minimum length window
3. Return smallest valid window

TIME COMPLEXITY: O(n^2 * m) where n=s.length, m=t.length
                 (n^2 substrings x m map operations)
SPACE COMPLEXITY: O(m) for the hash maps

WHY SLOW: Re-checks same characters many times, creates new map for each i
*/
string minimumWindowSubstring( string s , string t ){
    int n = s.size();
    int m = t.size();
    unordered_map<char , int> original;
    for( char p : t){
        original[p]++;
    }
    int maxlen = INT_MAX;
    string ans = "";

    for( int i = 0 ; i< n ;i++){
        unordered_map<char , int> mpp = original;  // fresh copy for each i
        for ( int j = i ; j<n ;j++ ){

            if( mpp.find(s[j]) != mpp.end()){
                mpp[s[j]]--;
                if(mpp[s[j]] == 0) mpp.erase( s[j]);
            }

              if( mpp.size() == 0){
                if( maxlen > ( j - i +1)){
                    maxlen = min( maxlen , ( j - i + 1));
                    ans = s.substr( i , j - i + 1);
                }
            }

        }
    }
    return ans.size() == 0 ? "-1" : ans;
    // for(int i = 0 ;i<n;i++){
    //     if( mpp.find(s[i]) != mpp.end()){
    //         mpp[s[i]]--;
    //         if(mpp[s[i]] == 0){
    //             mpp.erase(s[i]);
    //         }
    //     }
    // }
    // cout<<mpp.size()<<endl;
}


/*
==========================================================
APPROACH 2: OPTIMAL SLIDING WINDOW (minWindow)
==========================================================
IDEA: Use two pointers (left, right) to maintain a window.
      Expand right to include chars, contract left to minimize.

HOW IT WORKS:
1. Store frequency of each char in t (original map)
2. Track: formed = how many unique chars meet required frequency
3. Expand right pointer:
   - Add s[right] to window map
   - If this char's freq now matches original -> formed++
4. While window is valid (formed == required):
   - Update minimum answer
   - Remove s[left] from window map
   - If this char's freq drops below required -> formed--
   - Move left++ to shrink window
5. Continue until right reaches end

TIME COMPLEXITY: O(n) - each char visited at most twice (by left & right)
SPACE COMPLEXITY: O(m) for hash maps

KEY DIFFERENCE FROM BRUTE FORCE:
- No nested loops, single pass with two pointers
- Reuses window map instead of recreating
- Shrinks window immediately when valid (greedy)
- O(n) vs O(n^2) - massive speedup for large strings
*/
//optimal approach using sliding window technique
string minWindow( string s , string t ){
    int n  = s.size();
    int m = t.size();
    unordered_map<char , int> original;
    for( char p : t){
        original[p]++;
    }
    unordered_map< char , int > window;
    int left = 0 ;
    int right = 0 ;
    int minlen = INT_MAX;
    int formed = 0;              // unique chars in window meeting required freq
    int required = original.size();  // unique chars needed from t
    int minleft = 0 ;

    while( right < n ){
        char c = s[right];
        window[c]++;
        
        // if this char is in t AND window now has exactly required count
        if( original.count(c) && window[c] == original[c]){
            formed++;
        }
        // cout<<formed;
        //if the formed characters matches the required characters then we can try and contract the window till the point it ceases to be 'desirable'
        while( left <= right && formed == required){
            if( minlen > right - left + 1){
                minlen = min( minlen , right - left + 1);
                minleft = left;
            }
            char leftchar  = s[left];
            window[leftchar]--;
            // for( auto p : window){
            //     cout<<"element"<<p.first<<" frq"<<p.second<<endl;
            // }
            // if removing this char makes window invalid
            if ( original.count( leftchar ) && window[leftchar] < original[leftchar]){
                formed--;  
            }
            // cout<<formed;
            left++; 
        }
        // cout<<"-------------------------------"<<endl;
        right++;
    }
    return minlen == INT_MAX ? "-1" : s.substr( minleft , minlen);
}
int main(){
    string s = "ADOBECODEBANC";
    string t = "ABC";
    // cout << minimumWindowSubstring(s , t) << endl;
     cout << minWindow(s , t) << endl;

    return 0;
}