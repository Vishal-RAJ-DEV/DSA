//write a fuction to calculate the percentage of student from science,math and sanskrit;
#include <stdio.h>

int calpercnt(int science,int math,int sanskrit);

int main(){
    int science=77;
    int math=88;
    int sanskrit=98;
    printf("percentage is %d",calpercnt(science,math,sanskrit));
    
    return 0;
}

int calpercnt(int science,int math, int sanskrit){
    int percnt=((science+math+sanskrit)*100)/300;  //total mark is 300
    return percnt;
}