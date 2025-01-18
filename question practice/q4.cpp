#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(0));
    int guess;
    int magicNUM=(rand()%20)+1;
    int magicNUM1=(rand()%20)+1;
    printf("%d %d\n",magicNUM,magicNUM1);
   
    
    printf("guess the number\n");
    scanf("%d",&guess);
    if(guess==magicNUM||magicNUM1){
        printf("guess is right");
    }
    else{
        printf("guess is wrong");
    }

    return 0;
    



}