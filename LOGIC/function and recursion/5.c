//calculate the value of price with 18% gst in it.
#include <stdio.h>

void calculateprice(float value);
int main(){
    float value;
    printf("value : ");
    scanf("%f",&value);

    calculateprice(value);
    return 0;
}
void calculateprice(float value){
    value=value+(0.18 * value);
    printf("price is : %f",value);

}