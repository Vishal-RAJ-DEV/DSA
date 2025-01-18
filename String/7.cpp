#include <iostream>
#include <string.h>
using namespace std;

int main(){
    char firststr[]="HHA";
    char secstr[]="HHA"; 
    char comp= strcmp(firststr,secstr);
    printf("%d",comp);
    return 0;
}