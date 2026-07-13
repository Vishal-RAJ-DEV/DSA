#include <iostream>
using namespace std;
//
void storetable(int table[][10],int n,int m , int number){
    for(int i=0;i<m;i++){//0 to 10
        table[n][i]=number*(i+1);//2,4,6,8,10...
    }
}

int main(){
    int table[2][10];
    storetable(table,0,10,2);
    storetable(table,1,10,3);

    for(int i=0;i<10;i++){
        cout<<table[0][i]<<"\t";
    }
    cout<<"\n";
    for(int i=0;i<10;i++){
        cout<<table[1][i]<<"\t";

    }
    return 0;
}
