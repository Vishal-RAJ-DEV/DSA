#include <iostream>
using namespace std;

class complex
{
    int a,b;
    public:
    //creating a constructor
    //constructor is special member function with same name as of the class.
    //it is used to initialize the object of its class
    //it is auttomatically invocked whenver an object is created
    complex(void);
    void ptintnumber(){
        cout<<"the number is "<<a<<"+"<<b<<"i"<<endl;
    }

};
complex ::complex(void) //this is a difult constructor  as it take no parameter
{
    a=10;
    b=0;

}
int main(){
    complex c;
    c.ptintnumber();

}

/*charcterstic
1. it should be declared in the public section of the class
2. they are automatically invocked whenever the object is created 
3.they cannot return value and do not have return types ;
4. we cannot refer to their address
 */



