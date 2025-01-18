#include <stdio.h>
//traiangle pattern

int main(){
    int n=10;
    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            printf("%d",j);

        }
        printf("\n");
    }

    

    return 0;
}