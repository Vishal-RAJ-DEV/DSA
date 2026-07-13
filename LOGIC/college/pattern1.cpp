#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void printpatt(int n){
    for(int i=0;i<n;i++){
        for(int j=1;j<=i;j++){
            printf("%d",j);
        }
        printf("\n");
    }
}
int main(){
    int n;
    printpatt(5);
    return 0;
}