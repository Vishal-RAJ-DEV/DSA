#include <stdio.h>
//pyramid pattern

int main(){
    int n=8;

    for(int i=0;i<n;i++)
    {
        //print space
        for(int j=1;j<=n-i-1;j++){
            printf(" ");
        }
        //print set 1 number
        for(int j=1;j<=i+1;j++){
            printf("%d",j);
        }
        //print set 2 number
        for(int j=i;j>=1;j--){
            printf("%d",j);
        }
        printf("\n");

    }
    return 0;
}