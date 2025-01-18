#include <stdio.h>

void printhw(int coount);

int main(){
    printhw(10);

    return 0;
}

//recursive function
void printhw(int count){
    if(count==0){
        return;
    }
    printf("hello world\n");
    printhw(count-1);
}

