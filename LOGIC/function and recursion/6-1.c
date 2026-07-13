//use library function to calculate the square of a number given by user.
#include <stdio.h>

void number(int n);
int main(){
    int n;
    printf("enter a number : ");
    scanf("%d",&n);

    number(n);
    return 0;
}

void number(int n){
    printf("square is : %d",n*n);
}