#include <iostream>
using namespace std;

int main(){
    char name[]={'v','i','s','h','a','l',};
    //OR
    char yourname[]="vishal raj";
    printf("%s\n",yourname);//%s for print string

    char firstname[100];
   // cin>>firstname;//it cannot inputs muiltiple word strings with spaces so usse below function
    //cout<<firstname;
    
    //string function
    fgets(firstname,100,stdin);//scan the string function
    puts(firstname);//print string function
    
    
    return 0;
}