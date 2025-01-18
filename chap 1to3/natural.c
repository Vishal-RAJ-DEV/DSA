#include <stdio.h>
//write a program to check thatt given character isdigit or not?

int main(){

    char alp;
    printf("enter character");
    scanf("%c", &alp);

     if(alp>=0 && alp<=9){
        printf("%c is digit", alp);
     }

     else{
        printf("%c is not dight", alp);
     }
     return 0;
}