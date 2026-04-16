# C++ Calculator - Level 1

## Overview
A modern C++ calculator demonstrating object-oriented programming, error handling, and user interaction.

## Features
- **Basic Operations**: Addition, subtraction, multiplication, division
- **Advanced Operations**: Power, square root, percentage
- **Memory Operations**: Store, recall, clear, add to memory
- **Error Handling**: Division by zero protection, input validation
- **Interactive Menu**: User-friendly command-line interface

## Learning Objectives
- Modern C++ syntax (auto keyword, smart pointers, lambda expressions)
- Class design and implementation
- Method overloading and encapsulation
- Exception handling and error recovery
- Input validation and user interaction
- Modern C++ string handling

## Prerequisites
- C++ compiler (g++, clang++, or MSVC)
- Basic understanding of C++ syntax

## Compilation & Running

### Linux/macOS
```bash
# Compile
g++ -std=c++17 -o calculator calculator.cpp

# Run
./calculator
```

### Windows (with g++)
```bash
# Compile
g++ -std=c++17 -o calculator.exe calculator.cpp

# Run
calculator.exe
```

### Windows (Visual Studio)
1. Open Visual Studio
2. Create new C++ project
3. Copy calculator.cpp to main.cpp
4. Build and run

## Usage
1. Run the program
2. Follow the on-screen menu
3. Choose operations:
   - `1` - Perform calculation
   - `2` - Use last result as first number
   - `3` - View detailed status
   - `4` - Reset calculator
   - `5` - Exit

## Supported Operations
- `+` : Addition
- `-` : Subtraction  
- `*` : Multiplication
- `/` : Division
- `^` : Power (base^exponent)
- `r` : Square root
- `%` : Percentage (value%percent)
- `m` : Memory operations

## Example Session
```
=== C++ CALCULATOR - LEVEL 2 ===
Learn modern C++ through practical programming!

1. Perform calculation
2. Use last result as first number
3. View detailed status
4. Reset calculator
5. Exit

Choice: 1
Enter operation (+, -, *, /, ^, r, %, m): +
Enter first number: 10
Enter second number: 5
10 + 5 = 15

Choice: 2
Using last result: 15
Enter operation: *
Enter second number: 2
15 * 2 = 30
```

## Code Structure
```cpp
class Calculator {
private:
    double memory;
    double lastResult;
    int calculationCount;
    
public:
    // Arithmetic operations
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    
    // Advanced operations
    double power(double base, double exponent);
    double squareRoot(double number);
    double percentage(double value, double percent);
    
    // Memory operations
    void memoryStore(double value);
    double memoryRecall();
    void memoryClear();
    double memoryAdd(double value);
};
```

## Key Concepts Demonstrated
1. **Class Design**: Encapsulation of calculator functionality
2. **Method Overloading**: Multiple ways to perform operations
3. **Exception Handling**: Safe division and error recovery
4. **Input Validation**: Robust user input processing
5. **State Management**: Tracking calculation history and memory

## Troubleshooting

### Compilation Errors
- **"cout was not declared"**: Add `#include <iostream>`
- **"string was not declared"**: Add `#include <string>`
- **"auto not allowed"**: Use `g++ -std=c++17` or newer

### Runtime Errors
- **Division by zero**: Handled with exception - you'll see error message
- **Invalid input**: Program will prompt you to try again

### Platform-Specific Issues
- **Windows**: Use `g++` from MinGW-w64 or Visual Studio
- **macOS**: Install Xcode Command Line Tools
- **Linux**: Install `build-essential` package

## Extensions
Try these challenges to improve the program:
1. Add trigonometric functions (sin, cos, tan)
2. Implement a calculation history
3. Add support for variables
4. Create a GUI version using Qt or other framework
5. Add unit tests using a testing framework

## Next Steps
After mastering this calculator, try:
- Level 2: Enhanced Calculator (history, variables, scientific functions)
- Text Adventure Game (game development, state management)
- Data Structures (templates, algorithms, performance)

## About This Project
This calculator demonstrates modern C++ features while being accessible to beginners. The code is written with human-like comments and focuses on teaching concepts through practical implementation.

Happy coding!
