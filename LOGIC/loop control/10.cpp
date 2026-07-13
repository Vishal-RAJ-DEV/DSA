#include <stdio.h>

int main(){
    int n=3;

    int sum = 1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("  %d  ",  sum  );
            sum++;
        }
        printf("\n");
    }
    return 0;


}