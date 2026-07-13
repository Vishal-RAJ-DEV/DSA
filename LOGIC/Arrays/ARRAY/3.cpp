#include <iostream>
using namespace std;
//write a program to enter thr price 3 item and print their final cost with GST.
int main(){
    float price[3];
   cout<<"enter your number";
   cin>>price[0];
   cin>>price[1];
   cin>>price[2];

    //price with 18% GST

    cout<<"total price 1 = "<<price[0]+(0.18*price[0])<<endl;
    cout<<"total price 2 = "<<price[1]+(0.18*price[1])<<endl;
    cout<<"total price 3 = "<<price[2]+(0.18*price[2])<<endl;

    return 0;
}