#include <stdio.h>

int main() {
    int i, j;
    
    // Declare a 2-D array with 3 rows and 4 columns
    int matrix[3][4];
    
    // Input: Enter elements for the 2-D array
    printf("Enter elements for a 3x4 matrix:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("Element at position [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
    
    // Output: Print the 2-D array
    printf("\nThe 3x4 matrix is:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
