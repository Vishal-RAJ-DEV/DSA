///write a functinn to convert celcius into fahrenheit.
#include <stdio.h>

float converttemp(float celcius);

int main(){
    float farh=converttemp(37);
    printf("fahrenheit is %f",farh);
    return 0;
}

float converttemp(float celcius){
    float farh=celcius * (9.0/5.0) + 32;
    return farh;
    
}