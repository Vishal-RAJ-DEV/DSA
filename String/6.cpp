#include <iostream>
#include <string.h>
using namespace std;

int main(){
    char oldstring[] ="oldstring";
    char newstring[]="new string";
    strcpy(newstring,oldstring);//interchnage the value of strings.
    puts(newstring);
    return 0;
}