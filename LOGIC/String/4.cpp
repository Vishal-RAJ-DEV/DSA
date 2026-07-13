#include <iostream>
using namespace std;
//make a program that inputs user's name andprint it's length
int countlength(char arr[]);
int main(){
    char name[100];
    fgets(name,100,stdin);
    printf("length is %d",countlength(name));


    return 0;
}
int countlength(char arr[]){
    int count=0;
    for(int i=0;arr[i]!='\0';i++){ 
        count++;
    }
    return count-1;
   

}