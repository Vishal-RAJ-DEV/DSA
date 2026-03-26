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

//optimal solution using bit manipulation
class Solution {
public:
    int divide(int dividend, int divisor) {
        //FOR THE MAX VALUSE LIKE 
        //DVD = -2147483648
        //AND DIS = -1;
        if( dividend == INT_MIN  && divisor == -1) return INT_MAX;
        
        //use long long to prevent the overflow conditions
        //convert the divisor and dividend into the postive numbers 
        long long dvd = llabs((long long)dividend);
        long long dis = llabs((long long)divisor);

        long long  quotient = 0;
        while( dvd >= dis){
            int shifts = 0;

            //calcualte the maximums shifts , where dvd << shifts is lesser than dividend 
            while( dvd >= ( dis << shifts)) shifts++;

            //last shifts is extra for the checking so decrese the shifts one time 
            shifts--;

            //remove the left shift of the div from the dvd , which is dis * 2^ shifts
            dvd -= dis << shifts;
            //add the 2^shifts to the quotients 
            quotient += 1 << shifts;
        }

        //now restore the signs if there is negative 
        if((dividend < 0) ^ (divisor < 0)){
            //if the sign is same then it xor gives 0 , this if not executes 
            //if sign different , then quotient will negative
            quotient = -quotient;
        }

        return (int)quotient;
    }
};

int main()
{
    int dividend = 10, divisor = 3;
    cout << divide(dividend, divisor) << endl; // Output: 3             
    return 0;
}
