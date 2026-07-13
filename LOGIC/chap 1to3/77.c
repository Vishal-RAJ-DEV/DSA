#include <stdio.h>

int main(){
    char ALP;
    printf("enter your APL");
    scanf("%c", &ALP);

    if(ALP>='A' && ALP<='Z'){
        printf("UPPER case");
    }
    else if (ALP>='a' && ALP<='z')
    {
        printf("lower case");
    }
    else{
        printf("not english");
    }
    


    

    return  0;

}