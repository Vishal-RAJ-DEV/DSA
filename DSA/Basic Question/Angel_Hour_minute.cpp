#include <iostream>
#include <bits/stdc++.h>
using namespace std;
 double getAngle(string& s) {
        // code here
        int h = stoi(s.substr(0 , 2)); //first two letter form 0th index 
        int m = stoi(s.substr(3, 2));  //two letters form 3rd index 
        
        h = h % 12;  //convert the 24 hour into 12 hour 
        
        double hourAngle = h * 30 + m * 0.5;
        double minAngle =  m * 6;
        
        double angleDiff= fabs(hourAngle - minAngle);
        
        return min(angleDiff , 360 - angleDiff);
    }
int main(){
    string time = "10:30";
    cout << getAngle(time) << endl; 
    return 0;
}