#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int romanToInt(string s) {
        unordered_map<char, int> values = {
        { 'I'  , 1} , {'V' , 5 } , {'X', 10} ,
        {'L' , 50} , {'C' , 100} , {'D' , 500} 
        ,{'M' , 1000}
        };
        int total = 0;
        for(int i = 0 ; i<s.size();i++){
            int ch = values[s[i]];
            int next = (i+1 < s.size()) ? values[s[i+1]] : 0;  //store the value of next character if it exists otherwise store 0
            //if the current character is less than the next character then we subtract its value from the total otherwise we add its value to the total

            if(ch < next){  //if current character is less than next character then we subtract its value from the total
                total -= ch;
            }
            else{  //if current character is greater than or equal to next character then we add its value to the total 
                total += ch;
            }
        }
        return total;

    }
int main(){
    string s = "MCMXCIV";
    cout << romanToInt(s) << endl;
    return 0;
}