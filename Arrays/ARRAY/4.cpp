#include <stdio.h>

int main(){
    int age = 22;
    int *ptr = &age;
    //IN int adress incresed by 4 bites.
    
    printf(" ptr = %u",ptr);
    ptr++;
    printf("ptr = %u",ptr);
    ptr--;
    printf("ptr = %u",ptr);
    return 0;

}

