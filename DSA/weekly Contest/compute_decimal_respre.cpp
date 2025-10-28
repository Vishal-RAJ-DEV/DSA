#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<int> decimalRepresentation(int n) {
    vector<int> result;
    int power = 0;
    
    while (n > 0) {
        int digit = n % 10;
        if (digit != 0) {
            // Calculate the actual decimal place value
            // For example, for 102: 2*1, 0*10 (skipped), 1*100
            result.push_back(digit * pow(10, power));
        }
        n /= 10;
        power++;
    }
    
    // Sort in descending order (largest value first)
    sort(result.begin(), result.end(), greater<int>());
    
    return result;
}

int main() {
    int n = 102;
    vector<int> result = decimalRepresentation(n);
    cout << "Decimal representation of " << n << ": ";
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}