#include <iostream>
using namespace std;

class complex
{
    int a,b;
    public:
    complex(int x, int y);
    void ptintnumber(){
        cout<<"the number is "<<a<<"+"<<b<<"i"<<endl;
    }

};
complex ::complex(int x,int y) //this is a difult constructor  as it take no parameter
{
    a=x;
    b=y;

}
int main(){
    complex a(5,6);
    //or
    complex b=complex(9,3);
    a.ptintnumber();
    b.ptintnumber();

}



