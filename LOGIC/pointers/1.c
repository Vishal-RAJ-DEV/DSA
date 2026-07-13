//pointers
#include <stdio.h>
int main(){
    int age=20;
    int *ptr=&age;
    int _age=*ptr;
    printf("%d\n",_age);
    printf("%d\n",age);
    printf("%d\n",*ptr);
    printf("%d\n",*(&age));

    return 0;
}