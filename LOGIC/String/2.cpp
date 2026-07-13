#include <iostream>
using namespace std;
//create a string first name and last name to store the detail of user & print all charcater using loop;
void printstring(char arr[]){
    for(int i=0;arr[i]!='\0';i++){
        cout<<arr[i];
    }
    cout<<endl;
}

int main(){
    char firstname[]="vishal";
    char secondname[]="raj";

    printstring(firstname);
    printstring(secondname);

    return 0;

}