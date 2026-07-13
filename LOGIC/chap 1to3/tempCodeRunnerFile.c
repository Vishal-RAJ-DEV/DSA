#include <stdio.h>

// Global variable
int globalVar = 10;

void demoFunction() {
    // Static variable
    static int staticVar = 0;
    staticVar++;
    printf("Inside demoFunction: staticVar = %d\n", staticVar);
    
    // Local variable
    int localVar = 5;
    printf("Inside demoFunction: localVar = %d\n", localVar);
}

int main() {
    printf("Global variable: globalVar = %d\n", globalVar);
    
    for (int i = 0; i < 3; i++) {
        demoFunction();
    }
    
    return 0;
}
