//write a fuction to calculate the sum, product &average of 2 number print the average in the main function.

#include <stdio.h>

void dowork(int a, int b , int *sum , int *prod, int *avg);
int main(){
    int a=3;
    int b=5;
    int sum,prod,avg;
    avg=(a+b)/2;
    printf("avrage is %d", avg);
    dowork(a,b,&sum,&prod,&avg);
    printf("sum=%d\nprod=%d\navg=%d\n",sum, prod,avg);

    return 0;
}
void dowork(int a,int b,int *sum, int *prod, int *avg){
    *sum=a+b;
    *prod=a*b;
    *avg=(a+b)/2;

}

