#include <stdio.h>
//print the value of 'price'from its pointer to pointer. 

int main(){
    float price=100.00;
    float *ptr=&price;
    float **pptr=&ptr;

    printf("%f",*ptr);
    return 0;
}