#include <stdio.h>
void square(int n);
void _square(int *n);

int main(){
    int n=50;
    square(n);
    printf("number is %d\n",n);
    
    _square(&n);
    printf("number is %d\n",n);

return 0;

}
//call by value
void square(int n){
    n=n*n;
    printf("square  is %d\n",n);

}
//call by refrence
void _square(int *n){
    *n=(*n) * (*n);//50*50
    printf("_square is %d",*n);
}