#include <stdio.h>

int main()
{
    int math,english,science,sst,hindi;
    printf("math mark: ");
    scanf("%d", &math);

    printf("english mark:");
    scanf("%d", &english);

    printf("science mark:");
    scanf("%d", &science);

    printf("sst mark:");
    scanf("%d", &sst);

    printf("hindi mark:");
    scanf("%d", &hindi);

    int totalmark =  math+english+science+sst+hindi;

    printf(" your total mark is: %d \n",totalmark);
    printf("------------------------------------------------- \n");

    printf("your garde is \n");
    if(totalmark<30){
        printf("c \n");
        }
        
    else if(totalmark>=30 && totalmark<70){
        printf("A \n");

    }
    else if(totalmark>=70 && totalmark<90){
        printf("A \n");
    }
    else{
        printf("A+ \n");
    }
    printf("---------------------------------------------------------- \n");

    int percentage= totalmark*100/100;
    printf("pecentage:%d \n",percentage);


    return 0;
}