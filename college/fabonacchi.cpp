//write function of  nth term number of fibonacci sequence;
#include <stdio.h>
int main(){
    int n,a=0,b=1,c,count=0;
    printf("enter number of term");
    scanf("%d",&n);

    
    while(count<n){
    printf("%d\n",a);
    c=a+b;
    a=b;
    b=c;
    count++;
    }
    return 0;
}
