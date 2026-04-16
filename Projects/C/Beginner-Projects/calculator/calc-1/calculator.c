/* 🧮 Simple Calculator - C Level 1: Basic Math & Logic */
/* In Level 1, we write a simple "input-output" script. */
/* No loops, no functions. Just straight-line logic. */

#include <stdio.h>

int main() {
    double num1, num2;
    char operation;

    printf("=== 🧮 SIMPLE C CALCULATOR ===\n");
    
    // 1. Ask for the first number
    printf("Enter first number: ");
    scanf("%lf", &num1);

    // 2. Ask for the symbol (+, -, *, /)
    // The space before %c is IMPORTANT. It tells C to skip any leftovers in the keyboard.
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operation);

    // 3. Ask for the second number
    printf("Enter second number: ");
    scanf("%lf", &num2);

    // 4. Decision Logic
    if (operation == '+') {
        printf("Result: %.2lf\n", num1 + num2);
    } 
    else if (operation == '-') {
        printf("Result: %.2lf\n", num1 - num2);
    } 
    else if (operation == '*') {
        printf("Result: %.2lf\n", num1 * num2);
    } 
    else if (operation == '/') {
        // Safety check for dividing by zero
        if (num2 != 0) {
            printf("Result: %.2lf\n", num1 / num2);
        } else {
            printf("❌ Error: Div by 0!\n");
        }
    } 
    else {
        printf("⚠️ Unknown symbol!\n");
    }

    return 0;
}
