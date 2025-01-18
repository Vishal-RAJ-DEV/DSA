#include <iostream>
using namespace std;
int linnersearch(int array[],int key,int n){
    for(int i=0;i<n;i++){
        if(array[i]==key){
            return i;
        }
    }
    return -1;
}

int main(){
    int n;
    cin>>n;

    int array[n];
    for(int i=0;i<n;i++){
        cin>>array[i];
    }

    int key;
    cin>>key;
    
    int keynum=linnersearch(array,key,n);
    cout<<key<<" is in the index "<<keynum;

    return 0;
}