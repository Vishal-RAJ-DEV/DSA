
#include <stdio.h>

int main(){
      
      int x;
      printf("enter a number :");
      scanf("%d", &x);
    

      printf("even: 1 \n");
      printf("odd: 0 \n");

      printf("is x is divisible by 2? : %d",x%2==0);

      return 0;
}