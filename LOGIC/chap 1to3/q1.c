#include <stdio.h>

int main(){

    float a,b,c;
    printf("enter a : ");
    scanf("%f", &a);

    printf("enter b :");
    scanf("%f", &b);

    printf("enter c : ");
    scanf("%f",&c);


    float p = (a+b+c)/3;
    printf("average : %f", p);

    return 0;
}