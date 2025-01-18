//write a function that print "namaste" for indian user and "bonjour" for french user.
#include <stdio.h>

void namaste();
void bonjour();

int main(){
    char ch;
    printf("enter 'i' for indian and 'f' for french\n");
    scanf("%c",&ch);

    if(ch=='i'){
        namaste();
    }
    if(ch=='f'){
        bonjour();
    }
    else{
        printf("thank u");
        }
    
    return 0;
}


void namaste(){
    printf("namaste");
}
void bonjour(){
    printf("bonjour");
}
