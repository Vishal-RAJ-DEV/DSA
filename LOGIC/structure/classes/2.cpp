#include <iostream>
using namespace std;

class shop{
    int itemid[100];
    int itemprice[100];
    int counter;
    public:
       void intcounter(void) {counter=0;}
       void setprice(void);
       void displayprice(void);
};
void shop :: setprice(void){
    cout<<"enter your item id"<<counter+1<<endl;
    cin>>itemid[counter];
    cout<<"enter your item price"<<endl;
    cin>>itemprice[counter];
    counter++;

}
void shop :: displayprice(void){
    for(int i=0;i<counter;i++){
        cout<<"the price of item id"<<itemid[i]<<"is"<<itemprice[i]<<endl;
    }
}
int main(){
    
    shop dukan;
     dukan.intcounter();
     int n;
    cout<<"enter no of id want to restore"<<endl;
    cin>>n;
     for(int i=1;i<=n;i++){
        dukan.setprice();
     }
    dukan.displayprice();

    return 0;
}