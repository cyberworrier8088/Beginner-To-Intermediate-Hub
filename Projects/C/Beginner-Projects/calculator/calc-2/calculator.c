#include <stdio.h>
#include <stdlib.h>

// Function prototypes
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
void displayMenu();

int main() {
  int choice;
  double num1, num2, result;

  do {
    displayMenu();
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 4) {
      printf("Enter two numbers: ");
      scanf("%lf %lf", &num1, &num2);
    }

    switch (choice) {
    case 1:
      result = add(num1, num2);
      printf("Result: %.2lf\n", result);
      break;
    case 2:
      result = subtract(num1, num2);
      printf("Result: %.2lf\n", result);
      break;
    case 3:
      result = multiply(num1, num2);
      printf("Result: %.2lf\n", result);
      break;
    case 4:
      result = divide(num1, num2);
      printf("Result: %.2lf\n", result);
      break;
    case 5:
      printf("Exiting calculator. Goodbye!\n");
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }

    printf("\n");
  } while (choice != 5);

  return 0;
}

void displayMenu() {
  printf("=== MODULAR CALCULATOR ===\n");
  printf("1. Addition\n");
  printf("2. Subtraction\n");
  printf("3. Multiplication\n");
  printf("4. Division\n");
  printf("5. Exit\n");
}

double add(double a, double b) { return a + b; }

double subtract(double a, double b) { return a - b; }

double multiply(double a, double b) { return a * b; }

double divide(double a, double b) {
  if (b != 0) {
    return a / b;
  } else {
    printf("Error: Division by zero!\n");
    return 0;
  }
}
