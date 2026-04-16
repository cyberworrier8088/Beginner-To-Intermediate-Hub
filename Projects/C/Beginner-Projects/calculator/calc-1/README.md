# Calculator - Level 1: Basic Operations

## Learning Objectives
- Basic C syntax and structure
- User input with `scanf()`
- Conditional logic with `if-else`
- Mathematical operations
- Error handling for division by zero

## How to Compile and Run

### Step 1: Install a C Compiler
**Windows:**
```bash
# Install MinGW-w64 (recommended)
# Download from: https://www.mingw-w64.org/
# Or use MSYS2: https://www.msys2.org/
```

**Mac:**
```bash
# Install Xcode Command Line Tools
xcode-select --install
```

**Linux:**
```bash
# Install GCC
sudo apt-get install gcc  # Ubuntu/Debian
sudo yum install gcc      # CentOS/RHEL
```

### Step 2: Compile the Program
```bash
# Navigate to this directory
cd Projects/C/Beginner-Projects/calculator/calc-1/

# Compile the program
gcc calculator.c -o calculator

# Run the program
./calculator
```

**Windows users:**
```bash
# After compilation
calculator.exe
```

## What This Program Does
1. **Asks for two numbers** - Gets user input
2. **Asks for an operator** - (+, -, *, /)
3. **Performs the calculation** - Uses if-else logic
4. **Shows the result** - Displays the answer
5. **Handles errors** - Prevents division by zero

## Code Breakdown

```c
#include <stdio.h>  // Input/output library

int main() {
    double num1, num2;  // Variables for numbers
    char operation;     // Variable for operator
    
    // Get user input
    printf("Enter first number: ");
    scanf("%lf", &num1);
    
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operation);  // Note the space before %c
    
    printf("Enter second number: ");
    scanf("%lf", &num2);
    
    // Decision logic
    if (operation == '+') {
        printf("Result: %.2lf\n", num1 + num2);
    }
    // ... other conditions
    
    return 0;  // Success!
}
```

## Key Concepts Learned

### 1. Variables
- `double` - For decimal numbers
- `char` - For single characters

### 2. Input/Output
- `printf()` - Display text to user
- `scanf()` - Get input from user
- `%.2lf` - Format for decimal numbers

### 3. Conditional Logic
- `if-else if-else` - Decision making
- `==` - Comparison operator
- `!=` - Not equal operator

### 4. Error Handling
- Check for division by zero
- Display error messages

## Try These Challenges
1. **Add more operations** - Modulo (%), power (^)
2. **Add input validation** - Check if input is valid
3. **Add a loop** - Keep calculator running
4. **Add memory** - Store previous results

## Common Issues & Solutions

**Problem:** Program closes immediately
**Solution:** Add `getchar();` before `return 0;`

**Problem:** Input not working correctly
**Solution:** Add space before `%c` in scanf: `scanf(" %c", &op);`

**Problem:** Compilation error
**Solution:** Make sure GCC is installed and in PATH

## Next Level
Ready for Level 2? Try the **Modular Calculator** which uses functions and menus!

[Go to Level 2](../calc-2/)
