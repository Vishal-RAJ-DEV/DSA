#include <iostream>
#include <bits/stdc++.h>
using namespace std;

 void readnumber(int matrix[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("element of matrix[%d][%d]",i+1,j+1);
            scanf("%d",&matrix[i][j]);
        }

    }
 }
void printnum(int matrix[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("  %d  ",matrix[i][j]);
        }
        printf("\n");

    }
 }
 void addmatrix(int matrix1[3][3],int matrix2[3][3],int result[3][3]){
    for (int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            result[i][j]=matrix1[i][j]+matrix2[i][j];
        }
    }
 }
int main(){
    int matrix1[3][3],matrix2[3][3],result[3][3];
    readnumber(matrix1);
    readnumber(matrix2);

    addmatrix(matrix1,matrix2,result);
    printnum(result);


    return 0;
}