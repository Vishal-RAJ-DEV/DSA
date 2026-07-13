#include <stdio.h>

int main(){
    int n=4;

    for(int i=0;i<n;i++){            //outer line
        char ch = 'A';
        for(int j=0;j<n;j++){      //inner line = line start
            printf("%c",ch);
            ch++;
        }
        printf("\n");
    }

    return 0;
}