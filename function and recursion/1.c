//function declarti/prototype
#include <stdio.h>

void printhello();
void helloworld();

//fuction call  (number of function id depend on the how many time you write the function).
int main()
{
    printhello();
    helloworld();
    printhello();
    helloworld();
    return 0;

}
//function call
void printhello() {
printf("hello!\n");
}
void helloworld(){
    printf("helloworld\n");
}

