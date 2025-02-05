#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//dynmaic memmory allocation in C 
//syntax : ptr = (ptr-type*) malloc(size_in _bytes) 
int main(){
      int *ptr;
      ptr = (int*) malloc ( 10* sizeof(int));
      for(int i =0;i<3;i++){
        scanf("%d",&ptr[i]); 
      }
      for(int i =0;i<3;i++){
        printf("value at %d is %d\n",i,ptr[i]);
      }
    return 0;
}