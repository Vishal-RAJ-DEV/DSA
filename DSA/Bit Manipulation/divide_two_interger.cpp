#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int divide(int dividend, int divisor)
{
    long long sum = 0;
    int cnt = 0;
    while (sum < dividend)
    {
        cnt++;
        sum += divisor;
    }
    return cnt;
}
int main()
{
    int dividend = 10, divisor = 3;
    cout << divide(dividend, divisor) << endl; // Output: 3             
    return 0;
}
