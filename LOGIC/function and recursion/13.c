//write a function to print nt h term of the fibonacci sequence.
// sequence are 0,1,1,2,3,4,5,6,13,21,.........
#include <stdio.h>

int fib(int n);

int main(){
    int n;
    printf("enter the number of the term");
    scanf("%d", &n);
    for (int i = 0; i <=n; i++)
    {
        printf("%d\n",fib(i));
    }
    
    return 0;
    }
    int fib(int n){
        if(n==0){
            return 0;
        }
        if(n==1){
            return 1;
        }
        int fibNm1=fib(n-1);
        int fibNm2=fib(n-2);
        int fibN=fibNm1+fibNm2;
         return fibN;
    }

