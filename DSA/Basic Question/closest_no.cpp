#include <iostream>
#include <bits/stdc++.h>
using namespace std;

 int closestNumber(int n, int m) {
        // code here
        int quoitent = n / m;
        
        int n1 = quoitent * m;
        
        int n2 = ( n * m ) > 0 ? ( m *  (quoitent+ 1) ) : (m * (quoitent - 1));
        
        if(abs(n - n1) < abs(n - n2 )) return n1;
        
        return n2;
    }
int main(){
    int n = 10, m = 3;
    cout << closestNumber(n, m) << endl;    
    return 0;
}
