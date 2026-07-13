// Design a program to store the details purchase by a customer. Create array for the same to store multiple. Calculate the total amount of purchase and give discount based on following conditions: a) if total amount >5,000 then discount 10% b)  if total amount >3,000 then discount 7% c) else 5%.
    
#include <stdio.h>

// Structure to store purchase details
struct Purchase {
    char itemName[50];
    int quantity;
    float price;
};

// Function to take input for multiple purchases
void inputPurchases(struct Purchase purchases[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for item %d:\n", i + 1);
        printf("Enter Item Name: ");
        scanf(" %[^\n]", purchases[i].itemName);
        printf("Enter Quantity: ");
        scanf("%d", &purchases[i].quantity);
        printf("Enter Price per Unit: ");
        scanf("%f", &purchases[i].price);
    }
}

// Function to display purchase details
void displayPurchases(struct Purchase purchases[], int n) {
    printf("\n--- Purchase Details ---\n");
    for (int i = 0; i < n; i++) {
        printf("Item: %s | Quantity: %d | Price per unit: %.2f | Total: %.2f\n", 
               purchases[i].itemName, purchases[i].quantity, purchases[i].price, 
               purchases[i].quantity * purchases[i].price);
    }
}

// Function to calculate the total amount
float calculateTotalAmount(struct Purchase purchases[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += purchases[i].quantity * purchases[i].price;
    }
    return total;
}

// Function to calculate discount based on total amount
float calculateDiscount(float totalAmount) {
    if (totalAmount > 5000) {
        return totalAmount * 0.10;  // 10% discount
    } else if (totalAmount > 3000) {
        return totalAmount * 0.07;  // 7% discount
    } else {
        return totalAmount * 0.05;  // 5% discount
    }
}

// Main function
int main() {
    int n;
    printf("Enter the number of items purchased: ");
    scanf("%d", &n);

    struct Purchase purchases[n];

    // Taking purchase input
    inputPurchases(purchases, n);

    // Displaying purchase details
    displayPurchases(purchases, n);

    // Calculating total amount
    float totalAmount = calculateTotalAmount(purchases, n);
    printf("\nTotal Amount Before Discount: %.2f\n", totalAmount);

    // Calculating and displaying discount
    float discount = calculateDiscount(totalAmount);
    printf("Discount Applied: %.2f\n", discount);

    // Final amount after discount
    float finalAmount = totalAmount - discount;
    printf("Final Amount After Discount: %.2f\n", finalAmount);

    return 0;
}
