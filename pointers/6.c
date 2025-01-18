#include <stdio.h>
void adress(int *n);
int main(){
    int n = 4;
    adress(&n);
    printf("adress is %d",&n);


    return 0;
}

void adress(int *n){
    printf("adress is %d ", n);

}