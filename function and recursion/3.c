#include <stdio.h>

int sum(int a,int b);

int main(){
    int a,b;
    printf("enter your numbers");
    scanf("%d",&a);
    printf("enter anumber");
    scanf("%d",&b);

    int s = sum(a,b);
    printf("sum is : %d",s); 

    return 0;

}

int sum(int a,int b){
    return a+b;
}