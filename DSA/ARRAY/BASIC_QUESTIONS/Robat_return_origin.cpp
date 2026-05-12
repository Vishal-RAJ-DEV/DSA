#include <iostream>
#include <bits/stdc++.h>
using namespace std;

 bool judgeCircle(string moves) {
        int n = moves.length();
        int x=0 ;
        int y = 0;
        for(int i = 0 ; i<n;i++){
            if( moves[i] =='R') x+=1;
            else if (moves[i] == 'L') x-=1;
            else if (moves[i]== 'U') y+=1;
            else if(moves[i] == 'D') y-=1;
        }
        if(x==0 && y == 0) return true ;
        return false;
    }

    

    int main(){
        string moves;
        cin >> moves;
        if(judgeCircle(moves)) cout << "True";
        else cout << "False";
        return 0;
    }