#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int factorial(int n ){
    if(n == 0) return 1;
    return n * factorial(n - 1);
}
int permutation(int n , int r){
    return factorial(n) / factorial(n-r);
}
int main(){
    int n = 5, r = 2;
    cout << permutation(n, r) << endl;
    return 0;
}
