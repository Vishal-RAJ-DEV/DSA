#include <stdio.h>
//inverted triangle pattern 

int main(){
    int n=4;
    for(int i=0;i<n;i++){
        //print spaces
        for(int j=0;j<i;j++){
            printf(" ");
        }
        //print number
        for(int j=0;j<n-i;j++){
            printf("%d",i+1);
        }
        printf("\n");
    }
    
}