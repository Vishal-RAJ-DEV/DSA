//write a program to check that if the given number is armstrong  number or not.

#include <stdio.h>

int main(){
    int n,sum=0,x;
    printf("enter your number : ");
    scanf("%d",&n);
    x=n;
    while(n>0){
        sum=sum+(n%10)*(n%10)*(n%10);
        n=n/10;
    }
    if(sum==x){
        printf("the num is armstrong number");
    }
    else{
        printf("number is not armstrong number");
    }


    return 0;
}