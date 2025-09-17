#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int combinationRecursive(int n, int r) {
    if (r == 0 || r == n) return 1;
    return combinationRecursive(n - 1, r - 1) + combinationRecursive(n - 1, r);
}

double Multiplier(int start, int end) {
    if (start == end)
        return start;

    double res = 1;
    while (start <= end) {
        res *= start;
        start++;
    }
    return res;
}

int nCr(int n, int r) {
    // No valid combinations if r > n
    if (n < r) 
        return 0;
    // Base cases: nC0 or nCn = 1    
    if (n == r || r == 0) 
        return 1;

    // Use max(r, n-r) to minimize the 
    // number of multiplications
    int max_val = max(r, n - r);
    int min_val = min(r, n - r);

    double nume = Multiplier(max_val + 1, n);   //here max_val + 1 because we want to start from max_val + 1 to n
    double deno = Multiplier(1, min_val);  

    return int(nume / deno);
}

int main(){
    int n = 5, r = 2;
    cout << nCr(n, r) << endl;
    return 0;
}