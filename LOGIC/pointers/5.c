#include <stdio.h>
//swap two number a and b.
void swap(int a,int b);
void swap2(int*a, int*b);

int main(){
    int a=4;
    int b=5;
    swap2(&a,&b);
    printf("a=%d & b=%d\n",a,b);



    return 0;

}
//call by reference
void swap2(int*a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
    printf(" a= %d & b= %d\n",*a,*b);


}

void swap(int a,int b){
    int t=a;
    a=b;
    b=t;
     printf("a=%d & b=%d\n",a,b);
}