#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int binaryToDecimal(string &b)
{
    // Code here.
    string nums = b;
    int sum = 0;

    int base = 1; // the 2^0 = 1 that why
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        if (nums[i] == '1')
        {
            sum += base;
        }
        base *= 2;
    }
    return sum;
}

int main()
{
    string binary = "1101";
    cout << binaryToDecimal(binary) << endl;
    return 0;
}
