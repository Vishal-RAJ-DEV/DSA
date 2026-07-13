#include <iostream>
using namespace std;

struct student {
    char name[100];
    int roll ;
    float cgpa;

};

int main(){
    //initializing structure
    struct student s1={"vishal",35,9.7};
    struct student s2={"pallav",36,9.8};
    struct student s3={"luffy",37,10};

    cout<<"s1 name is "<<s1.name<<endl;
    cout<<"s2 roll no is :"<<s2.roll<<endl;
    cout<<"s3 cgpa is "<<s3.cgpa<<endl;

}