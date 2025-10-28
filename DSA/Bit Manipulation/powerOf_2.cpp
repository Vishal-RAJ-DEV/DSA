#include <iostream>
#include <bits/stdc++.h>
using namespace std;

bool powerOfTwo(int n){

    if(n <= 0) return false; //if n is less than or equal to 0, it cannot be a power of 2

    return (n & (n-1)) == 0; //if n is a power of 2, then n & (n-1) will be 0
}

bool powerOfTwo1(int n){ //alternative method
    if(n <= 0) return false; //if n is less than or equal to 0, it cannot be a power of 2

    while(n > 1){
        if(n % 2 != 0) return false; //if n is not divisible by 2, it cannot be a power of 2
        n /= 2; //divide n by 2
    }
    return true; //if we reach here, then n is a power of 2
}
int powerofX(int x , int n){
    if(n == 0) return 1; //base case
    if(x == 0) return 0; //if x is 0, then x^n is 0
    
    return x * powerofX(x, n-1); //recursive case
}

 double myPow(double x, int n) {
        double ans = 1.0;
        long long nn = n;
        if(nn < 0) nn = -1 * nn;//convert the power into the positve 
        while(nn){
            if(nn%2){//means nn % 2  = 1 (true) 
                ans = ans * x;
                nn = nn - 1;
            }
            else{
                x = x* x;
                nn = nn /2;
            }
        }
        if(n< 0) ans = double( 1.0) / double(ans); //for negtive exponent x*-1 = 1/x
        return ans;
    }

int main(){
    int n;
    cout<<"enter your number: "<<endl;
    cin>>n;
    if(powerOfTwo1(n)) {
        cout<<n<<" is a power of 2"<<endl;
    } else {
        cout<<n<<" is not a power of 2"<<endl;
    }
    int x, p;
    cout<<"enter the base and power: "<<endl;
    cin>>x>>p;
    cout<<x<<"^"<<p<<" = "<<powerofX(x, p)<<endl;

    double base;
    int exponent;
    cout << "Enter base and exponent: ";
    cin >> base >> exponent;
    cout << base << "^" << exponent << " = " << myPow(base, exponent) << endl;
    
    
    return 0;
}

/*
🔑 Key Idea

A number is a power of 2 if it has exactly one set bit (1) in its binary representation.

Examples:

1 → 0001

2 → 0010

4 → 0100

8 → 1000

16 → 10000

🧠 What happens when we subtract 1?

Subtracting 1 from a binary number flips all the bits after the last set bit (including the set bit itself).

Example:
8 = 1000 (binary)
8 - 1 = 7 = 0111

See how 1000 → 0111:
The single 1 became 0.
All bits after it became 1.

🛠 Why does (n & (n - 1)) == 0 work?
If n is a power of 2:
n has only one 1 bit.
n-1 has all 1s below that bit.
When you do n & (n-1), there’s no overlap — result is 0.

If n is not a power of 2:
n has more than one 1 in binary.
n-1 will overlap with at least one of those 1s.
So n & (n-1) ≠ 0.*/