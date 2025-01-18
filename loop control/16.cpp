#include <stdio.h>
//hollow diamond pattern
int main(){
    int n=4;
    //top
    for(int i=0;i<n;i++)
    {
        //spaces
        for(int j=0;j<n-i-1;j++){
            printf(" ");
        }
        printf("*");
        if(i!=0)
        {
            //spaces
            for(int j=0;j<2*i-1;j++){
                printf(" ");
                 }
                 printf("*");
        }
        
        printf("\n");
    }
    //bottom
    for(int i=0;i<n-1;i++)
    {
        //spaces
        for(int j=0;j<i+1;j++){
            printf(" ");
        }
        printf("*");
        if(i!=n-2){
            //spaces
            for(int j=0;j<2*(n-i)-5;j++){
                printf(" ");
            }
            printf("*");
        }
        printf("\n");
    }
    
}