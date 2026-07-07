#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    /*
     Intuition :-
    1.First pass removes bad )
    because while scanning left-to-right we immediately know if a ) has no matching (.
    
    2.Second pass removes extra (
    because only after finishing do we know how many opening brackets remained unmatched (bal), and scanning right-to-left removes exactly those extra openings.
*/
    int minAddToMakeValid(string s) {
        int n = s.size();
        int mincnt = 0;
        int cnt = 0;

        for( char c : s){
            if( c == '('){
                cnt++;

            }
            else{
                if( cnt> 0 ) cnt--;
                else mincnt++;
            }
        }

        return mincnt + cnt;


    }
};


int main(){
    string s = "()))((";
    Solution obj;
    int ans = obj.minAddToMakeValid(s);
    cout<<"The minimum number of parentheses to add to make the string valid is: "<<ans<<endl;
    
    return 0;
}