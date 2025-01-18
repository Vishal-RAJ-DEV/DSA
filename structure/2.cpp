#include <iostream>
#include <string.h>
using namespace std;

struct student{
    int roll;
    float cgpa;
    char name[100];
};

int main(){
    struct student ECE[100];//array in structure.    ECE student
    ECE[0].roll=197;
    ECE[0].cgpa=9.5;
    strcpy(ECE[0].name,"vishal");
    cout<<"vishal cgpa = "<<ECE[0].cgpa<<endl;

    ECE[1].roll=197;
    ECE[1].cgpa=9.5;
    strcpy(ECE[1].name,"pallav");
    cout<<"pallav cgpa =  "<<ECE[1].cgpa<<endl;

    struct student IT[100];//IT student
    IT[0].roll=198;
    IT[0].cgpa=6.5;
    strcpy(IT[0].name,"adarsh");
    cout<<"adarsh cgpa = "<<IT[0].cgpa<<endl;

    IT[1].roll=198;
    IT[1].cgpa=6.5;
    strcpy(IT[1].name,"nikhil");
    cout<<"nikhil cgpa = "<<IT[1].cgpa<<endl;






}