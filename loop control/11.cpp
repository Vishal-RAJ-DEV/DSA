#include <stdio.h>
//square pattern

int main(){
    int n=4;
    char ch='A';
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("  %c  ",ch);
            ch++;
        }
        printf("\n");

    }

    return 0;
} 