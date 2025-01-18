#include <iostream>
using namespace std;

int main(){
    int mark[3];
    cout<<"enter physics mark = "<<"\n";
    cin>>mark[0];
    cout<<"enter chemistry mark = "<<"\n";
    cin>>mark[1];
    cout<<"enter math mark = "<<"\n";
    cin>>mark[2];
    
    
    
   cout<<"phy = "<<mark[0]<<endl;
   cout<<"chem = "<<mark[1]<<endl;
   cout<<"math = "<<mark[2]<<endl;
    int totaLmark=mark[0]+mark[1]+mark[2];
    printf("totaLmark = %d\n",totaLmark);

    return 0;



}