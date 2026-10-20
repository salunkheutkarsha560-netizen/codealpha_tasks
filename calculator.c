
#include <stdio.h>

int main(void) {
    float num1, num2, result;
    int choice;

    printf("===== Simple Calculator =====\n");

    printf("Enter first number: ");
    if (scanf("%f", &num1) != 1) 
    {
        printf("Error: Please enter a valid number.\n");
        return 1;
    }

    printf("Enter second number: ");
    if (scanf("%f", &num2) != 1)
    {
        printf("Error: Please enter a valid number.\n");
        return 1;
    }

    printf("\nChoose an operation:\n");
    printf("1. Addition (+)\n");
    printf("2. Subtraction (-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("Enter your choice (1-4): ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Error: Please enter a valid choice.\n");
        return 1;
    }

    switch (choice) 
    {
        case 1:
            result = num1 + num2;
            printf("Result: %.2f\n", result);
            break;

        case 2:
            result = num1 - num2;
            printf("Result: %.2f\n", result);
            break;

        case 3:
            result = num1 * num2;
            printf("Result: %.2f\n", result);
            break;

        case 4:
            if (num2 == 0.0f) 
            {
                printf("Error: Division by zero is not allowed.\n");
            } else 
            {
                result = num1 / num2;
                printf("Result: %.2f\n", result);
            }
            break;

        default:
            printf("Error: Invalid choice. Select an option from 1 to 4.\n");
    }

    return 0;
}
