#include <iostream>
#include <string.h>
using namespace std;

void slice(char str[],int n,int m){
    char newstrig[200];
    int j=0;
    for(int i=n;i<=m;i++,j++){
        newstrig[j]=str[i];

    }
    newstrig[j]='\0';
    puts(newstrig);
}
int main(){
    char str[]="helloworld";
    slice(str,3,6);
}
