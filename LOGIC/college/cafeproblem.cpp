#include <stdio.h>

int main() {
    int code;
    float total = 0.0;

    printf("Welcome to the Convenience Store!\n");
    printf("Menu:\n");
    printf("1. Coffee - Rs. 2.50\n");
    printf("2. Tea - Rs. 2.00\n");
    printf("3. Sandwich - Rs. 5.00\n");
    printf("4. Salad - Rs. 4.00\n");
    printf("5. Juice - Rs. 3.00\n");
    printf("Enter 0 to finish your order.\n");

    while (1) {
        printf("\nEnter the item code: ");
        scanf("%d", &code);

        if (code == 0) {
            break; // Exit the loop if the user enters 0
        }

        switch (code) {
            case 1:
                total += 2.50;
                break;
            case 2:
                total += 2.00;
                break;
            case 3:
                total += 5.00;
                break;
            case 4:
                total += 4.00;
                break;
            case 5:
                total += 3.00;
                break;
            default:
                printf("Invalid code! Please enter a valid code.\n");
                break;
        }
    }

    // Apply a 10% discount if the total exceeds Rs. 20
    if (total > 20.0) {
        printf("\nCongratulations! You qualify for a 10%% discount.\n");
        total = total * 0.9; // Apply 10% discount
    }

    printf("\nTotal bill amount: Rs. %.2f\n", total);

    return 0;
}