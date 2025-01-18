#include <stdio.h>

int main()
{
    int age;
    printf("enter age: ");
    scanf("%d", &age);

    if(age>18){
        printf("adult \n");
        if(age<60){
            printf("married");
            } else{
                printf("not capabale of married");
            }
        
    }
    else if(age>13 && age<18){
        printf("teenage \n");
    }
    
    else{
        printf("child \n");
    }
    return 0;


}