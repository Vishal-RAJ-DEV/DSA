#include <stdio.h>
//factorial of n.
int factorial(int n);

int main(){
    printf("factorial is %d",factorial(5));

    return 0;
}

int factorial(int n){
    if(n==1){
        return 1;
    }
    int fac1TOn=factorial(n-1);
    int factN=fac1TOn*n;
    return factN;
}