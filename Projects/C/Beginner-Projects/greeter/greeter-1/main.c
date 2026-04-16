/* 👋 The Advanced Greeter - C Programming Level 1 */
/* Welcome to C! This is a "compiled" language. */
/* Unlike Python, you cannot just type 'python main.c' to run it. */
/* You must compile this raw text into a binary .exe file first. */

#include <stdio.h> // Standard Input/Output. This gives us printf() and scanf()

// In C, every program MUST start inside a function named 'main'.
int main() {
    // 1. We must declare our variables and their exact 'Types' before we use them!
    // A 'char' array holds text. We give it [50] spaces of memory for a long name.
    char name[50]; 
    // An 'int' holds whole numbers.
    int age;
    int current_year = 2024;
    int birth_year;

    printf("========================================\n");
    printf("        👋 THE ADVANCED GREETER       \n");
    printf("========================================\n");

    // 2. Ask for the user's name
    // \n means "New Line"
    printf("Enter your first name: ");
    
    // scanf reads keyboard input!
    // %49s means "Read a string, but stop at 49 characters to prevent memory hacking!"
    scanf("%49s", name);

    // 3. Ask for their age
    printf("Hello there, %s! How old are you? ", name);
    
    // %d means "Read a decimal integer".
    // Notice the '&' before age? That's a POINTER! 
    // We are telling scanf the exact RAM memory address where the 'age' variable lives.
    scanf("%d", &age);

    // 4. Basic Math
    birth_year = current_year - age;

    // 5. Output
    printf("\n--- RESULTS ---\n");
    printf("Ah, so you are %s.\n", name);
    printf("If you are %d years old in %d, you must have been born around %d!\n", age, current_year, birth_year);
    printf("========================================\n");
    
    printf("Welcome to the power of C Programming!\n");

    // 6. Return 0 tells the operating system "The program finished without crashing."
    return 0;
}
