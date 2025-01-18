#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class point{
    int x, y;
    public:
    point(int a, int b){
        x=a;
        y=b;
    }
    void displaynumber(){
        cout<<"the number is("<<x<<","<<y<<")"<<endl;
    }
     
};
int main(){
    point p(5,3);
    p.displaynumber();

    point q(33,98);
    q.displaynumber();

    return 0;
}