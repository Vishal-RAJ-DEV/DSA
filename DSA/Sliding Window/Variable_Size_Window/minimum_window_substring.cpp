#include <iostream>
#include <bits/stdc++.h>
using namespace std;

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
        unordered_map<char , int> mpp = original;
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
    int formed = 0;
    int required = original.size();
    int minleft = 0 ;

    while( right < n ){
        char c = s[right];
        window[c]++;
        
        //this means that this character is part of t and its frequency in current window matches the frequency in the original map
        //so we have formed one more character requirement
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
            if ( original.count( leftchar ) && window[leftchar] < original[leftchar]){
                formed--;  // here we are reducing the formed count as the window no longer contains enough of leftchar
                // cout<<formed;
            }
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