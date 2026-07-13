#include <iostream>
using namespace std;

int main(){
    int n;
    cout<<"enter your number";
    cin>>n;
    int count= 0;
    for(int i=1;i<=n;i++){
     if(n%i==0){
      count++;
     }
    }

    if(count==2){
        printf("number is prime");
    }
    else{
        printf("number is not prime");
    }
    return 0;
}