#include <iostream>
#include <string.h>
using namespace std;
void salting(char password[]){
    char salt[]="123";
    char newpassword[200];

    strcpy(newpassword,password);
    strcat(newpassword,salt);
    puts(newpassword);
}
int main(){
    char password[100];
    scanf("%s",password);
    salting(password);

    return 0;
}
