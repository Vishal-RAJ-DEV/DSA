//print a code of table of number n.


#include <stdio.h>

int main(){

    int n;
    printf("enter your number : ");
    scanf("%d",&n);

    for(int i=1;i<=10;i++){
        printf("%d\n",n*i);
    }


return 0;
}
