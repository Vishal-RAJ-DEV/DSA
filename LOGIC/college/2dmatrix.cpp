#include <stdio.h>

void readMatrix(int matrix[3][3], const char *name) {
    printf("Enter the elements of matrix %s (3x3):\n", name);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j  < 3; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void printMatrix(const int matrix[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(const int matrix1[3][3], const int matrix2[3][3], int result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

void transposeMatrix(const int matrix[3][3], int result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

void multiplyMatrices(const int matrix1[3][3], const int matrix2[3][3], int result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main() {
    int matrix1[3][3], matrix2[3][3], result[3][3];

    readMatrix(matrix1, "A");
    readMatrix(matrix2, "B");

    // Addition of two matrices
    addMatrices(matrix1, matrix2, result);
    printf("Addition of two matrices:\n");
    printMatrix(result);

    // Transpose of matrix A
    transposeMatrix(matrix1, result);
    printf("Transpose of matrix A:\n");
    printMatrix(result);

    // Multiplication of two matrices
    multiplyMatrices(matrix1, matrix2, result);
    printf("Multiplication of two matrices:\n");
    printMatrix(result);

    return 0;
}
