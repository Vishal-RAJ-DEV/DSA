#include <iostream>
using namespace std;


int main(){
    //int marks[3]={98,99,89};
    //printf("total  mark = %d",marks[0]+marks[1]+marks[2]);

    int mark[3];
    cout<<"enter your number"<<endl;
    cin>>mark[0];
    cin>>mark[1];
    scanf("%d",&mark[2]);
    int totalmark=mark[0]+mark[1]+mark[2];
    cout<<"total mark = "<<totalmark;
    return 0;
}