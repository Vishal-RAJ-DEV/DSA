#include <stdio.h>

int main(){
    int age = 22;
    int age1 = 23;
    int *ptr = &age;
    int *ptr1 =&age1;

    printf("ptr = %u\n ptr1 = %u\n difference = %u",ptr,ptr1,ptr-ptr1);
    ptr1 = &age;
   printf("comparison = %u\n",ptr==ptr1);
    return 0;

}