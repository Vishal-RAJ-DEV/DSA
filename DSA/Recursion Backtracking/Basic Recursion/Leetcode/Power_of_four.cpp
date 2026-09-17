#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPowerOfFour(int n) {
        // Base cases
        if (n == 1)
            return true;

        if (n <= 0 || n % 4 != 0)
            return false;

        // Recursive call
        return isPowerOfFour(n / 4);
    }
};


int main(){
    return 0;
}