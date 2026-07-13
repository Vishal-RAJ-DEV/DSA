#include <iostream>
using namespace std;
//pascal traingle

int main(){
    int n=5;
    int c=0;
    for(int i=0;i<n;i++){
        for(int s=1;s<=n-i;s++){
            cout<<"  ";
        }
        for(int j=0;j<=i;j++)
        {
            if(j==0 || i==0)
             c=1;
            else
            c=c*(i-j+1)/j;
            printf("%4d",c);

        }
        cout<<"\n";
    }
    return 0;
}