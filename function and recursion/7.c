//wwrite function to calculate area of square , a circle & a rectabgle
#include <stdio.h>
 float areasquare(float side);
 float areacircle(float radius);
 float arearectangle(float a ,float b);

 int main(){
       float side=2.2;
       float radius=8.5;
       float a=4;
       float b=5;
       printf("area of square: %f \n",areasquare(side));
       printf("area of circle:%f\n",areacircle(radius));
       printf("area of rectangle:%f\n",arearectangle(a,b));
       return 0;

 }
 float areasquare(float side){
    return side*side;
 }
 float areacircle(float radius){
    return 3.14*radius*radius;
 }
 float arearectangle(float a ,float b){
    return a*b;
 }
