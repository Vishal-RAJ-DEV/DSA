#include <stdio.h>

int main() {
    int n, i;
    
    // Input the size of the array
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    
    // Declare an array of the specified size
    int array[n];
    
    // Input the elements of the array
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    
    // Initialize max and min to the first element of the array
    int max = array[0];
    int min = array[0];
    
    // Find the maximum and minimum elements
    for (i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }
    
    // Output the maximum and minimum elements
    printf("Maximum element: %d\n", max);
    printf("Minimum element: %d\n", min);
    
    return 0;
}
