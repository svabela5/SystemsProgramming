#include <stdio.h>

int main() {
    // Declare variables
    float num1, num2;
    float sum, average, sum_of_squares;

    // Read input from the user
    printf("Enter the first number: ");
    scanf("%f", &num1);
    printf("Enter the second number: ");
    scanf("%f", &num2);

    // Perform calculations
    sum = num1 + num2;
    average = sum / 2.0;
    sum_of_squares = (num1 * num1) + (num2 * num2);

    // Print the results
    printf("\nResults:\n");
    printf("Sum: %.2f\n", sum);
    printf("Average: %.2f\n", average);
    printf("Sum of Squares: %.2f\n", sum_of_squares);

    return 0;
}