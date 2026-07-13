#include <iostream>
#include<string.h>
using namespace std;
struct student{    //declare of differnt data types using structure
    int roll;     ///structure can store different data types like int , float ,char.
    float cgpa;
    char name[100];

};
int main(){
    struct student s1;   //s1 is for 1st student whose data is written
    s1.roll=35;
    s1.cgpa=9.2;
    strcpy(s1.name,"vishal");  //name is copied in s1.name using strcpy

    cout<<"detail of student 1"<<endl;
    cout<<"student roll no = "<<s1.roll<<endl;
    cout<<"cgpa of student = "<<s1.cgpa<<endl;
    cout<<"name of student : "<<s1.name<<endl;

    cout<<"-------------------------------------------------------"<<endl;

    struct student s2;
    s2.roll=36;
    s2.cgpa=8.8;
    strcpy(s2.name,"pallav");

    cout<<"detail of student 2"<<endl;

    cout<<"student roll no = "<<s2.roll<<endl;
    cout<<"cgpa of student = "<<s2.cgpa<<endl;
    cout<<"name of student : "<<s2.name<<endl;



    return 0;


}