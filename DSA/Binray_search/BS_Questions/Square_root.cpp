
#include <bits/stdc++.h>
using namespace std;

int floorSqrt1(int n) {
    int low = 1, high = n;
    //Binary search on the answers:
    int ans = 0;
    while (low <= high) {
        long long mid = (low + high) / 2;
        long long val = mid * mid;
        if (val <= (long long)(n)) {
            ans = mid;
            //eliminate the left half:
            low = mid + 1;
        }
        else {
            //eliminate the right half:
            high = mid - 1;
        }
    }
    return ans;
}

//or use this optimized  version of this code:
int floorSqrt(int n) {
    int low = 1, high = n;
    //Binary search on the answers:
    while (low <= high) {
        long long mid = (low + high) / 2;
        long long val = mid * mid;
        if (val <= (long long)(n)) {  //here checking the mid * mid is less than or equal to n
            //if it is less than or equal to n, then this mid can be a possible
            //eliminate the left half:
            low = mid + 1;
        }
        else {
            //eliminate the right half:
            high = mid - 1;
        }
    }
    return high;   //this high will be the floor of sqrt(n) 
}

int main()
{
    int n = 16;
    int ans = floorSqrt(n);
    cout << "The floor of square root of " << n
         << " is: " << ans << "\n";
    return 0;
}