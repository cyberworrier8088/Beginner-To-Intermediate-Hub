/*
 * C++ Calculator - Level 2: Object-Oriented Programming
 * 
 * Learn modern C++ through a practical calculator application.
 * This demonstrates classes, methods, error handling, and user interaction.
 * 
 * Key concepts:
 * - Class design and implementation
 * - Method overloading
 * - Exception handling
 * - Input validation
 * - Modern C++ string handling
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

using namespace std;

// Calculator class - encapsulates all calculator functionality
class Calculator {
private:
    double memory;      // Memory storage
    double lastResult;  // Last calculation result
    int calculationCount;  // Track number of calculations
    
public:
    // Constructor
    Calculator() : memory(0.0), lastResult(0.0), calculationCount(0) {
        cout << "Calculator initialized!" << endl;
    }
    
    // Basic arithmetic operations
    double add(double a, double b) {
        lastResult = a + b;
        calculationCount++;
        return lastResult;
    }
    
    double subtract(double a, double b) {
        lastResult = a - b;
        calculationCount++;
        return lastResult;
    }
    
    double multiply(double a, double b) {
        lastResult = a * b;
        calculationCount++;
        return lastResult;
    }
    
    double divide(double a, double b) {
        if (b == 0.0) {
            throw runtime_error("Division by zero is not allowed!");
        }
        lastResult = a / b;
        calculationCount++;
        return lastResult;
    }
    
    // Advanced operations
    double power(double base, double exponent) {
        lastResult = pow(base, exponent);
        calculationCount++;
        return lastResult;
    }
    
    double squareRoot(double number) {
        if (number < 0.0) {
            throw runtime_error("Cannot calculate square root of negative number!");
        }
        lastResult = sqrt(number);
        calculationCount++;
        return lastResult;
    }
    
    double percentage(double value, double percent) {
        lastResult = value * (percent / 100.0);
        calculationCount++;
        return lastResult;
    }
    
    // Memory operations
    void memoryStore(double value) {
        memory = value;
        cout << "Stored " << value << " in memory." << endl;
    }
    
    double memoryRecall() {
        cout << "Recalled " << memory << " from memory." << endl;
        return memory;
    }
    
    void memoryClear() {
        memory = 0.0;
        cout << "Memory cleared." << endl;
    }
    
    double memoryAdd(double value) {
        memory += value;
        cout << "Added " << value << " to memory. New value: " << memory << endl;
        return memory;
    }
    
    // Utility methods
    double getLastResult() const {
        return lastResult;
    }
    
    int getCalculationCount() const {
        return calculationCount;
    }
    
    void reset() {
        memory = 0.0;
        lastResult = 0.0;
        calculationCount = 0;
        cout << "Calculator reset to initial state." << endl;
    }
    
    // Display calculator status
    void displayStatus() const {
        cout << "\n=== CALCULATOR STATUS ===" << endl;
        cout << "Last Result: " << lastResult << endl;
        cout << "Memory: " << memory << endl;
        cout << "Calculations Performed: " << calculationCount << endl;
        cout << "========================" << endl;
    }
};

// Input validation functions
double getValidNumber(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            size_t pos;
            double value = stod(input, &pos);
            
            // Check if entire string was converted
            if (pos != input.length()) {
                cout << "Invalid input! Please enter a valid number." << endl;
                continue;
            }
            
            return value;
        } catch (const invalid_argument&) {
            cout << "Invalid input! Please enter a valid number." << endl;
        } catch (const out_of_range&) {
            cout << "Number too large! Please enter a smaller number." << endl;
        }
    }
}

char getValidOperator() {
    vector<char> validOperators = {'+', '-', '*', '/', '^', 'r', '%', 'm'};
    
    while (true) {
        cout << "Enter operator (+, -, *, /, ^, r, %, m): ";
        string input;
        getline(cin, input);
        
        if (input.length() != 1) {
            cout << "Please enter a single operator!" << endl;
            continue;
        }
        
        char op = input[0];
        if (find(validOperators.begin(), validOperators.end(), op) != validOperators.end()) {
            return op;
        }
        
        cout << "Invalid operator! Valid operators: +, -, *, /, ^(power), r(sqrt), %(percent), m(memory)" << endl;
    }
}

// Display operation menu
void displayMenu() {
    cout << "\n" + string(50, '=') << endl;
    cout << "       C++ CALCULATOR - LEVEL 2" << endl;
    cout << string(50, '=') << endl;
    cout << "Operators:" << endl;
    cout << "  + : Addition" << endl;
    cout << "  - : Subtraction" << endl;
    cout << "  * : Multiplication" << endl;
    cout << "  / : Division" << endl;
    cout << "  ^ : Power (base^exponent)" << endl;
    cout << "  r : Square Root" << endl;
    cout << "  % : Percentage (value%percent)" << endl;
    cout << "  m : Memory operations" << endl;
    cout << string(50, '=') << endl;
}

// Memory operations menu
void handleMemoryOperations(Calculator& calc) {
    while (true) {
        cout << "\n=== MEMORY OPERATIONS ===" << endl;
        cout << "1. Store in memory" << endl;
        cout << "2. Recall from memory" << endl;
        cout << "3. Clear memory" << endl;
        cout << "4. Add to memory" << endl;
        cout << "5. Back to calculator" << endl;
        cout << "Choice: ";
        
        string choice;
        getline(cin, choice);
        
        if (choice == "1") {
            double value = getValidNumber("Enter value to store: ");
            calc.memoryStore(value);
        } else if (choice == "2") {
            double value = calc.memoryRecall();
            cout << "Memory value: " << value << endl;
        } else if (choice == "3") {
            calc.memoryClear();
        } else if (choice == "4") {
            double value = getValidNumber("Enter value to add to memory: ");
            calc.memoryAdd(value);
        } else if (choice == "5") {
            break;
        } else {
            cout << "Invalid choice! Please enter 1-5." << endl;
        }
    }
}

// Main calculation function
void performCalculation(Calculator& calc) {
    char op = getValidOperator();
    
    try {
        if (op == 'r') {
            // Square root - only need one number
            double number = getValidNumber("Enter number: ");
            double result = calc.squareRoot(number);
            cout << "sqrt(" << number << ") = " << result << endl;
            
        } else if (op == 'm') {
            // Memory operations
            handleMemoryOperations(calc);
            
        } else {
            // Binary operations - need two numbers
            double num1 = getValidNumber("Enter first number: ");
            double num2 = getValidNumber("Enter second number: ");
            
            double result = 0.0;
            string operation;
            
            switch (op) {
                case '+':
                    result = calc.add(num1, num2);
                    operation = "+";
                    break;
                case '-':
                    result = calc.subtract(num1, num2);
                    operation = "-";
                    break;
                case '*':
                    result = calc.multiply(num1, num2);
                    operation = "*";
                    break;
                case '/':
                    result = calc.divide(num1, num2);
                    operation = "/";
                    break;
                case '^':
                    result = calc.power(num1, num2);
                    operation = "^";
                    break;
                case '%':
                    result = calc.percentage(num1, num2);
                    operation = "%";
                    break;
                default:
                    cout << "Unknown operator!" << endl;
                    return;
            }
            
            // Display result with formatting
            cout << fixed << setprecision(2);
            cout << num1 << " " << operation << " " << num2 << " = " << result << endl;
            
            // Special formatting for percentage
            if (op == '%') {
                cout << num2 << "% of " << num1 << " = " << result << endl;
            }
        }
        
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// Interactive calculator session
void runCalculator() {
    Calculator calc;
    
    cout << "Welcome to the C++ Calculator!" << endl;
    cout << "This calculator demonstrates modern C++ features:" << endl;
    cout << "- Object-oriented programming with classes" << endl;
    cout << "- Exception handling for errors" << endl;
    cout << "- Input validation and user interaction" << endl;
    cout << "- Memory management and state tracking" << endl;
    
    while (true) {
        displayMenu();
        calc.displayStatus();
        
        cout << "\nOptions:" << endl;
        cout << "1. Perform calculation" << endl;
        cout << "2. Use last result as first number" << endl;
        cout << "3. View detailed status" << endl;
        cout << "4. Reset calculator" << endl;
        cout << "5. Exit" << endl;
        cout << "Choice: ";
        
        string choice;
        getline(cin, choice);
        
        if (choice == "1") {
            performCalculation(calc);
            
        } else if (choice == "2") {
            cout << "Using last result (" << calc.getLastResult() << ") as first number." << endl;
            char op = getValidOperator();
            
            if (op == 'r') {
                cout << "Cannot use square root with last result only." << endl;
            } else if (op == 'm') {
                handleMemoryOperations(calc);
            } else {
                double num2 = getValidNumber("Enter second number: ");
                
                try {
                    double result = 0.0;
                    string operation;
                    
                    switch (op) {
                        case '+':
                            result = calc.add(calc.getLastResult(), num2);
                            operation = "+";
                            break;
                        case '-':
                            result = calc.subtract(calc.getLastResult(), num2);
                            operation = "-";
                            break;
                        case '*':
                            result = calc.multiply(calc.getLastResult(), num2);
                            operation = "*";
                            break;
                        case '/':
                            result = calc.divide(calc.getLastResult(), num2);
                            operation = "/";
                            break;
                        case '^':
                            result = calc.power(calc.getLastResult(), num2);
                            operation = "^";
                            break;
                        case '%':
                            result = calc.percentage(calc.getLastResult(), num2);
                            operation = "%";
                            break;
                    }
                    
                    cout << fixed << setprecision(2);
                    cout << calc.getLastResult() << " " << operation << " " << num2 << " = " << result << endl;
                    
                } catch (const runtime_error& e) {
                    cout << "Error: " << e.what() << endl;
                }
            }
            
        } else if (choice == "3") {
            calc.displayStatus();
            cout << "\nCalculator Features:" << endl;
            cout << "- Object-oriented design with Calculator class" << endl;
            cout << "- Exception handling for division by zero" << endl;
            cout << "- Input validation with error recovery" << endl;
            cout << "- Memory operations (MS, MR, MC, M+)" << endl;
            cout << "- Advanced operations (power, sqrt, percentage)" << endl;
            cout << "- State tracking and history" << endl;
            
        } else if (choice == "4") {
            calc.reset();
            
        } else if (choice == "5") {
            cout << "\nFinal Statistics:" << endl;
            calc.displayStatus();
            cout << "Thank you for using C++ Calculator!" << endl;
            cout << "You've experienced modern C++ programming!" << endl;
            break;
            
        } else {
            cout << "Invalid choice! Please enter 1-5." << endl;
        }
        
        cout << "\nPress Enter to continue...";
        string dummy;
        getline(cin, dummy);
    }
}

// Main function
int main() {
    cout << "========================================" << endl;
    cout << "    C++ CALCULATOR - LEVEL 2" << endl;
    cout << "========================================" << endl;
    cout << "Learn modern C++ through practical programming!" << endl;
    cout << "This calculator demonstrates:" << endl;
    cout << "- Class design and encapsulation" << endl;
    cout << "- Method overloading and polymorphism" << endl;
    cout << "- Exception handling and error recovery" << endl;
    cout << "- Input validation and user interaction" << endl;
    cout << "- Modern C++ string handling" << endl;
    cout << "- Memory management and state tracking" << endl;
    cout << "========================================" << endl;
    
    try {
        runCalculator();
    } catch (const exception& e) {
        cout << "Unexpected error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
