#include <stdio.h>
//sum of first n natural number.

int sum(int n);

int main(){
    printf("sum is %d",sum(10));

    return 0;
}

int sum(int n){
    if(n==1){
        return 1;
    }
    int sumM=sum(n-1);  //sumM is sum of 1 to n. 
    int totalsum=sumM+n;
    return totalsum;

}
